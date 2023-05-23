#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <gelf.h>
#include <stdint.h>
#include <inttypes.h>

int main(int argc, char **argv)
{
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <elf_executable>\n", argv[0]);
    return 1;
  }

  Elf *exec_handle;
  Elf_Scn *section = NULL;
  GElf_Shdr section_header;
  Elf_Data *data;
  GElf_Sym symbol;
  int32_t fd;
  int32_t count;
  uint64_t iterator_print = 0;

  elf_version(EV_CURRENT);

  if ((fd = open(argv[1], O_RDONLY, 0)) < 0) {
    perror("open");
    return 1;
  }

  if ((exec_handle = elf_begin(fd, ELF_C_READ, NULL)) == NULL) {
    perror("elf_begin");
    return 1;
  }

  while ((section = elf_nextscn(exec_handle, section)) != NULL) {
    if (gelf_getshdr(section, &section_header) != &section_header)
      continue;

    if (section_header.sh_type == SHT_SYMTAB) {
      break;
    }
  }

  if (section == NULL) {
    fprintf(stderr, "No symbol table found.\n");
    elf_end(exec_handle);
    close(fd);
    return 0;
  }

  data = elf_getdata(section, NULL);
  count = section_header.sh_entsize != 0 ? section_header.sh_size / section_header.sh_entsize : 0;

  for (int ii = 0; ii < count; ++ii) {
    if (gelf_getsym(data, ii, &symbol) != &symbol) {
      fprintf(stderr, "gelf_getsym() failed: %s\n", elf_errmsg(-1));
      continue;
    }

    printf("%" PRIu64 ": ", iterator_print++);
    printf("0x%.8" PRIx64, symbol.st_value);
    printf(" 0x%.8" PRIx64, symbol.st_size);

    switch (GELF_ST_BIND(symbol.st_info)) {
    case STB_LOCAL:
      printf(" LOCL");
      break;
    case STB_GLOBAL:
      printf(" GLOB");
      break;
    case STB_WEAK:
      printf(" WEAK");
      break;
    case STB_NUM:
      printf("  NUM");
      break;

    default:
      break;
    }

    switch (GELF_ST_TYPE(symbol.st_info)) {
    case STT_OBJECT:
      printf(" OBJT");
      break;
    case STT_FILE:
      printf(" FILE");
      break;
    case STT_FUNC:
      printf(" FUNC");
      break;
    case STT_SECTION:
      printf(" SECT");
      break;
    case STT_NOTYPE:
      printf(" NTYP");
      break;

    default:
      break;
    }

    printf(" %s", elf_strptr(exec_handle, section_header.sh_link, symbol.st_name));
    printf("\n");
  }
  elf_end(exec_handle);
  close(fd);

  return 0;
}

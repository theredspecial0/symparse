# symparse

symparse is a command-line utility for parsing and displaying symbol tables from ELF files. It can be used to display information about the symbols in an ELF binary, including their addresses, sizes, and types.

## Usage

To use symparse, simply run the `symparse` executable followed by the path to the ELF binary you wish to parse. For example:

```
$ symparse $(which symparse) | tail -n 5    # Last 5 symbols shown for brevity

78: 0x00000000 0x00000000 WEAK NTYP _Jv_RegisterClasses
79: 0x006020b0 0x00000000 GLOB OBJT __TMC_END__
80: 0x00000000 0x00000000 WEAK NTYP _ITM_registerTMCloneTable
81: 0x00400878 0x00000000 GLOB FUNC _init
82: 0x006020c0 0x00000008 GLOB OBJT stderr@@GLIBC_2.2.5
```

> This displays information about the symbols in the symparse binary itself.

## Installation

To install symparse, simply clone the repository and run `make install`:

```
$ git clone https://github.com/theredspecial0/symparse
$ cd symparse
$ make install
```

This will install the `symparse` executable to `/usr/local/bin`. You may need to run `sudo make install` if you do not have write access to this directory.

To uninstall symparse, simply run `sudo make uninstall`:

```
$ cd symparse
$ sudo make uninstall
```

## License

This project is licensed under the MIT License. See the `LICENSE` file for detail
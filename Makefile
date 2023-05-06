CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
LDFLAGS = -lelf
DEBUGFLAGS = -g
SRC = main.c
OBJ = $(SRC:.c=.o)
TARGET = symparse
INSTALL_DIR = /usr/local/bin

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(if $(DEBUG), $(DEBUGFLAGS)) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

install: $(TARGET)
	@if [ -w $(INSTALL_DIR) ]; then \
		cp $(TARGET) $(INSTALL_DIR)/$(TARGET); \
	else \
		echo "\033[1;31mError:\033[0m You don't have write access to $(INSTALL_DIR).\nPlease run '\033[1msudo make install\033[0m' instead."; \
	fi

uninstall:
	@if [ "$$(id -u)" != 0 ]; then \
		echo "\033[1;31mError:\033[0m You don't have write access to $(INSTALL_DIR).\nPlease run '\033[1msudo make uninstall\033[0m' instead."; \
	else \
		sudo rm $(INSTALL_DIR)/$(TARGET); \
		echo "The $(TARGET) binary has been uninstalled from $(INSTALL_DIR)."; \
	fi

clean:
	rm -f $(OBJ) $(TARGET)

debug:
	$(MAKE) all DEBUG=1

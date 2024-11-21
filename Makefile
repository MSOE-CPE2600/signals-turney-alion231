# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Source files
SRC = signal_sigaction.c recv_signal.c recv_signal_tennis.c send_signal.c send_signal_tennis.c signal_alarm.c signal_handler.c signal_segfault.c

# Object files (derived from SRC)
OBJ = $(SRC:.c=.o)

# Executables
EXEC = signal_sigaction recv_signal recv_signal_tennis send_signal send_signal_tennis signal_alarm signal_handler signal_segfault

# Default target
all: $(EXEC)

# Pattern rule to build each executable
%: %.c
	$(CC) $(CFLAGS) $< -o $@

# Clean target to remove compiled files
clean:
	rm -f $(EXEC) $(OBJ)

# Phony targets
.PHONY: all clean
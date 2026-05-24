# Kompilator
CC = gcc

# Flagi kompilacji
CFLAGS = -Wall -Wextra -Iinclude

# Pliki zrodlowe
SRC = src/main.c

# Plik wynikowy
EXEC = sokoban.exe

# Glowna regula
all: $(EXEC)

# Regula budowania
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)
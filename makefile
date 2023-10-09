CC = gcc
CFLAGS = -std=c17 -Wall -fmax-errors=10 -Wextra
LFLAGS = 
LIBS = 
OBJFILES = unjumble.o read_cli.o
MAIN = unjumble



all: $(MAIN)

$(MAIN): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJFILES)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJFILES) $(MAIN)
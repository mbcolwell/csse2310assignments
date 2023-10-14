CC = gcc
CFLAGS = -std=c17 -Wall -fmax-errors=10 -Wextra
LFLAGS = 
LIBS = 
OBJFILES = unjumble.o read_cli.o read_dict.o matching.o sort.o
MAIN = unjumble



all: $(MAIN)

$(MAIN): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJFILES)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJFILES) $(MAIN) valgrind-out.txt

valgrind:
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./$(MAIN) -include c abde sample_dict
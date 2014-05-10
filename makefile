CC = g++
CFLAGS = -I.
DEPS = redblacktree.h 
OBJ = redblacktree.o main.o

all: redblacktree

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

redblacktree: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean
clean:
	rm -f $(OBJ)



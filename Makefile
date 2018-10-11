# compilateur
CC := gcc
# options de compilation
CFLAGS := -std=c99 -Wall -Wextra -pedantic -ggdb

# règle de compilation --- exécutables
all : main

SRC := src/
OBJF := obj/
OBJS := $(OBJF)main.o $(OBJF)noeud.o $(OBJF)liste_nd.o $(OBJF)utils.o $(OBJF)huffman.o

main : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^	

$(OBJF)%.o: $(SRC)%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -o $@ -c $<  -lm

# options de compilation
clean:
	rm -r obj main
	
run:
	valgrind ./main

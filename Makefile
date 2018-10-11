# compilateur
CC := gcc
# options de compilation
CFLAGS := -std=c99 -Wall -Wextra -pedantic -ggdb

# règle de compilation --- exécutables
all : main

OBJS := obj/main.o obj/noeud.o obj/liste_nd.o obj/utils.o obj/huffman.o

main : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^	

obj/%.o: %.c
	mkdir -p obj
	$(CC) $(CFLAGS) -o $@ -c $<  -lm

# options de compilation
clean:
	rm -r obj main
	
run:
	valgrind ./main

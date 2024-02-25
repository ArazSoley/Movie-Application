CC=g++
CFLAGS=-ansi -Wall -pedantic-errors -O0

all: twophase

twophase: bst.h movie.h trie.h  user.h user_interface.h user_interface.cpp  main_user_interface.cpp 
	$(CC) $(CFLAGS) user_interface.cpp main_user_interface.cpp -o twophase



clean:
	rm twophase

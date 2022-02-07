NAME = program4
CC = gcc
all: $(NAME).out

$(NAME).out: $(NAME).o
	$(CC) $(NAME).o -o $(NAME).out

$(NAME).o: $(NAME).c 
	$(CC) -c $(NAME).c

clean:
	rm *.o *.out

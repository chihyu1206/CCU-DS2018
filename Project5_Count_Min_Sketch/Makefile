NAME = program5
CC = g++
all: $(NAME).out

$(NAME).out: $(NAME).o
	$(CC) $(NAME).o -o $(NAME).out

$(NAME).o: $(NAME).cpp 
	$(CC) -c $(NAME).cpp

clean:
	rm *.o *.out

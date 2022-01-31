OBJ := program1.o
SRC := $(OBJ:.o=.c)
TARGET := $(OBJ:.o=.out)
all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $^ -lm -o $(TARGET)
$(OBJ): $(SRC)
	gcc -c $<
clean:
	rm *.o *.out

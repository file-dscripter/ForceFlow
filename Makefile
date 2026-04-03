CC= g++
CFLAGS= -std=c++17 -Wall -Wextra

SRC= *.cpp
OUT=FrictionSim

all: build 

build:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS)

clean:
	rm $(OUT)

run:
	clear && ./$(OUT)
	

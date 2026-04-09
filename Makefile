CC = c++
CFLAGS = -std=c++17 -Wall -Wextra $(shell pkg-config --cflags sdl3)
LDFLAGS = $(shell pkg-config --libs sdl3)

SRC = $(wildcard *.cpp)
OUT = ForceFlowFrictionSim

all: build

build:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OUT)

run:
	clear && ./$(OUT)
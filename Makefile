CC = c++
CFLAGS = -std=c++17 -Wall -Wextra $(pkgconfig --include SDL3)
LDFLAGS = -lSDL3

SRC = *.cpp
OUT = ForceFlowFrictionSim

all: build

build:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OUT)

run:
	clear && ./$(OUT)
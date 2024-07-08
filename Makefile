# Compiler options
CC = gcc
LD = gcc
CFLAGS = -std=gnu2x -Ofast -flto -march=native -Wall -Wno-missing-braces -I.
LDFLAGS = -flto -fopenmp -lm -lglfw -lGLU -lGL

# Output binary
OUT = engine
OUT_OBJ = $(patsubst %,./%.o,$(OUT))

# Installed binaries
# INSTDIR = /usr/bin/
# INST = $(patsubst %,$(INSTDIR)%,$(OUT))

# Source and Object files
SRC = $(shell find . -name "*.c")
OBJ = $(filter-out $(OUT_OBJ),$(SRC:.c=.o))

# Rules
.PHONY = all clean run # install uninstall

all: $(OUT)

#install: $(INST)

#uninstall:
#	rm -f $(INST)

clean:
	rm -f $(OBJ) $(OUT_OBJ)

run: $(OUT)
	./$(word 1, $(OUT))

$(OUT): %: $(OBJ) %.o
	$(LD) $^ $(LDFLAGS) -o $@

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(INST): $(INSTDIR)%: %
	cp $^ $@


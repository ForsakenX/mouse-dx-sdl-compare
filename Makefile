DEBUG=0
CC=gcc
FLAGS=-pipe
CFLAGS=$(FLAGS)
LDFLAGS=$(FLAGS)

ifeq ($(DEBUG),1)
	FLAGS+= -g -fstack-protector-all
	CFLAGS+=-Wall -Wextra -D_FORTIFY_SOURCE=2
else
	CFLAGS+=-O2
	LDFLAGS+=-s
endif

LIBS = $(shell sdl-config --libs)
CFLAGS += -I. $(shell sdl-config --cflags)

INCLUDE=$(wildcard *.h) 
SRC=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRC))

BIN=bin

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $(BIN) $(OBJS) $(LDFLAGS) $(LIBS)

$(OBJS): $(wildcard *.h)

clean:
	$(RM) $(OBJS) $(BIN)

.PHONY: all clean

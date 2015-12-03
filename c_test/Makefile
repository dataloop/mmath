UNAME_SYS := $(shell uname -s)
ifeq ($(UNAME_SYS), Darwin)
    CC ?= cc
    CFLAGS ?= -arch x86_64
	LDFLAGS ?= -flat_namespace -undefined suppress
else ifeq ($(UNAME_SYS), Linux)
    CC ?= gcc
endif
CFLAGS += -std=c99 -Wall -I../c_src
LDFLAGS += -shared

# TODO: fix building tested sources if ti somes to that, maybe separate nif stuff and dec lib

TESTED_SOURCES = ../c_src/dec_math.c ../c_src/dec_conv.c
SOURCES = $(shell find . -type f \( -name "*.c" \)) $(TESTED_SOURCES)
OBJECTS = $(addsuffix .o, $(basename $(SOURCES)))

run_all_tests: all_tests
	./all_tests

all_tests: $(OBJECTS)
	$(CC) $(OBJECTS) -o all_tests

clean:
	rm $(OBJECTS) ./all_tests

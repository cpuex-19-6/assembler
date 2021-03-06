CC = gcc
CFLAGS = -Wall -MMD -MP
LDFLAGS = -lm
TARGET = asm
SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)
DEPS = $(SRCS:%.c=%.d)

all: $(TARGET)

-include $(DEPS)

$(TARGET): $(OBJS)
	$(CC) -g -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< 

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

.PHONY: clean
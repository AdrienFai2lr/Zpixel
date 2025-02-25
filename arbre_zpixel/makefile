CC = gcc
CFLAGS = -Wall -Wextra -g -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -lglib-2.0
LDFLAGS = $(shell pkg-config --cflags --libs glib-2.0)

ARBORE_REP = .
ZPIXEL_REP = ../z_pixel
STACK_REP = ../stack
DEGRADATION_REP = ../degradation

ARBORE_SRCS = $(ARBORE_REP)/arbre.c $(ZPIXEL_REP)/zpixel.c main.c
ARBORE_OBJS = $(ARBORE_SRCS:%.c=%.o)

DEGRADATION_SRCS = $(wildcard $(DEGRADATION_REP)/*.c)
DEGRADATION_OBJS = $(DEGRADATION_SRCS:%.c=%.o)

STACK_SRCS = $(STACK_REP)/stack2_x86_64.c
STACK_OBJS = $(STACK_SRCS:%.c=%.o)

TEST_STACK_OBJ = teststack2.o

prog: $(ARBORE_OBJS) $(DEGRADATION_OBJS) $(STACK_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) -lm

teststack2: $(ARBORE_OBJS) $(STACK_OBJS) $(TEST_STACK_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) -lm

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f prog teststack2 $(ARBORE_OBJS) $(DEGRADATION_OBJS) $(STACK_OBJS) $(TEST_STACK_OBJ)

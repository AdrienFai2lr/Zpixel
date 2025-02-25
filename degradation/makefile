CC = gcc
CFLAGS = -Wall -Wextra -g -I../stack -I../z_pixel
LDFLAGS = $(shell pkg-config --cflags --libs glib-2.0)

DEGRADATION_REP = .
DEGRADATION_SRCS = $(DEGRADATION_REP)/degradation.c
DEGRADATION_OBJS = $(DEGRADATION_SRCS:%.c=%.o)
DEGRADATION_LIB = lib_degradation.a

all: $(DEGRADATION_LIB)

$(DEGRADATION_LIB): $(DEGRADATION_OBJS)
	ar rcs $@ $^

$(DEGRADATION_REP)/%.o: $(DEGRADATION_REP)/%.c
	$(CC) -c $(CFLAGS) $(LDFLAGS) $< -o $@

# Ajoutez la dépendance sur GLib
$(DEGRADATION_OBJS): $(DEGRADATION_REP)/%.o: $(DEGRADATION_REP)/%.c
	$(CC) -c $(CFLAGS) $(LDFLAGS) $< -o $@

clean:
	rm -f $(DEGRADATION_LIB) $(DEGRADATION_OBJS)

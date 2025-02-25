CC = gcc
CCFLAGS = -W -Wall -g
LIBS = `pkg-config --cflags --libs glib-2.0`

# Répertoires
ZPIXEL_REP = z_pixel
ARBRE_PIXEL_REP = arbre_zpixel
STACK_REP = stack

# Fichiers sources et objets pour chaque module
ZPIXEL_SRCS = $(ZPIXEL_REP)/zpixel.c $(ZPIXEL_REP)/main.c
ZPIXEL_OBJS = $(ZPIXEL_REP)/zpixel.o $(ZPIXEL_REP)/main.o

ARBRE_PIXEL_SRCS = $(ARBRE_PIXEL_REP)/arbre.c $(ARBRE_PIXEL_REP)/main.c
ARBRE_PIXEL_OBJS = $(ARBRE_PIXEL_REP)/arbre.o $(ARBRE_PIXEL_REP)/main.o

STACK_OBJS = $(STACK_REP)/stack2_x86_64.o

# Programme final
prog: $(ZPIXEL_OBJS) $(ARBRE_PIXEL_OBJS) $(STACK_OBJS)
	$(CC) $(ZPIXEL_OBJS) $(ARBRE_PIXEL_OBJS) $(STACK_OBJS) -o prog -lm $(LIBS)

# Règles pour les fichiers objets de zpixel
$(ZPIXEL_OBJS): $(ZPIXEL_SRCS)
	$(CC) -c $(CCFLAGS) $^ -o $@

# Règles pour les fichiers objets de arbre_pixel
$(ARBRE_PIXEL_OBJS): $(ARBRE_PIXEL_SRCS)
	$(CC) -c $(CCFLAGS) $^ -o $@

clean:
	rm -f prog $(ZPIXEL_OBJS) $(ARBRE_PIXEL_OBJS) $(STACK_OBJS)


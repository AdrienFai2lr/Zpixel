#ifndef DEGRADATION_H
#define DEGRADATION_H
#include "../stack/stack2.h"
#include "../z_pixel/zpixel.h"
#include <glib.h>

typedef struct {
    void (*evaluate)(GNode *node, my_stack_t *stack);
} CritereEval;

void calculerCouleur_DegradationZPixelTaille(GNode* node, my_stack_t* pile);
void calculerCouleur_DegradationZPixelLuminosite(GNode* node, my_stack_t* pile);
void calculerCouleur_DegradationZPixelDistance(GNode *node, my_stack_t *pile);

#endif

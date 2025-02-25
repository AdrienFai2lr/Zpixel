#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "degradation.h"
#include "../z_pixel/zpixel.h"
#include "../stack/stack2.h"
#include <glib.h>


//evalue la taille des zpixel les plus grand et les mets en priorite dans la pile
void calculerCouleur_DegradationZPixelTaille(GNode* node, my_stack_t* pile) {
    if (node != NULL && node->data != NULL && pile != NULL) {
        // Poussez les zpixels des fils dans la pile
        for (int i = 0; i < 4; i++) {
            GNode* child = g_node_nth_child(node, i);
            if (child != NULL) {
                stack_push(pile, child->data);
            }
        }
        while (!stack_is_empty(pile)) {
            zpixel* child_data = stack_pop(pile);
            if (child_data != NULL) {
                ((zpixel*)node->data)->r += ((zpixel*)child_data)->r;
                ((zpixel*)node->data)->v += ((zpixel*)child_data)->v;
                ((zpixel*)node->data)->b += ((zpixel*)child_data)->b;
            }
        }
        ((zpixel*)node->data)->r = ((((zpixel*)node->data)->r)+(((zpixel*)node->data)->s)) % 256;
        ((zpixel*)node->data)->v = ((((zpixel*)node->data)->v)+(((zpixel*)node->data)->s)) % 256;
        ((zpixel*)node->data)->b = ((((zpixel*)node->data)->b)+(((zpixel*)node->data)->s)) % 256;
        int distanceDiagonale = abs(((zpixel*)node->data)->x - ((zpixel*)node->data)->y);
        ((zpixel*)node->data)->degradation = (((zpixel*)node->data)->s - 1) * (1 + distanceDiagonale);
    }
}
//on evalue la lightness en utilsant la fonction dans zpixel
void calculerCouleur_DegradationZPixelLuminosite(GNode* node, my_stack_t* pile) {
    if (node != NULL && node->data != NULL && pile != NULL) {
        // Poussez les zpixels des fils dans la pile
        for (int i = 0; i < 4; i++) {
            GNode* child = g_node_nth_child(node, i);
            if (child != NULL) {
                stack_push(pile, child->data);
            }
        }
        while (!stack_is_empty(pile)) {
            zpixel* child_data = stack_pop(pile);
            if (child_data != NULL) {
                ((zpixel*)node->data)->r += ((zpixel*)child_data)->r;
                ((zpixel*)node->data)->v += ((zpixel*)child_data)->v;
                ((zpixel*)node->data)->b += ((zpixel*)child_data)->b;
            }
        }
        int luminosite=lightness((zpixel*)node->data);
        ((zpixel*)node->data)->r = ((((zpixel*)node->data)->r)+luminosite) % 256;
        ((zpixel*)node->data)->v = ((((zpixel*)node->data)->v)+luminosite) % 256;
        ((zpixel*)node->data)->b = ((((zpixel*)node->data)->b)+luminosite) % 256;
        int distanceDiagonale = abs(((zpixel*)node->data)->x - ((zpixel*)node->data)->y);
        ((zpixel*)node->data)->degradation = luminosite * (1 + distanceDiagonale);
    }
}

void calculerCouleur_DegradationZPixelDistance(GNode *node, my_stack_t *pile) {
    if (node != NULL && node->data != NULL && pile != NULL) {
        // Poussez les zpixels des fils dans la pile
        for (int i = 0; i < 4; i++) {
            GNode* child = g_node_nth_child(node, i);
            if (child != NULL) {
                stack_push(pile, child->data);
            }
        }

        float sumDistance = 0.0;

        while (!stack_is_empty(pile)) {
            zpixel* child_data = stack_pop(pile);
            if (child_data != NULL) {
                // Calcul de la distance euclidienne entre les couleurs
                float Ladistance = distance((zpixel*)node->data, child_data);
                sumDistance += Ladistance;
            }
        }

        // Mettez à jour les couleurs en fonction de la distance moyenne
        ((zpixel*)node->data)->r = (unsigned char)(((int)(((zpixel*)node->data)->r) + (int)sumDistance) % 256);
        ((zpixel*)node->data)->v = (unsigned char)(((int)(((zpixel*)node->data)->v) + (int)sumDistance) % 256);
        ((zpixel*)node->data)->b = (unsigned char)(((int)(((zpixel*)node->data)->b) + (int)sumDistance) % 256);

        // Calcul de la dégradation en fonction de la distance diagonale
        int distanceDiagonale = abs(((zpixel*)node->data)->x - ((zpixel*)node->data)->y);
        ((zpixel*)node->data)->degradation = (unsigned char)(sumDistance * (1 + distanceDiagonale));
    }
}


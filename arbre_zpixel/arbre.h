#ifndef ARBRE_H
#define ARBRE_H
#include "../degradation/degradation.h"
#include "../z_pixel/zpixel.h"
#include "../stack/stack2.h"
#include <glib.h>

void destroyNode(GNode* node, gpointer user_data);
void calculerCouleur_DegradationZPixel(zpixel* pixel, int x, int y, int taille);
GNode* buildArbre_zpixel(int x, int y,int taille, image* img);
void afficherArbre(GNode* node, int profondeur);
void parcoursArbre_projeterZpixel(GNode* root, float seuil, image* img);
int trouvertaille_zpixel(int nblig, int nbcol);
GNode* buildArbre_zpixel_ameliorer(int x, int y, int taille, image* img, const CritereEval* evalFunction);

#endif
#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"
#include "../z_pixel/zpixel.h"
#include "../stack/stack2.h"
#include "../degradation/degradation.h"

int main() {
    image *img = creer_image(2,2);
    if (img == NULL) {
        printf("Erreur : Impossible de créer l'image.\n");
        return 1;
    }
    printf("Image créée avec succès!\n");
    int taille_ideale = trouvertaille_zpixel(img->nbL, img->nbC);
    if(taille_ideale==8){
        printf("Taille ideale trouver %d \n",taille_ideale);
    }
    GNode* root = buildArbre_zpixel(0, 0, taille_ideale, img);
    if (root == NULL) {
        printf( "Erreur : Impossible de construire l'arbre.\n");
        destroy_image(img);
        return 1;
    }
    printf("Arbre créé avec succès!\n");
    printf("Image initiale :\n");
    afficher_image(img);
    printf("Arbre des zpixels :\n");
    afficherArbre(root, 0);
    printf("Après dégradation :\n");
    int seuil = 7;
    parcoursArbre_projeterZpixel(root, seuil, img);
    afficher_image(img);

    /*----------test partie 3-------------*/
    CritereEval CritereEval_Size = {calculerCouleur_DegradationZPixelTaille}; 
    printf("affichage de l'arbre ameliorer en fonction de la taille\n");
    GNode* rootSize = buildArbre_zpixel_ameliorer(0, 0, taille_ideale, img, &CritereEval_Size);
    afficherArbre(rootSize, 0);
    parcoursArbre_projeterZpixel(rootSize, seuil, img);
    afficher_image(img);

    CritereEval CritereEval_luminosite = {calculerCouleur_DegradationZPixelLuminosite}; 
    printf("affichage de l'arbre ameliorer en fonction de la luminosite\n");
    GNode* rootLightness = buildArbre_zpixel_ameliorer(0, 0, taille_ideale, img, &CritereEval_luminosite);
    afficherArbre(rootLightness, 0);
    parcoursArbre_projeterZpixel(rootLightness, seuil, img);
    afficher_image(img);

    CritereEval CritereEval_distance = {calculerCouleur_DegradationZPixelDistance}; 
    printf("affichage de l'arbre ameliorer en fonction de la distance\n");
    GNode* rootDistance = buildArbre_zpixel_ameliorer(0, 0, taille_ideale, img, &CritereEval_distance);
    afficherArbre(rootDistance, 0);
    parcoursArbre_projeterZpixel(rootDistance, seuil, img);
    afficher_image(img);




    destroy_image(img);
    gboolean nodesDestroyed = FALSE;
    destroyNode(root, &nodesDestroyed);
    if (nodesDestroyed) {
        printf("Tous les nœuds ont été détruits avec succès.\n");
    } else {
        printf("Aucun nœud n'a été détruit.\n");
    }
    
    return 0;
}   
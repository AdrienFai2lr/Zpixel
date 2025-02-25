#include "../degradation/degradation.h"
#include "arbre.h"
#include "../z_pixel/zpixel.h"
#include "../stack/stack2.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//destruction des noeuds
void destroyNode(GNode* node, gpointer user_data) {
    gboolean* nodesDestroyed = (gboolean*)user_data;

    if (node != NULL) {
        g_node_children_foreach(node, G_TRAVERSE_ALL, (GNodeForeachFunc)destroyNode, user_data);
       
        destroy_zpixel(node->data);
        g_node_destroy(node);

        *nodesDestroyed = TRUE;
    }
    
}

//trouver la taille ideale du zpixel
int trouvertaille_zpixel(int nblig, int nbcol) {
    //verification si les valeur sont identique ou pas 
    if ((nblig & (nblig - 1)) == 0) {
        return nblig;
   }
    if ((nbcol & (nbcol - 1)) == 0) {
        return nbcol;
    }   
    //trouver la valeur la plus grand 
    int maxDimension;
    if(nblig>nbcol){
        maxDimension=nblig;
    }else{
        maxDimension=nbcol;
    }
    int puissancede2 = 1;
    while (puissancede2 < maxDimension) {
        //decalage du bit de poid fort pour faire la puisssance de 2
        puissancede2 <<= 1; 
    }
    return puissancede2;
}
//méthode la dégradation d'un zpixel avec ca couleur
void calculerCouleur_DegradationZPixel(zpixel* pixel, int x, int y, int taille) {
    if (pixel != NULL) {
        pixel->r = x % 256;
        pixel->v = y % 256;
        pixel->b = (x + y) % 256;
        int distanceDiagonale = abs(x - y);
        pixel->degradation = (taille - 1) * (1 + distanceDiagonale);
    }
}
//creation de l'arbre de zpixel en fonction de l'image
GNode* buildArbre_zpixel(int x, int y, int taille, image* img) {
    if (x < 0 || y < 0 || x >= img->nbC || y >= img->nbL) {
        return NULL;
    }

    zpixel* pixel = creer_zpixel(x, y, taille);
    calculerCouleur_DegradationZPixel(pixel, x, y, taille);

    GNode* root = g_node_new(pixel);
    //creation de la pile
    my_stack_t* pile = stack_create(4);

    if (taille > 1) {
        for (int i = 0; i < 4; i++) {
            //appelle recursif
            GNode* child = buildArbre_zpixel(x + (i % 2) * (taille / 2),y + (i / 2) * (taille / 2),taille / 2,img);
            //ajout de chaque enfant dans la pike
            if (child != NULL) {
                stack_push(pile, child);
            }
        }

        while (!stack_is_empty(pile)) {
            GNode* child = stack_pop(pile);
            g_node_append(root, child);
        }
    }
    stack_remove(pile);
    return root;
}

//fonction qui parcours l'abre en profondeur et affiche dans le tampon image les zpixel
//les plus etendus possibles qui presente une degradaton superieur a un seuil donne
void parcoursArbre_projeterZpixel(GNode* root, float seuil, image* img) {
    if (root == NULL) {
        return;
    }
    my_stack_t* pile = stack_create(4);
    stack_push(pile, root);
    while (!stack_is_empty(pile)) {
        GNode* current = (GNode*)stack_pop(pile);
        zpixel* currentPixel = (zpixel*)current->data;
        if (currentPixel->s >= 1 && currentPixel->degradation < seuil) {
            printf("Le seuil/degradation : %f > %f, on projete %d,%d,%d en (%d,%d)\n",seuil, currentPixel->degradation, currentPixel->r, currentPixel->v, currentPixel->b, currentPixel->x, currentPixel->y);
            projection_zpixel_image(img, currentPixel, currentPixel->x, currentPixel->y);            
        } else {
            for (GNode* childNode = current->children; childNode != NULL; childNode = childNode->next) {
                stack_push(pile, childNode);
            }
        }
    }
    stack_remove(pile);
}



//affichage de l'arbre (pas demande juste pour voir la bonne creation de l'arbre avec des couleur pour bien recperer les noeuds etc)
void afficherArbre(GNode* node, int profondeur) {
    if (node != NULL) {
        int couleur = profondeur % 7 + 31;       
        for (int i = 0; i < profondeur; ++i) {
            printf("         "); 
        }
        printf("\033[1;%dm", couleur); 
        zpixel* pixel = (zpixel*)node->data;
        printf("((%d,%d),%d, %d, %d, %d, %f)\n", pixel->x,pixel->y,pixel->r, pixel->v, pixel->b, pixel->s,pixel->degradation);
        printf("\033[0m");        
        GNode* enfant = g_node_first_child(node);
        while (enfant != NULL) {
            afficherArbre(enfant, profondeur + 1);
            enfant = g_node_next_sibling(enfant);
        }
    }
}


GNode* buildArbre_zpixel_ameliorer(int x, int y, int taille, image* img, const CritereEval* evalFunction) {
    if (x < 0 || y < 0 || x >= img->nbC || y >= img->nbL) {
        return NULL;
    }
    zpixel* pixel = creer_zpixel(x, y, taille);
    
    GNode* root = g_node_new(pixel);
    my_stack_t* pile = stack_create(4);
    if (taille > 1) {
        for (int i = 0; i < 4; i++) {
            GNode* child = buildArbre_zpixel_ameliorer(x + (i % 2) * (taille / 2), y + (i / 2) * (taille / 2), taille / 2, img, evalFunction);
            if (child != NULL) {
                stack_push(pile, child);
            }
        }
        while (!stack_is_empty(pile)) {
            GNode* child = stack_pop(pile);
            g_node_append(root, child);
        }
        evalFunction->evaluate(root, pile);
    }
    stack_remove(pile);

    return root;
}

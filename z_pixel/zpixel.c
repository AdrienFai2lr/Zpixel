#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "zpixel.h"
#include <string.h>

//creaion du zpixel et initialisation des parametres x,y et taille, les couleurs sont à noir
zpixel * creer_zpixel(int x,int y,int taille){

    //allocation du zpixel
    zpixel * z1 = (zpixel*)malloc(sizeof(zpixel));
    
    if(z1 == NULL) {
        printf("erreur allocation");
        return NULL;
    }
    z1->r=0;
    z1->v=0;
    z1->b=0;
    z1->x=x;
    z1->y=y;
    z1->s=taille;

    //retour du z pixel par la fonction
    return z1;

}

//destruction du zpixel
void destroy_zpixel(zpixel * z1){
    if (z1 != NULL) { 
        free(z1);
        //printf("\nZpixel detruit avec succes\n");
    }
}
/*-------------INIT---------------------------------*/

void init_zpixel_blanc(zpixel * z1){
    if(z1!= NULL){
        z1->r=255;
        z1->v=255;
        z1->b=255;
    }else{
        printf("erreur pixel");
    }
}

void init_zpixel_couleur(zpixel * z1,char r,char v,char b){
    if(z1!= NULL){
        z1->r=r;
        z1->v=v;
        z1->b=b;
    }else{
        printf("erreur pixel");
    }
}

/*-------------FIN INIT---------------------------------*/
unsigned char max(unsigned char r,unsigned char v,unsigned char b){
    unsigned char max_value=r;
    if(v>max_value){
        max_value=v;
    }
    if(b>max_value){
        max_value=b;
    }
    return max_value;
}
unsigned char  min(unsigned char r,unsigned char v,unsigned char b){
    unsigned char min_value=r;
    if(v>min_value){
        min_value=v;
    }
    if(b>min_value){
        min_value=b;
    }
    return min_value;
}

//calcule de ligthness
unsigned char lightness(zpixel * z1){
    unsigned char  light;
    unsigned char  m_min=min(z1->r,z1->v,z1->b);
    unsigned char  m_max=max(z1->r,z1->v,z1->b);

    //calcule de ligthness
    light=((m_min+m_max)/2);
    return light;
}

//calcule de saturation
unsigned char saturation(zpixel * z1,int light){
    
    unsigned char saturation;
    unsigned char m_min=min(z1->r,z1->v,z1->b);
    unsigned char m_max=max(z1->r,z1->v,z1->b);
    //calcule saturation

    if (m_max == m_min) {
        saturation = 0;
    } else {
        // Calcul de la saturation en fonction de la luminosité
        if (light >= 128) {
            saturation = (255 * ((m_max - m_min) / (511 - (m_max + m_min))));
        } else {
            saturation = (255 * ((m_max - m_min) / (m_max + m_min)));
        }
    }

    return saturation;
}

//distance entre 2 zpixels
double distance(zpixel *z1,zpixel * z2){
    double distance = sqrt(((z1->r-z2->r)*(z1->r-z2->r))+((z1->v-z2->v)*(z1->v-z2->v))+((z1->b-z2->b)*(z1->b-z2->b)));
    return distance;
}

//cree et initialise l'img
image *creer_image(int nbL,int nbC){
    image *nouvelleImage = (image *)malloc(sizeof(image));
    if (nouvelleImage == NULL) {
        printf("Erreur d'allocation de mémoire pour l'image.");
        return NULL;
    }
    nouvelleImage->nbL = nbL;
    nouvelleImage->nbC = nbC;
    nouvelleImage->rowstride = nbC * 3;
    int pad = 0;

    // Calcul du pad nécessaire pour rendre rowstride multiple de 4
    if (nouvelleImage->rowstride % 4 != 0) {
        pad = 4 - (nouvelleImage->rowstride % 4);
    }

    nouvelleImage->rowstride += pad +1;

    // Allocation de mémoire pour le tableau de pixels
    nouvelleImage->tabPixel = (unsigned char *)malloc((nbL * nouvelleImage->rowstride) * sizeof(unsigned char));
    if (nouvelleImage->tabPixel == NULL) {
        printf("Erreur d'allocation de mémoire pour le tableau de pixels de l'image.");
        return NULL;
    }
    memset(nouvelleImage->tabPixel, 0, nbL * nouvelleImage->rowstride * sizeof(unsigned char));
    return nouvelleImage;
}
//detruit l'image cree
void destroy_image(image *img) {
    if (img != NULL) {
        if (img->tabPixel != NULL) {
            free(img->tabPixel);
        }
        free(img);
        printf("\nImage détruite avec succès.\n");
    } else {
        printf("\nPointeur d'image non valide.\n");
    }
}

//recupere les valeur r v b du pixel dans l'image
void get_pixel(image* img, int x, int y, unsigned char* pixel) {
    int index = y * img->rowstride + x * 3;

    if (pixel != NULL) {
        pixel[0] = img->tabPixel[index];
        pixel[1] = img->tabPixel[index + 1];
        pixel[2] = img->tabPixel[index + 2];
    }
}

//set pixel met a jour un pixel de l'image
void set_pixel(image *img, int x, int y, unsigned char r, unsigned char v, unsigned char b) {
    int index = y * img->rowstride + x * 3;
    img->tabPixel[index] = r;
    img->tabPixel[index + 1] = v;
    img->tabPixel[index + 2] = b;
}

//projete un zpixel dans l'image et utilise set pixel pour placer le zpixel
void projection_zpixel_image(image *img, zpixel *pixell, int x, int y) {
    if (img != NULL && pixell != NULL && x >= 0 && x < img->nbC && y >= 0 && y < img->nbL) {
        for (int i = 0; i < pixell->s; ++i) {
            for (int j = 0; j < pixell->s; ++j) {
                int currentX = x + i;
                int currentY = y + j;
                if (currentX >= 0 && currentX < img->nbC && currentY >= 0 && currentY < img->nbL) {
                    set_pixel(img,currentX,currentY,pixell->r,pixell->v,pixell->b);
                }
            }
        }
    } else {
        printf("Coordonnées invalides\n");
    }
}
void afficher_image(image *img) {
    unsigned char r = 0, v = 0, b = 0;
    for (int i = 0; i < img->nbL; i++) {
        for (int j = 0; j < img->nbC * 3; j += 3) {
            r = img->tabPixel[i * img->rowstride + j];
            v = img->tabPixel[i * img->rowstride + j + 1];
            b = img->tabPixel[i * img->rowstride + j + 2];

            printf("{%u,%u,%u} ", r, v, b);
        }
        printf("\n");
    }
}






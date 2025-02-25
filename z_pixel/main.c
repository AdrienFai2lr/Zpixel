
#include <stdio.h>
#include <stdlib.h>
#include "zpixel.h"

int main(){


    //programme de test
    
    /*-----------------------Creer z pixel--------------------------*/
    printf("Creation du zpixel z1\n");
    zpixel *z1=creer_zpixel(2,2,2);
    if(z1!=NULL){
        printf("---creation du zpixel z1 reussi---\n");
    }else{
        printf("---creation du zpixel z1 failed---\n");
    }

    /*----------------------Init z1 noir--------------------------*/
    printf("\n");
    printf("z1 couleur noir\n");
    printf("%u,%u,%u\n",z1->r,z1->v,z1->b);
    if(z1->r==0 && z1->v==0 && z1->b==0){
        printf("---init_zpixel_noir reussi---\n");
    }else{
        printf("---init_zpixel_noir failed---\n");
    }
   
    /*----------------------Init z1 blanc--------------------------*/
    printf("\n");
    printf("z1 couleur blanc\n");
    init_zpixel_blanc(z1);
    printf("%u,%u,%u\n",z1->r,z1->v,z1->b);
    if(z1->r==255 && z1->v==255 && z1->b==255){
        printf("---init_zpixel_blanc reussi---\n");
    }else{
        printf("---init_zpixel_blanc failed---\n");
    }

    /*----------------------Init z1 couleur quelconque--------------------------*/
    printf("\n");
    printf("z1 couleur quelconque\n");
    init_zpixel_couleur(z1,200,150,250);
    printf("%u,%u,%u\n",z1->r,z1->v,z1->b);
    if(z1->r==200 && z1->v==150 && z1->b==250){
        printf("---init_zpixel_couleur reussi---\n");
    }else{
        printf("---init_zpixel_couleur failed---\n");
    }

    /*----------------------Calcul de light-------------------------*/

    /*-----------------------passage zi a noir pour verification (cas divise par 0)-------------------------*/

    printf("\n");  
    unsigned char light = lightness(z1);
    printf("z1 lightness : %u \n",light);
    if(light == 250){
        printf("---lightness reussi\n---");
    }else{
        printf("---lightness failed\n---");
    }

    /*----------------------Calcul de saturation-------------------------*/
    printf("\n");
    unsigned char sat = saturation(z1,light);
    printf("z1 saturation : %u \n",sat);
    if(sat == 0){
        printf("---saturation reussi---\n");
    }else{
        printf("---saturation failed---\n");
    }
    
    /*----------------------Calcul de distance entre z1 et z2-------------------------*/
    /*----------------------creation du zpixel z2-------------------------*/
    printf("\n");
    zpixel * z2=creer_zpixel(4,4,2);
    if(z2!=NULL){
        printf("---creation du zpixel z2 reussi---\n");
    }else{
        printf("---creation du zpixel z2 failed---\n");
    }
    /*----------------------Init z2 couleur quelconque--------------------------*/
    printf("\n");
    init_zpixel_couleur(z2,100,50,250);
    if(z2->r==100 && z2->v==50 && z2->b==250){
        printf("---init_zpixel_couleur reussi---");
    }else{
        printf("---init_zpixel_couleur failed---");
    }
    /*----------------------appel de la fonction et recuperation de la valeur de la distance--------------------------*/
    printf("\n");
    double distance_z1_z2 = distance(z1,z2);  
    printf("distance entre zpixel1 et zpixel2: %f \n",distance_z1_z2);
    if(distance_z1_z2 >= 141.421356){
        printf("---distance reussi---\n");
    }else{
        printf("---distance failed---\n");
    }

    /*----------------------Creation d'une image-------------------------*/
    printf("\nCreation d'une image \n");
    image *img=creer_image(5,5);
    if(img!=NULL){
        printf("---creation d'une image reussi---\n");
    }else{
        printf("---creation d'une image failed---\n");
    }
    
    if(img->nbC == 5 && img->nbL == 5){
        printf("---init_image reussi---\n");
    }else{
        printf("---init_image failed---\n");
    }
    printf("nb colonne : %u,nb ligne : %u,rowstride : %d\n",img->nbC,img->nbL,img->rowstride);
    /*----------------------affichage de l'image-------------------------*/
    printf("\nAffichage de l'image \n");
    for (int i = 0; i < img->nbL; i++) {
        for (int j = 0; j < img->nbC*3; j+=3) {
            unsigned char r = img->tabPixel[i * img->rowstride + j];
            unsigned char v = img->tabPixel[i * img->rowstride + j + 1];
            unsigned char b = img->tabPixel[i * img->rowstride + j + 2];
            printf("{%u %u %u}", r, v, b);
        }
    printf("\n");
    }
    /*----------------------projection du zpixel dans l'image-------------------------*/
    printf("\n");
    /*----------------------couleur z1 passe a couleur quelconque------------------------*/
    init_zpixel_couleur(z1,200,150,250);
    if(z1->r==200 && z1->v==150 && z1->b==250){
        printf("---init_zpixel_couleur reussi---\n");
    }else{
        printf("---init_zpixel_couleur failed---\n");
    }
    /*----------------------initialise la taille du zpixel------------------------*/
    
    if(z2->s == 2 && z1->s == 2){
        printf("---init_taille reussi---\n");
        printf("z1 taille : %u * %u \n",z1->s,z1->s);
        printf("z1 taille : %u * %u \n",z2->s,z2->s);
    }else{
        printf("erreur init taille\n");
    }
    /*----------------------projection du zpixel dans l'image-------------------------*/
    printf("\n");
    projection_zpixel_image(img,z1,0,0);
    projection_zpixel_image(img,z2,2,2);
    /*----------------------affichage de l'image-------------------------*/
    printf("projection des zpixel dans l'image\n");
    for (int i = 0; i < img->nbL; i++) {
        for (int j = 0; j < img->nbC*3; j+=3) {
            unsigned char r = img->tabPixel[i * img->rowstride + j];
            unsigned char v = img->tabPixel[i * img->rowstride + j + 1];
            unsigned char b = img->tabPixel[i * img->rowstride + j + 2];
            printf(" {|%3u|%3u|%3u|} ", r, v, b);
        }
    printf("\n");
    }
    /*---GET PIXEL ----- SET PIXEL*/
    printf("\n");
    // Initialisation de quelques pixels
    set_pixel(img, 1, 1, 255, 0, 0);
    set_pixel(img, 3, 3, 0, 255, 0); 
    
    // Affichage de l'image apres set pixel
    printf("\nAffichage de l'image apres set pixel\n");
    for (int i = 0; i < img->nbL; i++) {
        for (int j = 0; j < img->nbC*3; j+=3) {
            unsigned char r = img->tabPixel[i * img->rowstride + j];
            unsigned char v = img->tabPixel[i * img->rowstride + j + 1];
            unsigned char b = img->tabPixel[i * img->rowstride + j + 2];
            printf(" {|%3u|%3u|%3u|} ", r, v, b);
        }
    printf("\n");
    }
    // Récupération et affichage des pixels
    unsigned char pixel1[3];
    unsigned char pixel2[3];

    get_pixel(img, 1, 1, pixel1);
    get_pixel(img, 3, 3, pixel2);

    printf("Pixel (1, 1): R=%d, V=%d, B=%d\n", pixel1[0], pixel1[1], pixel1[2]);
    printf("Pixel (3, 3): R=%d, V=%d, B=%d\n", pixel2[0], pixel2[1], pixel2[2]);

    if (pixel1[0] == 255 && pixel1[1] == 0 && pixel1[2] == 0 &&
        pixel2[0] == 0 && pixel2[1] == 255 && pixel2[2] == 0) {
        printf("---get_pixel suucces && set_pixel suucces.---\n");
    } else {
        printf("---get_pixel failed---\n");
    }



    //destruction d'une image 
    printf("\ndestruction de l'image img \n");
    destroy_image(img);
    //destruction du zpixel
    printf("\ndestruction du zpixel z1 & z2 \n");
    destroy_zpixel(z1);
    destroy_zpixel(z2);
    
    printf("\n");
    return 0;
}
#ifndef _ZPIXEL_H_
#define _ZPIXEL_H_

/* Definition d'une structure z_pixel & image*/

typedef struct {
    int x;
    int y;
    int s;
    unsigned char r;
    unsigned char v;
    unsigned char b;
    double degradation;
}zpixel;

typedef struct{
    unsigned char * tabPixel;
    int nbL;
    int nbC;
    int rowstride;
}image;


/* --------------------------FONCTION ZPIXEL-------------------------------- */
zpixel * creer_zpixel(int x,int y,int taille);
void init_zpixel_blanc(zpixel * z1);
void init_zpixel_couleur(zpixel * z1,char r,char v,char b);
void destroy_zpixel(zpixel *z1);
unsigned char lightness(zpixel * z1);
unsigned char saturation(zpixel * z1,int light);
double distance(zpixel *z1,zpixel * z2);

unsigned char min(unsigned char r,unsigned char v,unsigned char b);
unsigned char max(unsigned char r,unsigned char v,unsigned char b);

/* --------------------------FONCTION IMAGE-------------------------------- */
image *creer_image(int nbL,int nbC);
void destroy_image(image *img);
void projection_zpixel_image(image *img, zpixel *z, int x, int y);
void get_pixel(image* img, int x, int y, unsigned char* pixel);
void set_pixel(image *img, int x, int y, unsigned char r, unsigned char v, unsigned char b);
void afficher_image(image *img);
#endif /* _ZPIXEL_H_ */

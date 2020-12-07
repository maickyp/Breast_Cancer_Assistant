#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include "CImg.h"

// Function merging 2 images into 1
void Suma(cimg_library::CImg<int> &imagen_suma,cimg_library::CImg<int> &imagen1, cimg_library::CImg<int> &imagen2)
{
    int suma;

    cimg_forXY(imagen1,f,c)                                     // For cycle on the image 1, where runs on columns and rows.
    {
        for(int rgb = 0; rgb <3; ++rgb)                         // For cycle on the 3 channels of images, RED - GREEN - BLUE
        {
            suma = imagen1(f,c,0,rgb)+imagen2(f,c,0,rgb);       // Gets a number adding pixel from image 1 and image 2; place it on  suma

            if(suma>255)                                        // If value is over 255, it caps in 255
            {
                suma=255;
            }

            imagen_suma(f,c,0,rgb) = suma;                      // The new value is placed on the result image.
        }

    }

}


// Function making any pixel RED=255 be compleatly red by nullify other channels
void Remarcar(cimg_library::CImg<int> &imagen)    
{
    int suma;

    cimg_forXY(imagen,f,c)
    {
        for(int rgb = 0; rgb <3; ++rgb)
        {
            if (imagen (f,c,0,0) == 255)                        // If pixel red=255
                {
                imagen (f,c,0,1) = 0;                           // Other channels turns to 0
                imagen (f,c,0,2) = 0;
                }
        }

    }

}

// every pixel on red channel is put on new image
void ToRed(cimg_library::CImg<int> &imagen_roja, cimg_library::CImg<int> imagen_bn)
{
    cimg_forXY(imagen_bn,f,c)
    {
        imagen_roja(f,c,0,0) = imagen_bn(f,c,0,0);

    }
}

// Save file
void Guardar(cimg_library::CImg<int> &imagen)
{
    string im = "Imagen final";
    im = im + ".bmp";
    imagen.save_bmp(im.c_str());
}

// void Modificacion_Iluminacion (cimg_library::CImg<int> &imagen, float contraste, float brillo)
// {
//     int iluminacion;

//     for(int f=1; f<imagen.width()-1; ++f)
//         for(int c=1; c<imagen.height()-1; ++c)
//         {

//             iluminacion = (int) (contraste*imagen(f,c,0,0)+brillo);

//             if(iluminacion>255)
//                 iluminacion = 255;

//             if(iluminacion<0)
//                 iluminacion = 0;

//             imagen(f,c,0,0) = iluminacion;
//         }
// }


// Functions that takes every value from 8 neighbour pixels and get its average.
void Ero(cimg_library::CImg<int> &imagen_ero, cimg_library::CImg<int> imagen_bin)
{
    CImg<int> auxx(imagen_bin.width(),imagen_bin.height(),1,1,0);
    auxx = imagen_bin;
    int ero;
    int aux=0;
    imagen_ero=auxx;
    for(int k=0; k<5; k++)
    {
        for(int f=1; f<auxx.width()-1; ++f)
        {
            for(int c=1; c<auxx.height()-1; ++c)
            {
                aux=(auxx(f,c+1,0,0))+(auxx(f,c-1,0,0))+(auxx(f+1,c,0,0))+(auxx(f-1,c,0,0))+(auxx(f+1,c+1,0,0))+(auxx(f-1,c-1,0,0))+(auxx(f-1,c+1,0,0))+(auxx(f+1,c-1,0,0));
                aux=aux/255;
                if (aux<7)
                {
                    ero =255;
                }
                else
                {
                    ero=0;
                }

                imagen_ero(f,c,0,0) = ero;

            }
        }
        auxx=imagen_ero;

    }
}

// Sames as before but 20 times more
void Suavizado(cimg_library::CImg<int> &imagen_suave, cimg_library::CImg<int> imagen_bin)
{
    CImg<int> auxx(imagen_bin.width(),imagen_bin.height(),1,1,0);
    auxx = imagen_bin;
    int ero;
    int aux=0;
    imagen_suave=auxx;
    for(int k=0; k<100; k++)
    {

        for(int f=1; f<auxx.width()-1; ++f)
        {
            for(int c=1; c<auxx.height()-1; ++c)
            {

                aux=(auxx(f,c+1,0,0))+(auxx(f,c-1,0,0))+(auxx(f+1,c,0,0))+(auxx(f-1,c,0,0))+(auxx(f+1,c+1,0,0))+(auxx(f-1,c-1,0,0))+(auxx(f-1,c+1,0,0))+(auxx(f+1,c-1,0,0));
                aux=aux/255;
                if (aux<7)
                {
                    ero = 255;
                }
                else
                {
                    ero=0;
                }

                imagen_suave(f,c,0,0) = ero;

            }
        }
        auxx=imagen_suave;

    }
}

// Converts a color image to gray scale
void CGris (cimg_library::CImg<int> &imagen_gris, cimg_library::CImg<int> imagen)
{
    cimg_forXY(imagen,f,c)
    imagen_gris(f,c) = (int) (0.3333*(imagen(f,c,0,0)+imagen(f,c,0,1)+imagen(f,c,0,2)));
}

// Converts gray scale image to binary with a set threshold
void CBin (cimg_library::CImg<int> &imagen_binarizada, cimg_library::CImg<int> imagen_gris, int umbral)
{
    int bin;

    cimg_forXY(imagen_gris,f,c)
    {
        bin = imagen_gris(f,c);

        if(bin > umbral)
            imagen_binarizada(f,c) = 255;
        else
            imagen_binarizada(f,c) = 0;
    }
}


// void CInv (cimg_library::CImg<int> &imagen_invertida, cimg_library::CImg<int> imagen_bin)
// {
//     int bin;

//     cimg_forXY(imagen_bin,f,c)
//     {
//         bin = imagen_bin(f,c);

//         if(bin == 0)
//             imagen_invertida(f,c) = 255;
//         else
//             imagen_invertida(f,c) = 0;
//     }
// }


// void Filtro_Gauss (CImg<int> &imagen_gaussiano, CImg<int> imagen)
// {
//     float gaussiano;

//     for(int f=1; f<imagen.width()-1; ++f)
//     {
//         for(int c=1; c<imagen.height()-1; ++c)
//         {
//             for(int rgb=0; rgb<3; ++rgb)
//             {
//                 gaussiano = 1*(imagen(f-1,c-1,0,rgb)+imagen(f-1,c+1,0,rgb)+imagen(f+1,c-1,0,rgb)+imagen(f+1,c+1,0,rgb))+
//                             2*(imagen(f-1,c,0,rgb)+imagen(f,c-1,0,rgb)+imagen(f,c+1,0,rgb)+imagen(f+1,c,0,rgb))+
//                             4*imagen(f,c,0,rgb);

//                 imagen_gaussiano(f,c,0,rgb) = (int) (gaussiano/16);
//             }
//         }
//     }
// }

// Laplacian Filter for images
void Laplaciano (CImg<int> &imagen_bordes, CImg<int> imagen)
{

    float Bordes;

    for(int f=1; f<imagen.width()-1; ++f)
    {
        for(int c=1; c<imagen.height()-1; ++c)
        {

            Bordes = 0*imagen(f-1,c-1,0,0)+ 1*imagen(f-1,c,0,0) + 0*imagen(f-1,c+1,0,0) +
                     imagen(f,c-1,0,0) - 4*imagen(f,c,0,0) + imagen(f,c+1,0,0) +
                     0*imagen(f+1,c-1,0,0)+ 1*imagen(f+1,c,0,0) + 0*imagen(f+1,c+1,0,0);
            imagen_bordes(f,c,0,0) = (int) (Bordes);

        }
    }


}
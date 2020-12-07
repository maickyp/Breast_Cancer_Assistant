#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include "CImg.h"           
#include "functions.h"    


using namespace std;
using namespace cimg_library;

int main()
{
    for(;;)
    {
        string nombre_imagen;                                                   // String where user will type the image name.  
    
        cout << "Nombre de la imagen:" << endl;                                 // Image selection by typing it.
        cin >> nombre_imagen;
        nombre_imagen += ".bmp";                                                // adding ".bmp" extension
        int umbral=180;
        cout << "  " << endl;
        cout << " Procesando " << endl;
        cout << "  " << endl;

        // Declarating new images
        CImg<int> imagen(nombre_imagen.c_str());                                // Blank image with properly dimensions
        CImg<int> imagen_gris(imagen.width(),imagen.height(),1,1,0);            // Gray image
        CImg<int> imagen_bin(imagen.width(),imagen.height(),1,1,0);             // Binary image
        CImg<int> imagen_bordes(imagen.width(),imagen.height(),1,1,0);          // Edge image
        CImg<int> imagen_bordes_rojos(imagen.width(),imagen.height(),1,3,0);    // Red edge image
        CImg<int> imagen_ero(imagen.width(),imagen.height(),1,1,0);             // Erotion image
        CImg<int> imagen_suave(imagen.width(),imagen.height(),1,1,0);           // Soft image
        CImg<int> imagen_suma(imagen.width(),imagen.height(),1,1,0);            // Added image
        CImg<int> imagen_final(imagen.width(),imagen.height(),1,3,0);           // Final image
        CImgDisplay ventana;
        CImgList<int> imagenes;


        CGris(imagen_gris, imagen);                                             // Making image to gray scale
        cout<< "Gris terminado" << endl;
        CBin(imagen_bin, imagen_gris, umbral);                                  // Making gray scale image to binary image with 180 threshold
        cout<< "Binarizacion terminado" << endl;
        Ero(imagen_ero,imagen_bin);                                             // Proccess the image to be more soft
        cout<< "Erosion terminado" << endl;
        Suavizado(imagen_suave,imagen_bin);
        cout<< "Suavizado terminado" << endl;
        Laplaciano(imagen_bordes,imagen_suave);                                 // Gets the edges of softened image
        cout<< "Laplace terminado" << endl;
        ToRed(imagen_bordes_rojos, imagen_bordes);                              // turn this edges to red color
        cout<< "Rojos terminado" << endl;
        Suma(imagen_final,imagen_bordes_rojos,imagen);                          // adding this edges to orignal image
        cout<< "Suma terminado" << endl;    
        Remarcar(imagen_final);                                                 // make those red pixel even more red
        cout<< "Remarcado terminado" << endl;

        imagenes.push_back(imagen);
/*        imagenes.push_back(imagen_ero);
        imagenes.push_back(imagen_suave);
        imagenes.push_back(imagen_bordes);
       imagenes.push_back(imagen_bordes_rojos);
   */      imagenes.push_back(imagen_final);



        ventana.assign(3*imagen.width(),imagen.height(),"Imagenes",0);
        imagenes.display(ventana, false);
        system("cls");
    }
    return 0;
}


#ifndef __MAPA_H__
#define __MAPA_H__

#include <fstream>
#include <string>
#include "sprites.h"

using namespace std;

#define IMAGENES_DIMENSION 40

#define PANTALLA_ANCHO 20
#define PANTALLA_ALTO 15
#define RANDOM_MAXIMO 4
#define RANDOM_MINIMO 1

#define MUS_MAPA_1 "mapa1.ogg"

SDL_Surface *screen;

Mix_Music *mus_fondo ;
int use_sound;

int mapa_virtual[PANTALLA_ALTO][PANTALLA_ANCHO];
float porcentaje_obstaculos = RANDOM_MINIMO;

enum {
	ARRIBA,
	ABAJO,
	IZQ,
	DER
};

int muros [PANTALLA_ALTO][PANTALLA_ANCHO] = { 
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0}
};

int murallas [PANTALLA_ALTO][PANTALLA_ANCHO] = { 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0},
	{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
	{0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0},
	{0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0},
	{0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0},
	{0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0},
	{0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0},
	{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
	{0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int zig_zag [PANTALLA_ALTO][PANTALLA_ANCHO] = { 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void DibujarFondo () {
	SDL_Rect rect;
	for (int i = 0; i < PANTALLA_ALTO; i++) {
		for (int j = 0; j < PANTALLA_ANCHO; j++) {
			rect.x = j * IMAGENES_DIMENSION;
			rect.y = i * IMAGENES_DIMENSION;
			SDL_BlitSurface (images [IMG_SAND_1], NULL, screen, &rect);
			mapa_virtual[i][j] = ESTADO_CAMINABLE;
		}
	}
}

void DibujarObstaculos () {
	SDL_Rect rect;
	int tipo_mapa;
	for (int i = 0; i < PANTALLA_ALTO; i++) {
		for (int j = 0; j < PANTALLA_ANCHO; j++) {
			
			tipo_mapa = rand() % 11;
						
			if (tipo_mapa < porcentaje_obstaculos) {
				rect.x = j * IMAGENES_DIMENSION;
				rect.y = i * IMAGENES_DIMENSION;
				SDL_BlitSurface (images [IMG_GRASS_1], NULL, screen, &rect);
				mapa_virtual[i][j] = ESTADO_ANIMADO;
			}
		}
	}
}

void DibujarMapaPrecargado (int opcion) {
	SDL_Rect rect;
	for (int i = 0; i < PANTALLA_ALTO; i++) {
		for (int j = 0; j < PANTALLA_ANCHO; j++) {
			rect.x = j * IMAGENES_DIMENSION;
			rect.y = i * IMAGENES_DIMENSION;
			switch (opcion) {
				case 1:
					if (muros[i][j] == ESTADO_ANIMADO) {			
						SDL_BlitSurface (images [IMG_GRASS_1], NULL, screen, &rect);
						mapa_virtual[i][j] = ESTADO_ANIMADO;
					}
					break;
				case 2:
					if (murallas[i][j] == ESTADO_ANIMADO) {			
						SDL_BlitSurface (images [IMG_GRASS_1], NULL, screen, &rect);
						mapa_virtual[i][j] = ESTADO_ANIMADO;
					}
					break;
				case 3:
					if (zig_zag[i][j] == ESTADO_ANIMADO) {			
						SDL_BlitSurface (images [IMG_GRASS_1], NULL, screen, &rect);
						mapa_virtual[i][j] = ESTADO_ANIMADO;
					}
					break;
			}
		}
	}
}

void ColocarArbol (int posY, int posX) {
	SDL_Rect rect;
	
	rect.x = posX * IMAGENES_DIMENSION;
	rect.y = posY * IMAGENES_DIMENSION;
	SDL_BlitSurface (images [IMG_GRASS_1], NULL, screen, &rect);
	mapa_virtual[posY][posX] = ESTADO_ANIMADO;
}

void ColocarArena (int posY, int posX) {
	SDL_Rect rect;
	
	rect.x = posX * IMAGENES_DIMENSION;
	rect.y = posY * IMAGENES_DIMENSION;
	SDL_BlitSurface (images [IMG_SAND_1], NULL, screen, &rect);
	mapa_virtual[posY][posX] = ESTADO_CAMINABLE;
}

void GuardarMapa () {
	fstream archivo;
	string nombre_archivo;
	
	cout << "Cual es el nombre del archivo?: ";
	getline (cin, nombre_archivo);
	archivo.open(nombre_archivo + ".mapa", fstream::in | fstream::out | fstream::app);
	for (int i = 0; i < PANTALLA_ALTO; i++) {
		for (int j = 0; j < PANTALLA_ANCHO; j++) {
			archivo << mapa_virtual[i][j];
		}
	}
	cout << "Guardado...\n";
	archivo.close();
}

void AbrirMapa () {
	fstream archivo;
	string nombre_archivo, mapa_archivo;
	SDL_Rect rect;
	int h = 0;
	
	cout << "Cual es el nombre del archivo?: ";
	getline (cin, nombre_archivo);
	archivo.open(nombre_archivo + ".mapa", fstream::in | fstream::out | fstream::app);
	getline(archivo, mapa_archivo);
	for (int i = 0; i < PANTALLA_ALTO; i++) {
		for (int j = 0; j < PANTALLA_ANCHO; j++) {
			rect.x = j * IMAGENES_DIMENSION;
			rect.y = i * IMAGENES_DIMENSION;
			if (mapa_archivo[h++] - '0' == ESTADO_ANIMADO) {
				SDL_BlitSurface (images [IMG_GRASS_1], NULL, screen, &rect);
				mapa_virtual[i][j] = ESTADO_ANIMADO; 
			}
		}
	}
	cout << "Abriendo...\n";
	archivo.close();
}

#endif /* __MAPA_H__ */

















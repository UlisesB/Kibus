#ifndef __MAPA_H__
#define __MAPA_H__

#include "sprites.h"

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

void DibujarMenu () {
	SDL_Rect rect;
	
	rect.x = PANTALLA_ANCHO * IMAGENES_DIMENSION + 2;
	rect.y = 0;
	rect.h = PANTALLA_ALTO * IMAGENES_DIMENSION;
	rect.w = IMAGENES_DIMENSION;
	SDL_FillRect (screen, &rect, SDL_MapRGB(screen->format, 180, 223, 232));
	
	//Inicio
	rect.x = PANTALLA_ANCHO * IMAGENES_DIMENSION + 2;
	rect.y = (IMAGENES_DIMENSION * 0);
	SDL_BlitSurface (images [IMG_START_1], NULL, screen, &rect);
	
	//Mario
	rect.x = PANTALLA_ANCHO * IMAGENES_DIMENSION + 2;
	rect.y = (IMAGENES_DIMENSION * 1);
	SDL_BlitSurface (images [IMG_MARIO_1], NULL, screen, &rect);
	
	//Casa
	rect.x = PANTALLA_ANCHO * IMAGENES_DIMENSION + 2;
	rect.y = (IMAGENES_DIMENSION * 2);
	SDL_BlitSurface (images [IMG_HOUSE_YELLOW], NULL, screen, &rect);
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


#endif /* __MAPA_H__ */

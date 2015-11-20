#ifndef __CASA_H__
#define __CASA_H__

#include <cmath>
#include "sprites.h"
#include "mapa.h"

class Casa {
	public:
		int posX, posY;
		
		void Inicializar();
		bool esInicializado();
		void ColocarCasa (int newY, int newX);
		void DibujarCasa ();

};

void Casa::Inicializar() {
	posX = -1;
	posY = -1;
}

bool Casa::esInicializado() {
	return this->posX == -1 and this->posY == -1;
}

void Casa::ColocarCasa (int newY, int newX) {
	SDL_Rect rect;
	int calor = 100;
	int x, y;
	
	if(not this->esInicializado()) {
		rect.x = this->posX * IMAGENES_DIMENSION;
		rect.y = this->posY * IMAGENES_DIMENSION;
		SDL_BlitSurface (images [IMG_SAND_1], NULL, screen, &rect);
	}
	
	rect.x = newX * IMAGENES_DIMENSION;
	rect.y = newY * IMAGENES_DIMENSION;
	this->posX = newX; this->posY = newY;
	SDL_BlitSurface (images [IMG_HOUSE_YELLOW], NULL, screen, &rect);

	for (int i = 0; i < PANTALLA_ALTO; i++) {
		for (int j = 0; j < PANTALLA_ANCHO; j++) {
			x = abs(this->posY - i);
			y = abs(this->posX - j);
			mapa_calor[i][j] = (x >= y ? calor - x : calor - y);
		}
	}
	
}

void Casa::DibujarCasa () {
	SDL_Rect rect;
	
	rect.x = this->posX * IMAGENES_DIMENSION;
	rect.y = this->posY * IMAGENES_DIMENSION;
	SDL_BlitSurface (images [IMG_HOUSE_YELLOW], NULL, screen, &rect);
}

#endif








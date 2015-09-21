#ifndef __MARIO_H__
#define __MARIO_H__

#include "sprites.h"
#include "mapa.h"

class Mario {
	public:
		int posX, posY;
		
		void Inicializar();
		bool esInicializado();
		void ColocarMario (int newY, int newX);
		void DibujarMario (int frame);

};

void Mario::Inicializar() {
	posX = -1;
	posY = -1;
}

bool Mario::esInicializado() {
	return this->posX == -1 and this->posY == -1;
}

void Mario::ColocarMario (int newY, int newX) {
	SDL_Rect rect;
	if(not this->esInicializado()) {
		rect.x = this->posX * IMAGENES_DIMENSION;
		rect.y = this->posY * IMAGENES_DIMENSION;
		SDL_BlitSurface (images [IMG_SAND_1], NULL, screen, &rect);
	}
	
	rect.x = newX * IMAGENES_DIMENSION;
	rect.y = newY * IMAGENES_DIMENSION;
	this->posX = newX; this->posY = newY;
	SDL_BlitSurface (images [IMG_MARIO_1], NULL, screen, &rect);
}

void Mario::DibujarMario (int frame) {
	SDL_Rect rect;
	rect.x = this->posX * IMAGENES_DIMENSION;
		rect.y = this->posY * IMAGENES_DIMENSION;
	SDL_BlitSurface (images [IMG_MARIO_1 + frame], NULL, screen, &rect);
}

#endif

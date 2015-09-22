#ifndef __CASA_H__
#define __CASA_H__

#include "sprites.h"
#include "mapa.h"

class Casa {
	public:
		int posX, posY;
		
		void Inicializar();
		bool esInicializado();
		void ColocarCasa (int newY, int newX);
		void DibujarCasa (int frame);

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
	if(not this->esInicializado()) {
		rect.x = this->posX * IMAGENES_DIMENSION;
		rect.y = this->posY * IMAGENES_DIMENSION;
		mapa_virtual[this->posY][this->posX] = ESTADO_CAMINABLE;
		SDL_BlitSurface (images [IMG_SAND_1], NULL, screen, &rect);
	}
	
	rect.x = newX * IMAGENES_DIMENSION;
	rect.y = newY * IMAGENES_DIMENSION;
	this->posX = newX; this->posY = newY;
	mapa_virtual[this->posY][this->posX] = ESTADO_CASA;
	SDL_BlitSurface (images [IMG_HOUSE_YELLOW], NULL, screen, &rect);
}

#endif

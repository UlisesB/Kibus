#ifndef __MARIO_H__
#define __MARIO_H__

#include "sprites.h"
#include "mapa.h"
#include "casa.h"

using namespace std;

class Mario {
	public:
		stack<int> pila_movimientos;
		bool usando_pila;
		int posX, posY;
		
		void Inicializar();
		bool esInicializado();
		void ColocarMario (int newY, int newX, Casa casa);
		void AnimarMario (int frame);
		void MoverMario (int movimiento, Casa casa);

};

void Mario::Inicializar() {
	posX = -1;
	posY = -1;
	while (not pila_movimientos.empty()) {
		pila_movimientos.pop();
	}
	usando_pila = false;
}

bool Mario::esInicializado() {
	return this->posX == -1 and this->posY == -1;
}

void Mario::ColocarMario (int newY, int newX, Casa casa) {
	SDL_Rect rect;
	if(not this->esInicializado()) {
		rect.x = this->posX * IMAGENES_DIMENSION;
		rect.y = this->posY * IMAGENES_DIMENSION;
		if (casa.posX == this->posX and casa.posY == this->posY) {		
			SDL_BlitSurface (images [IMG_HOUSE_YELLOW], NULL, screen, &rect);
		}
		else {
			SDL_BlitSurface (images [IMG_SAND_1], NULL, screen, &rect);
		}
		
		while (not pila_movimientos.empty()) {
			pila_movimientos.pop();
		}
		usando_pila = false;
	}
	
	rect.x = newX * IMAGENES_DIMENSION;
	rect.y = newY * IMAGENES_DIMENSION;
	this->posX = newX; this->posY = newY;
	SDL_BlitSurface (images [IMG_MARIO_1], NULL, screen, &rect);
}

void Mario::AnimarMario (int frame) {
	SDL_Rect rect;
	rect.x = this->posX * IMAGENES_DIMENSION;
	rect.y = this->posY * IMAGENES_DIMENSION;
	SDL_BlitSurface (images [IMG_MARIO_1 + frame], NULL, screen, &rect);
}

void Mario::MoverMario (int movimiento, Casa casa) {
	SDL_Rect rect;
	
	rect.x = this->posX * IMAGENES_DIMENSION;
	rect.y = this->posY * IMAGENES_DIMENSION;
	if (casa.posX == this->posX and casa.posY == this->posY) {		
		SDL_BlitSurface (images [IMG_HOUSE_YELLOW], NULL, screen, &rect);
	}
	else {
		SDL_BlitSurface (images [IMG_SAND_1], NULL, screen, &rect);
	}
	
	switch (movimiento) {
		case ARRIBA:
			this->posY--;
			rect.x = this->posX * IMAGENES_DIMENSION;
			rect.y = this->posY * IMAGENES_DIMENSION;
			if (not usando_pila) pila_movimientos.push(ABAJO);
			break;
			
		case ABAJO:
			this->posY++;
			rect.x = this->posX * IMAGENES_DIMENSION;
			rect.y = this->posY * IMAGENES_DIMENSION;
			if (not usando_pila) pila_movimientos.push(ARRIBA);
			break;
			
		case IZQ:
			this->posX--;
			rect.x = this->posX * IMAGENES_DIMENSION;
			rect.y = this->posY * IMAGENES_DIMENSION;
			if (not usando_pila) pila_movimientos.push(DER);
			break;
			
		case DER:
			this->posX++;
			rect.x = this->posX * IMAGENES_DIMENSION;
			rect.y = this->posY * IMAGENES_DIMENSION;
			if (not usando_pila) pila_movimientos.push(IZQ);
			break;
	}
	
	SDL_BlitSurface (images [IMG_MARIO_1], NULL, screen, &rect);
}

#endif



















#ifndef __MARIO_H__
#define __MARIO_H__

#include "sprites.h"
#include "mapa.h"
#include "casa.h"
#include "administradorYoshis.h"

using namespace std;

class Mario {
	public:
		int posX, posY;
		AdminYoshi adminYoshis;
		int movimientos_etapa;
		
		void Inicializar();
		bool esInicializado();
		void ColocarMario (int newY, int newX, Casa casa);
		void AnimarMario (int frame);
		void MoverMario ();
};

void Mario::Inicializar() {
	posX = -1;
	posY = -1;
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
	}
	
	rect.x = newX * IMAGENES_DIMENSION;
	rect.y = newY * IMAGENES_DIMENSION;
	
	this->posX = newX; this->posY = newY;
	SDL_BlitSurface (images [IMG_MARIO_1], NULL, screen, &rect);
	
	adminYoshis.InicializarYoshis(this->posX, this->posY);
	movimientos_etapa = 0;
}

void Mario::AnimarMario (int frame) {
	SDL_Rect rect;
	rect.x = this->posX * IMAGENES_DIMENSION;
	rect.y = this->posY * IMAGENES_DIMENSION;
	SDL_BlitSurface (images [IMG_MARIO_1 + frame], NULL, screen, &rect);
}

void Mario::MoverMario () {
	SDL_Rect rect;
	
	if (movimientos_etapa < ETAPAS) {
		rect.x = this->posX * IMAGENES_DIMENSION;
		rect.y = this->posY * IMAGENES_DIMENSION;
		SDL_BlitSurface (images [IMG_SAND_1], NULL, screen, &rect);
	
		this->posX = adminYoshis.camino[movimientos_etapa].posX;
		this->posY = adminYoshis.camino[movimientos_etapa].posY;
	
		rect.x = this->posX * IMAGENES_DIMENSION;
		rect.y = this->posY * IMAGENES_DIMENSION;
		SDL_BlitSurface (images [IMG_MARIO_1], NULL, screen, &rect);
		
		movimientos_etapa++;
	}
	else {
		movimientos_etapa = 0;
		adminYoshis.InicializarYoshis(this->posX, this->posY);
	}
	
}

#endif



















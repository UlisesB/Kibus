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
		void MoverMario (Casa casa, int newX, int newY);
		void MovimientoAleatorio(int *newX, int *newY);
		void ActualizarBanderines();
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

void Mario::MoverMario (Casa casa, int newX, int newY) {
	SDL_Rect rect;
	
	rect.x = this->posX * IMAGENES_DIMENSION;
	rect.y = this->posY * IMAGENES_DIMENSION;
	if (casa.posX == this->posX and casa.posY == this->posY) {		
		SDL_BlitSurface (images [IMG_HOUSE_YELLOW], NULL, screen, &rect);
	}
	else {
		SDL_BlitSurface (images [IMG_SAND_1], NULL, screen, &rect);
	}
	
	this->posX = newX;
	this->posY = newY;
	
	rect.x = this->posX * IMAGENES_DIMENSION;
	rect.y = this->posY * IMAGENES_DIMENSION;
	SDL_BlitSurface (images [IMG_MARIO_1], NULL, screen, &rect);
}

void Mario::MovimientoAleatorio(int *newX, int *newY) {
	int opciones[] = {-1, 0, 1};
	int opcion;
	int intentos_1 = 2, intentos_2 = 3, intentos_3 = 6, intentos_4 = 10;
	
	do {
		do {
			opcion = rand() % 3;
			*newX = this->posX + opciones[opcion];
			opcion = rand() % 3;
			*newY = this->posY + opciones[opcion];
		} while ((*(newX) < 0 or *(newX) >= PANTALLA_ANCHO) or (*(newY) < 0 or *(newY) >= PANTALLA_ALTO) or 
				  mapa_virtual[*(newY)][*(newX)] == ESTADO_ANIMADO);
	
		switch (mapa_virtual[*(newY)][*(newX)]) {
			case ESTADO_CAMINABLE:
				mapa_banderines[this->posY][this->posX]++;
				ActualizarBanderines();
				return;
				break;
			case ESTADO_BANDERIN_1:
				if (--intentos_1 < 0) {
					mapa_banderines[this->posY][this->posX]++;
					ActualizarBanderines();
					return;
				}
				break;
			case ESTADO_BANDERIN_2:
				if (--intentos_2 < 0) {
					mapa_banderines[this->posY][this->posX]++;
					ActualizarBanderines();
					return;
				}
				break;
			case ESTADO_BANDERIN_3:
				if (--intentos_3 < 0) {
					mapa_banderines[this->posY][this->posX]++;
					ActualizarBanderines();
					return;
				}
				break;
			case ESTADO_BANDERIN_4:
				if (--intentos_4 < 0) {
					mapa_banderines[this->posY][this->posX]++;
					ActualizarBanderines();
					return;
				}
				break;
		}
	} while (1);
}

void Mario::ActualizarBanderines () {
	switch (mapa_banderines[this->posY][this->posX]) {
		case 5:
			mapa_virtual[this->posY][this->posX] = ESTADO_BANDERIN_1;
			break;
		case 8:
			mapa_virtual[this->posY][this->posX] = ESTADO_BANDERIN_2;
			break;
		case 10:
			mapa_virtual[this->posY][this->posX] = ESTADO_BANDERIN_3;
			break;
		case 12:
			mapa_virtual[this->posY][this->posX] = ESTADO_BANDERIN_4;
			break;
	}
}

#endif



















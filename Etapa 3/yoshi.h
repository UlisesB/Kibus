#ifndef __YOSHI_H__
#define __YOSHI_H__

#include "sprites.h"
#include "casa.h"
#include "mapa.h"

using namespace std;

class Yoshi {
	public:
		int posX, posY;
		RegistroMovimiento prueba;
		
		void MovimientoAleatorio(int *newX, int *newY);
		void TomarMuestra();
		void MoverYoshi (int newX, int newY);
};

void Yoshi::MovimientoAleatorio(int *newX, int *newY) {
	int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
	int dy[] = {-1, -1, 1, 0, 0, 1, 1, 1};
	int opcion;
	int intentos = 3;
	
	do {
		opcion = rand() % 8;
		*newX = this->posX + dx[opcion];
		opcion = rand() % 8;
		*newY = this->posY + dy[opcion];
	} while ((*(newX) < 0 or *(newX) >= PANTALLA_ANCHO) or (*(newY) < 0 or *(newY) >= PANTALLA_ALTO) or 
			  mapa_virtual[*(newY)][*(newX)] == ESTADO_ANIMADO);
}

void Yoshi::TomarMuestra () {
	prueba.posX = this->posX;
	prueba.posY = this->posY;
	prueba.calor = mapa_calor[this->posY][this->posX];
}

void Yoshi::MoverYoshi (int newX, int newY) {
	SDL_Rect rect;
	
	rect.x = this->posX * IMAGENES_DIMENSION;
	rect.y = this->posY * IMAGENES_DIMENSION;
	SDL_BlitSurface (images [IMG_SAND_1], NULL, screen, &rect);
	
	this->posX = newX;
	this->posY = newY;
	
	rect.x = this->posX * IMAGENES_DIMENSION;
	rect.y = this->posY * IMAGENES_DIMENSION;
	SDL_BlitSurface (images [IMG_YOSHI], NULL, screen, &rect);
}

#endif













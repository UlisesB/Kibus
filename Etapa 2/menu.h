#ifndef __MENU_H__
#define __MENU_H__

#include "mapa.h"

int estado_menu;

enum {
	PLAY,
	COLOCAR_MARIO,
	COLOCAR_CASA,
	COLOCAR_ARBOL,
	COLOCAR_ARENA
};

void DibujarMenu () {
	SDL_Rect rect;
	
	rect.x = PANTALLA_ANCHO * IMAGENES_DIMENSION + 2;
	rect.y = 0;
	rect.h = PANTALLA_ALTO * IMAGENES_DIMENSION;
	rect.w = IMAGENES_DIMENSION;
	SDL_FillRect (screen, &rect, SDL_MapRGB(screen->format, 180, 223, 232));
	
	//Play
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
	
	//Arbol
	rect.x = PANTALLA_ANCHO * IMAGENES_DIMENSION + 2;
	rect.y = (IMAGENES_DIMENSION * 3);
	SDL_BlitSurface (images [IMG_GRASS_1], NULL, screen, &rect);
	
	//Arena
	rect.x = PANTALLA_ANCHO * IMAGENES_DIMENSION + 2;
	rect.y = (IMAGENES_DIMENSION * 4);
	SDL_BlitSurface (images [IMG_SAND_1], NULL, screen, &rect);
}

void CambiarEstadoMenu (int boton_menu) {
	switch (boton_menu) {
		case PLAY:
			if (estado_menu == PLAY) {
				if (use_sound) Mix_HaltMusic();
				estado_menu = -1;
			}
			else {
				if (use_sound) Mix_PlayMusic (mus_fondo, -1);
				estado_menu = PLAY;
			}
			break;
		case COLOCAR_MARIO:
			if (estado_menu != PLAY)
				estado_menu = COLOCAR_MARIO;
			break;
		case COLOCAR_CASA:
			if (estado_menu != PLAY)
				estado_menu = COLOCAR_CASA;
			break;
		case COLOCAR_ARBOL:
			if (estado_menu != PLAY)
				estado_menu = COLOCAR_ARBOL;
			break;
		case COLOCAR_ARENA:
			if (estado_menu != PLAY)
				estado_menu = COLOCAR_ARENA;
			break;
	}
}

#endif /* __MENU_H__ */

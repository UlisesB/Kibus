#ifndef __MENU_H__
#define __MENU_H__

#include "mapa.h"

int estado_menu;

enum {
	PLAY,
	COLOCAR_MARIO,
	COLOCAR_CASA
};

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
	}
}

#endif /* __MENU_H__ */

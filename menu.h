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
			estado_menu = (estado_menu == PLAY) ? -1 : PLAY;
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

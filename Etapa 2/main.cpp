#include <iostream>
#include <stack>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#include "time.h"

#include "sprites.h"
#include "mario.h"
#include "casa.h"
#include "mapa.h"
#include "menu.h"


/* Prototipos de función */
void setup (void);


int main (int argc, char const* argv[])
{
	SDL_Rect rect;
	int g, h, frame, subframe;
	int mouseX, mouseY;
	srand(time(NULL));
	SDL_Event evento;
	Mario mario;
	Casa casa;
	
	mario.Inicializar();
	casa.Inicializar();
    
	setup();
	DibujarFondo();
	DibujarMenu();
	DibujarObstaculos();
	
	frame = 0;
	estado_menu = -1;
	
	do {
		
		SDL_GetMouseState(&mouseX, &mouseY);
	
		while (SDL_PollEvent (&evento)) {
			switch (evento.type) {
				case SDL_QUIT:
					return 0;
					break;
				
				case SDL_KEYDOWN:
					if (estado_menu == PLAY and not mario.usando_pila and not mario.esInicializado()) {
						std::cout << "asd\n" << std::endl;
						switch (evento.key.keysym.sym) {
							case SDLK_UP:
								if (mario.posY-1 >= 0 and mapa_virtual[mario.posY-1][mario.posX] == ESTADO_CAMINABLE) {
									mario.MoverMario(ARRIBA, casa);
								}
								break; /* Cierre de tecla arriba */
					
							case SDLK_DOWN:
								if (mario.posY+1 < PANTALLA_ALTO and mapa_virtual[mario.posY+1][mario.posX] == ESTADO_CAMINABLE) {
									mario.MoverMario(ABAJO, casa);
								}
								break; /* Cierre de tecla abajo */
					
							case SDLK_LEFT:
								if (mario.posX-1 >= 0 and mapa_virtual[mario.posY][mario.posX-1] == ESTADO_CAMINABLE) {
									mario.MoverMario(IZQ, casa);
								}
								break; /* Cierre tecla izq */
					
							case SDLK_RIGHT:
								if (mario.posX+1 < PANTALLA_ANCHO and mapa_virtual[mario.posY][mario.posX+1] == ESTADO_CAMINABLE) {
									mario.MoverMario(DER, casa);
								}
				                break; /* Cierre tecla der */
				                
				            case SDLK_BACKSPACE:
				            	if (not mario.pila_movimientos.empty()) {				            	
									mario.usando_pila = true;
				            	}
				                break;				                
						} /* Cierre del switch selector de tecla */
					}
                    break; /* Cierre de SDL_Keydown */
				
				case SDL_MOUSEBUTTONDOWN:
					switch(evento.button.button) {
						case SDL_BUTTON_WHEELUP:
							if (porcentaje_obstaculos < RANDOM_MAXIMO and estado_menu != PLAY) {
								porcentaje_obstaculos = porcentaje_obstaculos + 0.4;
								DibujarFondo ();
								DibujarObstaculos();
								mario.Inicializar();
								casa.Inicializar();
							}												
							break;				
						
						case SDL_BUTTON_WHEELDOWN:					
							if (porcentaje_obstaculos > RANDOM_MINIMO and estado_menu != PLAY) {
								porcentaje_obstaculos = porcentaje_obstaculos - 0.4;
								DibujarFondo ();
								DibujarObstaculos();
								mario.Inicializar();
								casa.Inicializar();
							}
							break;
						
						case SDL_BUTTON_LEFT:
							if (mouseX > PANTALLA_ANCHO * IMAGENES_DIMENSION + 2) {
								g = mouseY / IMAGENES_DIMENSION;							
								CambiarEstadoMenu (g);
							}
							else {
								switch (estado_menu) {
									case COLOCAR_MARIO:
										h = mouseY / IMAGENES_DIMENSION;
										g = mouseX / IMAGENES_DIMENSION;
										if (mapa_virtual[h][g] == ESTADO_CAMINABLE) {
											mario.ColocarMario(h, g, casa);
										}
										break;
									case COLOCAR_CASA:
										h = mouseY / IMAGENES_DIMENSION;
										g = mouseX / IMAGENES_DIMENSION;
										if (mapa_virtual[h][g] == ESTADO_CAMINABLE) {
											casa.ColocarCasa(h, g);
											mario.ColocarMario(h, g, casa);
										}
										break;
									case COLOCAR_ARBOL:
										h = mouseY / IMAGENES_DIMENSION;
										g = mouseX / IMAGENES_DIMENSION;
										if (mapa_virtual[h][g] == ESTADO_CAMINABLE and
											(mario.posX != g or mario.posY != h) and
											(casa.posX != g or casa.posY != h) ) {
											ColocarArbol(h, g);
										}
										break;
									case COLOCAR_ARENA:
										h = mouseY / IMAGENES_DIMENSION;
										g = mouseX / IMAGENES_DIMENSION;
										if (mapa_virtual[h][g] == ESTADO_ANIMADO and
											(mario.posX != g or mario.posY != h) and
											(casa.posX != g or casa.posY != h) ) {
											ColocarArena(h, g);
										}
										break;
								}
							}
							break;
					}					
					break;
			}
		}
		
		if (mario.usando_pila and (frame % 8) == 0 and estado_menu == PLAY) {
			mario.MoverMario(mario.pila_movimientos.top(), casa);
			mario.pila_movimientos.pop();
			if (mario.pila_movimientos.empty() or (mario.posX == casa.posX and mario.posY == casa.posY) ) {
				while (not mario.pila_movimientos.empty()) {
					mario.pila_movimientos.pop();
				}
				mario.usando_pila = false;
			}
		}
		
		/* ANIMAR las cosas */
		if (estado_menu == PLAY) {		
			/* Animar arbustos */
			subframe = frame / 8;
			for (g = 0; g < PANTALLA_ALTO; g++) {
				for (h = 0; h < PANTALLA_ANCHO; h++) {
					if (mapa_virtual [g][h] == ESTADO_ANIMADO) {
						rect.x = h * IMAGENES_DIMENSION;
						rect.y = g * IMAGENES_DIMENSION;
					
						SDL_BlitSurface (images [IMG_SAND_1], NULL, screen, &rect);
						SDL_BlitSurface (images [IMG_GRASS_1 + subframe], NULL, screen, &rect);
					}
				}
			}
			
			/* Animar Mario */
			mario.AnimarMario(((frame % 8) / 4));
		}
		
		frame++;
		if (frame > 31) frame = 0;
			
		SDL_Flip (screen);
		SDL_Delay (32);
		
	} while (1);
	
	return 0;
}

void setup (void) {
	SDL_Surface *carga;
	int g, bpp;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf (stderr,
			"Error: No se pudo inicializar el sistema de video\n"
			"El error devuelto por SDL es:\n"
			"%s\n", SDL_GetError());
		exit (1);
	}
	bpp = SDL_VideoModeOK ((IMAGENES_DIMENSION * PANTALLA_ANCHO) + IMAGENES_DIMENSION + 2, IMAGENES_DIMENSION * PANTALLA_ALTO, 16, 0);
	
	if (bpp == 0) {
		fprintf (stderr, "Error: No se pudo establecer el modo de video\n");
		exit (1);
	}
	
	screen = SDL_SetVideoMode ((IMAGENES_DIMENSION * PANTALLA_ANCHO) + IMAGENES_DIMENSION + 2, IMAGENES_DIMENSION * PANTALLA_ALTO, bpp, 0);
	
	for (g = 0; g < NUM_IMGS; g++) {
		carga = IMG_Load (images_names [g]);
		
		if (carga == NULL) {
			fprintf (stderr, "Error al cargar la imagen %s\n", images_names [g]);
			SDL_Quit ();
			exit (1);
		}
		
		images[g] = carga;
	}
	
	use_sound = 1;
	if (SDL_InitSubSystem (SDL_INIT_AUDIO) < 0) {
        fprintf (stderr, "Fallo al inicializar el audio, continuando...\n");
        use_sound = 0;
    }
    
    if (use_sound) {
        if (Mix_OpenAudio (22050, AUDIO_S16, 2, 4096) < 0) {
            fprintf (stderr, "Fallo al inicializar el mezclador, continuando...\n");
            use_sound = 0;
        }
    }

    if (use_sound) {
        mus_fondo = Mix_LoadMUS (MUS_MAPA_1);
        
        if (mus_fondo == NULL) {
            fprintf (stderr, "Fallo la musica de fondo %s\n", MUS_MAPA_1);
            SDL_Quit ();
            exit (1);
        }
    }
}

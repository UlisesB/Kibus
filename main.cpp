#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "time.h"

#include "sprites.h"
#include "mario.h"
#include "mapa.h"
#include "menu.h"

using namespace std;

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
				case SDL_MOUSEBUTTONDOWN:
					switch(evento.button.button) {
						case SDL_BUTTON_WHEELUP:
							if (porcentaje_obstaculos < RANDOM_MAXIMO and estado_menu != PLAY) {
								porcentaje_obstaculos = porcentaje_obstaculos + 0.4;
								DibujarFondo ();
								DibujarObstaculos();
								mario.Inicializar();
							}												
							break;				
						case SDL_BUTTON_WHEELDOWN:					
							if (porcentaje_obstaculos > RANDOM_MINIMO and estado_menu != PLAY) {
								porcentaje_obstaculos = porcentaje_obstaculos - 0.4;
								DibujarFondo ();
								DibujarObstaculos();
								mario.Inicializar();
							}
							break;
						case SDL_BUTTON_LEFT:
							if (mouseX > PANTALLA_ANCHO * IMAGENES_DIMENSION + 2) {
								g = mouseY / IMAGENES_DIMENSION;							
								CambiarEstadoMenu (g);
							}
							else {
								if (estado_menu == COLOCAR_MARIO) {
									h = mouseY / IMAGENES_DIMENSION;
									g = mouseX / IMAGENES_DIMENSION;
									if (mapa_virtual[h][g] & ESTADO_CAMINABLE) {
										mario.ColocarMario(h, g);
									}
								}
							}
							break;
					}					
					break;
			}
		}		
		
		/* ANIMAR las cosas */
		if (estado_menu == PLAY) {		
			/* Animar arbustos */
			subframe = frame / 8;
			for (g = 0; g < PANTALLA_ALTO; g++) {
				for (h = 0; h < PANTALLA_ANCHO; h++) {
					if (mapa_virtual [g][h] & ESTADO_ANIMADO) {
						rect.x = h * IMAGENES_DIMENSION;
						rect.y = g * IMAGENES_DIMENSION;
					
						SDL_BlitSurface (images [IMG_SAND_1], NULL, screen, &rect);
						SDL_BlitSurface (images [IMG_GRASS_1 + subframe], NULL, screen, &rect);
					}
				}
			}
			
			/* Animar Mario */
			mario.DibujarMario(((frame % 8) / 4));
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
	
	/*use_sound = 1;
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
        for (g = 0; g < NUM_SOUNDS; g++) {
            sounds [g] = Mix_LoadWAV (sound_names[g]);
            
            if (sounds [g] == NULL) {
                fprintf (stderr, "Fallo al cargar %s\n", sound_names [g]);
                SDL_Quit ();
                exit (1);
            }
            Mix_VolumeChunk (sounds[g], MIX_MAX_VOLUME / 2);
        }
        
        mus_fondo = Mix_LoadMUS (MUS_MAPA_1);
        
        if (mus_fondo == NULL) {
            fprintf (stderr, "Fallo la musica de fondo %s\n", MUS_MAPA_1);
            SDL_Quit ();
            exit (1);
        }
    }*/
}

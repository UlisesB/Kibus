#ifndef __SPRITES_H__
#define __SPRITES_H__

enum {
	IMG_SAND_1,
	
	IMG_GRASS_1,
	IMG_GRASS_2,
	IMG_GRASS_3,
	IMG_GRASS_4,
	
	IMG_HOUSE_YELLOW,
	
	IMG_MARIO_1,
	IMG_MARIO_2,
	
	IMG_START_1,
	
	IMG_YOSHI,
	
	NUM_IMGS
};

const char *images_names[NUM_IMGS] = {
	"sand-1.gif",
	
	"grass-1.gif",
	"grass-2.gif",
	"grass-3.gif",
	"grass-4.gif",
	
	"house-yellow.gif",
	
	"mario-1.gif",
	"mario-2.gif",
	
	"start.gif",
	
	"yoshi.gif"
};

enum {
	ESTADO_CAMINABLE,
	ESTADO_ANIMADO,
	ESTADO_BANDERIN_1,
	ESTADO_BANDERIN_2,
	ESTADO_BANDERIN_3,
	ESTADO_BANDERIN_4
};

SDL_Surface *images[NUM_IMGS];

#endif /* __SPRITES_H__ */

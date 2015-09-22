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
	
	IMG_COURSE_1_1,
	IMG_COURSE_1_2,
	
	IMG_COURSE_2_1,
	IMG_COURSE_2_2,
	
	IMG_COURSE_3_1,
	IMG_COURSE_3_2,
	
	IMG_COURSE_4_1,
	IMG_COURSE_4_2,
	
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
	
	"course1-1.gif",
	"course1-2.gif",
	
	"course2-1.gif",
	"course2-2.gif",
	
	"course3-1.gif",
	"course3-2.gif",
	
	"course4-1.gif",
	"course4-2.gif"
};

enum {
	ESTADO_CAMINABLE,
	ESTADO_ANIMADO,
	ESTADO_CASA
};

SDL_Surface *images[NUM_IMGS];

#endif /* __SPRITES_H__ */

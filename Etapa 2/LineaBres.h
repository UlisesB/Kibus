#ifndef __LINEABRES_H__
#define __LINEABRES_H__

#include "mapa.h"

#define swap(x,y,t) {t = x; x = y; y = t;}
 
void LineaBres (Mario *mario, Casa casa, int *newX, int *newY) {
    int x, y, dx, dy, p, incE, incNE, stepx, stepy;
    
    int x0 = mario->posX;
	int y0 = mario->posY;
    int x1 = casa.posX;
    int y1 = casa.posY;
    
    dx = (x1 - x0);
    dy = (y1 - y0);
 
    /* determinar que punto usar para empezar, cual para terminar */
    if (dy < 0) {
        dy = -dy;
        stepy = -1;
    }
    else {
        stepy = 1;
    }
 
    if (dx < 0) { 
        dx = -dx; 
        stepx = -1;
    }
    else {
        stepx = 1;
    }
    x = x0;
    y = y0;
    *newX = x;
    *newY = y;
    if (dx > dy) {
        p = 2*dy - dx;
        incE = 2*dy;
        incNE = 2*(dy - dx);
        while (x != x1) {
            x = x + stepx;
            if (p < 0) {
                p = p + incE;
            }
            else {
                y = y + stepy;
                p = p + incNE;
            }
            *newX = x;
            *newY = y;
            return;
        }
    }
    else {
        p = 2*dx - dy;
        incE = 2*dx;
        incNE = 2*(dx - dy);
        while (y != y1) {
            y = y + stepy;
            if (p < 0) {
                p = p + incE;
            }
            else {
                x = x + stepx;
                p = p + incNE;
            }
            *newX = x;
            *newY = y;
            return;
        }
    }
}

#endif

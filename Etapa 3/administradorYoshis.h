#ifndef __ADMINISTRADORYOSHIS_H__
#define __ADMINISTRADORYOSHIS_H__

#include "yoshi.h"
#include <iostream>

#define YOSHIS 5

using namespace std;

class AdminYoshi {
	public:
		Yoshi yoshi[YOSHIS];
		RegistroMovimiento camino[6];
		int etapa, lugar_recorrido;
		struct {
			int numero;
			int calor;
		} yoshi_ganador;
		int direccion; /*IDA = 1, VUELTA = 2*/
		
		void InicializarYoshis (int marioX, int marioY);
		void MoverYoshis ();
};

void AdminYoshi::InicializarYoshis (int marioX, int marioY) {
	for (int i = 0; i < YOSHIS; i++) {
		yoshi[i].posX = marioX;
		yoshi[i].posY = marioY;
	}
	etapa = 0;
	lugar_recorrido = 0;
	camino[0].posX = marioX;
	camino[0].posY = marioY;
	direccion = 1;
}

void AdminYoshi::MoverYoshis () {
	int newX, newY;
	
	switch (direccion) {
		case 1: /* IDA */
			if (lugar_recorrido <= etapa) {
				for(int i = 0; i < YOSHIS; i++) {
					yoshi[i].MoverYoshi(camino[lugar_recorrido].posX, camino[lugar_recorrido].posY);
				}
				mapa_calor[camino[lugar_recorrido].posY][camino[lugar_recorrido].posX] -= mapa_calor[camino[lugar_recorrido].posY][camino[lugar_recorrido].posX] > 0 ? 1 : 0;
				lugar_recorrido++;
			}
			else {
				for(int i = 0; i < YOSHIS; i++) {
					yoshi[i].MovimientoAleatorio(&newX, &newY);
					yoshi[i].MoverYoshi(newX, newY);
					yoshi[i].TomarMuestra();
//					cout << yoshi[i].prueba.calor << " " << yoshi[i].prueba.posX << "," << yoshi[i].prueba.posY << endl;
//					cout << "-" << endl;
				}
				direccion = 2;
			}			
			
			break;
			
		case 2: /* VUELTA */
			lugar_recorrido--;
			for(int i = 0; i < YOSHIS; i++) {
				yoshi[i].MoverYoshi(camino[lugar_recorrido].posX, camino[lugar_recorrido].posY);
			}
			if (lugar_recorrido == 0) {
				yoshi_ganador.numero = 0;
				yoshi_ganador.calor = -1;
				for (int i = 0; i < YOSHIS; i++) {
					if (yoshi[i].prueba.calor > yoshi_ganador.calor) {
						yoshi_ganador.numero = i;
						yoshi_ganador.calor = yoshi[i].prueba.calor;
					}					
				}
				etapa += 1;
				direccion = 1;				
				camino[etapa].posX = yoshi[yoshi_ganador.numero].prueba.posX;
				camino[etapa].posY = yoshi[yoshi_ganador.numero].prueba.posY;
				camino[etapa].calor = yoshi[yoshi_ganador.numero].prueba.calor;
//				cout << "----------" << endl;
//				cout << etapa << endl;
//				cout << yoshi[yoshi_ganador.numero].prueba.calor << " " << yoshi[yoshi_ganador.numero].prueba.posX << "," << yoshi[yoshi_ganador.numero].prueba.posY << endl<< endl;
//				
//				cout << camino[etapa].calor << " " << camino[etapa].posX << "," << camino[etapa].posY << endl<< endl;
//				cout << "----------" << endl;
			}
			break;
	}
}

#endif
















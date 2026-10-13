#pragma once
#include "Inclinacion_Politica.h"
#include <iostream>
using namespace std;

class Izquierda_Liberal : public Inclinacion_Politica
{
private:
public:
	Izquierda_Liberal();
	~Izquierda_Liberal();

	int evaluar(char respuesta1, char respuesta2, char respuesta3, char respuesta4);
};

Izquierda_Liberal::Izquierda_Liberal() : Inclinacion_Politica("Izquierda Liberal", 0, 0)
{
	//Ya se tienen los datos
}

Izquierda_Liberal::~Izquierda_Liberal()
{
	//Destructor Vacio
}

int Izquierda_Liberal::evaluar(char respuesta1, char respuesta2, char respuesta3, char respuesta4)
{
	puntaje = 0;

	if (respuesta1 == 'N')
	{
		puntaje = puntaje + 1;
	}

	if (respuesta3 == 'S')
	{
		puntaje = puntaje + 1;
	}

	return puntaje;
}
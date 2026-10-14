#pragma once
#include "Inclinacion_Politica.h"
#include <iostream>
using namespace std;

//Relacion: Derecha_Liberal hereda de Inclinacion_Politica
class Derecha_Liberal : public Inclinacion_Politica
{
private:
public:
	Derecha_Liberal();
	~Derecha_Liberal();

	int evaluar(char respuesta1, char respuesta2, char respuesta3, char respuesta4);
};

Derecha_Liberal::Derecha_Liberal() : Inclinacion_Politica("Derecha Liberal", 0, 0)
{
	//Ya se tienen los datos
}

Derecha_Liberal::~Derecha_Liberal()
{
	//Destructor vacio
}

int Derecha_Liberal::evaluar(char respuesta1, char respuesta2, char respuesta3, char respuesta4)
{
	puntaje = 0;

	if (respuesta1 == 'N')
	{
		puntaje = puntaje + 1;
	}

	if (respuesta2 == 'S')
	{
		puntaje = puntaje + 1;
	}

	return puntaje;
}
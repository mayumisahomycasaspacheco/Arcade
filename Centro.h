#pragma once
#include "Inclinacion_Politica.h"
#include <iostream>
using namespace std;

class Centro : public Inclinacion_Politica
{
private:
public:
	Centro();
	~Centro();

	int evaluar(char respuesta1, char respuesta2, char respuesta3, char respuesta4);
};

Centro::Centro() : Inclinacion_Politica("Centro", 0, 0)
{
	//Ya estan los datos
}

Centro::~Centro()
{
	//Destructor vacio
}

int Centro::evaluar(char respuesta1, char respuesta2, char respuesta3, char respuesta4)
{
	puntaje = 0;

	if (respuesta4 == 'S')
	{
		puntaje = puntaje + 1;
	}

	return puntaje;
}
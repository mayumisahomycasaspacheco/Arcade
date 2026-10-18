#pragma once
#include <iostream>
#include "Inclinacion_Politica.h"
using namespace std;

class Derecha_Conservadora : public Inclinacion_Politica
{
private:
public:
	Derecha_Conservadora();
	~Derecha_Conservadora();

	int evaluar(char respuesta1, char respuesta2, char respuesta3, char respuesta4);
	string descripcion();
};

Derecha_Conservadora::Derecha_Conservadora() : Inclinacion_Politica("Conservative Right", 0, 0)
{
	//Ya se tienen los datos
}

Derecha_Conservadora::~Derecha_Conservadora()
{
	//Destructor Vacio
}

int Derecha_Conservadora::evaluar(char respuesta1, char respuesta2, char respuesta3, char respuesta4)
{
	puntaje = 0;

	if (respuesta1 == 'Y')
	{
		puntaje = puntaje + 1;
	}

	if (respuesta2 == 'Y')
	{
		puntaje = puntaje + 1;
	}

	return puntaje;

}

string Derecha_Conservadora::descripcion()
{
	return "Values tradition, order and the role of values in public life. Usually supports the State acting on moral principles.";
}

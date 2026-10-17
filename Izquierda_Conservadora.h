#pragma once
#include <iostream>
#include "Inclinacion_Politica.h"
using namespace std;

class Izquierda_Conservadora : public Inclinacion_Politica
{
private:
public:
	Izquierda_Conservadora();
	~Izquierda_Conservadora();

	int evaluar(char respuesta1, char respuesta2, char respuesta3, char respuesta4);
	string descripcion();
};

Izquierda_Conservadora::Izquierda_Conservadora() : Inclinacion_Politica("Izquierda Conservadora", 0, 0)
{
	//Ya se tienen los datos
}

Izquierda_Conservadora::~Izquierda_Conservadora()
{
	//Destructor vacio
}

int Izquierda_Conservadora::evaluar(char respuesta1, char respuesta2, char respuesta3, char respuesta4)
{
	puntaje = 0;

	if (respuesta1 == 'N')
	{
		puntaje = puntaje + 1;
	}

	if (respuesta2 == 'N')
	{
		puntaje = puntaje + 1;
	}

	return puntaje;

}

string Izquierda_Conservadora::descripcion()
{
	return "Une la busqueda de igualdad social con posturas culturales tradicionales. Desconfia de mezclar Estado, religion y valores impuestos.";
}
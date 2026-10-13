#pragma once
#include <iostream>
using namespace std;

class Inclinacion_Politica
{
protected:
	string nombre;
	int puntaje;
	int cantidad;
public:
	Inclinacion_Politica(string pnombre, int ppuntaje, int pcantidad);
	~Inclinacion_Politica();

	string getnombre();
	int getpuntaje();
	int getcantidad();

	void setnombre(string pnombre);
	void setpuntaje(int ppuntaje);
	void setcantidad(int pcantidad);
};

Inclinacion_Politica::Inclinacion_Politica(string pnombre, int ppuntaje, int pcantidad)
{
	nombre = pnombre;
	puntaje = ppuntaje;
	cantidad = pcantidad;
}

Inclinacion_Politica::~Inclinacion_Politica()
{
	//Destructor vacio
}

string Inclinacion_Politica::getnombre()
{
	return nombre;
}

int Inclinacion_Politica::getpuntaje()
{
	return puntaje;
}

int Inclinacion_Politica::getcantidad()
{
	return cantidad;
}

void Inclinacion_Politica::setnombre(string pnombre)
{
	nombre = pnombre;
}

void Inclinacion_Politica::setpuntaje(int ppuntaje)
{
	puntaje = ppuntaje;
}

void Inclinacion_Politica::setcantidad(int pcantidad)
{
	cantidad = pcantidad;
}
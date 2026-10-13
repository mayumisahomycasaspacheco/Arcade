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
};

Izquierda_Conservadora::Izquierda_Conservadora() : Inclinacion_Politica("Izquierda Conservadora", 0, 0)
{
	//Ya se tienen los datos
}

Izquierda_Conservadora::~Izquierda_Conservadora()
{
	//Destructor vacio
}
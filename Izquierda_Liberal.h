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
};

Izquierda_Liberal::Izquierda_Liberal() : Inclinacion_Politica("Izquierda Liberal", 0, 0)
{
	//Ya se tienen los datos
}

Izquierda_Liberal::~Izquierda_Liberal()
{
	//Destructor Vacio
}
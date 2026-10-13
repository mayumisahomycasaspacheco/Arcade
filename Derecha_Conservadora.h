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
};

Derecha_Conservadora::Derecha_Conservadora() : Inclinacion_Politica("Derecha Conservadora", 0, 0)
{
	//Ya se tienen los datos
}

Derecha_Conservadora::~Derecha_Conservadora()
{
	//Destructor Vacio
}
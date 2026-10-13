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
};

Derecha_Liberal::Derecha_Liberal() : Inclinacion_Politica("Derecha Liberal", 0, 0)
{
	//Ya se tienen los datos
}

Derecha_Liberal::~Derecha_Liberal()
{
	//Destructor vacio
}
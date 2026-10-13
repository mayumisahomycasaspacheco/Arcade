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
};

Centro::Centro() : Inclinacion_Politica("Centro", 0, 0)
{
	//Ya estan los datos
}

Centro::~Centro()
{
	//Destructor vacio
}
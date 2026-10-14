#pragma once
#include "Suscripcion.h"
#include <iostream>
using namespace std;

class Suscripcion_Video : public Suscripcion
{
private:
	string resolucion;
	int numero_pantallas;
	bool premium;
public:
	Suscripcion_Video();
	~Suscripcion_Video();
};
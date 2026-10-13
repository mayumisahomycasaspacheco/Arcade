#pragma once
#include "Solicitud.h"
#include "Derecha_Conservadora.h"
#include "Derecha_Liberal.h"
#include "Izquierda_Conservadora.h"
#include "Izquierda_Liberal.h"
#include "Centro.h"
#include <iostream>
using namespace std;

class Robot
{
private:
	Inclinacion_Politica* inclinacion[5];
	Solicitud** solicitud;
	int encuestados;
public:
	Robot();
	~Robot();
};

Robot::Robot()
{

}
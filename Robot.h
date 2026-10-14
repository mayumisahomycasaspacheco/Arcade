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

	void agregar_solicitud(Solicitud* psolicitud);
	void ingresar_datos();
	void reporte();
};

Robot::Robot()
{
	inclinacion[0] = new Derecha_Conservadora();
	inclinacion[1] = new Derecha_Liberal();
	inclinacion[2] = new Izquierda_Conservadora();
	inclinacion[3] = new Izquierda_Liberal();
	inclinacion[4] = new Centro();

	solicitud = nullptr;
	encuestados = 0;
}

Robot::~Robot()
{
	for (int i = 0; i < 5; i++)
	{
		delete inclinacion[i];
	}

	for (int i = 0; i < encuestados; i++)
	{
		delete solicitud[i];
	}

	if (solicitud != nullptr)
	{
		delete [] solicitud;
	}
}

void Robot::agregar_solicitud(Solicitud* psolicitud)
{
	Solicitud** temporal = new Solicitud * [encuestados + 1];

	for (int i = 0; i < encuestados; i++)
	{
		temporal[i] = solicitud[i];
	}

	temporal[encuestados] = psolicitud;

	encuestados = encuestados + 1;

	if (solicitud != nullptr)
	{
		delete[] solicitud;
	}

	solicitud = temporal;
}

void Robot::ingresar_datos()
{
	char respuesta1, respuesta2, respuesta3, respuesta4;
	
	cout << "ROBOT POLITICO" << endl;
	cout << "Responde las siguientes preguntas" << endl;

	cout << "El estado debe financiar la iglesia? [S] Si, [N] No, [X] No sabe: " << endl;
	cin >> respuesta1;
	cout << "El estado actua con valores a la hora de gobernar? [S] Si, [N] No, [X] No sabe: " << endl;
	cin >> respuesta2;
	cout << "El estado tiene en cuenta a todas las iglesias? [S] Si, [N] No, [X] No sabe: " << endl;
	cin >> respuesta3;
	cout << "Usted tiene la mentalidad abierta? [S] Si, [N] No, [X] No sabe: " << endl;
	cin >> respuesta4;

	int puntaje_mayor = 0;

	for (int i = 0; i < 5; i++)
	{
		inclinacion[i]->evaluar(respuesta1, respuesta2, respuesta3, respuesta4);
		
		if (inclinacion[i]->getpuntaje() > puntaje_mayor)
		{
			puntaje_mayor = inclinacion[i]->getpuntaje();
		}
	}

	string resultado = "";

	cout << "RESULTADO" << endl;

	if (puntaje_mayor == 0)
	{
		cout << "No se pudo determinar su inlinación política" << endl;
		resultado = "Sin determinar";
	}
	else
	{
		cout << "Su inclinacion politica puede ser: " << endl;

		for (int i = 0; i < 5; i++)
		{
			if (inclinacion[i]->getpuntaje() == puntaje_mayor)
			{
				cout << inclinacion[i]->getnombre() << endl;
				resultado = resultado + inclinacion[i]->getnombre() + " ";
				inclinacion[i]->setcantidad(inclinacion[i]->getcantidad() + 1);
			}
		}
	}

	Solicitud* psolicitud = new Solicitud(respuesta1, respuesta2, respuesta3, respuesta4, resultado);
	agregar_solicitud(psolicitud);
}

void Robot::reporte()
{
	cout << "ROBOT POLÍTICO" << endl;
	cout << "REPORTE TOTAL: " << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << inclinacion[i]->getnombre() << ":" << inclinacion[i]->getcantidad() << " encuestados" << endl;
	}

	cout << "Total de personas atendidas: " << encuestados << endl;
}
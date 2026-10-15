#pragma once
#include "Suscripcion.h"
#include <iostream>
using namespace std;

class Suscripcion_Gaming : public Suscripcion
{
private:
	string plataforma;
	bool acceso_beta;
	int almacenamiento_nube;
public:
	Suscripcion_Gaming(int pid, int pdia, int pmes, int panio, double ptarifa_base, string pusuario, string pcorreo, string pplataforma, bool pacceso_beta, int palmacenamiento_nube);
	~Suscripcion_Gaming();

	string getplataforma();
	bool getacceso_beta();
	int getalmacenamiento_nube();

	void setplataforma(string pplataforma);
	void setacceso_beta(bool pacceso_beta);
	void setalmacenamiento_nube(int palmacenamiento_nube);

	double calcular_importe();
	void mostrar_detalles();
	string gettipo();
};

Suscripcion_Gaming::Suscripcion_Gaming(int pid, int pdia, int pmes, int panio, double ptarifa_base, string pusuario, string pcorreo, string pplataforma, bool pacceso_beta, int palmacenamiento_nube) : Suscripcion(pid, pdia, pmes, panio, ptarifa_base, pusuario, pcorreo)
{
	plataforma = pplataforma;
	acceso_beta = pacceso_beta;
	almacenamiento_nube = palmacenamiento_nube;
}

Suscripcion_Gaming::~Suscripcion_Gaming()
{
	//Destructor_Vacio
}

string Suscripcion_Gaming::getplataforma()
{
	return plataforma;
}

bool Suscripcion_Gaming::getacceso_beta()
{
	return acceso_beta;
}

int Suscripcion_Gaming::getalmacenamiento_nube()
{
	return almacenamiento_nube;
}

void Suscripcion_Gaming::setplataforma(string pplataforma)
{
	plataforma = pplataforma;
}

void Suscripcion_Gaming::setacceso_beta(bool pacceso_beta)
{
	acceso_beta = pacceso_beta;
}

void Suscripcion_Gaming::setalmacenamiento_nube(int palmacenamiento_nube)
{
	almacenamiento_nube = palmacenamiento_nube;
}

double Suscripcion_Gaming::calcular_importe()
{
	double total = tarifa_base;

	if (acceso_beta)
	{
		total = total + 5;
	}

	total = total + almacenamiento_nube * 0.1;
	return total;
}
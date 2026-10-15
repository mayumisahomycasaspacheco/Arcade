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
	Suscripcion_Video(int pid, int pdia, int pmes, int panio, double ptarifa_base, string pusuario, string pcorreo, string presolucion, int pnumero_pantallas, bool ppremium);
	~Suscripcion_Video();

	string getresolucion();
	int getnumero_pantallas();
	bool getpremium();
	void setresolucion(string presolucion);
	void setnumero_pantallas(int numero_pantallas);
	void setpremium(bool ppremium);

	double calcular_importe();
	void mostrar_detalles();
	string gettipo();
};

Suscripcion_Video::Suscripcion_Video(int pid, int pdia, int pmes, int panio, double ptarifa_base, string pusuario, string pcorreo, string presolucion, int pnumero_pantallas, bool ppremium) : Suscripcion(pid, pdia, pmes, panio, ptarifa_base, pusuario, pcorreo)
{
	resolucion = presolucion;
	numero_pantallas = pnumero_pantallas;
	premium = ppremium;
}

Suscripcion_Video::~Suscripcion_Video()
{
	//Destructor vacio
}

string Suscripcion_Video::getresolucion()
{
	return resolucion;
}

int Suscripcion_Video::getnumero_pantallas()
{
	return numero_pantallas;
}

bool Suscripcion_Video::getpremium()
{
	return premium;
}

void Suscripcion_Video::setresolucion(string presolucion)
{
	resolucion = presolucion;
}

void Suscripcion_Video::setnumero_pantallas(int pnumero_pantallas)
{
	numero_pantallas = pnumero_pantallas;
}

void Suscripcion_Video::setpremium(bool ppremium)
{
	premium = ppremium;
}

double Suscripcion_Video::calcular_importe()
{
	double total = tarifa_base;

	if (resolucion == "4K")
	{
		total = total + 10;
	}

	if (numero_pantallas > 1)
	{
		total = total + (numero_pantallas - 1) * 2;
	}

	if (premium)
	{
		total = total + 3;
	}

	return total;
}

void Suscripcion_Video::mostrar_detalles()
{
	cout << "[SERVICIO DE VIDEO]" << endl;
	Suscripcion::mostrar_detalles();
	cout << "Resolucion: " << resolucion << " | Pantallas: " << numero_pantallas << " | Importe Final: S/ " << calcular_importe() << endl;
}
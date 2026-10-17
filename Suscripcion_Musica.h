#pragma once
#include "Suscripcion.h"
#include <iostream>
using namespace std;

class Suscripcion_Musica : public Suscripcion
{
private:
	string calidad_audio;
	bool modo_offline;
public:
	Suscripcion_Musica(int pid, int pdia, int pmes, int panio, double ptarifa_base, string pusuario, string pcorreo, string pcalidad_audio, bool pmodo_ofline);
	~Suscripcion_Musica();

	string getcalidad_audio();
	bool getmodo_offline();
	void setcalidad_audio(string calidad_audio);
	void setmodo_offline(bool modo_offline);

	double calcular_importe();
	void mostrar_detalles();
	string gettipo();
};

Suscripcion_Musica::Suscripcion_Musica(int pid, int pdia, int pmes, int panio, double ptarifa_base, string pusuario, string pcorreo, string pcalidad_audio, bool pmodo_offline) : Suscripcion(pid, pdia, pmes, panio, ptarifa_base, pusuario, pcorreo)
{
	calidad_audio = pcalidad_audio;
	modo_offline = pmodo_offline;
}

Suscripcion_Musica::~Suscripcion_Musica()
{
	//Destructor Vacio
}

string Suscripcion_Musica::getcalidad_audio()
{
	return calidad_audio;
}

bool Suscripcion_Musica::getmodo_offline()
{
	return modo_offline;
}

void Suscripcion_Musica::setcalidad_audio(string pcalidad_audio)
{
	calidad_audio = pcalidad_audio;
}

void Suscripcion_Musica::setmodo_offline(bool pmodo_offline)
{
	modo_offline = pmodo_offline;
}

double Suscripcion_Musica::calcular_importe()
{
	double total = tarifa_base;


	if (calidad_audio == "Alta")
	{
		total = total + 3;
	}

	else if (calidad_audio == "HiFi")
	{
		total = total + 6;
	}

	if (modo_offline)
	{
		total = total + 4;
	}

	return total;
}

void Suscripcion_Musica::mostrar_detalles()
{
	cout << "[SERVICIO MUSICA]" << endl;
	Suscripcion::mostrar_detalles();
	cout << "Calidad Audio: " << calidad_audio << " | Offline: " << (modo_offline ? "Si" : "No") << " | Importe Final: S/ " << calcular_importe() << endl;
}

string Suscripcion_Musica::gettipo()
{
	return "MUSICA";
}
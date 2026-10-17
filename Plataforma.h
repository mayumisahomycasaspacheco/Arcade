#pragma once
#include <iostream>
#include "Suscripcion.h"
#include "Suscripcion_Video.h"
#include "Suscripcion_Musica.h"
#include "Suscripcion_Gaming.h"
using namespace std;

class Plataforma
{
private:
	Suscripcion** suscripcion;
	int cantidad;
	void agregar_a_lista(Suscripcion* psuscripcion);
	bool existe_id(int pid);
	double leer_decimal(string pmensaje);
	bool leer_si_no(string pmensaje);
	void leer_fecha(int& pdia, int& pmes, int& panio);
public:
	Plataforma();
	~Plataforma();
	int getcantidad();
	int leer_entero(string pmensaje, int pminimo, int pmaximo);
	void agregar_suscripcion();
	void listar_todo();
	void buscar_por_id(int pid_busqueda);
	void reporte_por_tipo();
};

Plataforma::Plataforma()
{
	suscripcion = nullptr;
	cantidad = 0;
}

Plataforma::~Plataforma()
{
	if (suscripcion != nullptr)
	{
		for (int i = 0; i < cantidad; i++)
		{
			delete suscripcion[i];
		}

		delete[] suscripcion;
	}
}
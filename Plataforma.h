#pragma once
#include <iostream>
#include <string>
#include <cctype>
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

int Plataforma::getcantidad()
{
	return cantidad;
}

void Plataforma::agregar_a_lista(Suscripcion* psuscripcion)
{
	Suscripcion** lista_nueva = new Suscripcion * [cantidad + 1];
	
	for (int i = 0; i < cantidad; i++)
	{
		lista_nueva[i] = suscripcion[i];
	}

	lista_nueva[cantidad] = psuscripcion;
	
	if (suscripcion != nullptr)
	{
		delete[] suscripcion;
	}

	suscripcion = lista_nueva;
	cantidad++;
}

bool Plataforma::existe_id(int pid)
{
	for (int i = 0; i < cantidad; i++)
	{
		if (suscripcion[i]->getid() == pid)
		{
			return true;
		}
	}

	return false;
}

int Plataforma::leer_entero(string pmensaje, int pminimo, int pmaximo)
{
	int valor;
	
	cout << pmensaje;

	while (!(cin >> valor) || valor < pminimo || valor > pmaximo)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Error: Ingrese un numero entero entre " << pminimo << " y " << pmaximo << "." << endl;
		cout << pmensaje;
	}

	cin.ignore(10000, '\n');
	
	return valor;
}

double Plataforma::leer_decimal(string pmensaje)
{
	double valor;

	cout << pmensaje;

	while (!(cin >> valor) || valor < 0)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Error: Ingrese un numero valido (mayor o igual a 0)." << endl;
		cout << pmensaje;
	}

	cin.ignore(10000, '\n');
	return valor;
}

bool Plataforma::leer_si_no(string pmensaje)
{
	string r;
	cout << pmensaje;
	cin >> r;

	cin.ignore(10000, '\n');
	while (r != "S" && r != "s" && r != "N" && r != "n")
	{
		cout << "Error: Ingrese S o N." << endl;
		cout << pmensaje;
		cin >> r;
		cin.ignore(10000, '\n');
	}

	return (r == "S" || r == "s");
}

void Plataforma::leer_fecha(int& pdia, int& pmes, int& panio)
{
	bool valida = false;

	do
	{
		cout << "Fecha (dd mm aaaa): ";
		if (cin >> pdia >> pmes >> panio)
		{
			if (pdia >= 1 && pdia <= 31 && pmes >= 1 && pmes <= 12 && panio >= 1900 && panio <= 2100)
			{
				valida = true;
			}

			else
			{
				cout << "Error: Fechas fuera de rango." << endl;
			}
		}

		else
		{
			cin.clear();
			cout << "Error: Ingrese tres numeros (dd mm aaaa)." << endl;
		}

		cin.ignore(10000, '\n');
	}

	while (true);
}


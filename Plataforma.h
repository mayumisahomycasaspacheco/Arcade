#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
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
	bool fecha_valida(int pdia, int pmes, int panio);
	double ingresos_totales();
	int nivel_para(double ptotal);
	double umbral_nivel(int pnivel);
	string nombre_nivel(int pnivel);
public:
	Plataforma();
	~Plataforma();
	int getcantidad();
	int leer_entero(string pmensaje, int pminimo, int pmaximo);
	void agregar_suscripcion();
	void listar_todo();
	void buscar_por_id(int pid_busqueda);
	void reporte_por_tipo();
	void panel_imperio();
	void eliminar_suscripcion();
	void cargar_demo();
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

void Plataforma::agregar_suscripcion()
{
	int tipo = leer_entero("Tipo de Suscripcion: [1] Video [2] Musica [3] Gaming: ", 1, 3);
	int id = leer_entero("ID: ", 1, 2147483647);
	if (existe_id(id))
	{
		cout << "Error, ya existe una suscripcion con ede ID." << endl;
		return;
	}

	string usuario;
	string correo;
	int dia;
	int mes;
	int anio;

	cout << "Usuario: ";
	cin >> usuario;
	cout << "Correo: ";
	cin >> correo;
	cin.ignore(10000, '\n');
	leer_fecha(dia, mes, anio);
	double tarifa = leer_decimal("Tarifa Base: ");

	if (tipo == 1)
	{
		string resolucion;
		cout << "Resolucion (HD/4k): ";
		cin >> resolucion;
		cin.ignore(10000, '\n');
		
		for (int i = 0; i < (int)resolucion.size(); i++)
		{
			resolucion[i] = toupper(resolucion[i]);
		}

		while (resolucion != "HD" && resolucion != "4k")
		{
			cout << "Error: Ingrese HD o 4K." << endl;
			cout << "Resolucion (HD/4K): ";
			cin >> resolucion;
			cin.ignore(10000, '\n');
			for (int i = 0; i < (int)resolucion.size(); i++)
			{
				resolucion[i] = toupper(resolucion[i]);
			}
		}

		int pantallas = leer_entero("Numero de Pantallas: ", 1, 10);
		bool premium = leer_si_no("Premium (S/N): ");
		agregar_a_lista(new Suscripcion_Video(id, dia, mes, anio, tarifa, usuario, correo, resolucion, pantallas, premium));
		
	}

	else
	{
		string plataforma;
		cout << "Plataforma (PC/Consola): ";
		cin >> plataforma;
		cin.ignore(10000, '\n');
		bool beta = leer_si_no("Acceso Beta (S/N): ");
		int nube = leer_entero("Almacenamiento Nube (GB): ", 0, 10000);
		agregar_a_lista(new Suscripcion_Gaming(id, dia, mes, anio, tarifa, usuario, correo, plataforma, beta, nube));
	}

	cout << "Suscripcion registrada correctamente." << endl;
}

void Plataforma::listar_todo()
{
	if (cantidad == 0)
	{
		cout << "No hay suscripciones registradas." << endl;
		return;
	}

	for (int i = 0; i < cantidad; i++)
	{
		suscripcion[i]->mostrar_detalles();
		cout << endl;
	}

}

void Plataforma::buscar_por_id(int pid_busqueda)
{
	for (int i = 0; i < cantidad; i++)
	{
		if (suscripcion[i]->getid() == pid_busqueda)
		{
			cout << endl;
			suscripcion[i]->mostrar_detalles();
			return;
		}
	}

	cout << "Error: ID no encontrado" << endl;
}

void Plataforma::reporte_por_tipo()
{
	int tipo = leer_entero("Filtrar: [1] Video [2] Musica [3] Gaming: ", 1, 3);
	string nombre;
	if (tipo == 1)
	{
		nombre = "VIDEO";
	}

	else if (tipo == 2)
	{
		nombre = "MUSICA";
	}

	else
	{
		nombre = "GAMING";
	}

	double total = 0;
	int encontrados = 0;
	cout << " " << endl;

	for (int i = 0; i < cantidad; i++)
	{
		if (suscripcion[i]->gettipo() == nombre)
		{
			suscripcion[i]->mostrar_detalles();
			cout << " " << endl;
			total = total + suscripcion[i]->calcular_importe();
			encontrados++;
		}
	}

	if (encontrados == 0)
	{
		cout << "No hay suscripciones de tipo " << nombre << "." << endl;
	}

	else
	{
		cout << "Total recaudado en " << nombre << ": S/ " << total << endl;
	}
}

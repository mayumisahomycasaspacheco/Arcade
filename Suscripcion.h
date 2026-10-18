#pragma once
#include <iostream>
#include <string>
#include "Utilidades.h"
using namespace std;

class Suscripcion
{
protected:
	int id;
	int dia, mes, anio;
	double tarifa_base;
	string usuario;
	string correo;
public:
	Suscripcion(int pid, int pdia, int pmes, int panio, double ptarifa_base, string pusuario, string pcorreo);
	virtual ~Suscripcion();

	int getid();
	int getdia();
	int getmes();
	int getanio();
	double gettarifa_base();
	string getusuario();
	string getcorreo();

	void setid(int pid);
	void setdia(int pdia);
	void setmes(int pmes);
	void setanio(int panio);
	void settarifa_base(double ptarifa_base);
	void setusuario(string pusuario);
	void setcorreo(string pcorreo);

	virtual double calcular_importe() = 0;
	virtual void mostrar_detalles();
	virtual string gettipo() = 0;
};

Suscripcion::Suscripcion(int pid, int pdia, int pmes, int panio, double ptarifa_base, string pusuario, string pcorreo)
{
	id = pid;
	dia = pdia;
	mes = pmes;
	anio = panio;
	tarifa_base = ptarifa_base;
	usuario = pusuario;
	correo = pcorreo;
}

Suscripcion::~Suscripcion()
{
	//Destructor Vacio
}

int Suscripcion::getid()
{
	return id;
}

int Suscripcion::getdia()
{
	return dia;
}

int Suscripcion::getmes()
{
	return mes;
}

int Suscripcion::getanio()
{
	return anio;
}

double Suscripcion::gettarifa_base()
{
	return tarifa_base;
}

string Suscripcion::getusuario()
{
	return usuario;
}

string Suscripcion::getcorreo()
{
	return correo;
}

void Suscripcion::setid(int pid)
{
	id = pid;
}

void Suscripcion::setdia(int pdia)
{
	dia = pdia;
}

void Suscripcion::setmes(int pmes)
{
	mes = pmes;
}

void Suscripcion::setanio(int panio)
{
	anio = panio;
}

void Suscripcion::settarifa_base(double ptarifa_base)
{
	tarifa_base = ptarifa_base;
}

void Suscripcion::setusuario(string pusuario)
{
	usuario = pusuario;
}

void Suscripcion::setcorreo(string pcorreo)
{
	correo = pcorreo;
}

void Suscripcion::mostrar_detalles()
{
	cout << C_AMARILLO << "ID: " << id << C_RESET << " | User: " << usuario << " | Date: " << dia << "/" << mes << "/" << anio << endl;
	cout << "Email: " << correo << " | Base Fee: S/ " << tarifa_base << endl;
}
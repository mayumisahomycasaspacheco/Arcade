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
};

Suscripcion_Gaming::Suscripcion_Gaming(int pid, int pdia, int pmes, int panio, double ptarifa_base, string pusuario, string pcorreo, string pplataforma, bool pacceso_beta, int palmacenamiento_nube) : Suscripcion(pid, pdia, pmes, panio, ptarifa_base, pusuario, pcorreo)
{
	plataforma = pplataforma;
	acceso_beta = pacceso_beta;
	almacenamiento_nube = palmacenamiento_nube;
}
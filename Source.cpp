#include<iostream>
#include "Derecha_Liberal.h"
#include "Derecha_Conservadora.h"
#include "Izquierda_Liberal.h"
#include "Izquierda_Conservadora.h"
#include "Centro.h"
#include "Robot.h"
#include "Windows.h"
#include "Suscripcion.h"
#include "Suscripcion_Video.h"
#include "Suscripcion_Musica.h"
#include "Suscripcion_Gaming.h"
#include "Plataforma.h"
using namespace std;
using namespace System;

int main()
{
	Robot robot;
	Plataforma plataforma;
	int opcion;
	int opcion1;
	int opcion2;

	do
	{
		cout << "ARCADE" << endl;
		cout << "1. Robot Politico" << endl;
		cout << "2. Simulacion de Streaming" << endl;
		cout << "Escoge una opcion: "; cin >> opcion;

		if (opcion == 1)
		{
			do
			{
				system("cls");

				cout << "===ROBOT POLITICO===" << endl;
				cout << "MENU" << endl;
				cout << "1. Ingresar datos" << endl;
				cout << "2. Reporte total" << endl;
				cout << "3. Salir" << endl;
				cout << "Eliga una opcion del menu: "; cin >> opcion1;

				if (opcion1 == 1)
				{
					system("cls");
					robot.ingresar_datos();
				}

				else if (opcion1 == 2)
				{
					system("cls");
					robot.reporte();
				}

				else
				{
					system("pause");
				}

				system("pause");
			}

			while (opcion1 != 3);
		}

		else if (opcion == 2)
		{
			do
			{
				system("cls");

				cout << "MENU STREAMING" << endl;
				cout << "==============" << endl;
				cout << "1. Registrar" << endl;
				cout << "2. Listar Todo" << endl;
				cout << "3. Buscar por ID" << endl;
				cout << "4. Reporte por tipo" << endl;
				cout << "5. Salir" << endl;

				if (opcion2 == 1)
				{
					system("cls");
					plataforma.agregar_suscripcion();
					system("pause");
				}

				else if (opcion2 == 2)
				{
					system("cls");
					plataforma.listar_todo();
					system("pause");
				}

				else if (opcion2 == 3)
				{
					system("cls");
					plataforma.buscar_por_id(plataforma.leer_entero("Ingrese ID a buscar: ", 1, 2147483647));
					system("pause");
				}

				else if (opcion2 == 4)
				{
					system("cls");
					plataforma.reporte_por_tipo();
					system("pause");
				}

				else
				{
					system("pause");
				}

				system("pause");

			}

			while (opcion2 != 5);
		}
	}

	while (opcion != 3);

	return 0;
}
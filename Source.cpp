#include<iostream>
#include "Derecha_Liberal.h"
#include "Derecha_Conservadora.h"
#include "Izquierda_Liberal.h"
#include "Izquierda_Conservadora.h"
#include "Centro.h"
#include "Robot.h"
#include "Windows.h"
using namespace std;
using namespace System;

int main()
{
	Robot robot;
	int opcion;

	do
	{
		system("cls");

		cout << "===ROBOT POLITICO===" << endl;
		cout << "MENU" << endl;
		cout << "1. Ingresar datos" << endl;
		cout << "2. Reporte total" << endl;
		cout << "3. Salir" << endl;
		cout << "Eliga una opcion del menu: "; cin >> opcion;

		if (opcion == 1)
		{
			system("cls");
			robot.ingresar_datos();
		}

		else if (opcion == 2)
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

	while (opcion != 3);

	return 0;
}
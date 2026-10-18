#pragma once
#include "Solicitud.h"
#include "Derecha_Conservadora.h"
#include "Derecha_Liberal.h"
#include "Izquierda_Conservadora.h"
#include "Izquierda_Liberal.h"
#include "Centro.h"
#include "Utilidades.h"
#include <iostream>
#include <iomanip>
using namespace std;

class Robot
{
private:
	Inclinacion_Politica* inclinacion[5];
	Solicitud** solicitud;
	int encuestados;
public:
	Robot();
	~Robot();

	int getencuestados();
	void agregar_solicitud(Solicitud* psolicitud);
	void mostrar_instrucciones();
	void ingresar_datos();
	void reporte();
	void historial();
};

Robot::Robot()
{
	inclinacion[0] = new Derecha_Conservadora();
	inclinacion[1] = new Derecha_Liberal();
	inclinacion[2] = new Izquierda_Conservadora();
	inclinacion[3] = new Izquierda_Liberal();
	inclinacion[4] = new Centro();

	solicitud = nullptr;
	encuestados = 0;
}

Robot::~Robot()
{
	for (int i = 0; i < 5; i++)
	{
		delete inclinacion[i];
	}

	for (int i = 0; i < encuestados; i++)
	{
		delete solicitud[i];
	}

	if (solicitud != nullptr)
	{
		delete[] solicitud;
	}
}

int Robot::getencuestados()
{
	return encuestados;
}

void Robot::agregar_solicitud(Solicitud* psolicitud)
{
	Solicitud** temporal = new Solicitud * [encuestados + 1];

	for (int i = 0; i < encuestados; i++)
	{
		temporal[i] = solicitud[i];
	}

	temporal[encuestados] = psolicitud;

	encuestados = encuestados + 1;

	if (solicitud != nullptr)
	{
		delete[] solicitud;
	}

	solicitud = temporal;
}

void Robot::mostrar_instrucciones()
{
	limpiar_pantalla();
	titulo("HOW IT WORKS: POLITICAL ROBOT", C_CIAN);
	cout << endl;
	cout << " The Political Robot asks you 4 quick questions and guesses" << endl;
	cout << " which political leaning you match the most." << endl << endl;
	cout << C_AMARILLO << " How to answer:" << C_RESET << endl;
	cout << "   Y = Yes    N = No    X = Don't know" << endl << endl;
	cout << C_AMARILLO << " What happens next:" << C_RESET << endl;
	cout << "   - Each stance adds points to one or more leanings." << endl;
	cout << "   - The one with the most points wins. If there is a tie, you'll" << endl;
	cout << "     have a mixed profile (that's allowed!)." << endl;
	cout << "   - If you answer X to everything, the robot can't decide." << endl << endl;
	cout << C_AMARILLO << " Extras:" << C_RESET << endl;
	cout << "   - Full report: ranking of everyone who took the test." << endl;
	cout << "   - History: the answers and result of each test." << endl << endl;
	cout << C_GRIS << " Note: this is a 4-question game, not a scientific study." << C_RESET << endl;
}

void Robot::ingresar_datos()
{
	string preguntas[4] = {
		"Should the state fund the church?",
		"Does the state act on values when governing?",
		"Does the state take all churches into account?",
		"Are you open-minded?"
	};
	char respuesta[4];

	limpiar_pantalla();
	titulo("POLITICAL ROBOT", C_CIAN);

	cout << C_CIAN << R"ART(
      ,-------.
     | [o] [o] |    Beep boop! I'm the Political Robot.
     |  \___/  |    I'm going to read your mind... or almost.
      '-------'
       /|   |\
)ART" << C_RESET << endl;

	cout << C_GRIS << "  Answer: Y = Yes | N = No | X = Don't know" << C_RESET << endl << endl;

	for (int i = 0; i < 4; i++)
	{
		cout << C_AMARILLO << "  Question " << (i + 1) << "/4  " << C_RESET << barra(i, 4, 12) << endl;
		cout << "  " << preguntas[i] << endl;
		respuesta[i] = leer_respuesta_sn_x("  > ");
		cout << endl;
	}

	char respuesta1 = respuesta[0];
	char respuesta2 = respuesta[1];
	char respuesta3 = respuesta[2];
	char respuesta4 = respuesta[3];

	cout << C_CIAN << "  Analyzing your answers" << C_RESET << flush;

	for (int i = 0; i < 3; i++)
	{
		esperar(350);
		cout << "." << flush;
	}

	esperar(300);
	cout << endl << endl;

	int puntaje_mayor = 0;

	for (int i = 0; i < 5; i++)
	{
		inclinacion[i]->evaluar(respuesta1, respuesta2, respuesta3, respuesta4);

		if (inclinacion[i]->getpuntaje() > puntaje_mayor)
		{
			puntaje_mayor = inclinacion[i]->getpuntaje();
		}
	}

	string resultado = "";

	titulo("RESULT", C_VERDE);
	cout << endl;

	if (puntaje_mayor == 0)
	{
		cout << C_AMARILLO << "  Your political leaning could not be determined." << C_RESET << endl;
		cout << "  With so many doubts the robot has nothing to work with. Try again!" << endl;
		resultado = "Undetermined";
	}
	else
	{
		int ganadoras = 0;

		for (int i = 0; i < 5; i++)
		{
			if (inclinacion[i]->getpuntaje() == puntaje_mayor)
			{
				ganadoras++;
			}
		}

		if (ganadoras == 1)
		{
			escribir_lento("  Your political leaning is...", 25);
			esperar(500);
			cout << endl << endl;
		}
		else
		{
			escribir_lento("  Mixed profile! You match equally with...", 25);
			esperar(500);
			cout << endl << endl;
		}

		for (int i = 0; i < 5; i++)
		{
			if (inclinacion[i]->getpuntaje() == puntaje_mayor)
			{
				cout << C_NEGRITA << C_AMARILLO << "  >> " << inclinacion[i]->getnombre() << C_RESET << endl;
				cout << "     " << inclinacion[i]->descripcion() << endl << endl;

				if (resultado != "")
				{
					resultado = resultado + " / ";
				}

				resultado = resultado + inclinacion[i]->getnombre();
				inclinacion[i]->setcantidad(inclinacion[i]->getcantidad() + 1);
			}
		}
	}

	cout << endl;
	separador();
	cout << C_GRIS << "  Points earned per leaning:" << C_RESET << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << "  " << left << setw(24) << inclinacion[i]->getnombre() << inclinacion[i]->getpuntaje() << " pt" << endl;
	}

	Solicitud* psolicitud = new Solicitud(respuesta1, respuesta2, respuesta3, respuesta4, resultado);
	agregar_solicitud(psolicitud);

	cout << endl << C_GRIS << "  Test #" << encuestados << " saved to the history." << C_RESET << endl;
}

void Robot::reporte()
{
	limpiar_pantalla();
	titulo("FULL REPORT", C_CIAN);
	cout << endl;

	if (encuestados == 0)
	{
		cout << "  No data yet. Take the test at least once!" << endl;
		return;
	}

	int maximo = 0;

	for (int i = 0; i < 5; i++)
	{
		if (inclinacion[i]->getcantidad() > maximo)
		{
			maximo = inclinacion[i]->getcantidad();
		}
	}

	for (int i = 0; i < 5; i++)
	{
		int cantidad = inclinacion[i]->getcantidad();
		int porcentaje = cantidad * 100 / encuestados;

		cout << "  " << left << setw(24) << inclinacion[i]->getnombre();

		if (cantidad == maximo && maximo > 0)
		{
			cout << C_AMARILLO;
		}

		cout << barra(cantidad, encuestados, 15) << C_RESET << " " << cantidad << " (" << porcentaje << "%)" << endl;
	}

	cout << endl;

	if (maximo > 0)
	{
		cout << C_VERDE << "  Dominant trend: " << C_RESET;
		bool primera = true;

		for (int i = 0; i < 5; i++)
		{
			if (inclinacion[i]->getcantidad() == maximo)
			{
				if (!primera)
				{
					cout << " / ";
				}

				cout << inclinacion[i]->getnombre();
				primera = false;
			}
		}

		cout << endl;
	}

	cout << "  Total people attended: " << encuestados << endl;
	cout << C_GRIS << "  (If there were ties, one person counts toward several leanings.)" << C_RESET << endl;
}

void Robot::historial()
{
	limpiar_pantalla();
	titulo("TEST HISTORY", C_CIAN);
	cout << endl;

	if (encuestados == 0)
	{
		cout << "  No tests recorded yet." << endl;
		return;
	}

	for (int i = 0; i < encuestados; i++)
	{
		cout << C_AMARILLO << "  #" << (i + 1) << C_RESET << "  Answers: "
			<< solicitud[i]->getrespuesta1() << " "
			<< solicitud[i]->getrespuesta2() << " "
			<< solicitud[i]->getrespuesta3() << " "
			<< solicitud[i]->getrespuesta4() << "  ->  " << solicitud[i]->getresultado() << endl;
	}
}

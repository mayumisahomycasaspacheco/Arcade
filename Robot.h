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
	titulo("COMO FUNCIONA: ROBOT POLITICO", C_CIAN);
	cout << endl;
	cout << " El Robot Politico te hace 4 preguntas rapidas y adivina" << endl;
	cout << " con que inclinacion politica coincides mas." << endl << endl;
	cout << C_AMARILLO << " Como se responde:" << C_RESET << endl;
	cout << "   S = Si    N = No    X = No sabe" << endl << endl;
	cout << C_AMARILLO << " Que pasa despues:" << C_RESET << endl;
	cout << "   - Cada postura suma puntos a una o mas inclinaciones." << endl;
	cout << "   - Gana la que tenga mas puntos. Si hay empate, tendras" << endl;
	cout << "     un perfil mixto (esta permitido!)." << endl;
	cout << "   - Si respondes X a todo, el robot no podra decidir." << endl << endl;
	cout << C_AMARILLO << " Extras:" << C_RESET << endl;
	cout << "   - Reporte total: ranking de todas las personas atendidas." << endl;
	cout << "   - Historial: las respuestas y el resultado de cada test." << endl << endl;
	cout << C_GRIS << " Nota: es un juego de 4 preguntas, no un estudio cientifico." << C_RESET << endl;
}

void Robot::ingresar_datos()
{
	string preguntas[4] = {
		"El estado debe financiar la iglesia?",
		"El estado actua con valores a la hora de gobernar?",
		"El estado tiene en cuenta a todas las iglesias?",
		"Usted tiene la mentalidad abierta?"
	};
	char respuesta[4];

	limpiar_pantalla();
	titulo("ROBOT POLITICO", C_CIAN);

	cout << C_CIAN << R"ART(
      ,-------.
     | [o] [o] |    Bip bop! Soy el Robot Politico.
     |  \___/  |    Voy a leer tu mente... o casi.
      '-------'
       /|   |\
)ART" << C_RESET << endl;

	cout << C_GRIS << "  Responde: S = Si | N = No | X = No sabe" << C_RESET << endl << endl;

	for (int i = 0; i < 4; i++)
	{
		cout << C_AMARILLO << "  Pregunta " << (i + 1) << "/4  " << C_RESET << barra(i, 4, 12) << endl;
		cout << "  " << preguntas[i] << endl;
		respuesta[i] = leer_respuesta_sn_x("  > ");
		cout << endl;
	}

	char respuesta1 = respuesta[0];
	char respuesta2 = respuesta[1];
	char respuesta3 = respuesta[2];
	char respuesta4 = respuesta[3];

	cout << C_CIAN << "  Analizando tus respuestas" << C_RESET << flush;

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

	titulo("RESULTADO", C_VERDE);
	cout << endl;

	if (puntaje_mayor == 0)
	{
		cout << C_AMARILLO << "  No se pudo determinar tu inclinacion politica." << C_RESET << endl;
		cout << "  Con tantas dudas el robot no tiene de donde agarrarse. Intenta otra vez!" << endl;
		resultado = "Sin determinar";
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
			escribir_lento("  Tu inclinacion politica es...", 25);
			esperar(500);
			cout << endl << endl;
		}
		else
		{
			escribir_lento("  Perfil mixto! Coincides por igual con...", 25);
			esperar(500);
			cout << " " << endl;
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
	cout << C_GRIS << "  Puntos obtenidos por inclinacion:" << C_RESET << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << "  " << left << setw(24) << inclinacion[i]->getnombre() << inclinacion[i]->getpuntaje() << " pt" << endl;
	}

	Solicitud* psolicitud = new Solicitud(respuesta1, respuesta2, respuesta3, respuesta4, resultado);
	agregar_solicitud(psolicitud);

	cout << endl << C_GRIS << "  Test #" << encuestados << " guardado en el historial." << C_RESET << endl;
}

void Robot::reporte()
{
	cout << "ROBOT POLÍTICO" << endl;
	cout << "REPORTE TOTAL: " << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << inclinacion[i]->getnombre() << ":" << inclinacion[i]->getcantidad() << " encuestados" << endl;
	}

	cout << "Total de personas atendidas: " << encuestados << endl;
}
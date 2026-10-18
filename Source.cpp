#include <iostream>
#include "Derecha_Liberal.h"
#include "Derecha_Conservadora.h"
#include "Izquierda_Liberal.h"
#include "Izquierda_Conservadora.h"
#include "Centro.h"
#include "Robot.h"
#include "Suscripcion.h"
#include "Suscripcion_Video.h"
#include "Suscripcion_Musica.h"
#include "Suscripcion_Gaming.h"
#include "Plataforma.h"
#include "Utilidades.h"
using namespace std;

void menu_robot(Robot& robot)
{
	int opcion;

	do
	{
		limpiar_pantalla();
		titulo("POLITICAL ROBOT", C_CIAN);
		cout << C_GRIS << " Tests taken: " << robot.getencuestados() << C_RESET << endl << endl;
		cout << " 1. Take the test" << endl;
		cout << " 2. Full report" << endl;
		cout << " 3. Test history" << endl;
		cout << " 4. How it works" << endl;
		cout << " 0. Back to Arcade" << endl << endl;
		opcion = leer_entero_rango("Choose a menu option: ", 0, 4);

		if (opcion == 1)
		{
			robot.ingresar_datos();
		}

		else if (opcion == 2)
		{
			robot.reporte();
		}

		else if (opcion == 3)
		{
			robot.historial();
		}

		else if (opcion == 4)
		{
			robot.mostrar_instrucciones();
		}

		if (opcion != 0)
		{
			pausar();
		}
	}

	while (opcion != 0);
}

void menu_streaming(Plataforma& plataforma)
{
	int opcion;

	do
	{
		limpiar_pantalla();
		titulo("STREAMING SIMULATOR", C_CIAN);
		plataforma.mostrar_estado();
		cout << endl;
		cout << " 1. Register subscription" << endl;
		cout << " 2. List all" << endl;
		cout << " 3. Search by ID" << endl;
		cout << " 4. Report by type" << endl;
		cout << " 5. Empire dashboard (statistics)" << endl;
		cout << " 6. Cancel subscription" << endl;
		cout << " 7. Load sample data" << endl;
		cout << " 8. How it works" << endl;
		cout << " 0. Back to Arcade" << endl << endl;
		opcion = leer_entero_rango("Choose a menu option: ", 0, 8);

		if (opcion != 0)
		{
			limpiar_pantalla();
		}

		if (opcion == 1)
		{
			plataforma.agregar_suscripcion();
		}

		else if (opcion == 2)
		{
			plataforma.listar_todo();
		}

		else if (opcion == 3)
		{
			titulo("SEARCH BY ID", C_CIAN);
			cout << endl;
			plataforma.buscar_por_id(plataforma.leer_entero("Enter ID to search: ", 1, 2147483647));
		}

		else if (opcion == 4)
		{
			titulo("REPORT BY TYPE", C_CIAN);
			cout << endl;
			plataforma.reporte_por_tipo();
		}

		else if (opcion == 5)
		{
			plataforma.panel_imperio();
		}

		else if (opcion == 6)
		{
			plataforma.eliminar_suscripcion();
		}

		else if (opcion == 7)
		{
			plataforma.cargar_demo();
		}

		else if (opcion == 8)
		{
			plataforma.mostrar_instrucciones();
		}

		if (opcion != 0)
		{
			pausar();
		}
	}

	while (opcion != 0);
}

int main()
{
	iniciar_consola();

	Robot robot;
	Plataforma plataforma;
	int opcion;

	do
	{
		limpiar_pantalla();
		mostrar_banner();
		cout << C_GRIS << "        Two minigames. Pick yours." << C_RESET << endl << endl;

		cout << C_AMARILLO << " 1. POLITICAL ROBOT" << C_RESET << endl;
		cout << "    Answer 4 questions and the robot will guess your" << endl;
		cout << "    political leaning. Ties and a global report included." << endl << endl;

		cout << C_AMARILLO << " 2. STREAMING SIMULATOR" << C_RESET << endl;
		cout << "    Run your Video, Music and Gaming platform:" << endl;
		cout << "    register subscribers, level up and become a" << endl;
		cout << "    Digital Empire." << endl << endl;

		cout << C_AMARILLO << " 0. Exit" << C_RESET << endl << endl;
		opcion = leer_entero_rango("Choose an option: ", 0, 2);

		if (opcion == 1)
		{
			menu_robot(robot);
		}

		else if (opcion == 2)
		{
			menu_streaming(plataforma);
		}
	}

	while (opcion != 0);

	limpiar_pantalla();
	cout << C_MAGENTA << "Thanks for playing. See you next time!" << C_RESET << endl;

	return 0;
}

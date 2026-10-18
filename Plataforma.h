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
#include "Utilidades.h"
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
	void mostrar_instrucciones();
	void mostrar_estado();
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
	return leer_entero_rango(pmensaje, pminimo, pmaximo);
}

double Plataforma::leer_decimal(string pmensaje)
{
	return leer_decimal_positivo(pmensaje);
}

bool Plataforma::leer_si_no(string pmensaje)
{
	return leer_confirmacion(pmensaje);
}

bool Plataforma::fecha_valida(int pdia, int pmes, int panio)
{
	if (panio < 1900 || panio > 2100 || pmes < 1 || pmes > 12 || pdia < 1)
	{
		return false;
	}

	int dias_por_mes[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	bool bisiesto = (panio % 4 == 0 && panio % 100 != 0) || (panio % 400 == 0);

	if (bisiesto)
	{
		dias_por_mes[1] = 29;
	}

	return pdia <= dias_por_mes[pmes - 1];
}

void Plataforma::leer_fecha(int& pdia, int& pmes, int& panio)
{
	bool valida = false;

	while (!valida)
	{
		string texto = leer_linea("Start date (dd mm yyyy): ");
		istringstream entrada(texto);
		string sobrante;

		if (entrada >> pdia >> pmes >> panio && !(entrada >> sobrante))
		{
			if (fecha_valida(pdia, pmes, panio))
			{
				valida = true;
			}
			else
			{
				mostrar_error("That date does not exist (check day, month and year).");
			}
		}
		else
		{
			mostrar_error("Enter three numbers separated by spaces (dd mm yyyy).");
		}
	}
}

// ===================== NIVELES (la parte "juego") =====================

double Plataforma::umbral_nivel(int pnivel)
{
	double umbrales[5] = { 0, 50, 150, 300, 500 };
	return umbrales[pnivel];
}

string Plataforma::nombre_nivel(int pnivel)
{
	string nombres[5] = { "Garage Startup", "Entrepreneur", "Growing Platform", "Streaming Giant", "Digital Empire" };
	return nombres[pnivel];
}

int Plataforma::nivel_para(double ptotal)
{
	for (int i = 4; i > 0; i--)
	{
		if (ptotal >= umbral_nivel(i))
		{
			return i;
		}
	}

	return 0;
}

double Plataforma::ingresos_totales()
{
	double total = 0;

	for (int i = 0; i < cantidad; i++)
	{
		total = total + suscripcion[i]->calcular_importe();
	}

	return total;
}

void Plataforma::mostrar_estado()
{
	double total = ingresos_totales();
	int nivel = nivel_para(total);

	cout << " Subscriptions: " << C_AMARILLO << cantidad << C_RESET
		<< "  |  Income: " << C_VERDE << "S/ " << total << C_RESET << endl;
	cout << " Level " << (nivel + 1) << ": " << C_NEGRITA << nombre_nivel(nivel) << C_RESET << endl;

	if (nivel < 4)
	{
		double desde = umbral_nivel(nivel);
		double hasta = umbral_nivel(nivel + 1);

		cout << " " << barra((int)(total - desde), (int)(hasta - desde), 20)
			<< C_GRIS << " next level at S/ " << hasta << C_RESET << endl;
	}
	else
	{
		cout << " " << C_AMARILLO << "MAX LEVEL REACHED!" << C_RESET << endl;
	}
}

void Plataforma::mostrar_instrucciones()
{
	limpiar_pantalla();
	titulo("HOW IT WORKS: STREAMING SIMULATOR", C_CIAN);
	cout << endl;
	cout << " You own a streaming platform. Register" << endl;
	cout << " Video, Music and Gaming subscriptions. Each one pays a" << endl;
	cout << " different amount depending on what it includes." << endl << endl;
	cout << C_AMARILLO << " Your goal:" << C_RESET << " raise your monthly income to rank up:" << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << "   Level " << (i + 1) << "  " << left << setw(28) << nombre_nivel(i) << "from S/ " << umbral_nivel(i) << endl;
	}

	cout << endl << C_AMARILLO << " How the amount is calculated (on top of the base fee):" << C_RESET << endl;
	cout << C_AZUL << "   Video:  " << C_RESET << "+10 if 4K | +2 per extra screen | +3 premium" << endl;
	cout << C_MAGENTA << "   Music:  " << C_RESET << "+3 High quality | +6 HiFi | +4 offline mode" << endl;
	cout << C_VERDE << "   Gaming: " << C_RESET << "+5 beta access | +0.10 per cloud GB" << endl << endl;
	cout << C_AMARILLO << " Tools:" << C_RESET << " list, search by ID, report by type," << endl;
	cout << " empire dashboard (statistics), cancel subscriptions" << endl;
	cout << " and load sample data to test quickly." << endl;
}

// ===================== OPERACIONES =====================

void Plataforma::agregar_suscripcion()
{
	titulo("NEW SUBSCRIPTION", C_CIAN);
	cout << endl;

	int tipo = leer_entero("Subscription type: [1] Video [2] Music [3] Gaming: ", 1, 3);
	int id = leer_entero("ID: ", 1, 2147483647);

	if (existe_id(id))
	{
		mostrar_error("A subscription with that ID already exists.");
		return;
	}

	string usuario = leer_texto_no_vacio("User: ");
	string correo = leer_correo("Email: ");
	int dia;
	int mes;
	int anio;
	leer_fecha(dia, mes, anio);
	double tarifa = leer_decimal("Base fee (S/): ");

	double total_antes = ingresos_totales();
	int nivel_antes = nivel_para(total_antes);

	if (tipo == 1)
	{
		int opcion_resolucion = leer_entero("Resolution: [1] HD [2] 4K: ", 1, 2);
		string resolucion = (opcion_resolucion == 1) ? "HD" : "4K";
		int pantallas = leer_entero("Number of screens (1-10): ", 1, 10);
		bool premium = leer_si_no("Premium (Y/N): ");
		agregar_a_lista(new Suscripcion_Video(id, dia, mes, anio, tarifa, usuario, correo, resolucion, pantallas, premium));
	}

	else if (tipo == 2)
	{
		int opcion_calidad = leer_entero("Audio quality: [1] Standard [2] High [3] HiFi: ", 1, 3);
		string calidad = "Standard";

		if (opcion_calidad == 2)
		{
			calidad = "High";
		}
		else if (opcion_calidad == 3)
		{
			calidad = "HiFi";
		}

		bool offline = leer_si_no("Offline mode (Y/N): ");
		agregar_a_lista(new Suscripcion_Musica(id, dia, mes, anio, tarifa, usuario, correo, calidad, offline));
	}

	else
	{
		int opcion_plataforma = leer_entero("Platform: [1] PC [2] Console: ", 1, 2);
		string plataforma = (opcion_plataforma == 1) ? "PC" : "Console";
		bool beta = leer_si_no("Beta access (Y/N): ");
		int nube = leer_entero("Cloud storage (GB, 0-10000): ", 0, 10000);
		agregar_a_lista(new Suscripcion_Gaming(id, dia, mes, anio, tarifa, usuario, correo, plataforma, beta, nube));
	}

	cout << endl << C_VERDE << "Subscription registered successfully." << C_RESET << endl;
	cout << "Monthly amount of this subscription: " << C_AMARILLO << "S/ " << suscripcion[cantidad - 1]->calcular_importe() << C_RESET << endl;

	int nivel_despues = nivel_para(ingresos_totales());

	if (nivel_despues > nivel_antes)
	{
		cout << endl << C_NEGRITA << C_AMARILLO << "  *** LEVEL UP! You are now: " << nombre_nivel(nivel_despues) << " ***" << C_RESET << endl;
	}
}

void Plataforma::listar_todo()
{
	titulo("ALL SUBSCRIPTIONS", C_CIAN);
	cout << endl;

	if (cantidad == 0)
	{
		cout << "No subscriptions registered." << endl;
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

	mostrar_error("ID not found.");
}

void Plataforma::reporte_por_tipo()
{
	int tipo = leer_entero("Filter: [1] Video [2] Music [3] Gaming: ", 1, 3);
	string nombre;

	if (tipo == 1)
	{
		nombre = "VIDEO";
	}

	else if (tipo == 2)
	{
		nombre = "MUSIC";
	}

	else
	{
		nombre = "GAMING";
	}

	double total = 0;
	int encontrados = 0;
	cout << endl;

	for (int i = 0; i < cantidad; i++)
	{
		if (suscripcion[i]->gettipo() == nombre)
		{
			suscripcion[i]->mostrar_detalles();
			cout << endl;
			total = total + suscripcion[i]->calcular_importe();
			encontrados++;
		}
	}

	if (encontrados == 0)
	{
		cout << "No subscriptions of type " << nombre << "." << endl;
	}

	else
	{
		cout << C_VERDE << "Total collected in " << nombre << ": S/ " << total << C_RESET
			<< " (" << encontrados << " subscriptions)" << endl;
	}
}

void Plataforma::panel_imperio()
{
	titulo("EMPIRE DASHBOARD", C_CIAN);
	cout << endl;

	if (cantidad == 0)
	{
		cout << "Your empire is empty. Register subscriptions or load sample data!" << endl;
		return;
	}

	mostrar_estado();
	cout << endl;

	string tipos[3] = { "VIDEO", "MUSIC", "GAMING" };
	string colores[3] = { C_AZUL, C_MAGENTA, C_VERDE };
	double ingresos[3] = { 0, 0, 0 };
	int cuantas[3] = { 0, 0, 0 };
	double total = ingresos_totales();
	int mejor = 0;

	for (int i = 0; i < cantidad; i++)
	{
		for (int t = 0; t < 3; t++)
		{
			if (suscripcion[i]->gettipo() == tipos[t])
			{
				ingresos[t] = ingresos[t] + suscripcion[i]->calcular_importe();
				cuantas[t]++;
			}
		}

		if (suscripcion[i]->calcular_importe() > suscripcion[mejor]->calcular_importe())
		{
			mejor = i;
		}
	}

	cout << C_AMARILLO << "Income by service:" << C_RESET << endl;

	for (int t = 0; t < 3; t++)
	{
		int porcentaje = (total > 0) ? (int)(ingresos[t] * 100 / total) : 0;

		cout << "  " << colores[t] << left << setw(8) << tipos[t] << C_RESET
			<< barra(porcentaje, 100, 20) << " S/ " << ingresos[t]
			<< " (" << cuantas[t] << " subs., " << porcentaje << "%)" << endl;
	}

	cout << endl << C_AMARILLO << "Your best customer:" << C_RESET << endl;
	suscripcion[mejor]->mostrar_detalles();
	cout << endl << "Average income per subscription: S/ " << (total / cantidad) << endl;
}

void Plataforma::eliminar_suscripcion()
{
	titulo("CANCEL SUBSCRIPTION", C_CIAN);
	cout << endl;

	if (cantidad == 0)
	{
		cout << "No subscriptions registered." << endl;
		return;
	}

	int id = leer_entero("ID to cancel: ", 1, 2147483647);
	int posicion = -1;

	for (int i = 0; i < cantidad; i++)
	{
		if (suscripcion[i]->getid() == id)
		{
			posicion = i;
		}
	}

	if (posicion == -1)
	{
		mostrar_error("ID not found.");
		return;
	}

	cout << endl;
	suscripcion[posicion]->mostrar_detalles();
	cout << endl;

	if (!leer_si_no("Are you sure you want to cancel it? (Y/N): "))
	{
		cout << "Operation cancelled. The subscription is still active." << endl;
		return;
	}

	delete suscripcion[posicion];

	if (cantidad == 1)
	{
		delete[] suscripcion;
		suscripcion = nullptr;
	}
	else
	{
		Suscripcion** lista_nueva = new Suscripcion * [cantidad - 1];
		int j = 0;

		for (int i = 0; i < cantidad; i++)
		{
			if (i != posicion)
			{
				lista_nueva[j] = suscripcion[i];
				j++;
			}
		}

		delete[] suscripcion;
		suscripcion = lista_nueva;
	}

	cantidad--;
	cout << C_ROJO << "Subscription cancelled." << C_RESET << endl;
}

void Plataforma::cargar_demo()
{
	titulo("SAMPLE DATA", C_CIAN);
	cout << endl;

	int agregadas = 0;

	if (!existe_id(101)) { agregar_a_lista(new Suscripcion_Video(101, 5, 1, 2026, 15.0, "ana_cine", "ana@mail.com", "4K", 3, true)); agregadas++; }
	if (!existe_id(102)) { agregar_a_lista(new Suscripcion_Musica(102, 12, 2, 2026, 10.0, "beto_beats", "beto@mail.com", "HiFi", true)); agregadas++; }
	if (!existe_id(103)) { agregar_a_lista(new Suscripcion_Gaming(103, 20, 3, 2026, 12.0, "caro_gamer", "caro@mail.com", "PC", true, 200)); agregadas++; }
	if (!existe_id(104)) { agregar_a_lista(new Suscripcion_Video(104, 2, 4, 2026, 9.0, "diego_tv", "diego@mail.com", "HD", 1, false)); agregadas++; }
	if (!existe_id(105)) { agregar_a_lista(new Suscripcion_Musica(105, 18, 5, 2026, 8.0, "eli_music", "eli@mail.com", "Standard", false)); agregadas++; }
	if (!existe_id(106)) { agregar_a_lista(new Suscripcion_Gaming(106, 9, 6, 2026, 11.0, "fer_play", "fer@mail.com", "Console", false, 50)); agregadas++; }

	if (agregadas == 0)
	{
		cout << "The sample data was already loaded (IDs 101 to 106)." << endl;
	}
	else
	{
		cout << C_VERDE << "Added " << agregadas << " sample subscriptions." << C_RESET << endl;
		cout << "Check the Empire dashboard to see how you're doing!" << endl;
	}
}

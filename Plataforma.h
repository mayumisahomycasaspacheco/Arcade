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
		string texto = leer_linea("Fecha de inicio (dd mm aaaa): ");
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
				mostrar_error("Esa fecha no existe (revisa dia, mes y anio).");
			}
		}
		else
		{
			mostrar_error("Ingresa tres numeros separados por espacios (dd mm aaaa).");
		}
	}
}

double Plataforma::umbral_nivel(int pnivel)
{
	double umbrales[5] = { 0, 50, 150, 300, 500 };
	return umbrales[pnivel];
}

string Plataforma::nombre_nivel(int pnivel)
{
	string nombres[5] = { "Garage Startup", "Emprendedor", "Plataforma en Crecimiento", "Gigante del Streaming", "Imperio Digital" };
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

	cout << " Suscripciones: " << C_AMARILLO << cantidad << C_RESET
		<< "  |  Ingresos: " << C_VERDE << "S/ " << total << C_RESET << endl;
	cout << " Nivel " << (nivel + 1) << ": " << C_NEGRITA << nombre_nivel(nivel) << C_RESET << endl;

	if (nivel < 4)
	{
		double desde = umbral_nivel(nivel);
		double hasta = umbral_nivel(nivel + 1);

		cout << " " << barra((int)(total - desde), (int)(hasta - desde), 20)
			<< C_GRIS << " siguiente nivel en S/ " << hasta << C_RESET << endl;
	}
	else
	{
		cout << " " << C_AMARILLO << "NIVEL MAXIMO ALCANZADO!" << C_RESET << endl;
	}
}

void Plataforma::mostrar_instrucciones()
{
	limpiar_pantalla();
	titulo("COMO FUNCIONA: SIMULADOR DE STREAMING", C_CIAN);
	cout << endl;
	cout << " Eres el dueno de una plataforma de streaming. Registra" << endl;
	cout << " suscripciones de Video, Musica y Gaming. Cada una paga un" << endl;
	cout << " importe distinto segun lo que contrate." << endl << endl;
	cout << C_AMARILLO << " Tu meta:" << C_RESET << " subir tus ingresos mensuales para ascender:" << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << "   Nivel " << (i + 1) << "  " << left << setw(28) << nombre_nivel(i) << "desde S/ " << umbral_nivel(i) << endl;
	}

	cout << endl << C_AMARILLO << " Como se calcula el importe (sobre la tarifa base):" << C_RESET << endl;
	cout << C_AZUL << "   Video:  " << C_RESET << "+10 si es 4K | +2 por cada pantalla extra | +3 premium" << endl;
	cout << C_MAGENTA << "   Musica: " << C_RESET << "+3 calidad Alta | +6 HiFi | +4 modo offline" << endl;
	cout << C_VERDE << "   Gaming: " << C_RESET << "+5 acceso beta | +0.10 por cada GB de nube" << endl << endl;
	cout << C_AMARILLO << " Herramientas:" << C_RESET << " listar, buscar por ID, reporte por tipo," << endl;
	cout << " panel del imperio (estadisticas), cancelar suscripciones" << endl;
	cout << " y cargar datos de ejemplo para probar rapido." << endl;
}

void Plataforma::agregar_suscripcion()
{
	titulo("NUEVA SUSCRIPCION", C_CIAN);
	cout << endl;

	int tipo = leer_entero("Tipo de Suscripcion: [1] Video [2] Musica [3] Gaming: ", 1, 3);
	int id = leer_entero("ID: ", 1, 2147483647);

	if (existe_id(id))
	{
		mostrar_error("Ya existe una suscripcion con ese ID.");
		return;
	}

	string usuario = leer_texto_no_vacio("Usuario: ");
	string correo = leer_correo("Correo: ");
	int dia;
	int mes;
	int anio;
	leer_fecha(dia, mes, anio);
	double tarifa = leer_decimal("Tarifa Base (S/): ");

	double total_antes = ingresos_totales();
	int nivel_antes = nivel_para(total_antes);

	if (tipo == 1)
	{
		int opcion_resolucion = leer_entero("Resolucion: [1] HD [2] 4K: ", 1, 2);
		string resolucion = (opcion_resolucion == 1) ? "HD" : "4K";
		int pantallas = leer_entero("Numero de Pantallas (1-10): ", 1, 10);
		bool premium = leer_si_no("Premium (S/N): ");
		agregar_a_lista(new Suscripcion_Video(id, dia, mes, anio, tarifa, usuario, correo, resolucion, pantallas, premium));
	}

	else if (tipo == 2)
	{
		int opcion_calidad = leer_entero("Calidad de Audio: [1] Estandar [2] Alta [3] HiFi: ", 1, 3);
		string calidad = "Estandar";

		if (opcion_calidad == 2)
		{
			calidad = "Alta";
		}
		else if (opcion_calidad == 3)
		{
			calidad = "HiFi";
		}

		bool offline = leer_si_no("Modo Offline (S/N): ");
		agregar_a_lista(new Suscripcion_Musica(id, dia, mes, anio, tarifa, usuario, correo, calidad, offline));
	}

	else
	{
		int opcion_plataforma = leer_entero("Plataforma: [1] PC [2] Consola: ", 1, 2);
		string plataforma = (opcion_plataforma == 1) ? "PC" : "Consola";
		bool beta = leer_si_no("Acceso Beta (S/N): ");
		int nube = leer_entero("Almacenamiento Nube (GB, 0-10000): ", 0, 10000);
		agregar_a_lista(new Suscripcion_Gaming(id, dia, mes, anio, tarifa, usuario, correo, plataforma, beta, nube));
	}

	cout << endl << C_VERDE << "Suscripcion registrada correctamente." << C_RESET << endl;
	cout << "Importe mensual de esta suscripcion: " << C_AMARILLO << "S/ " << suscripcion[cantidad - 1]->calcular_importe() << C_RESET << endl;

	int nivel_despues = nivel_para(ingresos_totales());

	if (nivel_despues > nivel_antes)
	{
		cout << endl << C_NEGRITA << C_AMARILLO << "  *** SUBISTE DE NIVEL! Ahora eres: " << nombre_nivel(nivel_despues) << " ***" << C_RESET << endl;
	}
}

void Plataforma::listar_todo()
{
	titulo("TODAS LAS SUSCRIPCIONES", C_CIAN);
	cout << endl;

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

	mostrar_error("ID no encontrado.");
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
		cout << "No hay suscripciones de tipo " << nombre << "." << endl;
	}

	else
	{
		cout << C_VERDE << "Total recaudado en " << nombre << ": S/ " << total << C_RESET
			<< " (" << encontrados << " suscripciones)" << endl;
	}
}

void Plataforma::panel_imperio()
{
	titulo("PANEL DEL IMPERIO", C_CIAN);
	cout << endl;

	if (cantidad == 0)
	{
		cout << "Tu imperio esta vacio. Registra suscripciones o carga datos de ejemplo!" << endl;
		return;
	}

	mostrar_estado();
	cout << endl;

	string tipos[3] = { "VIDEO", "MUSICA", "GAMING" };
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

	cout << C_AMARILLO << "Ingresos por servicio:" << C_RESET << endl;

	for (int t = 0; t < 3; t++)
	{
		int porcentaje = (total > 0) ? (int)(ingresos[t] * 100 / total) : 0;

		cout << "  " << colores[t] << left << setw(8) << tipos[t] << C_RESET
			<< barra(porcentaje, 100, 20) << " S/ " << ingresos[t]
			<< " (" << cuantas[t] << " susc., " << porcentaje << "%)" << endl;
	}

	cout << endl << C_AMARILLO << "Tu mejor cliente:" << C_RESET << endl;
	suscripcion[mejor]->mostrar_detalles();
	cout << endl << "Ingreso promedio por suscripcion: S/ " << (total / cantidad) << endl;
}

void Plataforma::eliminar_suscripcion()
{
	titulo("CANCELAR SUSCRIPCION", C_CIAN);
	cout << endl;

	if (cantidad == 0)
	{
		cout << "No hay suscripciones registradas." << endl;
		return;
	}

	int id = leer_entero("ID a cancelar: ", 1, 2147483647);
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
		mostrar_error("ID no encontrado.");
		return;
	}

	cout << endl;
	suscripcion[posicion]->mostrar_detalles();
	cout << endl;

	if (!leer_si_no("Seguro que quieres cancelarla? (S/N): "))
	{
		cout << "Operacion cancelada. La suscripcion sigue activa." << endl;
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
	cout << C_ROJO << "Suscripcion cancelada." << C_RESET << endl;
}

void Plataforma::cargar_demo()
{
	titulo("DATOS DE EJEMPLO", C_CIAN);
	cout << endl;

	int agregadas = 0;

	if (!existe_id(101)) { agregar_a_lista(new Suscripcion_Video(101, 5, 1, 2026, 15.0, "ana_cine", "ana@correo.com", "4K", 3, true)); agregadas++; }
	if (!existe_id(102)) { agregar_a_lista(new Suscripcion_Musica(102, 12, 2, 2026, 10.0, "beto_beats", "beto@correo.com", "HiFi", true)); agregadas++; }
	if (!existe_id(103)) { agregar_a_lista(new Suscripcion_Gaming(103, 20, 3, 2026, 12.0, "caro_gamer", "caro@correo.com", "PC", true, 200)); agregadas++; }
	if (!existe_id(104)) { agregar_a_lista(new Suscripcion_Video(104, 2, 4, 2026, 9.0, "diego_tv", "diego@correo.com", "HD", 1, false)); agregadas++; }
	if (!existe_id(105)) { agregar_a_lista(new Suscripcion_Musica(105, 18, 5, 2026, 8.0, "eli_music", "eli@correo.com", "Estandar", false)); agregadas++; }
	if (!existe_id(106)) { agregar_a_lista(new Suscripcion_Gaming(106, 9, 6, 2026, 11.0, "fer_play", "fer@correo.com", "Consola", false, 50)); agregadas++; }

	if (agregadas == 0)
	{
		cout << "Los datos de ejemplo ya estaban cargados (IDs 101 a 106)." << endl;
	}
	else
	{
		cout << C_VERDE << "Se agregaron " << agregadas << " suscripciones de ejemplo." << C_RESET << endl;
		cout << "Revisa el Panel del imperio para ver como vas!" << endl;
	}
}
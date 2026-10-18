#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cctype>
#include <thread>
#include <chrono>
#include <windows.h>

using namespace std;

const string C_RESET = "\033[0m";
const string C_NEGRITA = "\033[1m";
const string C_ROJO = "\033[91m";
const string C_VERDE = "\033[92m";
const string C_AMARILLO = "\033[93m";
const string C_AZUL = "\033[94m";
const string C_MAGNETA = "\033[95m";
const string C_CIAN = "\033[96m";
const string C_GRIS = "\033[90m";

inline void iniciar_consola()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD modo = 0;
	GetConsoleMode(h, &modo);
	SetConsoleMode(h, modo | 0x0004);
	cout << fixed << setprecision(2);
}

inline void limpiar_pantalla()
{
	system("cls");
}

inline void esperar(int milisegundos)
{
	this_thread::sleep_for(chrono::milliseconds(milisegundos));
}

inline string recortar(const string& texto)
{
	size_t inicio = 0;
	size_t fin = texto.size();

	while (inicio < fin && isspace((unsigned char)texto[inicio]))
	{
		inicio++;
	}

	while (fin > inicio && isspace((unsigned char)texto[fin - 1]))
	{
		fin--;
	}

	return texto.substr(inicio, fin - inicio);
}

inline string a_mayusculas(string texto)
{
	for (size_t i = 0; i < texto.size(); i++)
	{
		texto[i] = (char)toupper((unsigned char)texto[i]);
	}

	return texto;
}

inline string leer_linea(const string& mensaje)
{
	cout << mensaje;

	string linea;

	if (!getline(cin, linea))
	{
		cout << " " << endl;
		exit(0);
	}

	return recortar(linea);
}
#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cctype>
#include <thread>
#include <chrono>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

using namespace std;

// ===================== COLORES (ANSI) =====================
const string C_RESET = "\033[0m";
const string C_NEGRITA = "\033[1m";
const string C_ROJO = "\033[91m";
const string C_VERDE = "\033[92m";
const string C_AMARILLO = "\033[93m";
const string C_AZUL = "\033[94m";
const string C_MAGENTA = "\033[95m";
const string C_CIAN = "\033[96m";
const string C_GRIS = "\033[90m";

// ===================== CONSOLA =====================

// Activa los colores en la consola de Windows y deja los decimales con 2 digitos
inline void iniciar_consola()
{
#ifdef _WIN32
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD modo = 0;

	if (h != INVALID_HANDLE_VALUE && GetConsoleMode(h, &modo))
	{
		SetConsoleMode(h, modo | 0x0004); // ENABLE_VIRTUAL_TERMINAL_PROCESSING
	}
#endif
	cout << fixed << setprecision(2);
}

inline void limpiar_pantalla()
{
#ifdef _WIN32
	system("cls");
#else
	cout << "\033[2J\033[H";
#endif
}

inline void esperar(int milisegundos)
{
	this_thread::sleep_for(chrono::milliseconds(milisegundos));
}

// ===================== LECTURA SEGURA =====================
// Todo se lee por lineas completas: asi nunca quedan "\n" sueltos en el buffer
// y el programa no se cuelga si el usuario escribe letras donde van numeros.

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
		// Se cerro la entrada (Ctrl+Z / Ctrl+D): salimos sin quedar en un bucle infinito
		cout << endl;
		exit(0);
	}

	return recortar(linea);
}

inline void mostrar_error(const string& mensaje)
{
	cout << C_ROJO << "  [!] " << mensaje << C_RESET << endl;
}

inline int leer_entero_rango(const string& mensaje, int minimo, int maximo)
{
	while (true)
	{
		string texto = leer_linea(mensaje);
		size_t inicio = (!texto.empty() && (texto[0] == '-' || texto[0] == '+')) ? 1 : 0;
		bool valido = (inicio < texto.size()) && (texto.size() - inicio <= 18);

		for (size_t i = inicio; valido && i < texto.size(); i++)
		{
			if (!isdigit((unsigned char)texto[i]))
			{
				valido = false;
			}
		}

		if (valido)
		{
			long long valor = stoll(texto);

			if (valor >= minimo && valor <= maximo)
			{
				return (int)valor;
			}
		}

		mostrar_error("Enter a whole number between " + to_string(minimo) + " and " + to_string(maximo) + ".");
	}
}

inline double leer_decimal_positivo(const string& mensaje)
{
	while (true)
	{
		string texto = leer_linea(mensaje);

		for (size_t i = 0; i < texto.size(); i++)
		{
			if (texto[i] == ',')
			{
				texto[i] = '.';
			}
		}

		if (!texto.empty())
		{
			char* fin = nullptr;
			double valor = strtod(texto.c_str(), &fin);

			if (*fin == '\0' && valor >= 0 && valor < 1000000)
			{
				return valor;
			}
		}

		mostrar_error("Enter a valid number (0 or greater).");
	}
}

inline bool leer_confirmacion(const string& mensaje)
{
	while (true)
	{
		string texto = a_mayusculas(leer_linea(mensaje));

		if (texto == "Y" || texto == "YES")
		{
			return true;
		}

		if (texto == "N" || texto == "NO")
		{
			return false;
		}

		mostrar_error("Answer Y or N.");
	}
}

// Devuelve 'S', 'N' o 'X' (no sabe)
inline char leer_respuesta_sn_x(const string& mensaje)
{
	while (true)
	{
		string texto = a_mayusculas(leer_linea(mensaje));

		if (texto == "Y" || texto == "YES")
		{
			return 'Y';
		}

		if (texto == "N" || texto == "NO")
		{
			return 'N';
		}

		if (texto == "X")
		{
			return 'X';
		}

		mostrar_error("Answer Y (yes), N (no) or X (don't know).");
	}
}

inline string leer_texto_no_vacio(const string& mensaje)
{
	while (true)
	{
		string texto = leer_linea(mensaje);

		if (!texto.empty())
		{
			return texto;
		}

		mostrar_error("This field cannot be empty.");
	}
}

inline string leer_correo(const string& mensaje)
{
	while (true)
	{
		string texto = leer_linea(mensaje);
		size_t arroba = texto.find('@');

		if (arroba != string::npos && arroba > 0 && texto.find(' ') == string::npos
			&& texto.find('.', arroba) != string::npos && texto[texto.size() - 1] != '.')
		{
			return texto;
		}

		mostrar_error("Enter a valid email (example: name@mail.com).");
	}
}

inline void pausar()
{
	cout << endl << C_GRIS << "Press ENTER to continue..." << C_RESET;
	string basura;
	getline(cin, basura);
}

// ===================== DECORACION =====================

inline string repetir(const string& texto, int veces)
{
	string resultado = "";

	for (int i = 0; i < veces; i++)
	{
		resultado += texto;
	}

	return resultado;
}

// Caja con titulo centrado
inline void titulo(const string& texto, const string& color)
{
	int ancho = 54;
	int espacios = ancho - 2 - (int)texto.size();

	if (espacios < 0)
	{
		espacios = 0;
	}

	int izquierda = espacios / 2;
	int derecha = espacios - izquierda;

	cout << color << "+" << repetir("=", ancho - 2) << "+" << endl;
	cout << "|" << repetir(" ", izquierda) << C_NEGRITA << texto << C_RESET << color << repetir(" ", derecha) << "|" << endl;
	cout << "+" << repetir("=", ancho - 2) << "+" << C_RESET << endl;
}

inline void separador()
{
	cout << C_GRIS << repetir("-", 54) << C_RESET << endl;
}

// Barra de progreso: [#####-----]
inline string barra(int valor, int maximo, int ancho)
{
	int llenos = 0;

	if (maximo > 0)
	{
		llenos = valor * ancho / maximo;
	}

	if (llenos < 0)
	{
		llenos = 0;
	}

	if (llenos > ancho)
	{
		llenos = ancho;
	}

	return "[" + repetir("#", llenos) + repetir("-", ancho - llenos) + "]";
}

// Efecto maquina de escribir
inline void escribir_lento(const string& texto, int milisegundos)
{
	for (size_t i = 0; i < texto.size(); i++)
	{
		cout << texto[i] << flush;
		esperar(milisegundos);
	}
}

inline void mostrar_banner()
{
	cout << C_MAGENTA << R"ART(
    _    ____   ____    _    ____  _____
   / \  |  _ \ / ___|  / \  |  _ \| ____|
  / _ \ | |_) | |     / _ \ | | | |  _|
 / ___ \|  _ <| |___ / ___ \| |_| | |___
/_/   \_\_| \_\\____/_/   \_\____/|_____|
)ART" << C_RESET;
}

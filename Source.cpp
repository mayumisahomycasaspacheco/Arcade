#include<iostream>
#include "Derecha_Liberal.h"
#include "Derecha_Conservadora.h"
#include "Izquierda_Liberal.h"
#include "Izquierda_Conservadora.h"
#include "Centro.h"
using namespace std;

int main()
{
	Derecha_Liberal derecha_liberal; //Cree mi objeto
	cout << derecha_liberal.getnombre() << endl;
	cout << derecha_liberal.getpuntaje() << endl;
	cout << derecha_liberal.getcantidad() << endl;

	Derecha_Conservadora derecha_conservadora; //Cree mi objeto
	cout << derecha_conservadora.getnombre() << endl;
	cout << derecha_conservadora.getpuntaje() << endl;
	cout << derecha_conservadora.getcantidad() << endl;

	Izquierda_Liberal izquierda_liberal; //Cree mi objeto
	cout << izquierda_liberal.getnombre() << endl;
	cout << izquierda_liberal.getpuntaje() << endl;
	cout << izquierda_liberal.getcantidad() << endl;

	Izquierda_Conservadora izquierda_conservadora; //Cree mi objeto
	cout << izquierda_conservadora.getnombre() << endl;
	cout << izquierda_conservadora.getpuntaje() << endl;
	cout << izquierda_conservadora.getcantidad() << endl;

	Centro centro; //Cree mi objeto
	cout << centro.getnombre() << endl;
	cout << centro.getpuntaje() << endl;
	cout << centro.getcantidad() << endl;

	system("pause");
	return 0;
}
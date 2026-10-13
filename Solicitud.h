#pragma once
#include <iostream>
using namespace std;

class Solicitud
{
private:
	char respuesta1;
	char respuesta2;
	char respuesta3;
	char respuesta4;
	string resultado;
public:
	Solicitud(char prespuesta1, char prespuesta2, char prespuesta3, char prespuesta4, string presultado);
	~Solicitud();

	char getrespuesta1();
	char getrespuesta2();
	char getrespuesta3();
	char getrespuesta4();
	string getresultado();

	void setrespuesta1(char prespuesta1);
	void setrespuesta2(char prespuesta2);
	void setrespuesta3(char prespuesta3);
	void setrespuesta4(char prespuesta4);
	void setresultado(string presultado);
};

Solicitud::Solicitud(char prespuesta1, char prespuesta2, char prespuesta3, char prespuesta4, string presultado)
{
	respuesta1 = prespuesta1;
	respuesta2 = prespuesta2;
	respuesta3 = prespuesta3;
	respuesta4 = prespuesta4;
	resultado = presultado;
}

Solicitud::~Solicitud()
{
	//Destructor vacio
}

char Solicitud::getrespuesta1()
{
	return respuesta1;
}

char Solicitud::getrespuesta2()
{
	return respuesta2;
}

char Solicitud::getrespuesta3()
{
	return respuesta3;
}

char Solicitud::getrespuesta4()
{
	return respuesta4;
}

string Solicitud::getresultado()
{
	return resultado;
}

void Solicitud::setrespuesta1(char prespuesta1)
{
	respuesta1 = prespuesta1;
}

void Solicitud::setrespuesta2(char prespuesta2)
{
	respuesta2 = prespuesta2;
}

void Solicitud::setrespuesta3(char prespuesta3)
{
	respuesta3 = prespuesta3;
}

void Solicitud::setrespuesta4(char prespuesta4)
{
	respuesta4 = prespuesta4;
}

void Solicitud::setresultado(string presultado)
{
	resultado = presultado;
}
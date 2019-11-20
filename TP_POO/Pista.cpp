#include "Pista.h"
#include <iostream>

using namespace std;

Pista::Pista(int nM, int comp):comprimento(comp),nMax(nM)
{
	cout << "Construtor Pista" << endl;
}

Pista::~Pista()
{
	cout << "Destrutor da pista" << endl;
}

bool Pista::insere(Piloto * p)
{
	if (pilotosEmCompeticao.size() + 1 >= nMax) {
		pilotosEmCompeticao.push_back(p);
		cout << "A pista(" << nMax << ") ja nao aguenta com mais pilotos(" << pilotosEmCompeticao.size() << ")" << endl;	
		return false;
	}
		
	else {
		pilotosEmCompeticao.push_back(p);
		cout << "A Pista inseriu o piloto " << p->obtemNome() << endl;
		return true;
	}
		
}

int Pista::obtemComprimento() const
{
	return comprimento;
}

int Pista::obtemNMax() const
{
	return nMax;
}

bool Pista::passaSegundo()
{
	//verificar o piloto e conforme o seu tipo, atua

	//e possivel obter a localiza��o do carro atrav�s do piloto

	return true;
}

bool Pista::terminarCorrida()
{
	//Permite terminar a corrida.Os carros s�o removidos da pista e v�o para a garagem, e os pilotosaem dos ve�culos.
	
	return false;
}

std::string Pista::obtemCorrida()
{
	/*
	 indica se ela j� foi iniciada ou n�o, e, em caso afirmativo, detalhando a
	classifica��o atual. Um exemplo de classifica��o pode ser:
	Informa��o sobre a corrida no aut�dromo Silverstone(5000 m) :
	1. B Ferrari / Vettel(r�pido) - 5mAh, 290mAh - 2410m � 55m / s
	2. D Mercedes / Hamilton(crazy) - 5mAh, 350mAh - 2300m � 50m / s*/
	return std::string();
}

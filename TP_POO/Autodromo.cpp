#include "Autodromo.h"
#include <iostream>
#include <sstream>


using namespace std;

std::vector<std::string> Autodromo::todosNomesAutodromos;

Autodromo::Autodromo(int n_Max, int comprimento, std::string n) :pista(n_Max, comprimento), preparado(false)
{
	for (int i = 0; i < todosNomesAutodromos.size(); i++) {
		if (n == todosNomesAutodromos.at(i)) {
			n = n + "x";
			i = -1;
		}
	}

	todosNomesAutodromos.push_back(n);
	nome = n;
	//cout << "\tConstrutor_Autodromo:" << n << "|max=" << n_Max << "(" << comprimento << " metros)\n" << endl;
}

Autodromo::~Autodromo()
{
	//cout << "Destrutor_autodromo:'" << nome << "'" << endl;
	for (int i = 0; i < todosNomesAutodromos.size(); i++) {
		if (nome == todosNomesAutodromos.at(i)) {
			todosNomesAutodromos.erase(todosNomesAutodromos.begin() + i);
			break;
		}
	}
	vector<Carro*> todosCarros = retiraCarros();
	for (auto c : todosCarros)
		delete c;
}

std::string Autodromo::obtemNome() const
{
	return nome;
}

std::string Autodromo::autodromoToString() const
{
	ostringstream os;
	os << "Autodromo:" << nome << "|max=" << pista.obtemNMax() << "(" << pista.obtemComprimento() << " metros)";
	return os.str();
}

bool Autodromo::obtemEstado() const
{
	return preparado;
}

bool Autodromo::insereCarrosNaGaragem(vector<Carro*> carros)
{
	//cout << "Autdodromo '" << obtemNome() << "' vai tentar carregar o carro para a garagem" << endl;
	if (garagem.recebeTodosCarros(carros)) {
		preparado = true;
		return true;
	}
	else {
		preparado = false;
		return false;
	}
	return false;
}

bool Autodromo::carregaBaterias()
{
	return garagem.carregaTodasBaterias();
}

int Autodromo::verificaNumCarrosGaragem() const
{
	return garagem.obtemNumCarros();
}

bool Autodromo::obtemEstadoPista() const
{
	return pista.obtemEstado();
}

bool Autodromo::insereCarroPista()
{
	Carro * carroDisponivel;
	bool levaMais = true;//pista
	int pilotosInseridos = 0;

	while (levaMais) {//se houver espa�o na pista
		carroDisponivel = garagem.obtemCarroDisponivel();
		if (carroDisponivel == nullptr) {//se ja nao ha piloto
			//cout << "a garagem ja nao encontra mais pilotos disponiveis" << endl;
			break;
		}
		
		levaMais = pista.insereCarro(carroDisponivel);
		//cout << "inseri piloto e a pista =" << levaMais << endl;
		pilotosInseridos++;
	}


	//cout << "Autodromo[" << nome << "] inseriu " << pilotosInseridos << " carros na sua pista" << endl;
	return pilotosInseridos;
}

std::string Autodromo::listaCarrosGaragem() const
{
	ostringstream os;
	os << "O Autodromo '" << obtemNome() << "' tem os seguintes carros na garagem:" << endl;
	os << garagem.listaCarros();
	return os.str();
}

std::vector<Carro*> Autodromo::retiraCarros()
{
	vector<Carro*> tmp = garagem.retiraTodosCarros();//vai buscar os carros a garagem
	vector<Carro*> tmp2 = pista.removeTodosCarros();//vai buscar os carros a pista
	for (auto t : tmp2)
		tmp.push_back(t);

	return tmp;
}

void Autodromo::iniciaPista()
{
	pista.iniciaCorrida();
}

bool Autodromo::destroiCarro(char idCarro)
{
	Carro * c = pista.removeCarro(idCarro);

	if (c == nullptr) {
		return garagem.destroiCarro(idCarro);
	}
	else {
		delete c;
		return true;
	}

	return false;
}

void Autodromo::terminarCorrida()
{
	pista.terminarCorrida();
	preparado = false;
}

bool Autodromo::passaTempo(int segundos)
{
	return pista.passaTempo(segundos, &garagem);
}

bool Autodromo::stopPiloto(std::string nomePiloto)
{
	return pista.stopPiloto(nomePiloto);;
}

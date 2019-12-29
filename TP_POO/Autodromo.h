#pragma once
#include "Pista.h"
#include "Garagem.h"
#include <string>
#include <vector>
class Autodromo
{
	static std::vector<std::string> todosNomesAutodromos;
	std::string nome;
	Pista pista;
	Garagem garagem;
	bool preparado;
public:
	Autodromo(int n_Max, int comprimento, std::string n);
	~Autodromo();
	std::string obtemNome() const;
	std::string autodromoToString() const;

	//garagem
	bool obtemEstado() const;
	bool insereCarrosNaGaragem(std::vector<Carro *> e);
	bool carregaBaterias();
	int verificaNumCarrosGaragem() const;
	std::string listaCarrosGaragem() const;


	//pista
	bool obtemEstadoPista() const;
	bool insereEquipaPista();

	void iniciaPista();
	void terminarCorrida();
	bool passaTempo(int segundos);

};


#include "Jogo.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

Autodromo * Jogo::obtemAutodromo(std::string nomeA) const
{
	vector<Autodromo*>::const_iterator it = todosAutodromos.begin();
	while (it != todosAutodromos.end()) {
		if (nomeA == (*it)->obtemNome()) {
			return (*it);
		}
		it++;
	}
	return nullptr;
}

bool Jogo::verificaDigitos(std::string parametros)
{
	for (int i = 0; i < parametros.size(); i++)
		if (!isdigit(parametros[i]))
			return false;
	return true;
}

Jogo::Jogo():dvg("original")
{
}

Jogo::~Jogo()
{
	cout << "Destrutor_Jogo" << endl;
	for (auto a : todosAutodromos)
		delete a;
	for (auto d : bakcupsDVG)
		delete d;
}

bool Jogo::lerFicheiroPiloto(std::string fileName)
{
	//cout << "A abrir o ficheio:'" << fileName << "'" << endl;
	string line, tipo, nome;

	size_t pos;

	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			tipo = "", nome = "",pos = 0;//reset
			cout << "Linha:" << line << endl;

			//tipo
			pos = line.find_first_of(" ");
			tipo = line.substr(0, pos);
			line.erase(0, tipo.size() + 1);
			
			//nome
			nome = line;

			//cout << "\tPiloto:(" << tipo << "," << nome << ")\n" << endl;
			if (!nome.empty() && !tipo.empty()) {
				if (!criaPiloto(tipo, nome))
					cout << "Este tipo nao existe: " << tipo << endl;
			}
			else
				cout << "Valores de ficheiro invalidos" << endl;

		}
		myfile.close();
		return true;
	}
	else cout << "Erro na leitura do fichero:'" << fileName << "'" << endl;

	return false;
}

bool Jogo::lerFicheiroCarro(std::string fileName)
{
	string line, marca, modelo;
	int capI, capM, velMax;

	size_t pos;

	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			//marca = "", modelo = "";//reset
			marca.erase(), modelo.erase();//reset
			capI = -1, capM = -1, pos = 0, velMax = -1;

			cout << "Linha:" << line << endl;

			//Velocidade Maxima
			pos = line.find_first_of(" ");
			if (!verificaDigitos(line.substr(0, pos))) {
				cout << "Linha com parametros invalidos (ignorada)" << endl;
				continue;
			}
			velMax = stoi(line.substr(0, pos));
			line.erase(0, pos + 1);
			
			
			//Capacidade Inicial
			pos = line.find_first_of(" ");
			if (!verificaDigitos(line.substr(0, pos))) {
				cout << "Linha com parametros invalidos (ignorada)" << endl;
				continue;
			}
			capI = stoi(line.substr(0, pos));
			line.erase(0, pos + 1);
		

			//Capacidade Maxima
			pos = line.find_first_of(" ");
			if (!verificaDigitos(line.substr(0, pos))) {
				cout << "Linha com parametros invalidos (ignorada)" << endl;
				continue;
			}
			capM = stoi(line.substr(0, pos));
			line.erase(0, pos + 1);

			//Marca
			pos = line.find_first_of(" ");
			marca = line.substr(0, pos);
			line.erase(0, pos + 1);

			if (pos != -1) {
				modelo = line;	
			}
			
			if (velMax != -1 && capI != -1 && capM != -1 && !marca.empty()) {
				//cout << "\tCarro:" << marca << "," << modelo << "(" << capI << "/" << capM << ")\n" << endl;
				criaCarro(velMax, capI, capM, marca, modelo);
			}
			
		}
		myfile.close();
		return true;
	}
	else cout << "Erro na leitura do fichero:'" << fileName << "'" << endl;

	return false;
}

bool Jogo::lerFicheiroAutodromo(std::string fileName)
{
	string line, nome, tmp;

	int n, comprimento;

	size_t pos;

	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			nome = "", tmp = "";
			n = 0, comprimento = 0;//reset

			cout << "Linha:" << line << endl;

			//Numero m�ximo de carrosc
			pos = line.find_first_of(" ");
			if (!verificaDigitos(line.substr(0, pos))) {
				cout << "Linha com parametros invalidos (ignorada)" << endl;
				continue;
			}
			n = stoi(line.substr(0, pos));
			line.erase(0, pos + 1);

			pos = line.find_first_of(" ");
			if (!verificaDigitos(line.substr(0, pos))) {
				cout << "Linha com parametros invalidos (ignorada)" << endl;
				continue;
			}
			comprimento = stoi(line.substr(0, pos));
			line.erase(0, pos + 1);
			
			nome = line;

			if (n != -1 && comprimento != -1 && !nome.empty()) {
				//cout << "\tAutodromo[" << n << "]:" << nome << "(" << comprimento << " metros)\n" << endl;
				criaAutodromo(n, comprimento, nome);		
			}
				
			
		}
		myfile.close();
		return true;
	}
	else cout << "Erro na leitura do fichero:'" << fileName << "'" << endl;

	return false;
}

bool Jogo::criaCarro(int velMax, int capMaxima, int capInicial, std::string marca, std::string modelo)
{
	return dvg.criaCarro(velMax,capMaxima, capInicial, marca, modelo);
}

bool Jogo::criaPiloto(std::string tipo, std::string nome)
{
	return dvg.criaPiloto(tipo, nome);
}

bool Jogo::criaAutodromo(int nMax, int comprimento, std::string nome)
{
	Autodromo * tmp;

	tmp = new Autodromo(nMax, comprimento, nome);
	todosAutodromos.push_back(tmp);

	return true;
}

std::string Jogo::autodromosToString() const
{
	ostringstream os;
	vector<Autodromo*>::const_iterator it = todosAutodromos.begin();

	while (it != todosAutodromos.end()) {
		os << "\t" << (*it)->autodromoToString() << endl;
		it++;
	}
	return os.str();
}

bool Jogo::apagaCarro(char id)
{
	return dvg.apagaCarro(id);
}

bool Jogo::apagaPiloto(std::string nome)
{
	return dvg.apagaPiloto(nome);
}

bool Jogo::apagaAutodromo(std::string nome)
{
	vector<Autodromo*>::iterator it = todosAutodromos.begin();
	while (it != todosAutodromos.end()) {
		if ((*it)->obtemNome() == nome) {
			delete (*it);
			todosAutodromos.erase(it);
			return true;
		}
		it++;
	}
	return false;
}

bool Jogo::entraNoCarro(char idCarro, std::string nomePiloto)
{
	return dvg.associaCarroPiloto(idCarro,nomePiloto);
}

bool Jogo::saiDoCarro(char idCarro)
{
	return dvg.removePilotoCarro(idCarro);
}

std::string Jogo::lista() const
{
	ostringstream os;
	string carros = dvg.obtemTodosCarros();
	string pilotos = dvg.obtemTodosPilotos();
	string autodromos = autodromosToString();
	
	cout << "DGV atual:" << dvg.obtemNome() << endl;

	if (bakcupsDVG.size() == 0)
		cout << "Sem backups DGV" << endl;
	else {
		cout << "Bakcups DGV:" << endl;
		for (auto b : bakcupsDVG)
			cout << "\t" << b->obtemNome() << endl;
	}

	if (carros.empty())
		cout << "Ainda nao existem carros criados." << endl;
	else {
		cout << "Caros:" << endl;
		cout << carros << endl;
	}
	
	if (pilotos.empty())
		cout << "Ainda nao existem pilotos criados." << endl;
	else
	{
		cout << "Pilotos:" << endl;
		cout << pilotos << endl;
	}

	if (autodromos.empty())
		cout << "Ainda nao existem autodromos criados" << endl;
	else {
		cout << "Autodromos:" << endl;
		cout << autodromos << endl;

	}

	return os.str();
}

bool Jogo::saveDGV(std::string nome)
{
	bool checkNome = false;
	if (nome == dvg.obtemNome())
		checkNome = true;
	for (auto d : bakcupsDVG)
		if (d->obtemNome() == nome)
			checkNome = true;

	if (checkNome) {
		cout << "Ja existe uma dgv com este nome." << endl;
		return false;
	}


	DVG * newDVG = new DVG(dvg);
	newDVG->alteraNome(nome);
	//newDVG = &dvg;//construtor por c�pia

	bakcupsDVG.push_back(newDVG);

	return true;
}

bool Jogo::loadDGV(std::string nome)
{
	cout << "a procurar dgv..." << endl;
	for (auto d : bakcupsDVG)
		if (d->obtemNome() == nome) {
			cout << "vou agora trocar de DGV" << endl;
			dvg = *d;
			cout << "Feita a troca de DGV para :";
			cout << dvg.obtemNome() << endl;
			return true;
		}
	return false;
}

bool Jogo::delDGV(std::string nome)
{
	std::vector<DVG *>::iterator it = bakcupsDVG.begin();
	while (it != bakcupsDVG.end()) {
		if ((*it)->obtemNome() == nome) {
			//cout << "Encontrei a DGV '" << nome << "'" << endl;
			delete (*it);
			bakcupsDVG.erase(it);
			return true;
		}
		it++;
	}

	cout << "Nao foi possivel encontrar DGV com o nome:'" << nome << "'" << endl;
	return false;
}

bool Jogo::verificaAutodromo(std::string nomeA) const
{
	Autodromo * tmp = obtemAutodromo(nomeA);
	if (tmp != nullptr)
		return true;
	else
		return false;
}

bool Jogo::campeonato(vector<string> nomesAutodromoIn)
{
	if (camp == nullptr) {
		cout << "A criar um campeonato!" << endl;
		for (int i = 0; i < nomesAutodromoIn.size(); i++) {
			//cout << "A verificar o nome:" << nomesAutodromoIn.at(i) << endl;
			if (!verificaAutodromo(nomesAutodromoIn.at(i))) {
				nomesAutodromoIn.erase(nomesAutodromoIn.begin() + i);
				i--;
				continue;
			}
		}

		if (nomesAutodromoIn.empty()) {
			cout << "Nao tenho nenhum autodromo legitimo para criar um campeonato!" << endl;
			return false;
		}
			
		//final:
		cout << "\n\nFinal:" << endl;
		for (int i = 0; i < nomesAutodromoIn.size(); i++)
			cout << "\tNome:" << nomesAutodromoIn.at(i) << endl;

		//incia o campeonato com o vector de todos os autdromos validos neste campeonato
		vector<Autodromo*> autodromosCampeonato;
		for (int i = 0; i < nomesAutodromoIn.size(); i++) {
			autodromosCampeonato.push_back(obtemAutodromo(nomesAutodromoIn.at(i)));
		}

		camp = new Campeonato("local");
		camp->carregaAutodromos(autodromosCampeonato);
		return true;
	}
	else {
		cout << "Ja existe um campeonato a decorrer!" << endl;
		return false;
	}
	
}

std::string Jogo::listaCarros() const
{
	Autodromo * autodromoEmCompeticao = camp->obtemAutodromoCompeticao();
	return autodromoEmCompeticao->listaCarrosGaragem();
}

bool Jogo::carregaBat(char idCarro, int quantidade)
{
	if (quantidade <= 0)
		return false;

	Carro * c = dvg.obtemCarro(idCarro);
	if (c == nullptr)
		return false;

	c->carregaBateria(quantidade);
	return true;
}

bool Jogo::carregaTudo()
{
	//carrega as baterias todas
	Autodromo * autoCompeticao = camp->obtemAutodromoCompeticao();
	if (autoCompeticao == nullptr) {
		cout << "Nao existe autodromo em comepeticao" << endl;
		return false;
	}
	return autoCompeticao->carregaBaterias();
}

bool Jogo::insereCarrosAutodromo()
{
	Autodromo * autoCompeticao = camp->obtemAutodromoCompeticao();
	if (autoCompeticao == nullptr) {
		cout << "Nao existe autodromo em comepeticao" << endl;
		return false;
	}

	//insere os carros no autodromo onde vai decorrer a proxima corrida
	if (autoCompeticao->obtemEstado()) {
		cout << "A garagem ja esta preparada, experimente (corrida)" << endl;
		return true;
	}

	//cout << "numero de autodromo em competicao = " << camp->obtemNumAutodromoCompeticao() << endl;
	//getchar();
	if (camp->obtemNumAutodromoCompeticao() > 0) {//vai buscar carros ao autodromo anterior
		if (!autoCompeticao->insereCarrosNaGaragem(camp->obtemCarrosAutodromoAnterior())){//carro e piloto:
			cout << "Nao existem carros disponiveis para criar um campeonato, a eliminar (minimo 2)" << endl;
			delete camp;
			camp = nullptr;
			return false;
		}

	}
	else {//vai buscar carros a dgv
		if (dvg.obtemNumCarros() <= 0) {
		cout << "A dgv nao tem carros para competir." << endl;
		return false;
		}

		vector<Carro*> tmp;
		tmp = dvg.obtemVectorCarros();

		if (!autoCompeticao->insereCarrosNaGaragem(tmp)) {//carro e piloto:
			cout << "Nao existem carros disponiveis para criar um campeonato, a eliminar (minimo 2)" << endl;
			delete camp;
			camp = nullptr;
			return false;
		}
		camp->carregaCarros(tmp);
	}
	
	carregaTudo();//carrega as baterias todas
	
	return true;
}

bool Jogo::corrida()
{
	Autodromo * autoCompeticao = camp->obtemAutodromoCompeticao();

	if (autoCompeticao == nullptr) {
		cout << "Nao existe autodromo em competicao" << endl;
		return false;
	}

	if (autoCompeticao->obtemEstadoPista()) {//se a pista esta em competicao -> proximo autodromo
		cout << "A passar a competicao para o proximo autodromo." << endl;
		if (camp->proximoAutodromo() == false) {
			cout << "[Jogo]Fim do campeonato, pontuacao final:" << endl;
			cout << camp->obtemPontuacao();
			//obtem carros do autodromo
			dvg.carregaCarros(autoCompeticao->retiraCarros());
			delete camp;
			camp = nullptr;
			return false;
		}
			return corrida();
	}


	if (!insereCarrosAutodromo())
		return false;


	if (!autoCompeticao->insereCarroPista()) {
		cout << "Nao existem pilotos/carros disponiveis para correr (minimo 2)" << endl;
		return true;
	}

	autoCompeticao->iniciaPista();
	passatempo(0);
	return true;
}

bool Jogo::acidente(char idCarro)
{
	Carro * c = dvg.obtemCarro(idCarro);
	if (c == nullptr)
		return false;

	c->danificaCarro();
	return true;
}

bool Jogo::stopPiloto(std::string nome)
{
	Piloto * p = dvg.obtemPiloto(nome);
	if (p == nullptr) {
		//cout << "nao encontrei piloto na dgv" << endl;
		return false;
	}

	//verifica se tem carro
	if (p->verificaCarro()) {
		Carro * c = dvg.obtemCarro(p->obtemIdCarro());
		if (c != nullptr) {//se o carro esta no dgv
			p->stop(c);
		}
		else if(camp != nullptr){//se esta
			Autodromo * a = camp->obtemAutodromoCompeticao();
			a->stopPiloto(nome);
		}
	}
	return true;
}

bool Jogo::destroi(char idCarro)
{
	Carro * c = dvg.obtemCarro(idCarro);
	if (c != nullptr) {//se o carro esta na dgv
			delete c;
			return true;
	}
	else if (camp != nullptr) {//se existe um campeonato
		return camp->destroiCarro(idCarro);//percorre todos os autodromos(pista/garagem)
	}
	else//carro nao esta em lado nenhum
		return false;
}

bool Jogo::passatempo(int segundos)
{
	Autodromo * autoCompeticao = camp->obtemAutodromoCompeticao();

	if (autoCompeticao == nullptr) {
		cout << "Nao existe autodromo em comepeticao" << endl;
		return false;
	}

	if (!autoCompeticao->obtemEstadoPista()) {
		cout << "O autodromo nao esta em competicao, experimente (corrida)" << endl;
		return true;
	}

	if (!camp->passaTempo(segundos))//se a corrida acabar
		camp->proximoAutodromo();
	return true;
}

std::string Jogo::pontos() const
{
	if (camp == nullptr)
		return "Nao existe nenhum campeonato neste momento.";

	return camp->obtemPontuacao();
}

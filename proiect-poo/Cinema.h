#pragma once
#include <list>;
using namespace std;

const char* g_TempFilePrefix = "temp";
const char* g_BinarStocareFilme = "filme.bin";
const char* g_BinarStocareSali = "sali.bin";
const char* g_Prefix = "\t\t\t\t";
const int g_NumarFilmeDisponibile = 10;
const char* g_NumeCinema = "ASE Multiplex";

class ManagerCinema;
class Sala;
class Rezervare;
class Film;
class Bilet;
class Plata;

ostream& operator<<(ostream& out, ManagerCinema* managerCinema);

ostream& operator<<(ostream& out, Sala* sala);
istream& operator>>(istream& in, Sala* sala);

ostream& operator<<(ostream& out, Rezervare* rezervare);
istream& operator>>(istream& in, Rezervare* rezervare);

ostream& operator<<(ostream& out, Film* film);
istream& operator>>(istream& in, Film* film);

ostream& operator<<(ostream& out, Bilet* bilet);
istream& operator>>(istream& in, Bilet* bilet);

ostream& operator<<(ostream& out, Plata* plata);
istream& operator>>(istream& in, Plata* plata);

// interfata "afisabil"
class Afisabil {
	virtual void afiseaza() = 0;
};

// manager general pentru cinematograf
class ManagerCinema {
private:
	const char* _nume;
public:
	ManagerCinema(const char* nume);
	~ManagerCinema();
	ManagerCinema(const ManagerCinema& managerCinema);
	ManagerCinema& operator=(const ManagerCinema& managerCinema);

	static int _numarFilmeDisponibile;
	
	void initializeaza();
	void afiseazaHeader(string titlu);

	// Filme
	void afiseazaOptiuniFilme();
	void afiseazaFilme();
	void adaugaFilm();
	void editeazaFilm();
	int totalFilmeDisponibile();
	void stergeFilm();

	// Sali
	void afiseazaOptiuniSali();
	void afiseazaSali();
	void adaugaSala();
	void editeazaSala();
	void afiseazaListaSali();
	Sala cautaSala(int id);
	void stergeSala();
	int totalSaliDisponibile();

	void setNume(char* nume)
	{
		_nume = nume;
	}

	string getNume()
	{
		return _nume;
	}
};

class Sala : public Afisabil {
private:
	char* _nume;
	int _locuri_disponibile;

public:
	Sala();
	Sala(const char* nume, int locuri_disponibile);
	Sala(const Sala& sala);
	Sala& operator=(const Sala& sala);
	~Sala();
	Sala& operator!();
	bool operator>(Sala& sala);
	bool operator==(Sala& sala);

	void salveaza(const char* fisier);

	void setNume(const char* nume)
	{
		if (nume != nullptr)
		{
			if (this->_nume != nullptr)
				delete[]this->_nume;
			this->_nume = new char[strlen(nume) + 1];
			strcpy_s(this->_nume, strlen(nume) + 1, nume);
		}
		else
			_nume = nullptr;
	}

	const char* getNume()
	{
		return _nume;
	}

	void setLocuriDisponibile(int locuri_disponibile) {
		if(locuri_disponibile >= 0)
			_locuri_disponibile = locuri_disponibile;
	}

	int getLocuriDisponibile() {
		return _locuri_disponibile;
	};

	void afiseaza() override
	{
		cout << this;
	}
};

class Rezervare {
private:
	std::string nume_rezervare;
public:
	std::string getNume() { return nume_rezervare; }

	void setNume(std::string nume) { this->nume_rezervare = nume; }
};

class Film : public Afisabil {
private:
	char* _nume;
	int _an_lansare;
	int _durata;
	int _numarReviewuri;
	int* _noteReviewuri;

public:
	Film()
	{
		_nume = nullptr;
		_noteReviewuri = nullptr;
	}

	Film(const char* nume, int an, int durata);
	Film(const Film& film);
	Film& operator=(const Film& film);
	~Film();

	// set
	void setNume(const char* nume) 
	{ 
		if (nume != nullptr)
		{
			if (this->_nume != nullptr)
				delete[] this->_nume;
			this->_nume = new char[strlen(nume) + 1];
			strcpy_s(this->_nume, strlen(nume) + 1, nume);
		}
		else
		{
			this->_nume = nullptr;
		}
	}
	void setAnLansare(int an) { if(an >= 1900) _an_lansare = an;}
	void setDurata(int durata) { if(durata > 0) _durata = durata; }
	void setReviewuri(int numarReviewuri, int* reviweuri)
	{
		if (numarReviewuri > 0)
		{
			this->_numarReviewuri = numarReviewuri;
			if (this->_noteReviewuri != nullptr)
				delete[] this->_noteReviewuri;
			this->_noteReviewuri = new int[this->_numarReviewuri];
			for (int i = 0;i < numarReviewuri;i++)
				this->_noteReviewuri[i] = reviweuri[i];
		}
		else
		{
			this->_numarReviewuri = 0;
			this->_noteReviewuri = nullptr;
		}
	}

	// get
	const char* getNume() { return _nume; }
	int getAnLansare() { return _an_lansare; }
	int getDurata() { return _durata; }
	int getNumarReviewuri() { return _numarReviewuri; }

	void afiseaza() override
	{
		cout << this;
	}

	void salveaza(const char* fisier);
	void sterge();

	int operator[](int index);
};

class ManagerFilme {
private:
	static std::list<Film> _listaFilme;

public:
	static void adaugaFilm(Film film) { _listaFilme.push_back(film); }
	static Film* creeazaFilm(const char* nume, int an, int durata);
	static Film* cautaFilm(string nume);
	static void afiseazaFilme(string prefix);
	static void adaugaFilm();
};

class Bilet {
private:
	int id;
	std::string nume_bilet;
public:
	Bilet(int id, std::string nume);

	void setId(int id) { this->id = id; }
	void setNume(std::string nume) { this->nume_bilet = nume; }

	int getId() { return this->id; }
	std::string getNume() { return this->nume_bilet; }
};

class Plata {
private:
	std::string moneda;
	int suma;
public:
	Plata(std::string moneda, int suma);

	void setMoneda(std::string moneda) { this->moneda = moneda; }
	void setSuma(int suma) { this->suma = suma; }

	std::string getMoneda() { return this->moneda; }
	int getSuma() { return this->suma; }

	int operator+(int sumaExtra);
	Plata& operator++();
	Plata& operator++(int);

	operator int() const;
};

int operator+(int sumaExtra, Plata plata);
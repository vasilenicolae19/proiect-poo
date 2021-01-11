#pragma once
#include <list>;
using namespace std;

const char* g_BinarStocareFilme = "filme.bin";
const char* g_Prefix = "\t\t\t\t";
const int g_NumarFilmeDisponibile = 10;
const char* g_NumeCinema = "ASE Multiplex";

// interfata "afisabil"
class Afisabil {
	virtual void afiseaza() = 0;
};

// manager general pentru cinematograf
class ManagerCinema {
private:
	const char* _nume;

public:
	ManagerCinema();
	~ManagerCinema();

	void afiseazaOptiuniFilme();
	void initializeaza();
	void afiseazaHeader(string titlu);
	void afiseazaFilme();
	void adaugaFilm();

	void setNume(char* nume)
	{
		_nume = nume;
	}

	string getNume()
	{
		return _nume;
	}
};

class Rezervare {
private:
	char* nume_rezervare;
};

class Film : public Afisabil {
private:
	const char* _nume;
	int _an_lansare;
	int _durata;

public:
	Film();
	Film(const char* nume, int an, int durata);

	// set
	void setNume(const char* nume) { _nume = nume; }
	void setAnLansare(int an) { _an_lansare = an;}
	void setDurata(int durata) { _durata = durata; }

	// get
	const char* getNume() { return _nume; }
	int getAnLansare() { return _an_lansare; }
	int getDurata() { return _durata; }

	void afiseaza() override
	{
		cout << _nume << " - An: " << _an_lansare << " Durata: " << _durata << " minute" << endl;
	}

	void salveaza();
	void sterge();
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

class Sala {
private:
	char* nume_sala;
	int nr_locuri_total;
	int nr_locuri_rezervate;
};

class Bilet {
private:
	int id;
	char* nume_bilet;
};

class Plata {
private:
	char* moneda;
	int suma;
};
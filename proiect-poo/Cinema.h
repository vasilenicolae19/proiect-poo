#pragma once
#include <list>;
using namespace std;

const char* g_BinarStocareFilme = "filme.bin";
const char* g_BinarStocareSali = "sali.bin";
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

	static int _numarFilmeDisponibile;
	
	void initializeaza();
	void afiseazaHeader(string titlu);

	// Filme
	void afiseazaOptiuniFilme();
	void afiseazaFilme();
	void adaugaFilm();

	// Sali
	void afiseazaOptiuniSali();
	void afiseazaSali();
	void adaugaSala();

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
	const char* _nume;
	int _locuri_disponibile;

public:
	Sala();
	Sala(const char* nume, int locuri_disponibile);

	void salveaza();

	void setNume(const char* nume)
	{
		// TODO: Validare.
		_nume = nume;
	}

	const char* getNume()
	{
		return _nume;
	}

	void setLocuriDisponibile(int locuri_disponibile) {
		// TODO: Validare (>= 0).
		_locuri_disponibile = locuri_disponibile;
	}

	int getLocuriDisponibile() {
		return _locuri_disponibile;
	};

	void afiseaza() override
	{
		cout << "Sala " << getNume() << " Locuri: " << getLocuriDisponibile() << endl;
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
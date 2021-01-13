#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <cstring>

#include "Cinema.h"

using namespace std;

int ManagerCinema::_numarFilmeDisponibile = 0;


int main()
{
    ManagerCinema* p_ManagerCinema = new ManagerCinema(g_NumeCinema);
    p_ManagerCinema->initializeaza();

    delete p_ManagerCinema;
    return 0;
}

Film* ManagerFilme::creeazaFilm(const char* nume, int an, int durata)
{
    return new Film(nume, an, durata);
}

void ManagerFilme::afiseazaFilme(string prefix = "")
{
    ifstream inFile;
    inFile.open(g_BinarStocareFilme, ios::binary);

    Film filmAux;
    int idx = 0;

	int temp, temp1;
	int tempArray[100];
	char buffer[255];
	inFile.read((char*)&temp, sizeof(temp));
    while (!inFile.eof())
    {
		inFile.read(buffer, temp);
		filmAux.setNume(buffer);
		inFile.read((char*)&temp, sizeof(temp));
		filmAux.setAnLansare(temp);
		inFile.read((char*)&temp, sizeof(temp));
		filmAux.setDurata(temp);
		inFile.read((char*)&temp, sizeof(temp));
		for (int i = 0;i < temp;i++)
		{
			inFile.read((char*)&temp1, sizeof(temp1));
			tempArray[i] = temp1;
		}
		filmAux.setReviewuri(temp, tempArray);
        cout << prefix << idx + 1 << ". ";
        filmAux.afiseaza();
        idx++;

		inFile.read((char*)&temp, sizeof(temp));
    }

    if (idx == 0)
    {
        cout << "\n" << prefix << "Niciun film disponibil!\n";
    }

    inFile.close();
}

Film* ManagerFilme::cautaFilm(string nume)
{
    ifstream inFile;
    inFile.open(g_BinarStocareFilme, ios::binary);

    Film* filmAux;

    while (inFile.read((char*)&filmAux, sizeof(filmAux)))
    {
        if (filmAux->getNume() == nume) {
            break;
        }
    }

    inFile.close();

    return filmAux;
}

void ManagerFilme::adaugaFilm()
{
    string str_nume;
    string str_an;
    string str_durata;
	string nr_reviews;
	string review;
	int reviews[100];

    int an = 0;
    int durata = 0;
	int nrReviews = 0;

    cout << endl << g_Prefix << "Nume: ";
    cin >> str_nume;
    
    cout << endl << g_Prefix << "An: ";
    cin >> str_an;

    try { an = stoi(str_an); }
    catch (exception e) {}

    cout << endl << g_Prefix << "Durata: ";
    cin >> str_durata;

    try { durata = stoi(str_durata); }
    catch (exception e) {}

	cout << endl << g_Prefix << "Numar reviews: ";
	cin >> nr_reviews;

	try { nrReviews = stoi(nr_reviews); }
	catch (exception e) {}

	if (nrReviews > 0)
	{
		for (int i = 0;i < nrReviews;i++)
		{
			cout << endl << g_Prefix << "Nota: ";
			cin >> review;
			try { reviews[i] = stoi(review); }
			catch (exception e) {}
		}
	}

    Film* filmNou = new Film(str_nume.c_str(), an, durata);
	filmNou->setReviewuri(nrReviews, reviews);
	cout << g_Prefix << "Film adaugat: ";
    filmNou->afiseaza();

    filmNou->salveaza();
}

// Manager Cinema

void ManagerCinema::initializeaza()
{
    system("CLS");
    int optiune_selectata;

    do {
        afiseazaHeader("MENIU PRINCIPAL:");
        cout << g_Prefix << "1. Filme" << endl
             << g_Prefix << "2. Sali" << endl
             << g_Prefix << "3. Rezervari" << endl
             << g_Prefix << "4. Inchide" << endl;

        cout << endl << g_Prefix << "Va rugam selectati o optiune: ";
        cin >> optiune_selectata;

        switch (optiune_selectata) {
        case 1:
            afiseazaOptiuniFilme();
            break;
        case 2:
            afiseazaOptiuniSali();
        default:
            cout << g_Prefix << "\nVa rugam selectati o optiune valida!\n" << endl;
            cin.ignore();
        }
    } while (optiune_selectata != 4);
}

void ManagerCinema::afiseazaOptiuniSali()
{
    system("CLS");
    int optiune_selectata;

    do {
        afiseazaHeader("OPTIUNI SALI:");
        cout << g_Prefix << "1. Afiseaza sali" << endl
            << g_Prefix << "2. Adauga sala" << endl
            << g_Prefix << "3. Editeaza sala" << endl
            << g_Prefix << "4. Sterge sala" << endl
            << g_Prefix << "5. Inapoi" << endl;

        cout << endl << g_Prefix << "Va rugam selectati o optiune: ";
        cin >> optiune_selectata;

        switch (optiune_selectata)
        {
        case 1:
            afiseazaSali();
            break;

        case 2:
            adaugaSala();
            break;
        default:
            cout << "Va rugam selectati o optiune valida!" << endl;
            cin.ignore();
        }

    } while (optiune_selectata != 5);
}

void ManagerCinema::afiseazaSali()
{
    int optiune_selectata;

    do {
        system("CLS");
        afiseazaHeader("SALI DISPONIBILE:");
        
        ifstream inFile;
        inFile.open(g_BinarStocareSali, ios::binary);

		Sala sala;
        int idx = 0;

		int temp;
		char buffer[255];
		inFile.read((char*)&temp, sizeof(temp));
        while (!inFile.eof())
        {
			inFile.read(buffer, temp);
			sala.setNume(buffer);
			inFile.read((char*)&temp, sizeof(temp));
			sala.setLocuriDisponibile(temp);
            cout << g_Prefix << idx + 1 << ". ";
			sala.afiseaza();
            idx++;

			inFile.read((char*)&temp, sizeof(temp));
        }

        if (idx == 0)
        {
            cout << "\n" << g_Prefix << "Nicio sala disponibila!\n";
        }

        inFile.close();

        cout << "\n" << g_Prefix << "0. Inapoi" << endl;

        cout << endl << g_Prefix << "Va rugam selectati o optiune: ";
        cin >> optiune_selectata;

    } while (optiune_selectata != 0);

    afiseazaOptiuniSali();
}

void ManagerCinema::adaugaSala()
{
    system("CLS");
    afiseazaHeader("ADAUGA SALA  NOUA:");

    string str_nume;
    string str_locuri_disponibile;

    int locuri_disponibile = 0;

    cout << endl << g_Prefix << "Nume: ";
    cin >> str_nume;

    cout << endl << g_Prefix << "Locuri disponibile: ";
    cin >> str_locuri_disponibile;

    try {
        locuri_disponibile = stoi(str_locuri_disponibile);
    } catch (exception e){
        // TODO: trateaza exceptie.
    }

    Sala* salaNoua = new Sala(const_cast<char*>(str_nume.c_str()), locuri_disponibile);
    salaNoua->salveaza();
}

void ManagerCinema::afiseazaOptiuniFilme()
{
    system("CLS");
    int optiune_selectata;

    do {
        afiseazaHeader("OPTIUNI FILME:");
        cout << g_Prefix << "1. Afiseaza filme" << endl
             << g_Prefix << "2. Adauga film" << endl
             << g_Prefix << "3. Editeaza film" << endl
             << g_Prefix << "4. Sterge film" << endl
             << g_Prefix << "5. Inapoi" << endl;

        cout << endl << g_Prefix << "Va rugam selectati o optiune: ";
        cin >> optiune_selectata;

        switch (optiune_selectata) {
        case 1:
            afiseazaFilme();
            break;
        case 2:
            adaugaFilm();
            break;
        case 4:
            initializeaza();
            break;
        default:
            cout << "Va rugam selectati o optiune valida!" << endl;
            cin.ignore();
        }

    } while (optiune_selectata != 5);
}

void ManagerCinema::adaugaFilm()
{
    system("CLS");
    afiseazaHeader("ADAUGA FILM NOU:");
    ManagerFilme::adaugaFilm();
	_numarFilmeDisponibile++;
}

void ManagerCinema::afiseazaFilme()
{
    int optiune_selectata;

    do {
        system("CLS");
        afiseazaHeader("FILME DISPONIBILE:");
        ManagerFilme::afiseazaFilme(g_Prefix);

        cout << "\n" << g_Prefix << "0. Inapoi" << endl;

        cout << endl << g_Prefix << "Va rugam selectati o optiune: ";
        cin >> optiune_selectata;

    } while (optiune_selectata != 0);

    afiseazaOptiuniFilme();
}

void ManagerCinema::afiseazaHeader(string titlu)
{
    cout << g_Prefix << "===================================" << endl
         << g_Prefix << "Bine ati venit la: " << this << endl
         << g_Prefix << "===================================" << endl
         << g_Prefix << titlu << endl 
         << g_Prefix << "===================================" << endl;
}

ManagerCinema::ManagerCinema(const char* nume)
{
	if (nume != nullptr)
		_nume = nume;
	else
		_nume = nullptr;
}

ManagerCinema::~ManagerCinema()
{
    cout << "Cinematograful " << getNume() << " a fost inchis!";
}

ManagerCinema::ManagerCinema(const ManagerCinema& managerCinema)
{
	this->_nume = managerCinema._nume;
}

ManagerCinema& ManagerCinema::operator=(const ManagerCinema& managerCinema)
{
	this->_nume = managerCinema._nume;
	return *this;
}

ostream& operator<<(ostream& out, ManagerCinema* managerCinema)
{
	out << managerCinema->getNume();
	return out;
}

// Film

Film::Film(const char* nume, int an, int durata)
{
    this->setNume(nume);
    this->setAnLansare(an);
    this->setDurata(durata);
	_numarReviewuri = 0;
	_noteReviewuri = nullptr;
}

Film::Film(const Film& film)
{
	this->setNume(film._nume);
	this->setAnLansare(film._an_lansare);
	this->setDurata(film._durata);
	this->setReviewuri(film._numarReviewuri, film._noteReviewuri);
}

Film& Film::operator=(const Film& film)
{
	this->setNume(film._nume);
	this->setAnLansare(film._an_lansare);
	this->setDurata(film._durata);
	this->setReviewuri(film._numarReviewuri, film._noteReviewuri);
	return *this;
}

Film::~Film()
{
	if (this->_noteReviewuri != nullptr)
		delete[] this->_noteReviewuri;
	if (this->_nume != nullptr)
		delete[] this->_nume;
}

void Film::salveaza()
{
    ofstream outFile;
    outFile.open(g_BinarStocareFilme, ios::out | ios::app);

    Film* filmAux = ManagerFilme::creeazaFilm(this->getNume(), this->getAnLansare(), this->getDurata());
    
	int nameLength = strlen(filmAux->getNume()) + 1;
    outFile.write((char*)&nameLength, sizeof(nameLength));
	outFile.write(filmAux->getNume(), nameLength);
	int temp = filmAux->getAnLansare();
	int temp1;
	outFile.write((char*)&temp, sizeof(temp));
	temp = filmAux->getDurata();
	outFile.write((char*)&temp, sizeof(temp));
	temp = this->getNumarReviewuri();
	outFile.write((char*)&temp, sizeof(temp));
	for (int i = 0; i < temp;i++)
	{
		temp1 = (*this)[i];
		outFile.write((char*)&temp1, sizeof(temp1));
	}
    outFile.close();
}

ostream& operator<<(ostream& out, Film* film)
{
	out << film->getNume() <<  " - An: " << film->getAnLansare() << " Durata: " << film->getDurata() << " minute. " << endl;
	if (film->getNumarReviewuri() > 0)
	{
		out << g_Prefix << "	- Note: ";
		for (int i = 0;i < film->getNumarReviewuri();i++)
			out << (*film)[i] << " ";
		out << endl;
	}
	return out;
}

istream& operator>>(istream& in, Film* film)
{
	char buffer[255];
	in >> buffer;
	film->setNume(buffer);
	int temp;
	in >> temp;
	film->setAnLansare(temp);
	in >> temp;
	film->setDurata(temp);
	in >> temp;
	int tempArray[100];
	for (int i = 0;i < temp;i++)
	{
		in >> tempArray[i];
	}
	film->setReviewuri(temp, tempArray);
	return in;
}

int Film::operator[](int index)
{
	if (index >= 0 && index < this->_numarReviewuri)
	{
		return this->_noteReviewuri[index];
	}
	return 0;
}

// Sala

Sala::Sala() {}

Sala::Sala(const char* nume, int locuri_disponibile)
{
    this->setNume(nume);
    this->setLocuriDisponibile(locuri_disponibile);
}

Sala::Sala(const Sala& sala)
{
	this->setNume(sala._nume);
	this->setLocuriDisponibile(sala._locuri_disponibile);
}

Sala& Sala::operator=(const Sala& sala)
{
	this->setNume(sala._nume);
	this->setLocuriDisponibile(sala._locuri_disponibile);
	return *this;
}

Sala::~Sala()
{
	if (this->_nume != nullptr)
		delete[]this->_nume;
}

void Sala::salveaza()
{
    ofstream outFile;
    outFile.open(g_BinarStocareSali, ios::out | ios::app);

    Sala* salaAux = new Sala(this->getNume(), this->getLocuriDisponibile());
    
	int nameLength = strlen(salaAux->getNume()) + 1;
	outFile.write((char*)&nameLength, sizeof(nameLength));
	outFile.write(salaAux->getNume(), nameLength);
	int temp = salaAux->getLocuriDisponibile();
	outFile.write((char*)&temp, sizeof(temp));

    outFile.close();
}


ostream& operator<<(ostream& out, Sala* sala)
{
	out << "Sala " << sala->getNume() << " Locuri: " << sala->getLocuriDisponibile() << endl;
	return out;
}

istream& operator>>(istream& in, Sala* sala)
{
	char buffer[255];
	cout << "Introduceti nume sala:";
	in >> buffer;
	sala->setNume(buffer);
	cout << "Introduceti locuri disponibile:";
	int locuri;
	in >> locuri;
	sala->setLocuriDisponibile(locuri);
	return in;
}

Sala& Sala::operator!()
{
	Sala s(*this);
	s.setLocuriDisponibile(0);
	return s;
}

bool Sala::operator>(Sala& sala)
{
	if (this->_locuri_disponibile > sala._locuri_disponibile)
		return true;
	return false;
}

bool Sala::operator==(Sala& sala)
{
	if (strcmp(this->_nume, sala._nume) == 0 && this->_locuri_disponibile == sala._locuri_disponibile)
		return true;
	return false;
}

// Bilet

Bilet::Bilet(int id, string nume)
{
	this->id = id;
	this->nume_bilet = nume;
}

ostream& operator<<(ostream& out, Bilet* bilet)
{
	out << "id bilet: " << bilet->getId() << ", nume bilet: " << bilet->getNume();
	return out;
}

istream& operator>>(istream& in, Bilet* bilet)
{
	int temp;
	in >> temp;
	bilet->setId(temp);
	char buffer[255];
	in >> buffer;
	bilet->setNume(buffer);
	return in;
}


// Plata

Plata::Plata(std::string moneda, int suma)
{
	this->moneda = moneda;
	this->suma = suma;
}

int Plata::operator+(int sumaExtra)
{
	this->suma += sumaExtra;
	return this->suma;
}

int operator+(int sumaExtra, Plata plata)
{
	plata.setSuma(plata.getSuma() + sumaExtra);
	return plata.getSuma();
}

Plata& Plata::operator++()
{
	this->suma++;
	return *this;
}

Plata& Plata::operator++(int)
{
	this->suma++;
	return *this;
}

Plata::operator int() const
{
	return this->suma;
}

ostream& operator<<(ostream& out, Plata* plata)
{
	out << "moneda: " << plata->getMoneda() << ", suma: " << plata->getSuma();
	return out;
}

istream& operator>>(istream& in, Plata* plata)
{
	char buffer[255];
	in >> buffer;
	plata->setMoneda(buffer);
	int temp;
	in >> temp;
	plata->setSuma(temp);
	return in;
}

// Rezervare

ostream& operator<<(ostream& out, Rezervare* rezervare) 
{
	out << "Nume rezervare: " << rezervare->getNume();
	return out;
}

istream& operator>>(istream& in, Rezervare* rezervare)
{
	char buffer[255];
	in >> buffer;
	rezervare->setNume(buffer);
	return in;
}
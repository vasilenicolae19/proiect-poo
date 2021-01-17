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
	char buffer[255];

	inFile.read((char*)&temp, sizeof(temp));

    while (!inFile.eof())
    {
		std::vector<int> reviews;
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
			reviews.push_back(temp1);
		}

		filmAux.setReviewuri(reviews);
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

	std::vector<int> reviews;
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
			try { reviews.push_back(stoi(review)); }
			catch (exception e) {}
		}
	}

    Film* filmNou = new Film(str_nume.c_str(), an, durata);
	filmNou->setReviewuri(reviews);

	cout << g_Prefix << "Film adaugat: ";

	afisareDetaliata<Film>(filmNou);
    filmNou->salveaza(g_BinarStocareFilme);

    system("CLS");
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

        case 3:
            editeazaSala();
            break;

        case 4:
            stergeSala();
            break;

        case 5:
            initializeaza();
            break;

        default:
            cout << "Va rugam selectati o optiune valida!" << endl;
            cin.ignore();
        }

    } while (optiune_selectata != 5);
}

int ManagerCinema::totalFilmeDisponibile()
{
    ifstream inFile;
    inFile.open(g_BinarStocareFilme, ios::binary);

    int idx = 0;
    int temp, temp1;
    int tempArray[100];
    char buffer[255];

    inFile.read((char*)&temp, sizeof(temp));

    while (!inFile.eof())
    {
        inFile.read(buffer, temp);
        inFile.read((char*)&temp, sizeof(temp));
        inFile.read((char*)&temp, sizeof(temp));
        inFile.read((char*)&temp, sizeof(temp));

        for (int i = 0; i < temp; i++)
        {
            inFile.read((char*)&temp1, sizeof(temp1));
            tempArray[i] = temp1;
        }

        idx++;

        inFile.read((char*)&temp, sizeof(temp));
    }

    inFile.close();

    return idx;
}

int ManagerCinema::totalSaliDisponibile()
{
    ifstream inFile;
    inFile.open(g_BinarStocareSali, ios::binary);

    int idx = 0;

    int temp;
    char buffer[255];
    inFile.read((char*)&temp, sizeof(temp));

    while (!inFile.eof())
    {
        inFile.read(buffer, temp);
        inFile.read((char*)&temp, sizeof(temp));
        idx++;
        inFile.read((char*)&temp, sizeof(temp));
    }

    inFile.close();

    return idx;
}

void ManagerCinema::afiseazaSali()
{
    int optiune_selectata;

    do {
        system("CLS");
        afiseazaHeader("SALI DISPONIBILE: ");
        afiseazaListaSali();

        cout << "\n" << g_Prefix << "0. Inapoi" << endl;
        cout << endl << g_Prefix << "Va rugam selectati o optiune: ";

        cin >> optiune_selectata;

    } while (optiune_selectata != 0);

    afiseazaOptiuniSali();
}

void ManagerCinema::afiseazaListaSali()
{
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
}

Sala ManagerCinema::cautaSala(int id)
{
    ifstream inFile;
    inFile.open(g_BinarStocareSali, ios::binary);

    Sala salaAux;
    int idx = 1;

    int temp;
    char buffer[255];

    inFile.read((char*)&temp, sizeof(temp));

    while (!inFile.eof())
    {
        inFile.read(buffer, temp);
        inFile.read((char*)&temp, sizeof(temp));

        if (id == idx) {
            salaAux.setNume(buffer);
            salaAux.setLocuriDisponibile(temp);

            break;
        }

        idx++;

        inFile.read((char*)&temp, sizeof(temp));
    }

    inFile.close();

    return salaAux;
}

void ManagerCinema::editeazaSala()
{
    bool selectie_invalida;
    bool afiseaza_eroare = false;
    
    int total_sali_disponibile = totalSaliDisponibile();
    int sala_selectata;
    int sala_noua_locuri_disponibile;

    std::string str_mesaj_eroare;
    std::string str_sala_noua_nume;
    std::string str_sala_noua_nr_locuri;

    do {
        system("CLS");
        afiseazaHeader("EDITEAZA SALA:");

        if (afiseaza_eroare) {
            cout << endl << g_Prefix << "Eroare: " << str_mesaj_eroare << endl << endl;
        }

        afiseazaListaSali();

        cout << endl << g_Prefix << "Selectati sala: ";
        cin >> sala_selectata;
        
        selectie_invalida = sala_selectata <= 0 || sala_selectata > total_sali_disponibile;

        if (selectie_invalida) {
            afiseaza_eroare = true;
            str_mesaj_eroare = "Selectie invalida! (Valid: 1-" + std::to_string(total_sali_disponibile) + ")";
        }
    } while (selectie_invalida);

    cout << endl << g_Prefix << "Introduceti noile detalii: ";
    cout << endl << g_Prefix << "Nume: ";
    cin >> str_sala_noua_nume;

    cout << endl << g_Prefix << "Nr locuri: ";
    cin >> str_sala_noua_nr_locuri;

    try {
        sala_noua_locuri_disponibile = stoi(str_sala_noua_nr_locuri);
    } catch (exception e) {}

    ifstream inFile;

    std::string numeBinarTemp = std::string("temp") + std::string(g_BinarStocareSali);

    inFile.open(g_BinarStocareSali, ios::out | ios::app);

    Sala salaAux;
    int idx = 1;

    int temp;
    char buffer[255];

    inFile.read((char*)&temp, sizeof(temp));

    while (!inFile.eof())
    {
        inFile.read(buffer, temp);
        salaAux.setNume(buffer);

        inFile.read((char*)&temp, sizeof(temp));
        salaAux.setLocuriDisponibile(temp);

        if (sala_selectata == idx) {
            salaAux.setNume(const_cast<char*>(str_sala_noua_nume.c_str()));
            salaAux.setLocuriDisponibile(sala_noua_locuri_disponibile);
        }

        salaAux.salveaza(const_cast<char*>(numeBinarTemp.c_str()));

        idx++;

        inFile.read((char*)&temp, sizeof(temp));
    }

    inFile.close();

    remove(g_BinarStocareSali);
    rename(const_cast<char*>(numeBinarTemp.c_str()), g_BinarStocareSali);
    system("CLS");
}

void ManagerCinema::adaugaSala()
{
    system("CLS");
    afiseazaHeader("ADAUGA SALA NOUA:");

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
    salaNoua->salveaza(g_BinarStocareSali);
    system("CLS");
}

void ManagerCinema::stergeSala()
{
    bool selectie_invalida;
    bool afiseaza_eroare = false;

    int total_sali_disponibile = totalSaliDisponibile();
    int sala_selectata;
    int sala_noua_locuri_disponibile;

    std::string str_mesaj_eroare;

    do {
        system("CLS");
        afiseazaHeader("STERGE SALA:");

        if (afiseaza_eroare) {
            cout << endl << g_Prefix << "Eroare: " << str_mesaj_eroare << endl << endl;
        }

        afiseazaListaSali();

        cout << endl << g_Prefix << "Selectati sala: ";
        cin >> sala_selectata;

        selectie_invalida = sala_selectata <= 0 || sala_selectata > total_sali_disponibile;

        if (selectie_invalida) {
            afiseaza_eroare = true;
            str_mesaj_eroare = "Selectie invalida! (Valid: 1-" + std::to_string(total_sali_disponibile) + ")";
        }
    } while (selectie_invalida);

    ifstream inFile;

    std::string numeBinarTemp = std::string("temp") + std::string(g_BinarStocareSali);

    inFile.open(g_BinarStocareSali, ios::out | ios::app);

    Sala salaAux;
    int idx = 1;

    int temp;
    char buffer[255];

    inFile.read((char*)&temp, sizeof(temp));

    while (!inFile.eof())
    {
        inFile.read(buffer, temp);
        salaAux.setNume(buffer);

        inFile.read((char*)&temp, sizeof(temp));
        salaAux.setLocuriDisponibile(temp);

        if (sala_selectata == idx) {
            idx++;
            inFile.read((char*)&temp, sizeof(temp));

            continue;
        }

        salaAux.salveaza(const_cast<char*>(numeBinarTemp.c_str()));

        idx++;

        inFile.read((char*)&temp, sizeof(temp));
    }

    inFile.close();

    remove(g_BinarStocareSali);
    rename(const_cast<char*>(numeBinarTemp.c_str()), g_BinarStocareSali);
    system("CLS");
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

        case 3:
            editeazaFilm();

        case 4:
            stergeFilm();

        case 5:
            initializeaza();
            break;

        default:
            cout << "Va rugam selectati o optiune valida!" << endl;
            cin.ignore();
        }

    } while (optiune_selectata != 5);
}

void ManagerCinema::editeazaFilm()
{
    std::string str_mesaj_eroare;
    std::string str_film_nou_nume;
    std::string str_film_nou_an_lansare;
    std::string str_film_nou_durata;

    bool selectie_invalida;
    bool afiseaza_eroare = false;

    int total_filme_disponibile = totalFilmeDisponibile();
    int film_selectat;
    int film_nou_an_lansare;
    int film_nou_durata;

    do {
        system("CLS");
        afiseazaHeader("EDITEAZA FILM:");
        
        if (afiseaza_eroare)
        {
            cout << endl << g_Prefix << "Eroare: " << str_mesaj_eroare << endl << endl;
        }

        ManagerFilme::afiseazaFilme(g_Prefix);

        cout << endl << g_Prefix << "Selectati filmul: ";
        cin >> film_selectat;

        selectie_invalida = film_selectat <= 0 || film_selectat > total_filme_disponibile;

        if (selectie_invalida) {
            afiseaza_eroare = true;
            str_mesaj_eroare = "Selectie invalida! (Valid: 1-" + std::to_string(total_filme_disponibile) + ")";
        }
    } while (selectie_invalida);

    cout << endl << g_Prefix << "Introduceti noile detalii: ";
    
    // Nume nou
    cout << endl << g_Prefix << "Nume: ";
    cin >> str_film_nou_nume;

    // An lansare nou
    cout << endl << g_Prefix << "An lansare: ";
    cin >> str_film_nou_an_lansare;

    try {
        film_nou_an_lansare = stoi(str_film_nou_an_lansare);
    }
    catch (exception e) {}

    // Durata noua
    cout << endl << g_Prefix << "Durata: ";
    cin >> str_film_nou_durata;

    try {
        film_nou_durata = stoi(str_film_nou_durata);
    }
    catch (exception e) {}

    ifstream inFile;
    inFile.open(g_BinarStocareFilme, ios::binary);

    std::string numeBinarTemp = std::string("temp") + std::string(g_BinarStocareFilme);

    Film filmAux;

    int idx = 0;
    int temp, temp1;
    char buffer[255];

    inFile.read((char*)&temp, sizeof(temp));

    while (!inFile.eof())
    {
		std::vector<int> vector;
        inFile.read(buffer, temp);
        filmAux.setNume(buffer);

        inFile.read((char*)&temp, sizeof(temp));
        filmAux.setAnLansare(temp);

        inFile.read((char*)&temp, sizeof(temp));
        filmAux.setDurata(temp);

        inFile.read((char*)&temp, sizeof(temp));

        for (int i = 0; i < temp; i++)
        {
            inFile.read((char*)&temp1, sizeof(temp1));
			vector.push_back(temp1);
        }

        filmAux.setReviewuri(vector);

        idx++;

        inFile.read((char*)&temp, sizeof(temp));

        if (idx == film_selectat) {
            filmAux.setNume(const_cast<char*>(str_film_nou_nume.c_str()));
            filmAux.setAnLansare(film_nou_an_lansare);
            filmAux.setDurata(film_nou_durata);
        }

        filmAux.salveaza(const_cast<char*>(numeBinarTemp.c_str()));
    }

    inFile.close();

    remove(g_BinarStocareFilme);
    rename(const_cast<char*>(numeBinarTemp.c_str()), g_BinarStocareFilme);
    system("CLS");
}

void ManagerCinema::stergeFilm()
{
    std::string str_mesaj_eroare;
    std::string str_film_nou_nume;
    std::string str_film_nou_an_lansare;
    std::string str_film_nou_durata;

    bool selectie_invalida;
    bool afiseaza_eroare = false;

    int total_filme_disponibile = totalFilmeDisponibile();
    int film_selectat;
    int film_nou_an_lansare;
    int film_nou_durata;

    do {
        system("CLS");
        afiseazaHeader("STERGE FILM:");

        if (afiseaza_eroare)
        {
            cout << endl << g_Prefix << "Eroare: " << str_mesaj_eroare << endl << endl;
        }

        ManagerFilme::afiseazaFilme(g_Prefix);

        cout << endl << g_Prefix << "Selectati filmul: ";
        cin >> film_selectat;

        selectie_invalida = film_selectat <= 0 || film_selectat > total_filme_disponibile;

        if (selectie_invalida) {
            afiseaza_eroare = true;
            str_mesaj_eroare = "Selectie invalida! (Valid: 1-" + std::to_string(total_filme_disponibile) + ")";
        }
    } while (selectie_invalida);

    ifstream inFile;
    inFile.open(g_BinarStocareFilme, ios::binary);

    std::string numeBinarTemp = std::string("temp") + std::string(g_BinarStocareFilme);

    Film filmAux;

    int idx = 0;
    int temp, temp1;
    char buffer[255];

    inFile.read((char*)&temp, sizeof(temp));

    while (!inFile.eof())
    {
		std::vector<int> vector;
        inFile.read(buffer, temp);
        filmAux.setNume(buffer);

        inFile.read((char*)&temp, sizeof(temp));
        filmAux.setAnLansare(temp);

        inFile.read((char*)&temp, sizeof(temp));
        filmAux.setDurata(temp);

        inFile.read((char*)&temp, sizeof(temp));

        for (int i = 0; i < temp; i++)
        {
            inFile.read((char*)&temp1, sizeof(temp1));
			vector.push_back(temp1);
        }

        filmAux.setReviewuri(vector);

        idx++;

        inFile.read((char*)&temp, sizeof(temp));

        if (idx != film_selectat) {
            filmAux.salveaza(const_cast<char*>(numeBinarTemp.c_str()));
        }
    }

    inFile.close();

    remove(g_BinarStocareFilme);
    rename(const_cast<char*>(numeBinarTemp.c_str()), g_BinarStocareFilme);
    system("CLS");
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
    if (nume != nullptr) {
        _nume = nume;
    } else {
        _nume = nullptr;
    }

	this->plati["fizice"] = new Plata("ron", 100);
	this->plati["online"] = new PlataOnline("ron", 100);
}

ManagerCinema::~ManagerCinema()
{
    cout << g_Prefix << "Cinematograful " << getNume() << " a fost inchis!";
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
}

Film::Film(const Film& film)
{
	this->setNume(film._nume);
	this->setAnLansare(film._an_lansare);
	this->setDurata(film._durata);
	this->setReviewuri(film._noteReviewuri);
}

Film& Film::operator=(const Film& film)
{
	this->setNume(film._nume);
	this->setAnLansare(film._an_lansare);
	this->setDurata(film._durata);
	this->setReviewuri(film._noteReviewuri);

	return *this;
}

Film::~Film()
{
    if (this->_nume != nullptr) {
        delete[] this->_nume;
    }
}

void Film::salveaza(const char* fisier)
{
    ofstream outFile;
    outFile.open(fisier, ios::out | ios::app);

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
	int temp, temp1;
	in >> temp;
	film->setAnLansare(temp);
	in >> temp;
	film->setDurata(temp);
	in >> temp;
	std::vector<int> vector;

	for (int i = 0;i < temp;i++)
	{
		in >> temp1;
		vector.push_back(temp1);
	}

	film->setReviewuri(vector);

	return in;
}

int Film::operator[](int index)
{
	if (index >= 0 && index < this->_noteReviewuri.size())
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
    if (this->_nume != nullptr) {
        delete[]this->_nume;
    }
}

void Sala::salveaza(const char* fisier)
{
    ofstream outFile;
    outFile.open(fisier, ios::out | ios::app);

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
    if (this->_locuri_disponibile > sala._locuri_disponibile) {
        return true;
    }

	return false;
}

bool Sala::operator==(Sala& sala)
{
    if (strcmp(this->_nume, sala._nume) == 0 && this->_locuri_disponibile == sala._locuri_disponibile) {
        return true;
    }

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

void Plata::efectuarePlata(int suma)
{
	this->suma -= suma;
}

int Plata::restPlata()
{
	return this->suma;
}

// PlataOnline

void PlataOnline::efectuarePlata(int suma)
{
	//apelare endpoint plata online...
	this->suma -= suma;
}

int PlataOnline::restPlata()
{
	return 0.9 * this->suma;
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
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <cstring>

#include "Cinema.h"

using namespace std;

int main()
{
    ManagerCinema* p_ManagerCinema = new ManagerCinema;
    p_ManagerCinema->setNume(const_cast<char*>(g_NumeCinema));
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

    Film* filmAux;
    int idx = 0;

    while (inFile.read((char*)&filmAux, sizeof(filmAux)))
    {
        cout << prefix << idx + 1 << ". ";
        filmAux->afiseaza();
        idx++;
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

    int an = 0;
    int durata = 0;

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

    Film* filmNou = new Film();
    filmNou->setNume(str_nume.c_str());
    filmNou->setAnLansare(an);
    filmNou->setDurata(durata);
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
        default:
            cout << g_Prefix << "\nVa rugam selectati o optiune valida!\n" << endl;
            cin.ignore();
        }
    } while (optiune_selectata != 4);
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
         << g_Prefix << "Bine ati venit la: " << getNume() << endl
         << g_Prefix << "===================================" << endl
         << g_Prefix << titlu << endl 
         << g_Prefix << "===================================" << endl;
}

ManagerCinema::ManagerCinema()
{
}

ManagerCinema::~ManagerCinema()
{
    cout << "Cinematograful " << getNume() << " a fost inchis!";
}

// Film

Film::Film() {}

Film::Film(const char* nume, int an, int durata)
{
    this->setNume(nume);
    this->setAnLansare(an);
    this->setDurata(durata);
}

void Film::salveaza()
{
    ofstream outFile;
    outFile.open(g_BinarStocareFilme, ios::out | ios::app);
    Film* filmAux = ManagerFilme::creeazaFilm(this->getNume(), this->getAnLansare(), this->getDurata());
    outFile.write((char*)&filmAux, sizeof(this));
    outFile.close();
}


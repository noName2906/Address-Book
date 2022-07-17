#include <iostream>
#include <windows.h> //dla funkcji Sleep
#include <fstream> //praca z plikami
#include <sstream> //konwersja int na string
#include <cstdlib> //dla funkcji exit(0)
#include <algorithm>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

struct Adresat
{
    int id = 1;
    string imie, nazwisko, numerTelefonu, email, adres, noweImie, noweNazwisko, nowyNumerTelefonu, nowyEmail, nowyAdres;
};

void wczytajListe(vector <Adresat> &adresaci)
{
    string linia;
    int i = 0, nr_linii = 1;

    fstream plik;
    plik.open ("listaAdresatow.txt", ios::in);

    if (plik.good() == true)
    {
        Adresat obiekt;

        while (getline(plik, linia, '|'))
        {
            switch(nr_linii)
            {
            case 1:
                obiekt.id = atoi(linia.c_str());
                break;
            case 2:
                obiekt.imie = linia;
                break;
            case 3:
                obiekt.nazwisko = linia;
                break;
            case 4:
                obiekt.numerTelefonu = linia;
                break;
            case 5:
                obiekt.email = linia;
                break;
            case 6:
                obiekt.adres = linia;
                nr_linii = 0;
                getline(plik, linia);
                i++;
                adresaci.push_back(obiekt);
                break;
            }
            nr_linii++;
        }
    }
    plik.close();
}

void dodajAdresata(vector <Adresat> &adresaci)
{
    Adresat obiekt;
    string imie, nazwisko, numerTelefonu, email, adres;
    int idOstatniegoAdresata = 1;

    system("cls");
    cout << ">>>>> DODAWANIE NOWEGO ADRESATA <<<<<" << endl << endl;
    cin.ignore();
    cout << "Podaj imie: ";
    getline(cin, imie);
    cout << "Podaj nazwisko: ";
    getline(cin, nazwisko);
    cout << "Podaj numer telefonu: ";
    getline(cin, numerTelefonu);
    cout << "Podaj email: ";
    getline(cin, email);
    cout << "Podaj adres: ";
    getline(cin, adres);
    cout << endl;

    fstream plik;
    plik.open ("listaAdresatow.txt", ios::in);
    if(plik.good() == false)
    {
        idOstatniegoAdresata = 1;
    }
    else
    {
        idOstatniegoAdresata = adresaci.back().id + 1;
    }
    plik.close();

    obiekt.id = idOstatniegoAdresata;
    obiekt.imie = imie;
    obiekt.nazwisko = nazwisko;
    obiekt.numerTelefonu = numerTelefonu;
    obiekt.email = email;
    obiekt.adres = adres;

    adresaci.push_back(obiekt);

    cout << endl;
    plik.open ("listaAdresatow.txt", ios::out | ios::app);
    plik << idOstatniegoAdresata << "|" << imie << "|" << nazwisko << "|" << numerTelefonu << "|" << email << "|" << adres << "|" << endl;
    plik.close();
    cout << "Dane zostaly wprowadzone" << endl;
    Sleep(1500);
}

void wyswietlWszystkichAdresatow(vector <Adresat> &adresaci)
{
    fstream plik;
    plik.open ("listaAdresatow.txt", ios::in);
    if (plik.good() == false)
    {
        system ("cls");
        cout << ">>>>> UWAGA <<<<<" << endl << endl;
        cout << "Brak ksiazki adresowej. Nalezy ja uprzednio utworzyc" << endl << endl;
        system ("pause");
    }
    else
    {
        system("cls");
        cout << ">>>>> LISTA ADRESATOW <<<<<" << endl << endl;

        for(unsigned int i = 0; i < adresaci.size(); i++)
        {
            cout << "Numer ID:              " << adresaci[i].id << endl;
            cout << "Imie:                  " << adresaci[i].imie << endl;
            cout << "Nazwisko:              " << adresaci[i].nazwisko << endl;
            cout << "Numer telefonu:        " << adresaci[i].numerTelefonu << endl;
            cout << "Email:                 " << adresaci[i].email << endl;
            cout << "Adres:                 " << adresaci[i].adres << endl;
            cout << "-----------------      " << endl << endl;
        }
    }
    cout << "Ilosc adresatow w Twojej ksiazce: " << adresaci.size() << endl << endl;
    plik.close();
    system ("pause");
}

void wyszukajAdresataPoImieniu(vector <Adresat> &adresaci)
{
    string szukaneImie = "";
    int iloscAdresatow = 0, rozmiarWektora = adresaci.size();

    fstream plik;
    plik.open ("listaAdresatow.txt", ios::in);
    if (plik.good() == false)
    {
        system ("cls");
        cout << ">>>>> UWAGA <<<<<" << endl << endl;
        cout << "Brak ksiazki adresowej. Nalezy ja uprzednio utworzyc" << endl << endl;
        system("pause");
    }
    else
    {
        system ("cls");
        cout << ">>>>> WYSZUKAJ PO IMIENIU <<<<<" << endl << endl;
        cout << "Podaj szukane imie: ";
        cin >> szukaneImie;
        cout << endl;

        for (int i = 0; i < rozmiarWektora; i++)
        {
            if (adresaci[i].imie == szukaneImie)
            {
                cout << "Numer id:              " << adresaci[i].id << endl;
                cout << "Imie:                  " << adresaci[i].imie << endl;
                cout << "Nazwisko:              " << adresaci[i].nazwisko << endl;
                cout << "Numer telefonu:        " << adresaci[i].numerTelefonu << endl;
                cout << "Email:                 " << adresaci[i].email << endl;
                cout << "Adres:                 " << adresaci[i].adres << endl;
                cout << "-----------------------" << endl << endl;
                iloscAdresatow++;
            }
        }
        cout << endl;
        cout << "Ilosc adresatow o imieniu " << szukaneImie << ": " << iloscAdresatow << endl;
        system ("pause");
    }
}

void wyszukajAdresataPoNazwisku(vector <Adresat> &adresaci)
{
    string szukaneNazwisko = "";
    int iloscAdresatow = 0, rozmiarWektora = adresaci.size();

    fstream plik;
    plik.open ("listaAdresatow.txt", ios::in);
    if (plik.good() == false)
    {
        system ("cls");
        cout << ">>>>> UWAGA <<<<<" << endl << endl;
        cout << "Brak ksiazki adresowej. Nalezy ja uprzednio utworzyc" << endl << endl;
        system("pause");
    }

    else
    {
        system ("cls");
        cout << ">>>>> WYSZUKAJ PO NAZWISKU <<<<<" << endl << endl;
        cout << "Podaj szukane nazwisko: ";
        cin >> szukaneNazwisko;
        cout << endl;


        for (int i = 0; i < rozmiarWektora; i++)
        {
            if (adresaci[i].nazwisko == szukaneNazwisko)
            {
                cout << "Numer id:              " << adresaci[i].id << endl;
                cout << "Imie:                  " << adresaci[i].imie << endl;
                cout << "Nazwisko:              " << adresaci[i].nazwisko << endl;
                cout << "Numer telefonu:        " << adresaci[i].numerTelefonu << endl;
                cout << "Email:                 " << adresaci[i].email << endl;
                cout << "Adres:                 " << adresaci[i].adres << endl;
                cout << "-----------------------" << endl << endl;
                iloscAdresatow++;
            }
        }
        cout << endl;
        cout << "Ilosc adresatow o nazwisku " << szukaneNazwisko << ": " << iloscAdresatow << endl;
        system ("pause");
    }
}

void usunAdresata(vector <Adresat> &adresaci)
{
    vector <Adresat>::iterator it;
    int szukaneId = 0, rozmiarWektora = 0;
    char wybor;

    fstream plik;
    plik.open ("listaAdresatow.txt", ios::in);
    if (plik.good() == false)
    {
        system ("cls");
        cout << ">>>>> UWAGA <<<<<" << endl << endl;
        cout << "Brak ksiazki adresowej. Nalezy ja uprzednio utworzyc" << endl << endl;
        system("pause");
    }
    else
    {
        rozmiarWektora = adresaci.size();
        system ("cls");
        cout << ">>>>> USUN ADRESATA <<<<<" << endl << endl;
        cout << "Podaj ID osoby ktora chcesz usunac: ";
        cin >> szukaneId;
        cout << endl;

        for (int i = 0; i < rozmiarWektora; i++)
        {
            if (adresaci[i].id == szukaneId)
            {
                cout << "Numer ID:              " << adresaci[i].id << endl;
                cout << "Imie:                  " << adresaci[i].imie << endl;
                cout << "Nazwisko:              " << adresaci[i].nazwisko << endl;
                cout << "Numer telefonu:        " << adresaci[i].numerTelefonu << endl;
                cout << "Email:                 " << adresaci[i].email << endl;
                cout << "Adres:                 " << adresaci[i].adres << endl;
                cout << "-----------------------" << endl << endl;
                cout << "Czy na pewno chcesz usunac powyzszy adres?" << endl;
                cout << "Wcisnij 't' aby potwierdzic: ";
                cin >> wybor;

                if (wybor == 't')
                {
                    it = adresaci.begin() + i;
                    adresaci.erase(it);

                    rozmiarWektora = adresaci.size();
                    fstream plik;
                    plik.open("listaAdresatow.txt", ios::out);

                    for (int i = 0; i < rozmiarWektora; i++)
                    {
                        plik << adresaci[i].id << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|" << adresaci[i].numerTelefonu << "|" << adresaci[i].email << "|" << adresaci[i].adres << "|" << endl;
                    }
                    plik.close();
                    cout << endl;
                    cout << "Kontakt zostal usuniety" << endl;
                    Sleep (2000);
                }
                else
                {
                    cout << endl;
                    cout << "Kontakt nie zostal usuniety";
                    Sleep (2000);
                    break;
                }
            }
            else if (adresaci[i].id != szukaneId && i == rozmiarWektora-1)
            {
                cout << "Brak adresata o podanym numerze ID! Sprobuj jeszcze raz." << endl;
                Sleep(2000);
            }
        }
    }
}

void edytujAdresata(vector <Adresat> &adresaci)
{
    string noweImie, noweNazwisko, nowyNumerTelefonu, nowyEmail, nowyAdres;
    int szukaneId = 0, rozmiarWektora;
    char wybor = 0;

    fstream plik;
    plik.open ("listaAdresatow.txt", ios::in);
    if (plik.good() == false)
    {
        system ("cls");
        cout << ">>>>> UWAGA <<<<<" << endl << endl;
        cout << "Brak ksiazki adresowej. Nalezy ja uprzednio utworzyc" << endl << endl;
        system("pause");
    }
    else
    {
        rozmiarWektora = adresaci.size();
        system ("cls");
        cout << ">>>>> EDYTUJ ADRESATA <<<<<" << endl << endl;
        cout << "Podaj ID osoby, ktorej dane chcesz edytowac: ";
        cin >> szukaneId;
        cout << endl;

        for (int i = 0; i < rozmiarWektora; i++)
        {
            if (adresaci[i].id == szukaneId)
            {
                cout << "1. Imie:                  " << adresaci[i].imie << endl;
                cout << "2. Nazwisko:              " << adresaci[i].nazwisko << endl;
                cout << "3. Numer telefonu:        " << adresaci[i].numerTelefonu << endl;
                cout << "4. Email:                 " << adresaci[i].email << endl;
                cout << "5. Adres:                 " << adresaci[i].adres << endl;
                cout << "-----------------------" << endl << endl;
                cout << "Podaj numer elementu (1-5), ktory chcesz edytowac: ";
                cin >> wybor;
                cout << endl;

                cin.ignore();
                if (wybor == '1')
                {
                    cout << "Podaj nowe imie: ";
                    getline(cin, noweImie);
                    adresaci[i].imie = noweImie;
                }
                else if (wybor == '2')
                {
                    cout << "Podaj nowe nazwisko: ";
                    getline(cin, noweNazwisko);
                    adresaci[i].nazwisko = noweNazwisko;
                }
                else if (wybor == '3')
                {
                    cout << "Podaj nowy numer telefonu: ";
                    getline(cin, nowyNumerTelefonu);
                    adresaci[i].numerTelefonu = nowyNumerTelefonu;
                }
                else if (wybor == '4')
                {
                    cout << "Podaj nowy adres Email: ";
                    getline(cin, nowyEmail);
                    adresaci[i].email = nowyEmail;
                }
                else if (wybor =='5')
                {
                    cout << "Podaj nowy adres: ";
                    getline(cin, nowyAdres);
                    adresaci[i].adres = nowyAdres;
                }
                else
                {
                    cout << "Podales niepoprawna wartosc z przedzialu 1-5! Sprobuj jeszcze raz." << endl;
                    Sleep(2000);
                }
                fstream plik;
                plik.open("listaAdresatow.txt", ios::out);

                for (int i = 0; i < rozmiarWektora; i++)
                {
                    plik << adresaci[i].id << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|" << adresaci[i].numerTelefonu << "|" << adresaci[i].email << "|" << adresaci[i].adres << "|" << endl;
                }
                plik.close();

                if(wybor == '1' || wybor == '2' || wybor == '3' || wybor == '4' || wybor == '5')
                {
                    cout << endl;
                    cout << "Edycja kontaktu przebiegla pomyslnie" << endl;
                    Sleep (1500);
                    break;
                }
            }
            else if (adresaci[i].id != szukaneId && i == rozmiarWektora-1)
            {
                cout << "Brak adresata o podanym numerze ID! Sprobuj jeszcze raz." << endl;
                Sleep(2000);
            }
        }
    }
}

int main()
{
    vector <Adresat> adresaci;
    int wybor;

    wczytajListe(adresaci);

    while(true)
    {
        system("cls");
        cout << ">>>>> KSIAZKA ADRESOWA <<<<<" << endl << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyswietl wszystkich adresatow" << endl;
        cout << "3. Wyszukaj po imieniu" << endl;
        cout << "4. Wyszukaj po nazwisku" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl << endl;
        cout << "Twoj wybor: ";
        cin >> wybor;

        switch(wybor)
        {
        case 1:
             dodajAdresata(adresaci);
            break;
        case 2:
            wyswietlWszystkichAdresatow(adresaci);
            break;
        case 3:
            wyszukajAdresataPoImieniu(adresaci);
            break;
        case 4:
            wyszukajAdresataPoNazwisku(adresaci);
            break;
        case 5:
             usunAdresata(adresaci);
            break;
        case 6:
            edytujAdresata(adresaci);
            break;
        case 9:
            exit(0);
            break;
        default:
            cout << endl;
            cout << "Niepoprawny wybor. Sprobuj jeszcze raz" << endl;
            Sleep (1500);
            break;
        }
    }
    return 0;
}

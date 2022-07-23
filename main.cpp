#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

struct Uzytkownik
{
    int id = 1;
    string login, haslo;
};

struct Adresat
{
    int id = 1, idUzytkownika = 1;
    string imie, nazwisko, numerTelefonu, email, adres, noweImie, noweNazwisko, nowyNumerTelefonu, nowyEmail, nowyAdres;
};

void wczytajListe (vector <Uzytkownik> &uzytkownicy)
{
    string linia;
    int i = 0, nrLinii = 1;

    fstream plik;
    plik.open ("listaUzytkownikow.txt", ios::in);

    if (plik.good() == true)
    {
        Uzytkownik obiekt;

        while (getline(plik, linia, '|' ))
        {
            switch (nrLinii)
            {
            case 1:
                obiekt.id = atoi(linia.c_str());
                break;
            case 2:
                obiekt.login = linia;
                break;
            case 3:
                obiekt.haslo = linia;
                nrLinii = 0;
                getline(plik, linia);
                i++;
                uzytkownicy.push_back(obiekt);
                break;
            }
            nrLinii++;
        }
    }
    plik.close();
}

void wczytajListeAdresatow(vector <Adresat> &adresaci)
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
                obiekt.idUzytkownika = atoi(linia.c_str());
                break;
            case 3:
                obiekt.imie = linia;
                break;
            case 4:
                obiekt.nazwisko = linia;
                break;
            case 5:
                obiekt.numerTelefonu = linia;
                break;
            case 6:
                obiekt.email = linia;
                break;
            case 7:
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

void rejestracja (vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik obiekt;
    string login, haslo;
    int idOstatniegoUzytkownika = 1;

    system("cls");
    cout << ">>>>> REJESTRACJA <<<<<" << endl;
    cout << "-----------------------" << endl;
    cin.ignore();
    cout << "Podaj swoj login: ";
    getline(cin, login);
    cout << "Podaj swoje haslo: ";
    getline(cin, haslo);
    cout << endl;

    fstream plik;
    plik.open ("listaUzytkownikow.txt", ios::in);
    if(plik.good() == false)
    {
        idOstatniegoUzytkownika = 1;
    }
    else
    {
        idOstatniegoUzytkownika = uzytkownicy.back().id + 1;
    }
    plik.close();

    obiekt.id = idOstatniegoUzytkownika;
    obiekt.login = login;
    obiekt.haslo = haslo;

    uzytkownicy.push_back(obiekt);

    plik.open ("listaUzytkownikow.txt", ios::out | ios::app);
    plik << idOstatniegoUzytkownika << "|" << login << "|" << haslo << "|" << endl;
    plik.close();
    cout << "Uzytkownik " << login << " zostal poprawnie zarejestrowany" << endl;
    Sleep(2500);
}

int logowanie(vector <Uzytkownik> &uzytkownicy)
{
    string login, haslo;
    int rozmiarWektora = uzytkownicy.size();
    int idUzytkownika = 0;
    int main ();

    fstream plik;
    plik.open ("listaUzytkownikow.txt", ios::in);
    if (plik.good() == false)
    {
        system ("cls");
        cout << ">>>>> UWAGA <<<<<" << endl;
        cout << "-----------------" << endl;
        cout << "Brak zarejestrowanych uzytkownikow!" << endl;
        Sleep (2000);
        cout << "Nalezy uprzednio dokonac rejestracji." << endl << endl;
        Sleep (3000);
        return main ();
    }
    else
    {
        system ("cls");
        cout << ">>>>> LOGOWANIE <<<<<" << endl;
        cout << "---------------------" << endl;
        cout << "Podaj swoj login: ";
        cin >> login;

        for (int i = 0; i < rozmiarWektora; i++)
        {
            if (uzytkownicy[i].login == login)
            {
                for (int proby = 0; proby < 3; proby++)
                {
                    system ("cls");
                    cout << ">>>>> LOGOWANIE <<<<<" << endl;
                    cout << "---------------------" << endl;
                    cout << "Ilosc Twoich pozostalych prob logowania: " << 3-proby << endl << endl;
                    cout << "Podaj swoje haslo: ";
                    cin >> haslo;

                    if (uzytkownicy[i].haslo == haslo)
                    {
                        idUzytkownika = uzytkownicy[i].id;
                        cout << "Logowanie do systemu. Prosze czekac..." << endl;
                        Sleep (2500);
                        return idUzytkownika;
                    }
                }
                cout << endl;
                cout << "Podales 3 razy bledne haslo!" << endl;
                Sleep (2000);
                cout << "System zostal zablokowany i konczy swoje dzialanie..." << endl;
                Sleep (3000);
                exit (0);
            }
            else if (uzytkownicy[i].login != login && i == rozmiarWektora-1)
            {
                system ("cls");
                cout << ">>>>> LOGOWANIE <<<<<" << endl;
                cout << "---------------------" << endl;
                cout << "Brak uzytkownika z podanym loginem. Sprobuj jeszcze raz!";
                Sleep (2500);
                return main();
            }
        }
    }
    return idUzytkownika;
}

void dodajAdresata(vector <Adresat> &adresaci, int &idUzytkownika)
{
    Adresat obiekt;
    string imie, nazwisko, numerTelefonu, email, adres;
    int idOstatniegoAdresata = 1;

    system("cls");
    cout << ">>>>> DODAWANIE NOWEGO ADRESATA <<<<<" << endl;
    cout << "-------------------------------------" << endl;
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
    obiekt.idUzytkownika = idUzytkownika;
    obiekt.imie = imie;
    obiekt.nazwisko = nazwisko;
    obiekt.numerTelefonu = numerTelefonu;
    obiekt.email = email;
    obiekt.adres = adres;

    adresaci.push_back(obiekt);

    plik.open ("listaAdresatow.txt", ios::out | ios::app);
    plik << idOstatniegoAdresata << "|" << idUzytkownika << "|" << imie << "|" << nazwisko << "|" << numerTelefonu << "|" << email << "|" << adres << "|" << endl;
    plik.close();
    cout << "Dane zostaly wprowadzone" << endl;
    Sleep(2000);
}

void wyswietlWszystkichAdresatow(vector <Adresat> &adresaci, int &idUzytkownika)
{
    int iloscUzytkownikow = 0;
    fstream plik;
    plik.open ("listaAdresatow.txt", ios::in);
    if (plik.good() == false)
    {
        system ("cls");
        cout << ">>>>> UWAGA <<<<<" << endl;
        cout << "-----------------" << endl;
        cout << "Brak ksiazki adresowej. Nalezy ja uprzednio utworzyc" << endl << endl;
        system ("pause");
    }
    else
    {
        system("cls");
        cout << ">>>>> LISTA ADRESATOW <<<<<" << endl;
        cout << "---------------------------" << endl;
        for(unsigned int i = 0; i < adresaci.size(); i++)
        {
            if (adresaci[i].idUzytkownika == idUzytkownika)
            {
                cout << "Numer ID:              " << adresaci[i].id << endl;
                cout << "Imie:                  " << adresaci[i].imie << endl;
                cout << "Nazwisko:              " << adresaci[i].nazwisko << endl;
                cout << "Numer telefonu:        " << adresaci[i].numerTelefonu << endl;
                cout << "Email:                 " << adresaci[i].email << endl;
                cout << "Adres:                 " << adresaci[i].adres << endl;
                cout << "-----------------      " << endl << endl;
                iloscUzytkownikow++;
            }
        }
        cout << "Ilosc adresatow w Twojej ksiazce: " << iloscUzytkownikow << endl << endl;
        system ("pause");
    }
    plik.close();
}

void wyszukajAdresataPoImieniu(vector <Adresat> &adresaci, int &idUzytkownika)
{
    string szukaneImie = "";
    int iloscAdresatow = 0, rozmiarWektora = adresaci.size();

    fstream plik;
    plik.open ("listaAdresatow.txt", ios::in);
    if (plik.good() == false)
    {
        system ("cls");
        cout << ">>>>> UWAGA <<<<<" << endl;
        cout << "-----------------" << endl;
        cout << "Brak ksiazki adresowej. Nalezy ja uprzednio utworzyc" << endl << endl;
        system("pause");
    }
    else
    {
        system ("cls");
        cout << ">>>>> WYSZUKAJ PO IMIENIU <<<<<" << endl;
        cout << "-------------------------------" << endl;
        cout << "Podaj szukane imie: ";
        cin >> szukaneImie;
        cout << endl;

        for (int i = 0; i < rozmiarWektora; i++)
        {
            if (adresaci[i].idUzytkownika == idUzytkownika && adresaci[i].imie == szukaneImie)
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

void wyszukajAdresataPoNazwisku(vector <Adresat> &adresaci, int &idUzytkownika)
{
    string szukaneNazwisko = "";
    int iloscAdresatow = 0, rozmiarWektora = adresaci.size();

    fstream plik;
    plik.open ("listaAdresatow.txt", ios::in);
    if (plik.good() == false)
    {
        system ("cls");
        cout << ">>>>> UWAGA <<<<<" << endl;
        cout << "-----------------" << endl;
        cout << "Brak ksiazki adresowej. Nalezy ja uprzednio utworzyc" << endl << endl;
        system("pause");
    }
    else
    {
        system ("cls");
        cout << ">>>>> WYSZUKAJ PO NAZWISKU <<<<<" << endl;
        cout << "Podaj szukane nazwisko: ";
        cin >> szukaneNazwisko;
        cout << endl;

        for (int i = 0; i < rozmiarWektora; i++)
        {
            if (adresaci[i].idUzytkownika == idUzytkownika && adresaci[i].nazwisko == szukaneNazwisko)
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

void usunAdresata(vector <Adresat> &adresaci, int &idUzytkownika)
{
    vector <Adresat>::iterator it;
    int szukaneId = 0, rozmiarWektora = 0;
    char wybor;

    fstream plik;
    plik.open ("listaAdresatow.txt", ios::in);
    if (plik.good() == false)
    {
        system ("cls");
        cout << ">>>>> UWAGA <<<<<" << endl;
        cout << "-----------------" << endl;
        cout << "Brak ksiazki adresowej. Nalezy ja uprzednio utworzyc" << endl << endl;
        system("pause");
    }
    else
    {
        rozmiarWektora = adresaci.size();
        system ("cls");
        cout << ">>>>> USUN ADRESATA <<<<<" << endl;
        cout << "-------------------------" << endl;
        cout << "Podaj ID osoby ktora chcesz usunac: ";
        cin >> szukaneId;
        cout << endl;

        for (int i = 0; i < rozmiarWektora; i++)
        {
            if (adresaci[i].idUzytkownika == idUzytkownika && adresaci[i].id == szukaneId)
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
                        plik << adresaci[i].id << "|" << adresaci[i].idUzytkownika << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|" << adresaci[i].numerTelefonu << "|" << adresaci[i].email << "|" << adresaci[i].adres << "|" << endl;
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
            else if (adresaci[i].idUzytkownika == idUzytkownika && adresaci[i].id != szukaneId && i == rozmiarWektora-1)
            {
                cout << "Brak adresata o podanym numerze ID! Sprobuj jeszcze raz." << endl;
                Sleep (2000);
            }
            else if (adresaci[i].idUzytkownika != idUzytkownika && adresaci[i].id != szukaneId && i == rozmiarWektora-1)
            {
                cout << "Brak adresata o podanym numerze ID! Sprobuj jeszcze raz." << endl;
                Sleep (2000);
            }
    }
}
}

void edytujAdresata(vector <Adresat> &adresaci, int &idUzytkownika)
{
    string noweImie, noweNazwisko, nowyNumerTelefonu, nowyEmail, nowyAdres;
    int szukaneId = 0, rozmiarWektora;
    char wybor = 0;

    fstream plik;
    plik.open ("listaAdresatow.txt", ios::in);
    if (plik.good() == false)
    {
        system ("cls");
        cout << ">>>>> UWAGA <<<<<" << endl;
        cout << "-----------------" << endl;
        cout << "Brak ksiazki adresowej. Nalezy ja uprzednio utworzyc" << endl << endl;
        system("pause");
    }
    else
    {
        rozmiarWektora = adresaci.size();
        system ("cls");
        cout << ">>>>> EDYTUJ ADRESATA <<<<<" << endl;
        cout << "---------------------------" << endl;
        cout << "Podaj ID osoby, ktorej dane chcesz edytowac: ";
        cin >> szukaneId;
        cout << endl;

        for (int i = 0; i < rozmiarWektora; i++)
        {
            if (adresaci[i].idUzytkownika == idUzytkownika && adresaci[i].id == szukaneId)
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
                    plik << adresaci[i].id << "|" << adresaci[i].idUzytkownika << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|" << adresaci[i].numerTelefonu << "|" << adresaci[i].email << "|" << adresaci[i].adres << "|" << endl;
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

void zmianaHasla(vector <Uzytkownik> &uzytkownicy, int &idUzytkownika)
{
    int rozmiarWektora = 0;
    string noweHaslo;

    system ("cls");
    cout << ">>>>> ZMIANA HASLA <<<<<" << endl;
    cout << "------------------------" << endl;
    cout << "Podaj nowe haslo: ";
    cin.ignore();
    getline(cin, noweHaslo);

    fstream plik;
    plik.open ("listaUzytkownikow.txt", ios::in);

    if (plik.good() == true)
    {
        rozmiarWektora = uzytkownicy.size();
    }
    plik.close();

    for (int i = 0; i < rozmiarWektora; i++)
    {
        if (uzytkownicy[i].id == idUzytkownika)
        {
            uzytkownicy[i].haslo = noweHaslo;
            i = rozmiarWektora;
        }
    }

    plik.open("listaUzytkownikow.txt", ios::out);

    for (int i = 0; i < rozmiarWektora; i++)
    {
        plik << uzytkownicy[i].id << "|" << uzytkownicy[i].login << "|" << uzytkownicy[i].haslo << "|" << endl;
    }

    plik.close();
    cout << endl;
    cout << "Edycja hasla przebiegla pomyslnie" << endl;
    Sleep (1500);
}

int main()
{
    vector <Uzytkownik> uzytkownicy;
    vector <Adresat> adresaci;

    int wyborUzytkownicy = 0, wyborAdresaci = 0, idUzytkownika = 0;

    wczytajListe(uzytkownicy);

    while(true)
    {
        system("cls");
        cout << ">>>>> MENU GLOWNE <<<<<" << endl;
        cout << "-----------------------" << endl;
        cout << "1. Rejestracja" << endl;
        cout << "2. Logowanie" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "-----------------------" << endl;
        cout << "Twoj wybor: ";
        cin >> wyborUzytkownicy;

        switch(wyborUzytkownicy)
        {
        case 1:
            rejestracja(uzytkownicy);
            break;
        case 2:
            idUzytkownika = logowanie(uzytkownicy);
            wczytajListeAdresatow(adresaci);
            while(true)
            {
                system("cls");
                cout << ">>>>> MENU UZYTKOWNIKA <<<<<" << endl;
                cout << "----------------------------" << endl;
                cout << "1. Dodaj adresata" << endl;
                cout << "2. Wyswietl wszystkich adresatow" << endl;
                cout << "3. Wyszukaj po imieniu" << endl;
                cout << "4. Wyszukaj po nazwisku" << endl;
                cout << "5. Usun adresata" << endl;
                cout << "6. Edytuj adresata" << endl;
                cout << "----------------------------" << endl;
                cout << "7. Zmien haslo" << endl;
                cout << "8. Wyloguj sie" << endl;
                cout << "----------------------------" << endl;
                cout << "Twoj wybor: ";
                cin >> wyborAdresaci;

                switch(wyborAdresaci)
                {
                case 1:
                    dodajAdresata(adresaci, idUzytkownika);
                    break;
                case 2:
                    wyswietlWszystkichAdresatow(adresaci, idUzytkownika);
                    break;
                case 3:
                    wyszukajAdresataPoImieniu(adresaci, idUzytkownika);
                    break;
                case 4:
                    wyszukajAdresataPoNazwisku(adresaci, idUzytkownika);
                    break;
                case 5:
                    usunAdresata(adresaci, idUzytkownika);
                    break;
                case 6:
                    edytujAdresata(adresaci, idUzytkownika);
                    break;
                case 7:
                    zmianaHasla(uzytkownicy, idUzytkownika);
                    break;
                case 8:
                    return main();
                    break;
                default:
                    cout << endl;
                    cout << "Niepoprawny wybor. Sprobuj jeszcze raz" << endl;
                    Sleep (1500);
                    break;
                }
            }
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

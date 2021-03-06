// arnakoid.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctime>


using std::cin;
using std::cout;
using std::endl;

struct kulka{
	unsigned char x;
	unsigned char y;
	bool kierunekX;// true - prawo, false - lewo
	bool kierunekY;//true - gora, false - dol
};

void nowaGra(unsigned char tablica[][15], unsigned char poziomGry, short int *iloscKlockow);
void pokazPlansze(unsigned char tablica[][15]);
void resetujPlansze();
unsigned char ruchStatku(unsigned char pozycja, unsigned char dlugoscStatku);
void rysujStatek(unsigned char tablica[][15], unsigned char pozycja, unsigned char dlugoscStatku);
void losujPlansze(unsigned char tablica[][15], unsigned char poziomGry, short int *iloscKlockow);
kulka ruchPilki(kulka obiekt, unsigned char tablica[][15], bool* wyjscie, short int *iloscKlockow);
void pokazPilke(kulka obiekt, unsigned char tablica[][15]);
void usunPilke(kulka obiekt, unsigned char tablica[][15]);
unsigned char wyborPoziomuTrudnosci();

int main()
{
	bool* wyjscie = new bool;
	*wyjscie = false;
	unsigned char plansza[15][15]; // inicjacja gry
	unsigned char dlugoscStatku = 5;
	unsigned char pozycjaStatku = 3;
	unsigned char poziomGry = 2;
	unsigned char poziomTrudnosci = wyborPoziomuTrudnosci();
	short int iloscKlockow = poziomGry*poziomTrudnosci;
	kulka pilka;
	pilka.kierunekX = true;
	pilka.kierunekY = true;
	pilka.x = 1;	// Pozycja startowa
	pilka.y = 7;	// pilki
	nowaGra(plansza,poziomGry,&iloscKlockow);
	while (!*wyjscie) {
		pokazPlansze(plansza);
		usunPilke(pilka, plansza);
		pilka = ruchPilki(pilka, plansza, wyjscie, &iloscKlockow);
		pokazPilke(pilka, plansza);
		pozycjaStatku = ruchStatku(pozycjaStatku, dlugoscStatku);
		rysujStatek(plansza, pozycjaStatku, dlugoscStatku);
		resetujPlansze();
		if (iloscKlockow == 0) {
			poziomGry++;
			iloscKlockow = poziomGry * poziomTrudnosci;
			nowaGra(plansza, poziomGry, &iloscKlockow);
		}
	}
	delete wyjscie;
	cout << "Koniec gry. Wci\230nij Enter aby zako\344czy\206" << endl;
	//cin.ignore();
	cin.get();
    return 0;
}


void nowaGra(unsigned char tablica[][15],unsigned char poziomGry, short int* iloscKlockow) {

	for (unsigned char i = 0; i < 15; i++) {
		for (unsigned char j = 0; j < 15; j++) {
			 j == 0 || j == 14 ? tablica[i][j] = '|' : tablica[i][j] = ' ';
		}
	}
	losujPlansze(tablica, poziomGry, iloscKlockow);
}
void pokazPlansze(unsigned char tablica[][15]) {
	for (unsigned char i = 0; i < 15; i++) {
		for (unsigned char j = 0; j < 15; j++) {
			cout << tablica[i][j] << ' ';
		}
		cout << endl;
	}
}

void resetujPlansze() {
	Sleep(200);
	system("cls");
}

unsigned char ruchStatku(unsigned char pozycja,unsigned char dlugoscStatku) {
	if (GetAsyncKeyState(VK_LEFT) & 0x25) {
		if (pozycja - 1) pozycja--;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x27) {
		if (pozycja + dlugoscStatku != 14) pozycja++;
	}
	return pozycja;
}
void rysujStatek(unsigned char tablica[][15], unsigned char pozycja, unsigned char dlugoscStatku) {
	for (unsigned char i = 1; i < 14; i++) {
		tablica[14][i] = ' ';
	}

	for (unsigned char i = 1; i < 14; i++)
	{
		if (i == pozycja) {
			for(unsigned char j = pozycja;j < pozycja + dlugoscStatku ; j++)
			tablica[14][j] = '1';
		}
	}
}
void losujPlansze(unsigned char tablica[][15], unsigned char poziomGry, short int *iloscKlockow) {
	srand(time(NULL));
	for (short int i = 0; i < *iloscKlockow; i++) {
		tablica[rand() % poziomGry][rand() % 13 + 1] = '*';
	}
 }

kulka ruchPilki(kulka obiekt, unsigned char tablica[][15], bool* wyjscie, short int* iloscKlockow){
	if (obiekt.x  == 13) obiekt.kierunekX = false;
	if (obiekt.x == 1) obiekt.kierunekX = true;
	if (obiekt.y == 0) obiekt.kierunekY = false;
	if (obiekt.y == 14) *wyjscie = true;//obiekt.kierunekY = true;
	if (obiekt.y  != 0) {
		if (tablica[obiekt.y - 1][obiekt.x] == '*' && obiekt.kierunekY == true) {
			tablica[obiekt.y - 1][obiekt.x] = ' ';
			*iloscKlockow = *iloscKlockow - 1;
			obiekt.kierunekY = false;
		}
		if (tablica[obiekt.y][obiekt.x - 1] == '*' && obiekt.kierunekX == false) {
			tablica[obiekt.y][obiekt.x - 1] = ' ';
			*iloscKlockow = *iloscKlockow - 1;
			obiekt.kierunekX = true;
		}
		if (tablica[obiekt.y][obiekt.x + 1] == '*' && obiekt.kierunekX == true) {
			tablica[obiekt.y][obiekt.x + 1] = ' ';
			*iloscKlockow = *iloscKlockow - 1;
			obiekt.kierunekX = false;
		}
		if (tablica[obiekt.y + 1][obiekt.x] == '*' && obiekt.kierunekY == false) {
			tablica[obiekt.y + 1][obiekt.x] = ' ';
			*iloscKlockow = *iloscKlockow - 1;
			obiekt.kierunekY = true;
		}
		// ukosnie
		if (tablica[obiekt.y + 1][obiekt.x + 1] == '*' && obiekt.kierunekX == true && obiekt.kierunekY == false) {
			tablica[obiekt.y + 1][obiekt.x + 1] = ' ';
			*iloscKlockow = *iloscKlockow - 1;
			obiekt.kierunekY = true;
			obiekt.kierunekX = false;
		}
		if (tablica[obiekt.y - 1][obiekt.x - 1] == '*' && obiekt.kierunekX == false && obiekt.kierunekY == true) {
			tablica[obiekt.y - 1][obiekt.x - 1] = ' ';
			*iloscKlockow = *iloscKlockow - 1;
			obiekt.kierunekY = false;
			obiekt.kierunekX = true;
		}
		if (tablica[obiekt.y + 1][obiekt.x - 1] == '*' && obiekt.kierunekX == false && obiekt.kierunekY == false) {
			tablica[obiekt.y + 1][obiekt.x - 1] = ' ';
			*iloscKlockow = *iloscKlockow - 1;
			obiekt.kierunekY = true;
			obiekt.kierunekX = true;
		}
		if (tablica[obiekt.y - 1][obiekt.x + 1] == '*' && obiekt.kierunekX == true && obiekt.kierunekY == true) {
			tablica[obiekt.y - 1][obiekt.x + 1] = ' ';
			*iloscKlockow = *iloscKlockow - 1;
			obiekt.kierunekY = false;
			obiekt.kierunekX = false;
		}
	}

	if (tablica[obiekt.y + 1][obiekt.x] == '1')  obiekt.kierunekY = true;


	cout << tablica[obiekt.y][obiekt.x] << endl;
	obiekt.kierunekX ? obiekt.x++ : obiekt.x--;
	obiekt.kierunekY ? obiekt.y-- : obiekt.y++;
	return obiekt;
}
void pokazPilke(kulka obiekt, unsigned char tablica[][15]) {
	tablica[obiekt.y][obiekt.x] = 1;
	//cout << (int)obiekt.x << (int)obiekt.y;
	
}
void usunPilke(kulka obiekt, unsigned char tablica[][15]) {
	tablica[obiekt.y][obiekt.x] = ' ';
}

unsigned char wyborPoziomuTrudnosci() {
	cout << "Wybierz poziom trudnosci" << endl;
	cout << "1.Latwy" << endl;
	cout << "2.Sredni" << endl;
	cout << "3.Trudny" << endl;
	unsigned char poziom;
	cin >> poziom;
	switch (poziom) {
	case '1': {return 3; break; }
	case '2': {return 4; break; }
	case '3': {return 5; break; }
	default: {cout << "Wprowadziles zla liczbe"; break; }
	}
}
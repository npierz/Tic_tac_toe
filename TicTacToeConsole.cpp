// TickTackToeConsole.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <string>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>


using namespace std;
char plansza[3][3];
char Gracz = ' ';
char Komputer = ' ';
void wyswietl_plansze();
void umiesc_symbol(int, int, char);
void sprobuj_umiescic_symbol(int, int, char);
void nowa_gra();
void koniec_gry(string);
bool sprawdz_wygrana(char);
bool sprawdz_remis();
int sprawdz_stan_gry();
void ruch_komputera();

int main()
{
	srand(time(NULL));
	while (true) {
		nowa_gra();
		wyswietl_plansze();
		cout << "Wybierz kto zaczyna (g - gracz, k - komputer): " << endl;
		char kto_zaczyna;
		cin >> kto_zaczyna;
		int biezacy_gracz = (kto_zaczyna == 'g') ? 0 : 1;
		for (int i = 0; i < 9 && sprawdz_stan_gry() == 0; i++) {
			if (i % 2 == biezacy_gracz) {
				while (true) {
					int xt = 0, yt = 0;
					int kod_klawisza = 0;
					cout << "Wybierz miejsce strzalkami :" << endl;
					cout << "x = 0, y = 0" << endl;
					while (kod_klawisza != VK_RETURN) {
						FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
						_getch();
						kod_klawisza = _getch();
						switch (kod_klawisza) {
						case 72:
							yt = (yt + 1) % 3;
							break;
						case 80:
							yt = (yt - 1) % 3;
							break;
						case 75:
							xt = (xt - 1) % 3;
							break;
						case 77:
							xt = (xt + 1) % 3;
							break;
						default:
							if (kod_klawisza != VK_RETURN) cout << "Nacisnij strzalke albo enter" << endl;
							break;
						}
						cout << "x = " << abs(xt) << ", y = " << abs(yt) << endl;
					}
					int x, y;
					x = abs(xt);
					y = abs(yt);
					if (plansza[x][y] == ' ') plansza[x][y] = Gracz;
					else continue;
					break;
				}
			}
			else {
				if (i == 0 || i == 1) {
					while (true) {
						int x = rand() % 3;
						int y = rand() % 3;
						if (plansza[x][y] == ' ') plansza[x][y] = Komputer;
						else continue;
						break;
					}
				}
				else ruch_komputera();
			}
			wyswietl_plansze();
		}
		if (sprawdz_wygrana(Gracz)) cout << "Wygral gracz!" << endl;
		else if (sprawdz_wygrana(Komputer)) cout << "Wygral komputer!" << endl;
		else if (sprawdz_remis()) cout << "Remis!" << endl;
		wyswietl_plansze();
		cout << "Czy chcesz sprobowac ocalic ludzkosc przed inteligentnymi komputerami? Nacisnij 0 aby sie poddac: " << endl;
		int wybor_menu;
		cin >> wybor_menu;
		if (wybor_menu == 0) return 0;
	}
	system("cmd /c pause");
	return 0;
}

void umiesc_symbol(int x, int y, char symbol) {
	plansza[x][y] = symbol;
}

void sprobuj_umiescic_symbol(int x, int y, char symbol) {
	if (plansza[x][y] == ' ') {
		umiesc_symbol(x, y, symbol);
	}
	else cout << "W tym miejscu juz ktos stoi" << endl;
}

void nowa_gra() {
	system("cmd /c cls");
	for (int x = 0; x < 3; x++) for (int y = 0; y < 3; y++) plansza[x][y] = ' ';
	cout << "Podaj symbol gracza : ";
	cin >> Gracz;
	while (true) {
		cout << "Podaj symbol komputera : ";
		char tmp = ' ';
		cin >> tmp;
		if (tmp == Gracz) continue;
		else {
			Komputer = tmp;
			break;
		}
	}
}

void koniec_gry(string wiadomosc) {
	cout << "Gra zakonczona : " << wiadomosc << endl;
}

void wyswietl_plansze() {
	cout << " _____________ " << endl;
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			cout << " | " << plansza[x][y];
		}
		cout << " |";
		cout << endl << " _____________ " << endl;
	}
}

bool sprawdz_wygrana(char symbol) {
	for (int x = 0; x < 3; x++)
		if ((plansza[x][0] == symbol) && (plansza[x][1] == symbol) && (plansza[x][2] == symbol)) return true;
	for (int y = 0; y < 3; y++)
		if ((plansza[0][y] == symbol) && (plansza[1][y] == symbol) && (plansza[2][y] == symbol)) return true;
	if ((plansza[0][0] == symbol) && (plansza[1][1] == symbol) && (plansza[2][2] == symbol)) return true;
	if ((plansza[2][0] == symbol) && (plansza[1][1] == symbol) && (plansza[0][2] == symbol)) return true;
	return false;
}

bool sprawdz_remis() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (plansza[i][j] == ' ') return false;
		}
	}
	return true;
}

int sprawdz_stan_gry() {
	if (sprawdz_remis()) return 3;
	if (sprawdz_wygrana(Gracz)) return 1;
	if (sprawdz_wygrana(Komputer)) return 2;
	return 0;
}

int minimax(char aktualny_gracz) {
	int biezaca_wartosc, maksymalna_wartosc;
	if (sprawdz_wygrana(aktualny_gracz)) return (aktualny_gracz == Komputer) ? 1 : -1;
	if (sprawdz_remis()) return 0;
	aktualny_gracz = (aktualny_gracz == Komputer) ? Gracz : Komputer;
	maksymalna_wartosc = (aktualny_gracz == Gracz) ? 1000 : -1000;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (plansza[i][j] == ' ') {
				plansza[i][j] = aktualny_gracz;
				biezaca_wartosc = minimax(aktualny_gracz);
				plansza[i][j] = ' ';
				if ((aktualny_gracz == Gracz && biezaca_wartosc < maksymalna_wartosc) || (aktualny_gracz == Komputer && biezaca_wartosc > maksymalna_wartosc)) maksymalna_wartosc = biezaca_wartosc;
			}
		}
	}
	return maksymalna_wartosc;
}

void ruch_komputera() {
	int biezaca_wartosc, maksymalna_wartosc;
	maksymalna_wartosc = -1000;
	int wybrany_ruch[] = { 0,0 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (plansza[i][j] == ' ') {
				plansza[i][j] = Komputer;
				biezaca_wartosc = minimax(Komputer);
				plansza[i][j] = ' ';
				if (biezaca_wartosc > maksymalna_wartosc) {
					maksymalna_wartosc = biezaca_wartosc;
					wybrany_ruch[0] = i;
					wybrany_ruch[1] = j;
				}
			}
		}
	}
	sprobuj_umiescic_symbol(wybrany_ruch[0], wybrany_ruch[1], Komputer);
}

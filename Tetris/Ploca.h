#include <iostream>
#include <random>
#include <windows.h>
#include <io.h>
#include <conio.h>
#include"Lik.h"

using namespace std;

typedef int Stanje;

// sadrzi glavninu logike igre
class Ploca {
private:
	int _visina;
	int _sirina;
	bool _kraj = false;
	vector<vector<Stanje>> _matrica;
	Lik* _trenutniLik;
	Lik* _sljedeciLik;
	int _rezultat;
	bool _partijaIzgubljena = false; // oznacava kraj partije

	// pomocna metoda za generiranje nasumicnog broja koji odreduje nasumicni lik
	int nasumicniBroj(int min, int max);

	// generira nasumicne likove
	Lik* nasumicniLik();

	// brise redak ako je u potpunosti ispunjen
	void cisti();

	// prebacuje sljedeci lik na plocu
	void sljedeciLik();

	// zapocinje novu igru
	void novaIgra();

	// unos (kontrola) igre pomocu tipkovnice
	void unos();

	// crta trenutno stanje ploce
	void crtaj();

public:
	Ploca(int visina = 16, int sirina = 10);

	// pokrece igru
	bool igraj();
};
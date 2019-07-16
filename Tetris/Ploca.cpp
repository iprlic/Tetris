#include "Ploca.h"

// generiranje nasumicnog broja (stackoverflow)
int Ploca::nasumicniBroj(int min, int max) {
	random_device rd;     // only used once to initialise (seed) engine
	mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	uniform_int_distribution<int> uni(min, max); // guaranteed unbiased

	return uni(rng);
}

// odabiremo jednog od 7 mogucih likova
Lik * Ploca::nasumicniLik() {
	int r = nasumicniBroj(0, 6);

	switch (r) {
	case 0: return new O();
	case 1: return new T();
	case 2: return new I();
	case 3: return new Z();
	case 4: return new S();
	case 5: return new J();
	case 6: return new L();
	}
}

void Ploca::cisti() {
	int ocisceno = 0;
	for (int x = 0; x < _visina; x++) {
		bool svi = true;
		for (int y = 0; y < _sirina; y++)
			if (_matrica[x][y] == 0) svi = false;

		if (svi) {
			for (int y = 0; y < _sirina; y++) {
				for (int z = x; z >= 1; z--) {
					_matrica[z][y] = _matrica[z - 1][y];
				}

				_matrica[0][y] = 0;
			}
			ocisceno++;
		}
	}

	_rezultat += ocisceno * ocisceno; // kvadrat broja ociscenih linija (bolje je ocistit vise linija odjednom)
}

void Ploca::sljedeciLik() {
	_trenutniLik = _sljedeciLik;
	_sljedeciLik = nasumicniLik();
}

Ploca::Ploca(int visina, int sirina) {
	_visina = visina;
	_sirina = sirina;
	novaIgra();
}

void Ploca::novaIgra() {
	_partijaIzgubljena = false;
	_matrica.clear();
	_matrica.resize(_visina, vector<Stanje>(_sirina, 0));
	_rezultat = 0;
	_trenutniLik = nasumicniLik();
	_sljedeciLik = nasumicniLik();
}

bool Ploca::igraj() {
	int multiplier = 5; // svako x crtanje, lik pada
	int crtanja = 0;


	while (!_kraj)
	{
		crtaj();
		crtanja++;
		unos();

		if (crtanja - 1 == multiplier) { // igra mijenja stanje samo nakon svakih x crtanja (moguce prilagoditi)
			if (!_partijaIzgubljena) {
				if (_trenutniLik->uglavi(_matrica))
				{
					if (!_trenutniLik->vanPloce()) {
						cisti();
						sljedeciLik();
					}
					else {
						_partijaIzgubljena = true;
					}
				}

				*_trenutniLik - _matrica;
			}
			crtanja = 0;
		}

		Sleep(20);
	}

	return _kraj;
}

void Ploca::unos() {
	if (_kbhit()) {
		switch (_getch())
		{
		// https://stackoverflow.com/questions/10463201/getch-and-arrow-codes
		case 0:
		case 224:
			if(!_partijaIzgubljena)
			switch (_getch()) {
				case 72:
					//gore (rotiraj)
					*_trenutniLik * _matrica;
					break;
				case 80:
					//dolje
					*_trenutniLik - _matrica;
					break;
				case 77:
					//desno
					*_trenutniLik > _matrica;
					break;
				case 75:
					*_trenutniLik < _matrica;
					//lijevo
					break;
				}
				break;
		case 'n':
			//nova Igra
			novaIgra();
			break;
		case 'q':
			_kraj = true;
			break;
		}
	}
}

void Ploca::crtaj() {
	system("cls");

	for (int x = 0; x < _visina; x++) {
		cout << "|";;
		for (int y = 0; y < _sirina; y++) {
			if (_matrica[x][y] == 1)
				cout << "O";
			else if (_trenutniLik->sadrzi(x, y))
				cout << "X";
			else
				cout << " ";
		}
		cout << "|" << endl;;
	}

	
	for (int i = 0; i < _sirina; i++) {
		cout << "=";
	}

	cout << "==" << endl; // trebamo jos 2 za zatvoriti "polje"

	cout << "Rezultat: " << _rezultat << "\n" << endl;

	if (_kraj)
		cout << "Kraj igre, pritisnite 'n' za novu igru!" << endl;
	else {
		cout << "Sljedeci lik: " << endl;
		cout << *_sljedeciLik; // Lik ima nadgreden operator ispis
	}
}
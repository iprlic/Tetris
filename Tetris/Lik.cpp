#include "Lik.h"

Lik::Lik(int sirina=40, int visina=4) {
	_sirina = sirina;
	_visina = visina;
	_matrica.resize(_visina, vector<Stanje>(_sirina, 1));
}

bool Lik::uglavi(vector<vector<Stanje>> &ploca) {
	bool mozeUglavljenje = !mozeDolje(ploca);

	if (mozeUglavljenje) {
		for (int i = 0; i < _visina; i++)
			for (int j = 0; j < _sirina; j++)
				if (_matrica[i][j] == 1 && _lokacija_y + i > 0)
					ploca[_lokacija_y + i][_lokacija_x + j] = 1;
		return true;
	}

	return false;
}

bool Lik::sadrzi(int y, int x) {
	for (int i = 0; i < _visina; i++)
		for (int j = 0; j < _sirina; j++)
			if (j + _lokacija_x == x && i + _lokacija_y == y && _matrica[i][j] == 1)
				return true;
	return false;
}

bool Lik::vanPloce() {
	for (int i = 0; i < _visina; i++)
		for (int j = 0; j < _sirina; j++)
			if (i + _lokacija_y < 0 && _matrica[i][j] == 1)
				return true;
	return false;
}

bool Lik::mozeDesno(vector<vector<Stanje>>& ploca) {
	int _plocaSirina = ploca[0].size();
	for (int i = _visina - 1; i >= 0; i--)
		for (int j = 0; j < _sirina; j++)
			if (_matrica[i][j] == 1)
				if (_lokacija_x + j == _plocaSirina - 1)
					return false;
				else if (_lokacija_x + j + 1 <= _plocaSirina - 1 && _lokacija_y + i >= 0)
					if (ploca[_lokacija_y + i][_lokacija_x + j + 1] == 1) // ako je desno lika polje zauzeto
						return false;
	return true;
}

bool Lik::mozeLijevo(vector<vector<Stanje>>& ploca) {
	for (int i = 0; i < _visina; i++)
		for (int j = 0; j < _sirina; j++)
			if (_matrica[i][j] == 1)
				if (_lokacija_x + j == 0)
					return false;
				else if (_lokacija_x + j - 1 >= 0 && _lokacija_y + i >= 0)
					if (ploca[_lokacija_y + i][_lokacija_x + j - 1] == 1) // ako je lijevo lika polje zauzeto
						return false;

	return true;
}

bool Lik::mozeDolje(vector<vector<Stanje>>& ploca) {
	// moguca optimizacija -> ne provjeravati polja koja nisu na dnu
	for (int j = _sirina - 1; j >= 0; j--) // trazimo po redcima od dolje
		for (int i = 0; i < _visina; i++)
			if (_matrica[i][j] == 1)
				if (_lokacija_y + i == ploca.size() - 1) // ako smo u donjem retku
					return false;
				else if (_lokacija_y + i + 1 >= 0)
					if (ploca[_lokacija_y + i + 1][_lokacija_x + j] == 1) // ako je ispod lika polje zauzeto
						return false;

	return true;
}

bool Lik::mozeRotacija(vector<vector<Stanje>> &ploca, vector<vector<Stanje>> &nova_matrica) {
	for (int i = 0; i < _visina; i++)
		for (int j = 0; j < _sirina; j++)
			if (i + _lokacija_x < 0 || i + _lokacija_x > 9)
				return false;
			else if (j + _lokacija_y > 15)
				return false;
			else if (j + _lokacija_y > 0 && ploca[j + _lokacija_y][i + _lokacija_x] == 1 && nova_matrica[i][j] == 1)
				return false;
	return true;
}

void Lik::padaj() {
	_lokacija_y++;
}

void Lik::rotiraj(vector<vector<Stanje>> &ploca) {}

void Lik::desno() {
	_lokacija_x++;
}

void Lik::lijevo() {
	_lokacija_x--;
}

ostream& Lik::ispis(ostream& tok) {
	tok << endl;
	for (int i = 0; i < _visina; i++) {
		tok << "   ";
		for (int j = 0; j < _sirina; j++)
			if (_matrica[i][j] == 1)
				tok << "X";
			else
				tok << " ";
		tok << endl;
	}
	return tok;
}

// nadgradjeni operator ispisa:
ostream& operator<<(ostream& tok, Lik lik)
{
	return lik.ispis(tok);
}

void Lik::operator<(vector<vector<Stanje>> &ploca) {
	if (mozeLijevo(ploca)) lijevo();
}

void Lik::operator>(vector<vector<Stanje>> &ploca) {
	if (mozeDesno(ploca)) desno();
}

void Lik::operator-(vector<vector<Stanje>> &ploca) {
	if (mozeDolje(ploca)) padaj();
}

void Lik::operator*(vector<vector<Stanje>> &ploca) {
	rotiraj(ploca);
}


O::O() : Lik(2, 2) {
	_lokacija_y = -2;
}

I::I() : Lik(4, 4) {
	_lokacija_y = -4;
	_lokacija_x = 3;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (i != 2)
				_matrica[j][i] = 0;
}

void I::rotiraj(vector<vector<Stanje>> &ploca) {
	vector<vector<Stanje>> nova_matrica;
	nova_matrica.resize(_visina, vector<Stanje>(_sirina, 0));

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (_matrica[2][0] == 1) // trenutno horizontalan
				nova_matrica[j][i] = i != 2 ? 0: 1;
			else // trenutno vertikalan
				nova_matrica[j][i] = j != 2 ? 0 : 1;


	if (mozeRotacija(ploca, nova_matrica))
		_matrica = nova_matrica;
}

void TSZLJ::rotirajTocku(int x, int y, vector<vector<Stanje>>& nova_matrica) {
	float s = sin(PI / 2);
	float c = cos(PI / 2);

	x--;
	y--;

	// rotate point
	float x_novi = x * c - y * s;
	float y_novi = x * s + y * c;

	// translate point back:
	x = (int)round(x_novi + 1);
	y = (int)round(y_novi + 1);
	nova_matrica[x][y] = 1;
}

TSZLJ::TSZLJ(int sirina, int visina) : Lik(sirina, visina) {

}

void TSZLJ::rotiraj(vector<vector<Stanje>> &ploca) {
	vector<vector<Stanje>> nova_matrica;
	nova_matrica.resize(_visina, vector<Stanje>(_sirina, 0));

	nova_matrica[1][1] = _matrica[1][1];

	for (int i = 0; i < _visina; i++)
		for (int j = 0; j < _sirina; j++)
			if (!(i == 1 && j == 1) && _matrica[i][j] == 1)
				rotirajTocku(i, j, nova_matrica);
	if(mozeRotacija(ploca, nova_matrica))
		_matrica = nova_matrica;
}

J::J() : TSZLJ(3, 3) {
	_lokacija_y = -3;
	for (int i = 0; i < 3; i++)
		_matrica[0][i] = 0;
	_matrica[1][1] = 0;
	_matrica[1][2] = 0;
}

T::T() : TSZLJ(3, 3) {
	_lokacija_y = -3;
	for (int i = 0; i < 3; i++)
		_matrica[0][i] = 0;
	_matrica[1][0] = 0;
	_matrica[1][2] = 0;
}

S::S() : TSZLJ(3, 3) {
	_lokacija_y = -3;
	for (int i = 0; i < 3; i++)
		_matrica[0][i] = 0;
	_matrica[1][0] = 0;
	_matrica[2][2] = 0;
}

Z::Z() : TSZLJ(3, 3) {
	_lokacija_y = -3;
	for (int i = 0; i < 3; i++)
		_matrica[0][i] = 0;
	_matrica[1][2] = 0;
	_matrica[2][0] = 0;
}

L::L() : TSZLJ(3, 3) {
	_lokacija_y = -3;
	for (int i = 0; i < 3; i++)
		_matrica[0][i] = 0;
	_matrica[1][0] = 0;
	_matrica[1][1] = 0;
}

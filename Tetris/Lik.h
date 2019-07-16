#include <vector>
#include <iostream>
#define PI 3.14159265

typedef int Stanje;

using namespace std;

// nadklasa za sve likove
class Lik {
private:
	friend ostream & operator<<(ostream& tok, Lik lik);
protected:
	vector<vector<Stanje>> _matrica;
	int _lokacija_x = 4;
	int _lokacija_y = -2;
	int _sirina = 4;
	int _visina = 4;

	// provjera moze li se lik pomaknuti lijevo na ploci
	bool mozeLijevo(vector<vector<Stanje>> &ploca);

	// pomicanje lijevo na ploci
	void lijevo();

	// provjera moze li se lik pomaknuti desno na ploci
	bool mozeDesno(vector<vector<Stanje>> &ploca);

	// pomicanje desno na ploci
	void desno();

	// provjera moze li se lik pomaknuti dolje na ploci
	bool mozeDolje(vector<vector<Stanje>> &ploca);

	// pomicanje dolje (pad) na ploci
	void padaj();

	// provjera moze li se lik rotirati
	bool mozeRotacija(vector<vector<Stanje>> &ploca, vector<vector<Stanje>> &nova_lokacija);

	//rotiranje lika
	virtual void rotiraj(vector<vector<Stanje>> &ploca);

	// ispis lika
	ostream& ispis(ostream& tok);

public:
	Lik(int sirina, int visina);

	//uglavlivanje lika u plocu (kod pada do dna)
	bool uglavi(vector<vector<Stanje>> &ploca);

	//provjera sadrzi li lik odredene koordinate
	bool sadrzi(int y, int x);

	//provjera nalazi li se lik van ploce
	bool vanPloce();

	// operator micanja lijevo na ploci
	void operator<(vector<vector<Stanje>> &ploca);

	// operator micanja desno na ploci
	void operator>(vector<vector<Stanje>> &ploca);

	// operator micanja padanja na ploci
	void operator-(vector<vector<Stanje>> &ploca);

	// operator micanja rotiranja na ploci
	void operator*(vector<vector<Stanje>> &ploca);
};

// lik O -> "kocka": ne rotira se
class O : public Lik {
public:
	O();
};

// lik I -> "crta": rotacija ima samo 2 stanja
class I : public Lik {
protected:
	void rotiraj(vector<vector<Stanje>> &ploca);
public:
	I();
};

// nadklasa za ostale likove: puna rotacija, od 4 stanja
class TSZLJ : public Lik {
protected:
	// pomocna metoda za rotiranje tocke oko osi
	void rotirajTocku(int x, int y, vector<vector<Stanje>> &nova_matrica);
	void rotiraj(vector<vector<Stanje>> &ploca);

public:
	TSZLJ(int sirina = 3, int visina = 3);
};

class J : public TSZLJ {
public:
	J();
};

class T : public TSZLJ {
public:
	T();
};


class S : public TSZLJ {
public:
	S();
};

class Z : public TSZLJ {
public:
	Z();
};

class L : public TSZLJ {
public:
	L();
};

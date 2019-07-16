#include <iostream>
#include "Ploca.h"

using namespace std;

bool kraj = false;

int main() {

	Ploca ploca;

	system("cls");
	cout << "\n*****************TETRIS*******************"
		 << "\n\n-----------------Upute--------------------"
		 << "\nIgru igrate strelicama:"
		 << "\n - strelica lijevo mice lik lijevo"
		 << "\n - strelica desno mice lik desno"
		 << "\n - strelica dolje ubrzava pad lika"
		 << "\n - strelica gore rotira lik"
		<< "\nIgru možete prekinuti i poceti novi tipkom 'n'"
		 << "\n------------------------------------------"
		 << "\nUtipkajte 's' za pocetak ili 'q' to izlaz: ";

	do {
		char input = 's';
		cin >> input;
		if (input == 's')
			kraj = ploca.igraj();
		else if (input == 'q')
			kraj = true;

	} while (kraj == false);

	return 0;
}




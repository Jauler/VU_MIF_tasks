#include <iostream>

#include "DesignerDecorator.h"
#include "CoderDecorator.h"
#include "TesterDecorator.h"


using namespace std;

/*
	Situacija:
		Turime įmone su darbuotojais, įvairūs darbuotojai gali atlikti
		skirtingus darbus, tarkime, kad tai IT įmonė, tad darbuotojas
		gali atlikti šiuos veiksmus; "Design, Code, Test". Tai yra tarsi
		mūsų Rolė. Kartais darbuotojai gali atlikti kelius veiksmus vienam projektui
		pvz gali projektuoti ir programuoti ar pan. Projektuotojai turi. Kiekvienas darbuotojas
		turi savybę "atlyginimas" ir speciali rolė "manager" gali ją sau keisti
		Taip pat "manager" rolė turi specialią funkciją kuri leidžia pakeisti
		atlyginimą kitam darbuotojui.
*/

int main(void)
{
	cout << "Hello World!\n";

	//Create a general worker, but extended to do Designer and coding and testing
	Worker w("Rytis", 3000);
	CoderDecorator e(&w);
	DesignerDecorator e2(&e);
	TesterDecorator e3(&e2);
	e3.work();


	return 0;
}

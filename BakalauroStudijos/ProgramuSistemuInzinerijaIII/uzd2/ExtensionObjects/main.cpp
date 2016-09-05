#include <iostream>

#include "ManagerExtension.h"
#include "DesignerExtension.h"
#include "CoderExtension.h"
#include "TesterExtension.h"


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
	//Signle Extension example
	cout << "Single decorator example...\n";
	Worker w0("Worker0", 3000);
	CoderExtension ce0(&w0);
	w0.addExtension(&ce0);
	w0.work();
	cout << "\n\n";

	//Multiple Extension example
	cout << "Multiple decorator example...\n";
	Worker w1("Worker1", 2500);
	CoderExtension cd1(&w1);
	w1.addExtension(&cd1);
	DesignerExtension dd1(&w1);
	w1.addExtension(&dd1);
	TesterExtension td1(&w1);
	w1.addExtension(&td1);
	w1.work();
	cout << "\n\n";

	//Specific interface example
	cout << "Specific interface example...\n";
	Worker w2("Worker2", 4000);
	ManagerExtension md2(&w2);
	w2.addExtension(&md2);
	DesignerExtension dd2(&w2);
	w2.addExtension(&dd2);
	WorkerExtension *pmd2 = w2.getExtension("ManagerExtension");
	if(pmd2 != NULL){
		cout << "This is manager, so giving a raise to " << w0.getName() << "...\n";
		((ManagerExtension *)pmd2)->raiseWage(300, &w0);
	} else {
		cout << "ManagerExtension not found...\n";
	}
	cout << "\n\n";

	//Role removing example #0
	cout << "Role removing first extension example...\n";
	Worker w4("Worker4", 2500);
	DesignerExtension de4(&w4);
	w4.addExtension(&de4);
	CoderExtension ce4(&w4);
	w4.addExtension(&ce4);
	ManagerExtension me4(&w4);
	w4.addExtension(&me4);
	w4.work();
	cout << "Removing Designer Extension...\n";
	w4.rmExtension("DesignerExtension");
	w4.work();
	cout << "\n\n";

	//Role removing example #1
	cout << "Role removing middle extension example...\n";
	Worker w5("Worker5", 2500);
	DesignerExtension de5(&w5);
	w5.addExtension(&de5);
	CoderExtension ce5(&w5);
	w5.addExtension(&ce5);
	ManagerExtension me5(&w5);
	w5.addExtension(&me5);
	w5.work();
	cout << "Removing Coder Extension...\n";
	w5.rmExtension("CoderExtension");
	w5.work();
	cout << "\n\n";

	//Role removing example #2
	cout << "Role removing last extension example...\n";
	Worker w6("Worker6", 2500);
	DesignerExtension de6(&w6);
	w6.addExtension(&de6);
	CoderExtension ce6(&w6);
	w6.addExtension(&ce6);
	ManagerExtension me6(&w6);
	w6.addExtension(&me6);
	w6.work();
	cout << "Removing Manager Extension...\n";
	w6.rmExtension("ManagerExtension");
	w6.work();
	cout << "\n\n";

	//Role removing example #3
	cout << "Role removing multiple extension example...\n";
	Worker w7("Worker7", 2500);
	ManagerExtension de7(&w7);
	w7.addExtension(&de7);
	CoderExtension ce7(&w7);
	w7.addExtension(&ce7);
	ManagerExtension me7(&w7);
	w7.addExtension(&me7);
	w7.work();
	cout << "Removing Manager Extension...\n";
	w7.rmExtension("ManagerExtension");
	w7.work();
	cout << "\n\n";

	//Role removing example #4
	cout << "Role removing multiple in a row extension example...\n";
	Worker w8("Worker8", 2500);
	ManagerExtension de8(&w8);
	w8.addExtension(&de8);
	ManagerExtension ce8(&w8);
	w8.addExtension(&ce8);
	ManagerExtension me8(&w8);
	w8.addExtension(&me8);
	w8.work();
	cout << "Removing Manager Extension...\n";
	w8.rmExtension("ManagerExtension");
	w8.work();
	cout << "\n\n";

	return 0;
}

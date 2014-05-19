#include <iostream>

#include "ManagerDecorator.h"
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
	//Signle Decorator example
	cout << "Single decorator example...\n";
	Worker w0("Worker0", 3000);
	WorkerDecorator wd0(&w0);
	cout << w0.getWage() << endl << endl;

	wd0.work();
	cout << wd0.getWage() << endl;

	CoderDecorator cd0(&wd0);
	cout << cd0.getWage() << endl;
	cd0.work();
	cout << cd0.getWage() << endl;
	cout << "\n\n";

	//Multiple Decorator example
	cout << "Multiple decorator example...\n";
	Worker w1("Worker1", 2500);
	CoderDecorator cd1(&w1);
	DesignerDecorator dd1(&cd1);
	TesterDecorator td1(&dd1);
	td1.work();
	cout << "\n\n";

	//Specific interface example
	cout << "Specific interface example...\n";
	Worker w2("Worker2", 4000);
	ManagerDecorator md2(&w2);
	DesignerDecorator dd2(&md2);
	WorkerDecorator *pmd2 = dd2.getRole("ManagerDecorator");
	if(pmd2 != NULL){
		cout << "This is manager, so giving a raise to " << w0.getName() << "...\n";
		((ManagerDecorator *)pmd2)->raiseWage(300, &w0);
	} else {
		cout << "ManagerDecorator not found...\n";
	}
	cout << "\n\n";

	//Role acquiring example
	cout << "Role acquiring example...\n";
	Worker *w3 = new Worker("Worker3", 2450);
	Worker *tmpW3 = w3;
	w3->work();
	cout << "Adding designer role...\n";
	w3 = new DesignerDecorator(w3);
	Worker *tmpDD3 = w3;
	w3->work();
	cout << "Adding coder role...\n";
	w3 = new CoderDecorator(w3);
	Worker *tmpCD3 = w3;
	w3->work();
	cout << "\n\n";
	//Cleanup after example
	delete tmpW3;
	delete tmpDD3;
	delete tmpCD3;
	w3 = NULL;

	//Role removing example #0
	cout << "Role removing first decorator example...\n";
	Worker *w4 = new Worker("Worker4", 2500);
	Worker *tmpW4 = w4;
	w4 = new DesignerDecorator(w4);
	Worker *tmpDD4 = w4;
	w4 = new CoderDecorator(w4);
	Worker *tmpDC4 = w4;
	w4 = new ManagerDecorator(w4);
	Worker *tmpMD4 = w4;
	w4->work();
	cout << "Removing Designer decorator...\n";
	w4 = ((WorkerDecorator *)w4)->removeRole("DesignerDecorator");
	w4->work();
	delete tmpW4;
	delete tmpDD4;
	delete tmpDC4;
	delete tmpMD4;
	cout << "\n\n";

	//Role removing example, #1
	cout << "Role removing middle decorator example...\n";
	Worker *w5 = new Worker("Worker5", 2500);
	Worker *tmpW5 = w5;
	w5 = new DesignerDecorator(w5);
	Worker *tmpDD5 = w5;
	w5 = new CoderDecorator(w5);
	Worker *tmpDC5 = w5;
	w5 = new ManagerDecorator(w5);
	Worker *tmpMD5 = w5;
	w5->work();
	cout << "Removing Coder decorator...\n";
	w5 = ((WorkerDecorator *)w5)->removeRole("CoderDecorator");
	w5->work();
	delete tmpW5;
	delete tmpDD5;
	delete tmpDC5;
	delete tmpMD5;
	cout << "\n\n";

	//Role removing example, #3
	cout << "Role removing last decorator example...\n";
	Worker *w6 = new Worker("Worker6", 2500);
	Worker *tmpW6 = w6;
	w6 = new DesignerDecorator(w6);
	Worker *tmpDD6 = w6;
	w6 = new CoderDecorator(w6);
	Worker *tmpDC6 = w6;
	w6 = new ManagerDecorator(w6);
	Worker *tmpMD6 = w6;
	w6->work();
	cout << "Removing Manager decorator...\n";
	w6 = ((WorkerDecorator *)w6)->removeRole("ManagerDecorator");
	w6->work();
	delete tmpW6;
	delete tmpDD6;
	delete tmpDC6;
	delete tmpMD6;
	cout << "\n\n";

	//Role removing example, #4
	cout << "Role removing the same decorators example...\n";
	Worker *w7 = new Worker("Worker7", 2500);
	Worker *tmpW7 = w7;
	w7 = new ManagerDecorator(w7);
	Worker *tmpDD7 = w7;
	w7 = new CoderDecorator(w7);
	Worker *tmpDC7 = w7;
	w7 = new ManagerDecorator(w7);
	Worker *tmpMD7 = w7;
	w7->work();
	cout << "Removing Manager decorator...\n";
	w7 = ((WorkerDecorator *)w7)->removeRole("ManagerDecorator");
	w7->work();
	delete tmpW7;
	delete tmpDD7;
	delete tmpDC7;
	delete tmpMD7;
	cout << "\n\n";


	//Role removing example, #5
	cout << "Role removing the same decorators in a row example...\n";
	Worker *w8 = new Worker("Worker8", 2500);
	Worker *tmpW8 = w8;
	w8 = new ManagerDecorator(w8);
	Worker *tmpDD8 = w8;
	w8 = new ManagerDecorator(w8);
	Worker *tmpMD8 = w8;
	w8 = new CoderDecorator(w8);
	Worker *tmpDC8 = w8;
	w8->work();
	cout << "Removing Manager decorator...\n";
	w8 = ((WorkerDecorator *)w8)->removeRole("ManagerDecorator");
	w8->work();
	delete tmpW8;
	delete tmpDD8;
	delete tmpDC8;
	delete tmpMD8;
	cout << "\n\n";

	return 0;
}

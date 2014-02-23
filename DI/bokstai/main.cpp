#include <iostream>

#include <vector>
#include <string>

#include <stdio.h>

using namespace std;

class Pole {
public:
	char name;
	vector<unsigned int> discs;

	Pole(char name, vector<unsigned int> discs);
};

Pole::Pole(char _name, vector<unsigned int> _discs)
{
	name = _name;
	discs = _discs;
}

class Poles {
private:
	vector<Pole> poles;

public:
	Poles(int n);
	Pole &getPole(int n);
	string toString();
};

Poles::Poles(int n)
{
	poles.clear();

	//prepare discs vectors
	vector<unsigned int> srcPoles;
	vector<unsigned int> otherPoles;

	int i;
	for(i = 1; i <= n; i++)
		srcPoles.push_back(i);

	//create poles
	Pole poleA('A', srcPoles);
	poles.push_back(poleA);

	Pole poleB('B', otherPoles);
	poles.push_back(poleB);

	Pole poleC('C', otherPoles);
	poles.push_back(poleC);

	return;
}

Pole &Poles::getPole(int n)
{
	return poles[n];
}

string Poles::toString()
{
	string str;
	str = "{";
	int i, j;
	for(i = 0; i < poles.size(); i++){
		str+= "{";
		for(j = 0; j < poles[i].discs.size(); j++){
//			printf("dbg %d %lu\n", j, poles[i].discs.size());
//			fflush(stdout);
			str += std::to_string(poles[i].discs[j]);
			if(j + 1 < poles[i].discs.size())
				str += ",";
		}
		str+= "}";
	}

	str += "}";

	return str;
}



void moveDiscs(Poles &poles, Pole &src, Pole &tmp, Pole &dst, int start, int n)
{
	static int moves = 0;
	if(start)
		moves = 0;

	if(n <= 0)
		return;

	//move N-1 onto tmp
	if(n - 1 > 0)
		moveDiscs(poles, src, dst, tmp, 0, n - 1);

	//move disc to dsc
	int discN = src.discs.back();
	src.discs.pop_back();
	dst.discs.push_back(discN);

	moves++;
	cout << to_string(moves) + ": ";
	cout << poles.toString();
	printf(" Moved disc %d from pole %c to pole %c\n",
						discN,
						src.name,
						dst.name);

	//move N-1 from tmp to src
	if(n - 1 > 0)
		moveDiscs(poles, tmp, src, dst, 0, n - 1);

	return;
}


int main(void)
{
	int n;
	cout << "Please enter how much discs to put on first pole\n";
	cin >> n;

	//check our n
	if(n <= 0 || n > 10){
		cout << "Please enter number in the interval [1;10]\n";
		return 0;
	}

	Poles poles(n);

	cout << "Initially: " + poles.toString() + "\n";

	moveDiscs(poles, poles.getPole(0), poles.getPole(1), poles.getPole(2), 1, n);
	return 0;
}

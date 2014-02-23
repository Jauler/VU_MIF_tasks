#include <iostream>
#include <vector>

#include <stdio.h>

using namespace std;

class Pole {
public:
	char name;
	vector<unsigned int> discs;

	Pole(char name, vector<unsigned int> discs);
	void moveDiscs(Pole src, Pole tmp, Pole dst, int n);
};

Pole::Pole(char _name, vector<unsigned int> _discs)
{
	name = _name;
	discs = _discs;
}

void Pole::moveDiscs(Pole src, Pole tmp, Pole dst, int n)
{
	//do nothing if we have nothing to move
	if(n <= 0)
		return;

	if(n > 1){
		moveDiscs(src, dst, tmp, n - 1);
		moveDiscs(src, tmp, dst, 1);
		moveDiscs(tmp, src, dst, n - 1);
		return;
	}

	if(n == 1){
		unsigned int tmpDisc = src.discs.back();
		printf("moving %d from %c to %c\n", tmpDisc, src.name, dst.name);
		fflush(stdout);
		src.discs.pop_back();
		dst.discs.push_back(tmpDisc);
		printf("moved\n");
		fflush(stdout);
	}

	return;
}


int main(void)
{
	//prepare discs vectors
	vector<unsigned int> srcPoles;
	vector<unsigned int> otherPoles;

	int i;
	for(i = 1; i <= 3; i++)
		srcPoles.push_back(i);

	//create poles
	Pole poleA('A', srcPoles);
	Pole poleB('B', otherPoles);
	Pole poleC('C', otherPoles);

	poleA.moveDiscs(poleA, poleB, poleC, 3);

	return 0;
}

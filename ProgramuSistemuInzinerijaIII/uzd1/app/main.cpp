
//STLib includes
#include <iostream>

//General includes
#include "DeadlineEstimator.h"

//Strategy includes
#include "../strategy/QualityFirstDeadlineEstimator.h"
#include "../strategy/SpeedFirstDeadlineEstimator.h"
#include "../strategy/TeamATimeEstimator.h"
#include "../strategy/TeamBTimeEstimator.h"

//Template Method includes
#include "../tm/TM_QualityFirstDeadlineEstimator.h"
#include "../tm/TM_SpeedFirstDeadlineEstimator.h"
#include "../tm/TM_QualityFirstTeamADeadlineEstimator.h"
#include "../tm/TM_QualityFirstTeamBDeadlineEstimator.h"
#include "../tm/TM_QualityFirstTeamCDeadlineEstimator.h"
#include "../tm/TM_SpeedFirstTeamADeadlineEstimator.h"
#include "../tm/TM_SpeedFirstTeamBDeadlineEstimator.h"


using namespace std;

int main(void)
{
	//Read difficulty
	int difficulty;
	cout << "    Please enter project difficulty on the scale from 1 to 10: ";
	cin >> difficulty;
	if(difficulty <= 0 || difficulty > 10){
		cout << "    Difficulty should be in the range of [1;10]";
		return 0;
	}
	cout << "    Difficulty level is set to " << difficulty << "\n";

	/*
		Strategy Demonstation
	*/

	//Print out results
	cout << "Strategy Demostration:\n";
	cout << "    ---------Results-------\n";

	//declare deadline estimator
	DeadlineEstimator *deadlineEstimator0;
	DeadlineEstimator *deadlineEstimator1;
	DeadlineEstimator *deadlineEstimator2;
	DeadlineEstimator *deadlineEstimator3;

	DeadlineEstimator *deadlineEstimator4;
	DeadlineEstimator *deadlineEstimator5;
	DeadlineEstimator *deadlineEstimator6;
	DeadlineEstimator *deadlineEstimator7;

	TimeEstimator *te;

	//Quality first, team A
	te = new TeamATimeEstimator();
	deadlineEstimator0 = new QualityFirstDeadlineEstimator(te);
	cout << "    Quality first, Team A time to deadline: ";
	cout << deadlineEstimator0->calcTimeToDeadline(difficulty);
	cout << "\n";
	delete deadlineEstimator0;
	delete te;

	//Quality first, team B
	te = new TeamBTimeEstimator();
	deadlineEstimator1 = new QualityFirstDeadlineEstimator(te);
	cout << "    Quality first, Team B time to deadline: ";
	cout << deadlineEstimator1->calcTimeToDeadline(difficulty);
	cout << "\n";
	delete deadlineEstimator1;
	delete te;

	//Speed first, team A
	te = new TeamATimeEstimator();
	deadlineEstimator2 = new SpeedFirstDeadlineEstimator(te);
	cout << "    Speed first, Team A time to deadline: ";
	cout << deadlineEstimator2->calcTimeToDeadline(difficulty);
	cout << "\n";
	delete deadlineEstimator2;
	delete te;

	//Speed first, team A
	te = new TeamBTimeEstimator();
	deadlineEstimator3 = new SpeedFirstDeadlineEstimator(te);
	cout << "    Speed first, Team B time to deadline: ";
	cout << deadlineEstimator3->calcTimeToDeadline(difficulty);
	cout << "\n";
	delete deadlineEstimator3;
	delete te;

	/*
		Method Template Demonstration
	*/

	//Introduction
	cout << "Method Template Demosntration:\n";
	cout << "    -----------Results------\n";

	//Quality first, team A
	deadlineEstimator4 = new TM_QualityFirstTeamADeadlineEstimator();
	cout << "    Quality first, Team A time to deadline: ";
	cout << deadlineEstimator4->calcTimeToDeadline(difficulty);
	cout << "\n";
	delete deadlineEstimator4;

	//Quality first, team B
	deadlineEstimator5 = new TM_QualityFirstTeamBDeadlineEstimator();
	cout << "    Quality first, Team B time to deadline: ";
	cout << deadlineEstimator5->calcTimeToDeadline(difficulty);
	cout << "\n";
	delete deadlineEstimator5;

	//Quality first, team C
	deadlineEstimator5 = new TM_QualityFirstTeamCDeadlineEstimator();
	cout << "    Quality first, Team C time to deadline: ";
	cout << deadlineEstimator5->calcTimeToDeadline(difficulty);
	cout << "\n";
	delete deadlineEstimator5;

	//Speed first, team A
	deadlineEstimator6 = new TM_SpeedFirstTeamADeadlineEstimator();
	cout << "    Speed first, Team A time to deadline: ";
	cout << deadlineEstimator6->calcTimeToDeadline(difficulty);
	cout << "\n";
	delete deadlineEstimator6;

	//Speed first, team B
	deadlineEstimator7 = new TM_SpeedFirstTeamBDeadlineEstimator();
	cout << "    Speed first, Team B time to deadline: ";
	cout << deadlineEstimator7->calcTimeToDeadline(difficulty);
	cout << "\n";
	delete deadlineEstimator7;

	return 0;
}








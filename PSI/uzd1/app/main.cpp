
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
		return;
	}
	cout << "    Difficulty level is set to " << difficulty << "\n";

	/*
		Strategy Demonstation
	*/

	//Print out results
	cout << "Strategy Demostration:\n";
	cout << "    ---------Results-------\n";

	//declare deadline estimator
	DeadlineEstimator *deadlineEstimator;
	TimeEstimator *te;

	//Quality first, team A
	te = new TeamATimeEstimator();
	deadlineEstimator = new QualityFirstDeadlineEstimator(te);
	cout << "    Quality first, Team A time to deadline: ";
	cout << deadlineEstimator->calcTimeToDeadline(difficulty);
	cout << "\n";
	delete deadlineEstimator;
	delete te;

	//Quality first, team B
	te = new TeamBTimeEstimator();
	deadlineEstimator = new QualityFirstDeadlineEstimator(te);
	cout << "    Quality first, Team B time to deadline: ";
	cout << deadlineEstimator->calcTimeToDeadline(difficulty);
	cout << "\n";
	delete deadlineEstimator;
	delete te;

	//Speed first, team A
	te = new TeamATimeEstimator();
	deadlineEstimator = new SpeedFirstDeadlineEstimator(te);
	cout << "    Speed first, Team A time to deadline: ";
	cout << deadlineEstimator->calcTimeToDeadline(difficulty);
	cout << "\n";
	delete deadlineEstimator;
	delete te;

	//Speed first, team A
	te = new TeamBTimeEstimator();
	deadlineEstimator = new SpeedFirstDeadlineEstimator(te);
	cout << "    Speed first, Team B time to deadline: ";
	cout << deadlineEstimator->calcTimeToDeadline(difficulty);
	cout << "\n";
	delete deadlineEstimator;
	delete te;

	/*
		Method Template Demonstration
	*/

	//Introduction
	cout << "Method Template Demosntration:\n";
	cout << "    -----------Results------\n";

	//Quality first, team A
	deadlineEstimator = new TM_QualityFirstTeamADeadlineEstimator();
	cout << "    Quality first, Team A time to deadline: ";
	cout << deadlineEstimator->calcTimeToDeadline(difficulty);
	cout << "\n";
	delete deadlineEstimator;

	//Quality first, team B
	deadlineEstimator = new TM_QualityFirstTeamBDeadlineEstimator();
	cout << "    Quality first, Team B time to deadline: ";
	cout << deadlineEstimator->calcTimeToDeadline(difficulty);
	cout << "\n";
	delete deadlineEstimator;

	//Speed first, team A
	deadlineEstimator = new TM_SpeedFirstTeamADeadlineEstimator();
	cout << "    Speed first, Team A time to deadline: ";
	cout << deadlineEstimator->calcTimeToDeadline(difficulty);
	cout << "\n";
	delete deadlineEstimator;

	//Speed first, team B
	deadlineEstimator = new TM_SpeedFirstTeamBDeadlineEstimator();
	cout << "    Speed first, Team B time to deadline: ";
	cout << deadlineEstimator->calcTimeToDeadline(difficulty);
	cout << "\n";
	delete deadlineEstimator;

	return 0;
}








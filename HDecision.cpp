/*******************************************************************
 *
 *  DESCRIPTION: Atomic Model Hero Decision
 *
 *  AUTHOR: Qingzhong Liang
 *
 *  EMAIL: liangqz89@gmail.com
 *
 *  DATE: 11/10/2014
 *
 *******************************************************************/

/** include files **/
#include "HDecision.h"      // class HDecision
#include "Common.h"
#include <stdlib.h>
#include <stdlib.h>
#include "message.h"    // class ExternalMessage, InternalMessage
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )
#include <stdlib.h>

/** public functions **/

/*******************************************************************
 * Function Name: Ddecision
 * Description:
 ********************************************************************/
int HDecision::heroCount = 0;

HDecision::HDecision(const string &name) :	Atomic(name)
, creepIn(addInputPort("creepIn"))
, heroIn(addInputPort("heroIn"))
, attackOut(addOutputPort("attackOut"))
//, preparationTime( 0, 0, 3, 0 )
{
	index = 1;
	heroCount++;
	heroId = heroCount;

	hp = 100;
	damage = 50;

	isEnemyCreepDead = false;
	isEnemyHeroDead = false;
	takeTheLastHit = false;
	isDead = false;
}

/*******************************************************************
 * Function Name: initFunction
 * Description: Initialize model, set to passive
 ********************************************************************/
Model &HDecision::initFunction() {
	this-> passivate();


	return *this;
}

/*******************************************************************
 * Function Name: externalFunction
 * Description:
 ********************************************************************/
Model &HDecision::externalFunction(const ExternalMessage &msg) {
	cout << msg.time() << " hero " << heroId << " decision externalFunction" << endl;
	int fromTargetIndex = -1;
	char *fromTarget[2] = { "Enemy Creep", "Enemy Hero" };
	if (msg.port() == creepIn) {
		fromTargetIndex = 0;
	} else if (msg.port() == heroIn) {
		fromTargetIndex = 1;
	}

	packet = static_cast<int> (msg.value());
	int messageType = getMessageType(packet);
	int parameter = getMessageParameter(packet);
	//dead
	if (messageType == Dead) {
		cout << fromTarget[fromTargetIndex] << " is Dead" << endl;
		if (fromTargetIndex == 0) {
			isEnemyCreepDead = true;
		} else {
			isEnemyHeroDead = true;
		}
	}
	//attack
	else if (messageType == Damage) {
		cout << "From " << fromTarget[fromTargetIndex] << " Damage: -"
				<< parameter << endl;
		hp = hp - parameter;

		if (hp <= 0) {
			cout << "hero is dead" << endl;
			isDead = true;
		} else {
			cout << "hero " << heroId << " remain " << hp << " hp" << endl;
		}
	}
	//health point
	else if (messageType == ShowCreepsHP) {
		cout << "Enemy creep's HP: " << parameter << endl;
		if (parameter <= damage) {
			takeTheLastHit = true;
		}
	}

	attackFunction();

	holdIn(active, Time::Zero); //instant decision
	return *this;
}

/*******************************************************************
 * Function Name: internalFunction
 * Description:
 ********************************************************************/
Model &HDecision::internalFunction(const InternalMessage &) {
	passivate();
	return *this;
}

/*******************************************************************
 * Function Name: outputFunction
 * Description:
 ********************************************************************/
Model &HDecision::outputFunction(const InternalMessage &msg) {
	cout << msg.time() << " hero " << heroId << " decision outputFunction" << endl;
	//To Do
	int message = getToSendMessage(atkMessage, damage);
	cout << "outputMessage: " << message << endl;
	sendOutput(msg.time(), attackOut, message);
	takeTheLastHit = false;
	cout << endl;
	return *this;
}

void HDecision::attackFunction() {

	int n = rand() % 100;
	if (takeTheLastHit) {
		atkMessage = attackCreep;
	} else if (isDead) {
		atkMessage = heroDead;
	} else if (isEnemyHeroDead) {
		atkMessage = enemyHeroDead;
	} else if (!isEnemyCreepDead) {
		if (n < 60) {
			atkMessage = doNothing;
		} else {

			n = rand() % 100;
			if (n < 70) {
				atkMessage = attackCreep;
			} else {
				atkMessage = attackHero;
			}
		}
	} else {
		atkMessage = attackHero;
	}

}

HDecision::~HDecision() {
	//delete dist;
	//delete packet;
	//delete index;
	//delete hp;
}

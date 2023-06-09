/*******************************************************************
*
*  DESCRIPTION: Atomic Model Creep
*
*  AUTHOR: Qingzhong Liang
*
*  EMAIL: liangqz89@gmail.com
*
*  DATE: 11/10/2014
*
*******************************************************************/

/** include files **/
#include "CreepModel.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: CreepModel
* Description: 
********************************************************************/
int CreepModel::creepCount = 0;
CreepModel::CreepModel( const string &name )
: Atomic( name )
, heroIn( addInputPort( "heroIn" ) )
, creepIn( addInputPort( "creepIn" ) )
, heroOut( addOutputPort( "heroOut" ) )
, creepOut( addOutputPort( "creepOut" ) )
, preparationTime( 0, 0, 1, 500 ) //10 seconds
{
	isEnemyCreepDead = false;
	isDead = false;
	doNotSendMsg = false;
	damage = 25;
	hp = 50;
	creepCount++;
	creepId = creepCount;
}

/*******************************************************************
* Function Name: initFunction
* Description:
********************************************************************/
Model &CreepModel::initFunction()
{
	this->passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &CreepModel::externalFunction( const ExternalMessage &msg )
{
	if (!isDead) {
		cout << msg.time() << " creep " << creepId << " externalFunction"
				<< endl;
		int fromTargetIndex = -1;
		char *fromTarget[2] = { "Enemy Creep", "Enemy Hero" };
		if (msg.port() == creepIn) {
			fromTargetIndex = 0;
		} else if (msg.port() == heroIn) {
			fromTargetIndex = 1;
		}

		int value = static_cast<int> (msg.value());
		messageType = getMessageType(value);
		int fromDamage = getMessageParameter(value);

		if (messageType == Damage) {
			hp = hp - fromDamage;
			if (hp <= 0) {
				hp = 0;
				isDead = true;
				cout << "Creep " << creepId << " is dead" << endl;

			}
			cout << "Creep " << creepId << " received damage " << fromDamage
					<< " from " << fromTarget[fromTargetIndex];
			cout << ", remain " << hp << " hp" << endl;

		} else if (messageType == ShowHeroDamageToCreep) {
			shouldAttackHero = true;
			cout << "Creep " << creepId << " saw that "
					<< fromTarget[fromTargetIndex] << " attacked hero" << endl;

		} else if (messageType == Dead) // only enemy creep will tell other creep, i am dead
		{
			isEnemyCreepDead = true;
			cout << "Creep " << creepId << " saw that enemy creep was dead"
					<< endl;
		} else {
			cout << "Creep " << creepId << " saw that enemy hero do nothing."
					<< endl;
		}
		holdIn(active, preparationTime); //normal attack prepare time
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &CreepModel::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &CreepModel::outputFunction( const InternalMessage &msg )
{
	if (!doNotSendMsg) {
		cout << msg.time() << " creep " << creepId << " outputFunction" << endl;
		if (isDead) {
			int toSendMsg = getToSendMessage(Dead, 0);
			sendOutput(msg.time(), creepOut, toSendMsg);
			cout << "Send Dead to creepOut" << endl;

			sendOutput(msg.time(), heroOut, toSendMsg);
			cout << "Send Dead to heroOut" << endl;
			doNotSendMsg = true;
		} else if (shouldAttackHero || isEnemyCreepDead) {
			int toSendMsg = getToSendMessage(Damage, damage);
			sendOutput(msg.time(), heroOut, toSendMsg);
			cout << "Send Damage to heroOut" << endl;

			shouldAttackHero = false;

		} else {
			int toSendMsg = getToSendMessage(Damage, damage);
			sendOutput(msg.time(), creepOut, toSendMsg);
			cout << "Send Damage to creepOut" << endl;
		}
		cout << endl;
	}
	return *this ;
}

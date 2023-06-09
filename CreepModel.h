/*******************************************************************
*
*  DESCRIPTION: Atomic Creep  Model
*
*  AUTHOR: Qingzhong Liang
*
*  EMAIL: liangqz89@gmail.com
*
*  DATE: 11/10/2014
*
*******************************************************************/

#ifndef __CreepModel_H
#define __CreepModel_H

//#include <list>
#include "atomic.h"     // class Atomic
#include "Common.h"

class CreepModel : public Atomic
{
public:
	CreepModel( const string &name = "CreepModel" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &heroIn;
	const Port &creepIn;

	Port &heroOut;
	Port &creepOut;

	Time preparationTime;

	static int creepCount;

	int damage;
	int hp;
	int messageType;
	int creepId;
	SendType atkMessage;
	bool isEnemyCreepDead;
	bool isDead;
	bool shouldAttackHero;
	bool doNotSendMsg;
//	typedef list<Value> ElementList ;
//	ElementList elements ;

//	Time timeLeft;

};	// class CreepModel

// ** inline ** // 
inline
string CreepModel::className() const
{
	return "CreepModel" ;
}

#endif   //__CreepModel_H

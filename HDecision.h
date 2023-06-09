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

#ifndef __HDecision_H
#define __HDecision_H

#include "atomic.h"     // class Atomic
#include "Common.h"
class HDecision : public Atomic
{
public:
	HDecision( const string &name = "HDecision" );					//Default constructor
	~HDecision();
	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

	void attackFunction();
private:
	const Port &heroIn;
	const Port &creepIn;

	Port &attackOut;

	int packet;
	int index;
	int hp;
	int damage;

	bool isEnemyCreepDead;
	bool isEnemyHeroDead;

	static int heroCount;
	int heroId;
	enum AttackMessage atkMessage;
	bool takeTheLastHit;
	bool isDead;
};	// class HDecision

// ** inline ** // 
inline
string HDecision::className() const
{
	return "HDecision" ;
}

#endif   //__HDecision_H

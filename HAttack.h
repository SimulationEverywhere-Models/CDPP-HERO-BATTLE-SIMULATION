/*******************************************************************
*
*  DESCRIPTION: Atomic Hero Attack Model
*
*  AUTHOR: Qingzhong Liang
*
*  EMAIL: liangqz89@gmail.com
*
*  DATE: 11/10/2014
*
*******************************************************************/

#ifndef __HATTACK_H
#define __HATTACK_H

//#include <list>
#include "atomic.h"     // class Atomic

class HAttack : public Atomic
{
public:
	HAttack( const string &name = "HAttack" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in;
	Port &heroOut;
	Port &creepOut;
	Port &resultOut;

	Time skillTime;
	Time attackTime;

	int messageType;
	int damage;

	bool isUseSkill;

	static int heroCount;
	int heroId;
//	typedef list<Value> ElementList ;
//	ElementList elements ;

//	Time timeLeft;

};	// class HAttack

// ** inline ** // 
inline
string HAttack::className() const
{
	return "HAttack" ;
}

#endif   //__HAttack_H

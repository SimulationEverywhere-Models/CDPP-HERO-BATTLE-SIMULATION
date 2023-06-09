/*******************************************************************
 *
 *  DESCRIPTION: Atomic Model Hero Attack
 *
 *  AUTHOR: Qingzhong Liang
 *
 *  EMAIL: liangqz89@gmail.com
 *
 *  DATE: 11/10/2014
 *
 *******************************************************************/

/** include files **/
#include "HAttack.h"      // class Queue
#include "Common.h"
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
/** public functions **/

/*******************************************************************
 * Function Name: HAttack
 * Description:
 ********************************************************************/
int HAttack::heroCount = 0;

HAttack::HAttack(const string &name) :Atomic(name)
,in(addInputPort("in"))
,heroOut(addOutputPort("heroOut"))
,creepOut(addOutputPort("creepOut"))
,resultOut(addOutputPort("resultOut"))
,skillTime(0, 0, 1, 500)
,attackTime(0, 0, 1,500) {
	heroCount++;
	heroId = heroCount;
}

/*******************************************************************
 * Function Name: initFunction
 * Description:
 ********************************************************************/
Model &HAttack::initFunction() {
	this-> passivate();

	return *this;
}

/*******************************************************************
 * Function Name: externalFunction
 * Description:
 ********************************************************************/
Model &HAttack::externalFunction(const ExternalMessage &msg) {
	cout << msg.time() << " hero " << heroId << " attack externalFunction" << endl;
	int value = static_cast<int> (msg.value());
	messageType = getMessageType(value);
	damage = getMessageParameter(value);

	//use skill or not
	int n = rand()%100;
	if (n < 70)
	{
		isUseSkill = false;
	}
	else
	{
		isUseSkill = true;
		damage = damage * 2;
	}

	//
	if(messageType == attackHero || messageType == attackCreep)
	{
		if (isUseSkill)
		{
			holdIn(active, skillTime); //skill attack prepare time
		}
		else
		{
			holdIn(active, attackTime); //normal attack prepare time
		}
	}
	else
	{
		holdIn(active, attackTime);		//do nothing or other
	}
	return *this;
}

/*******************************************************************
 * Function Name: internalFunction
 * Description:
 ********************************************************************/
Model &HAttack::internalFunction(const InternalMessage &) {
	passivate();
	return *this;
}

/*******************************************************************
 * Function Name: outputFunction
 * Description:
 ********************************************************************/
Model &HAttack::outputFunction(const InternalMessage &msg) {
	cout << msg.time() << " hero " << heroId << " attack outputFunction" << endl;

	if (messageType == enemyHeroDead) {

		sendOutput(msg.time(), resultOut, Win);
		cout << "Send Win to result" << endl;
	}
	if (messageType == heroDead) {
		sendOutput(msg.time(), resultOut, Lose);
		cout << "Send Lose to result " << endl;

		int message = getToSendMessage(Dead, 0);
		sendOutput(msg.time(), heroOut, message);
		cout << "Send Dead to heroOut " << message << endl;
	}
	if (messageType == attackHero) {
		int message = getToSendMessage(Damage, damage);
		sendOutput(msg.time(), heroOut, message);
		cout << "Send Damage to heroOut " << message << endl;

		message = getToSendMessage(ShowHeroDamageToCreep, damage);
		sendOutput(msg.time(), creepOut, message);
		cout << "Send ShowHeroDamageToCreep to creepOut " << message << endl;
	}
	if (messageType == attackCreep) {
		int message = getToSendMessage(Damage, damage);
		sendOutput(msg.time(), creepOut, message);
		cout << "Send Damage to creepOut " << message << endl;

		message = getToSendMessage(DoNothing, 0);
		sendOutput(msg.time(), heroOut, message);
		cout << "Send doNothing to heroOut " << message << endl;

	}
	if (messageType == doNothing) {
		int message = getToSendMessage(DoNothing, 0);
		sendOutput(msg.time(), creepOut, message);
		cout << "Send doNothing to creepOut " << message << endl;

		message = getToSendMessage(DoNothing, 0);
		sendOutput(msg.time(), heroOut, message);
		cout << "Send doNothing to heroOut " << message << endl;
	}

	cout << endl;
	return *this;
}

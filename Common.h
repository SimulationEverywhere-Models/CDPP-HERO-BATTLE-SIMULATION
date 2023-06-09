/*******************************************************************
*
*  DESCRIPTION: Common class, use for process the messages
*
*  AUTHOR: Qingzhong Liang
*
*  EMAIL: liangqz89@gmail.com
*
*  DATE: 11/10/2014
*
*******************************************************************/

#ifndef __Common_H
#define __Common_H


static int const factor = 1000000;

//use for sending message to attack model
enum AttackMessage
	{
		enemyHeroDead = 1,
		attackHero,
		attackCreep ,
		doNothing ,
		heroDead
	};

//use for sending message to hero or creep model
enum SendType
{
	Damage = 1,
	ShowHeroDamageToCreep,
	ShowCreepsHP,
	DoNothing,
	Dead = 9
};
enum FightResult
{
	Fighting,
	Win,
	Lose
};
int getToSendMessage(int,int);
int getMessageType(int);

int getMessageParameter(int message);
#endif

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


/** public functions **/

/*******************************************************************
* Function Name: Common
* Description:
********************************************************************/
#include "Common.h"

int getToSendMessage(int type,int parameter)
{
	int result = type * factor + parameter;

	return result;

}

int getMessageType(int message)
{
	int type = message / factor;
	return type;
}

int getMessageParameter(int message)
{
	int result = message % factor;
	return result;
}

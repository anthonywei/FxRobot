//$ id FxSipEvent.cpp anthony.wei 2009-11-10 aotai //

#include "FxSipEvent.h"

/*
* //Get the event by its event string
*/
SipEvent GetEventFromString(char* szString)
{
	if(strcmp(szString, "AddBuddy") == 0)
		return AddBuddy;
	if(strcmp(szString,  "AddMobileBuddy") == 0)
		return AddMobileBuddy;
	if(strcmp(szString, "contact") == 0)
		return contact;
	if(strcmp(szString, "GetContactsInfo") == 0)
		return GetContactsInfo;
	if(strcmp(szString, "HandleContactRequest") == 0)
		return HandleContactRequest;
	if(strcmp(szString, "permission") == 0)
		return permission;
	if(strcmp(szString, "presence") == 0)
		return presence;
	if(strcmp(szString, "registration") == 0)
		return registration;

	return None;
}
#include <stdio.h>
#include "FxACEClient.h"



int main(int argc, char *argv[])
{

	ACEClient* pClient = new ACEClient();

	pClient->Init();

	/*
	* //Connect to china mobile server
	*/
	pClient->Connect();

	/*
	* //Login to the china mobile server
	*/
	pClient->LoginToServer();
	
	/*
	* //Start the cycle thread
	*/
	pClient->StartHandle();

	return 0;
}


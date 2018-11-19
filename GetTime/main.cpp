#include "Timestamp.h"
#include <stdio.h>
#include <unistd.h>
#include <string>
int main()
{
	std::string sNow = Timestamp::localtime();
	printf("Now is %s\n",sNow.c_str());

	Timestamp stTimestamp;
	usleep(1000000);
	printf("Time Elapsed %ld ms\n",stTimestamp.elapsed());



	return 1;

}


#include "convbond.h"
#define NB_DIVID 5
int main(int argc, char ** argv)
{
	checkMemotyLeaks();
	return 0;
}

// check memory leaks
int checkMemotyLeaks()
{
	// creating dividend schedule for test
	std::vector< std::vector< double > > div_sched;
	div_sched.resize(2);
	int i;
	for (i = 0; i < 2; i++)
	{
		div_sched[i].resize(NB_DIVID);
	}
	for(i = 0; i< 5; i++)
	{
		div_sched[0][i] = i + 0.73;
		div_sched[1][i] = 0.025;
	}
	//######################################
	i=0;
	while (1)
	{
		printf("iter %d cbprice=%f\n", ++i, CBpriceCpp(20, 0.25, 0.01, 0.03, 1, 0.02, 1, 0.015, div_sched, 4, 0, 1, 5, 100, 0, 0, 0, 0, 0, 0, 0, 0, 100));
	}
	return 0;
}

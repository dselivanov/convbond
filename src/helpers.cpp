#include "convbond.h"
int* createIndex(int N)
{
  int *indx=NULL;
  indx=new int[N];
	for(int i = 0; i<N; i++)
	{
		indx[i] = i;
	}
	return indx;
}
double prod(double *arr, int *index, int indexLen)
{
	double res = 1.0;
	for(int i = 0; i<indexLen; i++)
	{
		res = res * arr[index[i]];
	}
	delete[] index;
	return res;
}
double prod_with_cond(double *arr, int *index, int indexLen, double condition)
{
	double res = 1.0;
	double arr_elem, adj_elem;
	for(int i = 0; i<indexLen; i++)
	{
		arr_elem = arr[index[i]];
		if (arr_elem < 1)
		{
			adj_elem = arr_elem;
			if ( adj_elem < (1 - condition))
			{
				adj_elem = condition + arr_elem;
			} else 
			{
				adj_elem = 1;
			}
			res = res * adj_elem;
		}
	}
	delete[] index;
	return res;
}
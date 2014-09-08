#include "convbond.h"
// returns poduct of first N elements of array
double prod(double *arr, int N)
{
	double res = 1.0;
	for(int i = 0; i < N; i++)
	{
		res *= arr[i];
	}
	return res;
}

// returns poduct of first N elements of dividend discount array, adjusted to dividend protection
// For example if condition==0.03 (dividend protection level 3%)  
// and arr[i]==0.95 (dividend discount at time i == 0.95, which mean issuer pays 5% dividend)
// we adjust conversion ratio to condition + arr[i]. So new conversion ratio will 
// be 1 / (condition + arr[i]) = 1 / (0.03 + 0.95) = 1 / 0.98
// function prod_with_cond() returns this adjusttion for conversion ratio (in our example it returns 0.98)
double prod_with_cond(double *arr, int N, double condition)
{
	double res = 1.0;
	double arr_elem, adj_elem;
	for(int i = 0; i < N; i++)
	{
		arr_elem = arr[i];
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
			res *= adj_elem;
		}
	}
	return res;
}

/*
// creates array of 0 1 2 3 ... N - 1
int* createIndex(int N)
{
	int *indx = NULL;
	indx=new int[N];
	for(int i = 0; i<N; i++)
	{
		indx[i] = i;
	}
	return indx;
}*/
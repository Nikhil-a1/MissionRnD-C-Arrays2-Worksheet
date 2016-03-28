/*
OVERVIEW: Given an array where every element occurs three times, except one element which occurs only
once. Find the element that occurs once.
E.g.: Input: arr = 12, 1, 12, 3, 12, 1, 1, 2, 3, 3
ouput: 2

INPUTS: Integer array and length of the array.

OUTPUT: Element that occurs only once.

ERROR CASES: Return -1 for invalid inputs.

NOTES:
There are better ways of solving the problem than a brute-force solution which is of O(n^2)
complexity .
*/
//time complexity O(nlogn)
#include<stdlib.h>
void mergesort(int[], int, int);
void merge(int[], int, int);

int findSingleOccurenceNumber(int *A, int len) {
	if (A == NULL||len<=0)
	return -1;
	int low = 0, i;
	mergesort(A, 0, len-1);
	for (i = 0; i <len;)
	{
		if (A[i] == A[i + 1] && i < len - 1)
			i = i + 3;
		else
			return A[i];
	}

}
void mergesort(int* arr, int low, int high)
{
	int mid;
	mid = (low + high) / 2;
	if (low >= high)
		return;
	else
	{
		mergesort(arr, low, mid);
		mergesort(arr, mid + 1, high);
		merge(arr, low, high);
	}
}
void merge(int* arr, int low, int high)
{
	int start = low, begin = low, mid = (low + high) / 2;
	int k = mid + 1, end = high, b[50];
	while (start <= mid && k <= high)
	{
		if (arr[start] >= arr[k])
			b[begin++] = arr[k++];
		else
			b[begin++] = arr[start++];
	}
	if (start > mid)
	{
		for (; k <= high; k++)
			b[begin++] = arr[k];
	}
	else if (k > high)
	{
		for (; start <= mid; start++)
			b[begin++] = arr[start];
	}
	for (start = low; start <= high; start++)
		arr[start] = b[start];
	return;
}
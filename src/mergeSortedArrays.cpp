/*
OVERVIEW: You are given 2 bank statements that are ordered by date - 
Write a function that produces a single merged statement ordered by dates.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[2] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" } };
Output: { { 10, "09-10-2003", "First" }, { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" },  30, "03-03-2005", "Third" }, { 220, "18-01-2010", "Sixth" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Combined statement ordered by transaction date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <iostream>
#include<stdlib.h>
struct transaction {
	int amount;
	char date[11];
	char description[20];
};
struct calender
{
	int date;
	int mnth;
	int yr;
};
void copy(char*, char*);
struct transaction * mergeSortedArrays(struct transaction *A, int ALen, struct transaction *B, int BLen) {
	if (A == NULL || B == NULL)
		return NULL;
	else if (ALen <= 0 ||BLen<=0)
	return NULL;
	
	struct calender *calen1, *calen2;
	calen1 = (struct calender*)calloc(sizeof(struct calender), ALen);
	calen2 = (struct calender*)calloc(sizeof(struct calender), BLen);
	int i = 0, j = 0;
	for (i = 0; i < ALen; i++)
	{
		for (j = 0; A[i].date[j] != '-'; j++)
			calen1[i].date = calen1[i].date * 10 + A[i].date[j] - '0';
		j++;
		for (; A[i].date[j] != '-'; j++)
			calen1[i].mnth = calen1[i].mnth * 10 + A[i].date[j] - '0';
		j++;
		for (; A[i].date[j] != '\0'; j++)
			calen1[i].yr = calen1[i].yr * 10 + A[i].date[j] - '0';
	}
	for (i = 0; i < BLen; i++)
	{
		for (j = 0; B[i].date[j] != '-'; j++)
			calen2[i].date = calen2[i].date * 10 + B[i].date[j] - '0';
		j++;
		for (; B[i].date[j] != '-'; j++)
			calen2[i].mnth = calen2[i].mnth * 10 + B[i].date[j] - '0';
		j++;
		for (; B[i].date[j] != '\0'; j++)
			calen2[i].yr = calen2[i].yr * 10 + B[i].date[j] - '0';
	}
	int start = 0, k = 0, end1 = ALen, end2 = BLen, begin = 0;
	int end = end1 + end2;
	struct transaction *merged_list;
	merged_list = (struct transaction*)malloc(sizeof(struct transaction)*(ALen + BLen));
	while (start < end1 && k < end2)
	{
		if (calen1[start].date <= calen2[k].date && calen1[start].mnth <= calen2[k].mnth && calen1[start].yr <= calen2[k].yr)
		{
			merged_list[begin].amount = A[start].amount;
			copy(merged_list[begin].date, A[start].date);
			copy(merged_list[begin].description, A[start].description);
			begin++;
			start++;
		}
		else
		{
			merged_list[begin].amount = B[k].amount;
			copy(merged_list[begin].date, B[k].date);
			copy(merged_list[begin].description, B[k].description);
			begin++;
			k++;
		}
	}
	if (start < end1)
	{
		for (; start < end1; start++)
		{
			merged_list[begin].amount = A[start].amount;
			copy(merged_list[begin].date, A[start].date);
			copy(merged_list[begin].description, A[start].description);
			begin++;
		}
	}
	else if (k < end2)
	{
		for (; k < end2; k++)
		{
			merged_list[begin].amount = B[k].amount;
			copy(merged_list[begin].date, B[k].date);
			copy(merged_list[begin].description, B[k].description);
			begin++;
		}
	}
	return merged_list;
}
void copy(char* string1, char* string2)
{
	int i = 0;
	while (string2[i] != '\0')
	{
		string1[i] = string2[i];
		i++;
	}
	string1[i] = '\0';
}

/*
OVERVIEW: You are given 2 bank statements that are ordered by date. 
Write a function that returns dates common to both statements
(ie both statements have transactions in these dates).
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[3] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" }, { 320, "27-08-2015", "Seventh" } };
Output: { { 10, "09-10-2003", "First" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Transactions having same dates.


ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <iostream>

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
void cpy(char*, char*);
struct transaction * sortedArraysCommonElements(struct transaction *A, int ALen, struct transaction *B, int BLen) {
	if (A==NULL||B==NULL ||ALen<=0||BLen<=0)
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
	int start = 0, k = 0, end1 = ALen, end2 = BLen, begin = 0, size = 1,flag=0;
	int end = end1 + end2;
	struct transaction *merged_list;
	merged_list = (struct transaction*)malloc(sizeof(struct transaction) * 20);
	while (start < end1 && k < end2)
	{
		if (calen1[start].yr > calen2[k].yr)
			k++;
		else
			if (calen1[start].mnth > calen2[k].mnth)
				k++;
			else
				if (calen1[start].date > calen2[k].date)
					k++;
				else if (calen1[start].date < calen2[k].date)
					start++;
				else if (calen1[start].mnth < calen2[k].mnth)
					start++;
				else if (calen1[start].yr < calen2[k].yr)
					start++;
				else
				{
					flag = 1;
					merged_list[begin].amount = A[start].amount;
					cpy(merged_list[begin].date, A[start].date);
					cpy(merged_list[begin].description, A[start].description);
					begin++;
					k++;
					start++;
				}
	}
	if (flag==1)
	return merged_list;
	else 
		return	NULL;
}
void cpy(char* string1, char* string2)
{
	int j = 0;
	while (string2[j] != '\0')
	{
		string1[j] = string2[j];
		j++;
	}
	string1[j] = '\0';
}
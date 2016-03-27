/*
OVERVIEW: You are given a bank statement where transactions are ordered by date. Write a function that finds the number of transactions in that statement after a given date.
-- find the count of numbers greater than a given number in a sorted array.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
date = "19-10-2004"
Output: 1 (as there is only one transaction { 30, "03-03-2005", "Third" })

INPUTS: One bank statement (array of transactions) and date.

OUTPUT: Return the number of transactions in that statement after a given date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/
//time complexity O(n)
#include<stdlib.h>

struct transaction {
	int amount;
	char date[11];
	char description[20];
};

int check_valid_date(struct calender*);//to check whether input is valid or not
int search_for_transaction(struct calender*, int, struct calender*);

struct calender
{
	int dat;
	int mnth;
	int yr;
};
int countGreaterNumbers(struct transaction *Arr, int len, char *date) {
	if (Arr == NULL || len <= 0 || date == NULL)
		return -1;
	int i = 0, j = 0, flag = 1, trasctn_after_given_date;
	struct calender *calen;
	calen = (struct calender*)calloc(sizeof(struct calender), len);
	for (i = 0; i < len; i++)
	{
		for (j = 0; Arr[i].date[j] != '-'; j++)
			calen[i].dat = calen[i].dat * 10 + (Arr[i].date[j] - '0');
		j++;
		for (; Arr[i].date[j] != '-'; j++)
			calen[i].mnth = calen[i].mnth * 10 + (Arr[i].date[j] - '0');
		j++;
		for (; Arr[i].date[j] != '\0'; j++)
			calen[i].yr = calen[i].yr * 10 + (Arr[i].date[j] - '0');
	}
	struct calender *input;
	input = (struct calender*)calloc(sizeof(struct calender), 1);
	for (; *date != '-'; date++)
		input->dat = input->dat * 10 + (*date - '0');
	date++;
	for (; *date != '-'; date++)
		input->mnth = input->mnth * 10 + (*date - '0');
	date++;
	for (; *date != '\0'; date++)
		input->yr = input->yr * 10 + (*date - '0');
	flag = check_valid_date(input);
	if (flag == 0)
		return -1;
	else
		trasctn_after_given_date = search_for_transaction(calen, len, input);
	return trasctn_after_given_date;
}
int check_valid_date(struct calender* input)
{
	int flag = 0;
	if (input->yr <= 0)
		return flag;
	else if (input->mnth > 12 || input->mnth <= 0)
		return flag;
	else if (input->dat > 31 || input->dat <= 0)
		return flag;
	else
	{
		switch (input->mnth)
		{
		case 2: if (input->yr % 100 == 0 && input->yr % 400 == 0 && input->dat > 29)
			return flag;
				else if (input->yr % 4 == 0 && input->dat > 29)
					return flag;
				else if (input->dat > 28)
					return flag;
				break;
		case 4:
		case 6:
		case 8:
		case 9:
		case 11: if (input->dat > 30)
			return flag;
			break;
		default:return flag = 1;
			break;
		}
	}
}

int search_for_transaction(struct calender* calen, int len, struct calender* input)
{
	int transaction = 0, i = 0;
	for (i = 0; i < len; i++)
	{
		if (calen[i].yr>input->yr)
		{
			transaction = len - i ;
			break;
		}
		else if (calen[i].mnth > input->mnth && calen[i].yr >= input->yr)
		{
			transaction = len - i ;
			break;
		}
		else if (calen[i].dat > input->dat && calen[i].mnth >= input->mnth && calen[i].yr >= input->yr)
		{
			transaction = len - i ;
			break;
		}
	}
	return transaction;
}

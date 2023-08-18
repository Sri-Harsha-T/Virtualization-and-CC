#include "functions.h"
#include "functionslist.h"
#include <math.h>

extern char* url_list[32];
// extern farr func_arr[];
char prstr[8]="False";
char hellostr[16]="Hello";
char ppstr[32]="PingPong";
char hwrldstr[32]="Hello, World!";
char sqstr[16] = "1";
char custr[16] = "1";
char fibstr[16] = "1";

char *my_itoa(int num, char* str)
{
	if(str == NULL||strcmp(str, "No query")==0) return NULL;
	sprintf(str, "%d", num);
	return str;
}


int url_index_map(char *url_s){
	for(int i =0 ; i<10;i++){
		if(strcmp(url_s, url_list[i]) == 0){
			return i;
		}
	}
	return -1;
}

char *
rootmsg(char *quer)
{
	strcpy(hellostr, "Hello World!");
	return hellostr;
	// return nullptr;
}

char *
square(char *p)
{
	if(p==NULL||strcmp(p, "No query")==0){
		strcpy(sqstr, "1");
		return sqstr;
	}
	// int ip = (int)p;
	int ip = atoi(p);
	int q = ip*ip;
	// strcpy(sqstr, itoa(q));
	my_itoa(q, sqstr);
	return sqstr;
	// return nullptr;
}

char *
cube(char *p)
{
	if(p==NULL||strcmp(p, "No query")==0){
		strcpy(custr, "1");
		return custr;
	}
	int ip = atoi(p);
	int q = (ip*ip)*ip;
	// strcpy(custr, itoa(q));
	my_itoa(q, custr);
	return custr;
	// return nullptr;
}

char *
fibonacci(char *ik)
{
	if(ik==NULL||strcmp(ik, "No query")==0){
		strcpy(fibstr, "1");
		return fibstr;
	}

	int k = atoi(ik);
	// if(k<1) return itoa(0);
	if(k<1){
		my_itoa(0, fibstr);
		return fibstr;
	}
	if(k==1||k==2){
		my_itoa(1, fibstr);
		return fibstr;
	}
	int fibarr[k];
	fibarr[0] = 1;
	fibarr[1] = 1;
	for(int i=2;i<k;i++)
	{
		fibarr[i] = fibarr[i-1] + fibarr[i-2];
	}
	// strcpy(fibstr, itoa(fibarr[k-1]));
	my_itoa(fibarr[k-1], fibstr);
	return fibstr;
	// return nullptr;
}

char *
prime(char *ik)
{
	if(ik==NULL||strcmp(ik, "No query")==0) {
		strcpy(prstr, "False");
		return prstr;
	}
	int k = atoi(ik);
	strcpy(prstr, "False");
	if(k<=1||k%2==0) return prstr;
	// int j = sqrt(k);
	for(int i=3; i*i<=k; i++){
		if(k%i==0)return prstr;
	}
	strcpy(prstr, "True");
	return prstr;
	// return nullptr;
}

char *
pingpong(char *quer)
{
	if(quer==NULL||strcmp(quer, "No query")==0){
		strcpy(ppstr, "PingPong");
		return ppstr;
	}
	strcpy(ppstr, quer);
	return ppstr;
	// return nullptr;
}

char *
helloworld(char *quer)
{
	if(quer == NULL||strcmp(quer, "No query")==0){
		strcpy(hwrldstr, "Hello");
		return hwrldstr;
	}
	strcpy(hwrldstr, "Hello, ");
	strcat(hwrldstr, quer);
	return hwrldstr;
	// return nullptr;
}


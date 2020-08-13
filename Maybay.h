#ifndef MAYBAY_H 
#define MAYBAY_H
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string.h>
using namespace std;


const int MAXLIST = 300;



struct Maybay{
	char sohieu [16];//C15
	char loai   [41];//C40
	int soday;       // <=9
	int sodong;      // <=100
	
};

struct Listmaybay{
	int n = 0;
	Maybay *nodes [MAXLIST];
};



struct luot_thuc_hien_chuyen_bay{
	char sohieumb [16];//C15
	char loaimb   [41];//C40
	int soluot;
};

struct List_mb_thuchien_chuyenbay{
	luot_thuc_hien_chuyen_bay *node;
	
};

#endif




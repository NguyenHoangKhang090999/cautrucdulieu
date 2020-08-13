#ifndef CHUYENBAY_H 
#define CHUYENBAY_H 
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include "Ve.h"
using namespace std;


struct Date{
	int ngay;
	int thang;
	int nam;
	int gio;
	int phut;
};


struct Chuyenbay {
	char ID[16]; //C15
	Date date;
	char diadiem[30];
	int  trangthai; // 0: huy - 1 : còn vé - 2: het ve - 3: hoan tat
	char sohieumb[16]; //C15
	DSVe danhsachve;
};

struct Nodechuyenbay{
	Chuyenbay cb;
	Nodechuyenbay *next;
};
typedef Nodechuyenbay *CBPTR;



#endif

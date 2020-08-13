
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string.h>
using namespace std ;


struct Hanhkhach{
	char Cmnd[11];
	char Ho[20];
	char Ten[16];
	char Gioitinh[4];
};

struct NodeHanhkhach{
	Hanhkhach hk;
	NodeHanhkhach *pLeft, *pRight;	
};
typedef NodeHanhkhach *HKPTR;

//khoi tao cay
void Initialize(HKPTR &tree){
   tree = NULL;
}











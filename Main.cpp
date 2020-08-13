#include <iostream>
#include "Display.h"
//#include "Xuly.h"
using namespace std;

int main(){
	Listmaybay dsmb;	
	CBPTR dscb; dscb = NULL;
	HKPTR tree;
	Initialize(tree);
	
	
	while(true){
		MenuChinh(dsmb,dscb,tree);
	}	

}

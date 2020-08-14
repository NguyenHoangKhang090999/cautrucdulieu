#include <iostream>
#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include "Xuly.h"
using namespace std;


void MenuChinh(Listmaybay &dsmb,CBPTR &dscb,HKPTR &tree);
int MenuMB(Listmaybay &dsmb,CBPTR &dscb);
int MenuCB(Listmaybay &dsmb,CBPTR &dscb);

//void gotoxy(int x, int y)
//{
//    static HANDLE h = NULL;
//    if(!h)
//    {
//        h = GetStdHandle(STD_OUTPUT_HANDLE);
//        COORD c = {x,y};
//        SetConsoleCursorPosition(h,c);
//    }
//}
int Drawtext(int line, int cot, int focus, char Text[])
{
       
    HANDLE hConsoleColor;
    hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleColor,focus);
    
    printf("%s\n",Text);
    
}


void Dichuyen(int k,char *Menu[][50]){


}

int MenuMB(Listmaybay &dsmb,CBPTR &dscb){
	
	system("cls");
	char MenuMB[][50] = { "----QUAN LY MAY BAY----     ESC-thoat ",
						"1. Xem danh sach may bay ",
						"2. Them may bay     ",
						"3. Xoa may bay      ",
						"4. Hieu Chinh may bay    ",
						"5. Thoat                 ",
	 				};		
		
		
		char ch;
	int i =2 ;
	do{
		system("cls");
		for(int t=1;t<=6;t++){
			if (t==i){ 
//				gotoxy(40,t-1);
				Drawtext(7+t,2,3,MenuMB[t-1]);
			}else{
//				gotoxy(40,t);
				Drawtext(7+t,2,14,MenuMB[t-1]);
			} 			
		}
		do{
	            ch = getch();
	            if (ch==224) ch=getch();
	        } while (!(ch==224||ch==13||ch==27||ch==80||ch==72));
		if(ch==80){         //ky tu xuong
	        i++; 
	        if (i>6) i = 2; //het dong k quay lai dong 2
	    }
	   	if (ch==72){          //ky tu len
	        i--; 
	        if (i<2) i = 6; 
	    }
	    if(ch==27){
	    	return 2;
		}
	}while (!(ch == 13));
	
	LoadMB(dsmb,"dsmaybay");
//	LoadCB(dscb,"dschuyenbay");
	switch(i){
		case 2:
			{
				system("cls");
//				LoadMB(dsmb,"dsmaybay");
				LietkeDSMB(dsmb);
				break;
			}
		case 3:
			{
				system("cls");
//				LoadMB(dsmb,"dsmaybay");
				NhapDSMB(dsmb);
				SapxepMB(dsmb);
				SaveMB(dsmb,"dsmaybay");
				break;
			}
		case 4:
			{	
				system("cls");
				XoaMB(dsmb,dscb);
				SaveMB(dsmb,"dsmaybay");
				break;
			}
		case 5:
			{
				system("cls");
				HieuchinhMB(dsmb,dscb);
				SaveMB(dsmb,"dsmaybay");
				break;
			}
		case 6:
			{
				 return 2;
//				 break;
			}
	}			
}



int MenuCB(Listmaybay &dsmb,CBPTR &dscb){
	
	system("cls");
	char MenuMB[][50] = { "----QUAN LY CHUYEN BAY----     ESC-thoat ",
						"1. Xem danh sach chuyen bay ",
						"2. Them chuyen bay     ",
						"3. Xoa chuyen bay      ",
						"4. Hieu Chinh chuyen bay    ",
						"5. Huy chuyen bay    ",
						"6. Thoat               ",
	 				};		
		
		
		char ch;
	int i =2 ;
	do{
		system("cls");
		for(int t=1;t<=7;t++){
			if (t==i){ 
//				gotoxy(40,t-1);
				Drawtext(7+t,2,3,MenuMB[t-1]);
			}else{
//				gotoxy(40,t);
				Drawtext(7+t,2,14,MenuMB[t-1]);
			} 			
		}
		do{
	            ch = getch();
	            if (ch==224) ch=getch();
	        } while (!(ch==224||ch==13||ch==27||ch==80||ch==72));
		if(ch==80){         //ky tu xuong
	        i++; 
	        if (i>7) i = 2; //het dong k quay lai dong 2
	    }
	   	if (ch==72){          //ky tu len
	        i--; 
	        if (i<2) i = 7; 
	    }
	    if(ch==27){
	    	return 2;
		}
	}while (!(ch == 13 ));
	
	LoadMB(dsmb,"dsmaybay");
//	LoadDSCB(dscb);
	switch(i){
		case 2:
			{
				system("cls");
				LietkeDSCB(dscb);
				break;
			}
		case 3:
			{
				system("cls");
				NhapDSCB(dscb,dsmb);
				SapXepCBTheoID(dscb);
				SaveDSCB(dscb);
				break;
			}
		case 4:
			{
				system("cls");	
				XoaCB(dscb);
				SaveDSCB(dscb);
				break;
			}
		case 5:
			{
				system("cls");
				HieuchinhCB(dscb);
				SaveDSCB(dscb);
				break;
			}
		case 6:
			{
				system("cls");
				HuyCB(dscb);
				SaveDSCB(dscb);
				 break;
			}
		case 7:
			{
				 return 2;
//				 break;
			}
	}			
}



void MenuChinh(Listmaybay &dsmb,CBPTR &dscb,HKPTR &tree){
	
	system("cls");
	char MenuChinh[][1000] = { "-------------------------------AIR-BUS-MANAGEMENT------------------------------   ESC-thoat ",
						"|\t\t\t\ 1. Quan ly may bay                                                                |",
						"|\t\t\t\ 2. Quan ly chuyen bay                                                             |",
						"|\t\t\t\ 3. Dat ve                                                                         |",
						"|\t\t\t\ 4. Huy ve                                                                         |",
						"|\t\t\t\ 5. Danh sach hanh khach - chuyen bay                                              |",
						"|\t\t\t\ 6. Danh sach chuyen bay theo yeu cau                                              |",
						"|\t\t\t\ 7. Danh sach ve trong - chuyen bay                                                |",
						"|\t\t\t\ 8. Thong ke luot thuc hien chuyen bay                                             |",
						"------------------------------------------------------------------------------------------------------------",
						
	 				};
	
	char ch;
	int i =2 ;
	do{
		system("cls");
		for(int t=1;t<=10;t++){
			if (t==i){ 
//				gotoxy(40,t-1);
				//Khungdatve();
				Drawtext(7+t,2,3,MenuChinh[t-1]);
			}else{
//				gotoxy(40,t);
				Drawtext(7+t,2,14,MenuChinh[t-1]);
			} 
			
		}
		do{
	            ch = getch();
	            if (ch==224) ch=getch();
	        } while (!(ch==224||ch==13||ch==27||ch==80||ch==72));
		if(ch==80){         //ky tu xuong
	        i++; 
	        if (i>9) i = 2; //het dong k quay lai dong 2
	    }
	   	if (ch==72){          //ky tu len
	        i--; 
	        if (i<2) i = 9; 
	    }
	    if(ch == 27){
				exit(0);
		}
	}while (!(ch == 13));
	
	LoadMB(dsmb,"dsmaybay");
	LoadDSCB(dscb);
	
	switch(i){
		case 2:
			{
				while(true){
					int kt = MenuMB(dsmb,dscb);
					if(kt == 2) return;
				}	
			}
		case 3:
			{
				while(true){
					int kt = MenuCB(dsmb,dscb);
					if(kt == 2) return;
				}
			}
		case 4:
			{
				system("cls");
				Datve(dscb,tree,dsmb);
				SaveDSCB(dscb);
				break;
			}
		case 5:
			{
				system("cls");
				HuyVE(dscb,tree);
				break;
			}
		case 6:
			{
				system("cls");
				LietkeDSHK_CB(dscb,tree);
				break;			
			}
		case 7:
			{
				system("cls");
				LietkeDSCBYeuCau(dscb);
				break;
			}
		case 8:
			{
				system("cls");
				LietkeDSVETrong(dscb,dsmb);
				break;
			}
		case 9:
			{
				system("cls");
				Thongkeluotchuyenbay(dscb,dsmb);
				break;
			}
		case 10:
			{
				exit(0);
			}
	}
}





























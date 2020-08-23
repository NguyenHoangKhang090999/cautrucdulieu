#include <iostream>
#include <sstream>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "Maybay.h"
#include "Chuyenbay.h"
#include "Hanhkhach.h"
#include<windows.h>
using namespace std;




int Hieuungyesno(string yeucau);
int NhapHK(HKPTR &tree,Hanhkhach &hk);
int  NhapDSHK(HKPTR &tree);
int HieuungluachonLK_DSHK_CB(string yeucau);
int Chonchongoi(Chuyenbay cb,Listmaybay dsmb,string tieude);


   
	
void gotoxy(short x,short y)
{
        HANDLE hConsoleOutput;
        COORD Cursor_an_Pos = { x,y};
        hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}  

int wherex( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}

int wherey( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}

int sosanh(char *s1,char *s2){
	int n = 0;
   short flag = 1;
   
   while (s1[n] != '\0') {
      if(s1[n] != s2[n]) {
         flag = 0;
         break;
      }
      n++;
   }
   return flag;
}


/////////////// May bay ////////////////////

int SearchMB(Listmaybay &dsmb,char *name){
	for(int i=0;i<dsmb.n;i++){
		if(sosanh(dsmb.nodes[i]->sohieu,name)==1) return i;
	}
	return -1;
}

void NhapChuoi (char *tieude, char *S) {
	cout << tieude ;  fflush(stdin);
    do
	  gets(S);
    while (strcmp(S,"")==0)  ;	
}


int NhapMB(Listmaybay &dsmb,Maybay &mb){
	
	while(1){
		cout<<"Thong tin may bay thu "<<dsmb.n+1<<endl;
		NhapChuoi("Nhap so hieu may bay: ",mb.sohieu);
		if(SearchMB(dsmb,mb.sohieu)>=0){
			cout<<"so hieu may bay da ton tai !!!"<<endl;
			continue;		
		}
		NhapChuoi("Nhap loai may bay: ",mb.loai);
		cout<<"Nhap so day may bay(<=9): ";
		cin>>mb.soday;
		if(mb.soday<=0) return 0;
		cout<<"Nhap so dong may bay(<=100): ";
		cin>>mb.sodong;
		cout<<endl;
		if(mb.sodong<=0) return 0;
		
		return 1;
	}
	
}

void Themthutu(Listmaybay &dsmb,Maybay mb){
	int j, k;
	if (dsmb.n == MAXLIST ){
		cout<<"danh sach day!!!";
		system("pause");
		return;
	} 
	for (j=0; j < dsmb.n && dsmb.nodes[j]->sodong < mb.sodong ; j++ );{		
		for ( k = dsmb.n-1; k >=j  ; k--) {
		   dsmb.nodes[k+1]= dsmb.nodes[k];
		}
    }
	dsmb.nodes[j]= new Maybay;
	*dsmb.nodes[j]=mb; 
	dsmb.n++;

}

void NhapDSMB(Listmaybay &dsmb){
	Maybay mb;
	int soluong;
	if(dsmb.n == MAXLIST){ 
		cout<<"danh sach day!!!"<<endl;
		system("pause");
		return;
	}
	Loop:	
	cout<<"Nhap so luong may bay can them vao: "; 
	cin>>soluong; cout<<endl;
	if((dsmb.n + soluong)> MAXLIST ){
		cout<<"Danh sach chi co the them duoc "<<MAXLIST-dsmb.n-1<<" may bay"<<endl;
		goto Loop;
	}
	for(int i=0;i<soluong;i++){
		if(NhapMB(dsmb,mb)==0) return;
		
		dsmb.nodes[dsmb.n] = new Maybay;
		*dsmb.nodes[dsmb.n] = mb;
		dsmb.n++ ;
//		Themthutu(dsmb,mb);
	}
	cout<<"Nhap may bay hoan tat!!!"<<
	system("pause");
}


void LietkeDSMB(Listmaybay &dsmb){

	char ch;
	do{	
			system("cls");
		if(dsmb.n == 0){
			cout<<"		DANH SACH RONG"<<endl;
			system("pause");
			return;
		}
		cout<<"                 DANH SACH MAY BAY                     ESC : thoat"<<endl;
		cout<<"STT     So hieu       Loai        So day        So dong "<<endl;
		for(int i=0;i<dsmb.n;i++){
			cout<<" "<<i+1;
			gotoxy(10,i+2);
			cout<<dsmb.nodes[i]->sohieu;
			gotoxy(23,i+2);
			cout<<dsmb.nodes[i]->loai;
			gotoxy(36,i+2); 
			cout<<dsmb.nodes[i]->soday;
			gotoxy(51,i+2);
			cout<<dsmb.nodes[i]->sodong <<endl;						
		}		
		ch = getch();
	}while(ch != 27);	
}


void Thongtinmaybay(Listmaybay &dsmb,int ivitri){
	cout<<"                 THONG TIN MAY BAY "<<endl;
	cout<<"STT   So hieu         Loai        So day        So dong "<<endl;
		cout<<" 1";
		gotoxy(7,2);
		cout<<"  "<<dsmb.nodes[ivitri]->sohieu<<"             ";
		gotoxy(23,2);
		cout<<dsmb.nodes[ivitri]->loai<<"             ";
		gotoxy(36,2); 
		cout<<dsmb.nodes[ivitri]->soday<<"             ";
		gotoxy(51,2);
		cout<<dsmb.nodes[ivitri]->sodong <<endl;
	
}

void HieuungMB(int i,int f,Listmaybay dsmb){
	HANDLE hConsoleColor;
    hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);		
	SetConsoleTextAttribute(hConsoleColor, f); // f la mau
	cout<<" "<<i+1;
	gotoxy(10,i+2);
	cout<<dsmb.nodes[i]->sohieu;
	gotoxy(23,i+2);
	cout<<dsmb.nodes[i]->loai;
	gotoxy(36,i+2); 
	cout<<dsmb.nodes[i]->soday;
	gotoxy(51,i+2);
	cout<<dsmb.nodes[i]->sodong <<endl;	
}


int HieuungthongtinMB(Listmaybay dsmb){
	int i=0;
	char ch;

	do{
		system("cls");
		HANDLE hConsoleColor;
   		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);		
		SetConsoleTextAttribute(hConsoleColor, 12);
		cout<<"                 DANH SACH MAY BAY                     ESC : thoat"<<endl;
		cout<<"STT     So hieu       Loai        So day        So dong "<<endl;
		for(int t=0;t<dsmb.n;t++){	
			if (t==i){ 
				HieuungMB(t,1,dsmb);
			}else HieuungMB(t,2,dsmb);
		}
		do{
	            ch = getch();
	            if (ch==224) ch=getch();
	        } while (!(ch==224||ch==13||ch==27||ch==80||ch==72));
	        if(ch==80){         //ky tu xuong
	             i=i+1; 
	             if (i>dsmb.n-1) i = 0; 
	        }
	        if (ch==72){          //ky tu len
	            i=i-1; 
	            if (i<0) i = dsmb.n-1; 
	   		}
	   		if(ch == 27){
	   			return -1;
			 }
	}while (!(ch == 13));
			return i;
}



void XoaMB(Listmaybay &dsmb,CBPTR First){
	string yeucau = "Ban that su muon xoa ?";
	Loop:
	if(dsmb.n == 0){
		cout<<"		                    CHUA CO MAY BAY TRONG DANH SACH       ESC : thoat"<<endl;
		char ch = getch();
		if( ch == 27) return;
		goto Loop;
	}	
	int ixoamb = HieuungthongtinMB(dsmb);
	if(ixoamb == -1){
		return;
	} 

		for(CBPTR p = First;p!=NULL;p=p->next){
			if(strcmp(p->cb.sohieumb,dsmb.nodes[ixoamb]->sohieu) == 0 && ((p->cb.trangthai==1) ) ){
				system("cls");
				cout<<"may bay dang thuc hien chuyen bay "<<p->cb.ID<<endl;
				system("pause");
				return;
			}	
		}	
		
		int ixacnhan = Hieuungyesno(yeucau);	
		if(ixacnhan == -1 || ixacnhan == 1){
			return;
		}else{								
			if(ixoamb == dsmb.n-1){
				delete dsmb.nodes[ixoamb];
				dsmb.n--;
				return;
			}else{
				delete dsmb.nodes[ixoamb];
				for(int i=ixoamb;i<=dsmb.n-1;i++){
					dsmb.nodes[i]=dsmb.nodes[i+1];				
				}
				dsmb.n--;
				return;
			}
		}
			
}	

void SaveMB(Listmaybay &dsmb,char *filename) {
 FILE * f;
 if ((f=fopen(filename,"wb"))==NULL){  
 	cout<<"Loi mo file de ghi";
    return ;
 }
 for (int i=0; i < dsmb.n; i++){
   fwrite (dsmb.nodes[i], sizeof (Maybay), 1, f);
   }
 fclose(f);
// cout<<"Da ghi xong danh sach vao file";

}

void LoadMB(Listmaybay &dsmb, char *filename) {
 FILE * f; Maybay mb;
 if ((f=fopen(filename,"rb"))==NULL)
 {  
 	cout<<"Loi mo file de doc"<<endl; 
	return ;
 }
 dsmb.n =0;
 while  (fread (&mb, sizeof (Maybay), 1, f)!=0) {
 	dsmb.nodes[dsmb.n]=new Maybay;
 	*dsmb.nodes[dsmb.n]=mb;
 	dsmb.n ++;
 }
    
 fclose(f);
// cout<<"Da load xong danh sach vao bo nho"<<endl;

}

void SapxepMB(Listmaybay &dsmb){
	
	for( int i=0;i<dsmb.n;i++){
		for(int j=dsmb.n-1;j>i;j--){
			if(strcmp(dsmb.nodes[i]->sohieu,dsmb.nodes[j]->sohieu)==1){

				Maybay tam;
				tam = *dsmb.nodes[i];
				*dsmb.nodes[i] = *dsmb.nodes[j];
				*dsmb.nodes[j] = tam;		
			}		
		}
	}
}

int HieuchinhMB(Listmaybay &dsmb,CBPTR First){
	char xet[16];
	Maybay mb;

	while(true){

//		NhapChuoi("Tim kiem so hieu may bay can dieu chinh: ",xet);
//		int sohieucu = SearchMB(dsmb,xet);
//		if(sohieucu == -1){
//			cout<<"so hieu may bay khong ton tai!!!"<<endl;
//			continue;		
//		}
		if(dsmb.n == 0){
			cout<<"DANH SACH RONG!!!"<<endl;
			system("Pause");
			return 1;
		}
		int imb = HieuungthongtinMB(dsmb);
		if(imb == -1) return true;
		system("cls");
		Thongtinmaybay(dsmb,imb);
		
		for(CBPTR p = First; p!=NULL ; p = p->next){
			if(strcmp(p->cb.sohieumb,xet) == 0 ){
				if(p->cb.trangthai == 1 || p->cb.trangthai == 2){
					cout<<"May bay dang thuc hien chuyen bay "<<p->cb.ID<<endl;
					NhapChuoi("Nhap loai may bay can dieu chinh: ",mb.loai);
					goto Loop3;	
				}else{			
					goto Loop;
				}
				
			}	
		}
		
		
		
		
		
		// kiem tra so hieu may bay nhap moi
		
		Loop:
	 	NhapChuoi("Nhap so hieu may bay can dieu chinh: ",mb.sohieu);
	 		
		if( SearchMB(dsmb,mb.sohieu) != imb && SearchMB(dsmb,mb.sohieu) >= 0){
			cout<<"So hieu may bay da ton tai"<<endl;
			goto Loop;
		}		
				
		NhapChuoi("Nhap loai may bay can dieu chinh: ",mb.loai);
		
		Loop1:
		cout<<"Nhap so day may bay can dieu chinh(<=9): ";
		cin>>mb.soday;
		if(mb.soday<=0) goto Loop1;
		Loop2:
		cout<<"Nhap so dong may bay can dieu chinh(<=100): ";
		cin>>mb.sodong;
		cout<<endl;
		if(mb.sodong<=0) goto Loop2;
		
		Loop3:
		// dieu chinh thong tin cu = moi
		*dsmb.nodes[imb] = mb;
			
		return true;
	}
		
}


/////////////////// Chuyen Bay ////////////////

time_t tghientai = time(0);
tm *thoigian = localtime(&tghientai);


CBPTR SearchCBID(CBPTR First,char *ID){
	for(CBPTR p = First;p!=NULL;p=p->next){
		if(strcmp(p->cb.ID,ID)==0 && ((p->cb.trangthai == 1 ) || (p->cb.trangthai == 2 ))) 
		  return p;	
	}
	return NULL;
}

CBPTR SearchCBDD(CBPTR First,char *name){
	for(CBPTR p = First;p!=NULL;p=p->next){
		if(strcmp(p->cb.diadiem,name)==0) 
		  return p;	
	}
	return NULL;
}


void NhapChuoiCB (char *tieude, char *S) {
	cout << tieude ;  fflush(stdin);
    do
	  gets(S);
    while (strcmp(S,"")==0)  ;	
}

void ThemcuoiCB (CBPTR &First , Chuyenbay cb) {
	    CBPTR p = new Nodechuyenbay ;
		p->cb = cb ; p->next=NULL;
		if (First==NULL){ 
			First = p;
		}else { 
		CBPTR Last = First;
//		for (Last = First;Last->next !=NULL; Last=Last->next);	
//		    Last->next = p;	
		while(Last->next != NULL){
			Last = Last->next;
		}	
			Last->next = p;
		}
//		return First;
}

//void InsertLast (PTR &First , Sinhvien sv) {
//	    PTR p = new node ;
//		p->sv = sv ; p->next=NULL;
//		if (First==NULL) First = p;
//		else { PTR Last;
//		       for (Last = First;Last->next !=NULL; Last=Last->next) ;		
//		       Last->next = p;
//		     }
//}
int CheckAvailable(char *sh,CBPTR First){
	int i;
	for(CBPTR p = First;p!=NULL;p=p->next){
		if(strcmp(p->cb.sohieumb,sh)==0)
		{
			if(p->cb.trangthai == 1 || p->cb.trangthai == 2 ){	 
				i = 1;
				return i;
			}
			else if(p->cb.trangthai == 3 && p->cb.trangthai == 1){
				i = 1;
				return i;
			}else if(p->cb.trangthai == 3 && p->cb.trangthai == 2){
				i = 1;
				return i;
			}else if(p->cb.trangthai == 3 && p->cb.trangthai == 0){
				i = 0;
				return i;
			}
			
		 } 
 }
 }
	
//int CheckDD(CBPTR First,char *dd,int y,int m,int d,int h,int min){
//	
////	int y = 1900 + thoigian->tm_year;
////	int m = 1 + thoigian->tm_mon;
////	int d = thoigian->tm_mday;
////	int h = thoigian->tm_hour;
////	int min = thoigian->tm_min;
//	
//	for(CBPTR p=First;p!=NULL;p=p->next){
//		
//		int checkgio;
//		int checkphut=p->cb.date.phut;
//		
//		if(strcmp(dd,p->cb.diadiem)==0 && p->cb.trangthai == 1 ){
//			
//			int ngay = p->cb.date.ngay;
//			int thang = p->cb.date.thang;
//			int nam = p->cb.date.nam;
//			int gio = p->cb.date.gio;
//			int phut = p->cb.date.phut;	
//		
//		
//		
//		if(y == nam){
//		if(m == thang){
//			if(d == ngay){
//				if((h - gio) >=3 && min >= phut){
//					return 9;
//				}	
//				
//				}else if( d > ngay){
//					
//					if(gio < 21){
//							return 9;
//					}
//					else if(gio == 21)
//						checkgio=0;
//					else if(gio == 22)
//						checkgio=1;
//					else if(gio == 23)
//						checkgio=2;
//				
//						
//						
//						if(h >= checkgio &&  min >= checkphut){
//							return 9;
//						
//						}		
//						
//					}
//			}else if((m - thang) == 1 && d == 1){
//			
//				if(thang == 1 || thang == 3 || thang == 5 || thang == 7 || thang == 8 || thang == 10 || thang == 12)
//				{
//					if(ngay == 31){
//					
//						if(gio < 21){
//							return 9;
//					}
//					else if(gio == 21)
//						checkgio=0;
//					else if(gio == 22)
//						checkgio=1;
//					else if(gio == 23)
//						checkgio=2;
//						
//						
//						if(h >= checkgio &&  min >= checkphut){
//							return 9;
//						
//						}		
//					}else 
//						return 9;
//					
//			
//			}else if(thang == 4 || thang == 6 || thang == 9 || thang == 11 ){
//				if(ngay == 30){
//						if(gio < 21){
//							return 9;
//					}
//					else if(gio == 21)
//						checkgio=0;
//					else if(gio == 22)
//						checkgio=1;
//					else if(gio == 23)
//						checkgio=2;
//						
//						if(h >= checkgio &&  min >= checkphut){
//							return 9;
//						
//						}		
//					}else 
//						return 9;
//					
//				}else if(thang == 2){
//					if(y % 4 == 0 && y % 100 != 0 || y % 400 ==0){
//						if(ngay == 29){
//							
//							if(gio < 21){
//							return 9;
//					}
//					else if(gio == 21)
//						checkgio=0;
//					else if(gio == 22)
//						checkgio=1;
//					else if(gio == 23)
//						checkgio=2;
//						
//						
//						if(h >= checkgio &&  min >= checkphut){
//							return 9;
//						
//						}		
//					}else 
//						return 9;
//					}else 
//						if(ngay == 28){
//							
//							if(gio < 21){
//							return 9;
//					}
//					else if(gio == 21)
//						checkgio=0;
//					else if(gio == 22)
//						checkgio=1;
//					else if(gio == 23)
//						checkgio=2;
//						
//						
//						if(h >= checkgio &&  min >= checkphut){
//							return 9;
//						
//						}		
//					}else 
//						return 9;
//				}
//			}else if((m - thang) > 1)
//				return 9;
//			
//	}else if(y > nam){
//		if(m == 1 && thang == 12){
//		if(ngay == 31){
//				if(gio < 21){
//							return 9;
//					}
//					else if(gio == 21)
//						checkgio=0;
//					else if(gio == 22)
//						checkgio=1;
//					else if(gio == 23)
//						checkgio=2;
//						
//						
//						if(h >= checkgio &&  min >=checkphut){
//							return 9;
//						
//						}
//		}else 	
//			return 9;
//		
//	}else 
//		return 9;
//}
//}
//}
//}



int TinhNgay(int year, int month, int day) {
        if (month < 3) {
            year--;
            month += 12;
        }
        return 365*year + year/4 - year/100 + year/400 + (153*month - 457)/5 + day - 306;
    }


void NhapDate(Date &dt){
	Loop:
		
	do{
	
	system("cls");
			
	cout<<"  NHAP THONG TIN CHUYEN BAY "<<endl;
	
	cout<<"  Nhap nam: ";cin>>dt.nam;
	cout<<"  Nhap thang: ";cin>>dt.thang;
	cout<<"  Nhap Ngay: ";cin>>dt.ngay;

	cout<<"  Nhap gio: ";cin>>dt.gio;
	cout<<"  Nhap phut: ";cin>>dt.phut;
	
	}while(dt.gio >23 || dt.phut > 60 || dt.thang > 12 || dt.ngay > 31 );



	int y = 1900 + thoigian->tm_year;
	int m = 1 + thoigian->tm_mon;
	int d = thoigian->tm_mday;
	int h = thoigian->tm_hour;
	int min = thoigian->tm_min;

	

	//kiem tra date tao so voi thoi gian thuc
		if(dt.thang > 0 && dt.thang <= 12){
		if(dt.thang == 1 || dt.thang == 3 ||dt.thang == 5 || dt.thang == 7 || dt.thang == 8 || dt.thang ==10 || dt.thang == 12){
			if(dt.ngay <=31 && dt.ngay > 0){
				if((TinhNgay(dt.nam,dt.thang,dt.ngay) - TinhNgay(y,m,d)) >= 7){
					cout<<"Hoan Tat!!!"<<endl;
					return;
				}else
					cout<<"Ngay thang khong hop le!!!"<<endl;
					goto Loop;
			}else
				cout<<"Ngay thang khong hop le!!!"<<endl;
				goto Loop;
		}else if(dt.thang == 4 || dt.thang == 6 || dt.thang ==9 || dt.thang ==11){
			if(dt.ngay <=30 && dt.ngay > 0 ){
				if((TinhNgay(dt.nam,dt.thang,dt.ngay) - TinhNgay(y,m,d)) >= 7){
					cout<<"Hoan Tat!!!"<<endl;
					return;
			}else
				cout<<"Ngay thang khong hop le!!!"<<endl;
				goto Loop;
			}else
				cout<<"Ngay thang khong hop le!!!"<<endl;
				goto Loop;
		}else if(dt.thang == 2){
			if(dt.nam % 4 == 0 && dt.nam % 100 != 0 || dt.nam % 400 ==0){
				if(dt.ngay <= 29 && dt.ngay > 0){
					if((TinhNgay(dt.nam,dt.thang,dt.ngay) - TinhNgay(y,m,d)) >= 7){
						cout<<"Hoan tat!!!"<<endl;
						return;
					}else
						cout<<"Ngay thang khong hop le!!!"<<endl;
						goto Loop;
				}else{
					cout<<"Ngay thang khong hop le!!!"<<endl;
					goto Loop;
				}
		}else{
			if(dt.ngay <=28 && dt.ngay > 0){
				if((TinhNgay(dt.nam,dt.thang,dt.ngay) - TinhNgay(y,m,d)) >= 7){
						cout<<"Hoan Tat!!!"<<endl;
						return;
				}else
					cout<<"Ngay thang khong hop le!!!"<<endl;
					goto Loop;
				}else{
						cout<<"Ngay thang khong hop le!!!"<<endl;
						goto Loop;
					}
			}
	
	}
}else 
		cout<<"Ngay thang khong hop le!!!"<<endl;
		goto Loop;
		

}



void NhapNgay(Date &dt,char *kt){
	Loop:
	int K=0;
	
	system("cls");
	
	CBPTR First;		
	cout<<"  NHAP THONG TIN CHUYEN BAY "<<endl;
	cout<<"  Nhap nam: ";cin>>dt.nam;
	cout<<"  Nhap thang: ";cin>>dt.thang;
	cout<<"  Nhap Ngay: ";cin>>dt.ngay;
	cout<<"  Nhap gio: ";cin>>dt.gio;
	cout<<"  Nhap phut: ";cin>>dt.phut;
	
	
	for(CBPTR p=First;p!=NULL;p=p->next){
		
		int checkgio;
		int checkphut=p->cb.date.phut;
		
		if(strcmp(kt,p->cb.diadiem)==0 && p->cb.trangthai == 1 ){
			
			int ngay = p->cb.date.ngay;
			int thang = p->cb.date.thang;
			int nam = p->cb.date.nam;
			int gio = p->cb.date.gio;
			int phut = p->cb.date.phut;	
		
		if(dt.nam == nam){
			if(dt.thang == thang){
				if(dt.ngay == ngay){
					if((dt.gio - gio) >=3 && dt.phut >= phut){
						
						K=1;
						}else
						cout<<"Khong the tao chuyen bay nay!!!"<<endl;
						system("pause");
					}
					}
					}
	}
		

	if(K!=1)
		goto Loop;
	else{

		int y = 1900 + thoigian->tm_year;
		int m = 1 + thoigian->tm_mon;
		int d = thoigian->tm_mday;
		int h = thoigian->tm_hour;
		int min = thoigian->tm_min;
	
	 
	
		if(dt.thang > 0 && dt.thang <= 12){
		if(dt.thang == 1 || dt.thang == 3 ||dt.thang == 5 || dt.thang == 7 || dt.thang == 8 || dt.thang ==10 || dt.thang == 12){
			if(dt.ngay <=31 && dt.ngay > 0){
				if((TinhNgay(dt.nam,dt.thang,dt.ngay) - TinhNgay(y,m,d)) >= 7){
					cout<<"Hoan Tat!!!"<<endl;
					return;
				}else
					cout<<"Ngay thang khong hop le!!!"<<endl;
					goto Loop;
			}else
				cout<<"Ngay thang khong hop le!!!"<<endl;
				goto Loop;
		}else if(dt.thang == 4 || dt.thang == 6 || dt.thang ==9 || dt.thang ==11){
			if(dt.ngay <=30 && dt.ngay > 0 ){
				if((TinhNgay(dt.nam,dt.thang,dt.ngay) - TinhNgay(y,m,d)) >= 7){
					cout<<"Hoan Tat!!!"<<endl;
					return;
			}else
				cout<<"Ngay thang khong hop le!!!"<<endl;
				goto Loop;
			}else
				cout<<"Ngay thang khong hop le!!!"<<endl;
				goto Loop;
		}else if(dt.thang == 2){
			if(dt.nam % 4 == 0 && dt.nam % 100 != 0 || dt.nam % 400 ==0){
				if(dt.ngay <= 29 && dt.ngay > 0){
					if((TinhNgay(dt.nam,dt.thang,dt.ngay) - TinhNgay(y,m,d)) >= 7){
						cout<<"Hoan tat!!!"<<endl;
						return;
					}else
						cout<<"Ngay thang khong hop le!!!"<<endl;
						goto Loop;
				}else{
					cout<<"Ngay thang khong hop le!!!"<<endl;
					goto Loop;
				}
		}else{
			if(dt.ngay <=28 && dt.ngay > 0){
				if((TinhNgay(dt.nam,dt.thang,dt.ngay) - TinhNgay(y,m,d)) >= 7){
						cout<<"Hoan Tat!!!"<<endl;
						return;
				}else
					cout<<"Ngay thang khong hop le!!!"<<endl;
					goto Loop;
				}else{
						cout<<"Ngay thang khong hop le!!!"<<endl;
						goto Loop;
					}
			}
	
	}
}else 
		cout<<"Ngay thang khong hop le!!!"<<endl;
		goto Loop;
		
}
		

}
}



void UpdateTrangThaiCB(CBPTR &First){
	

	CBPTR p;
	// lay so lieu thoi gian thuc
//	 int y = 1900 + thoigian->tm_year;
//	int m = 1 + thoigian->tm_mon;
//	int d = thoigian->tm_mday;
//  int h = thoigian->tm_hour;
// 	int min = thoigian->tm_minute;

//thoi gian thuc gia dinh de test chuong trinh
	int h = 4;
	int min = 0;
	int y = 2021;
	int m = 3;
	int d = 10;
	
	
	for(p=First; p!= NULL; p=p->next){
		int checkgio;
		int checkphut=p->cb.date.phut;

// thoi gian hoan tat chuyen bay la 5 gio ke tu thoi diem khoi hanh
	if(y == p->cb.date.nam){
		if(m == p->cb.date.thang){
			if(d == p->cb.date.ngay){
				if((h - p->cb.date.gio) >=5 && min >= p->cb.date.phut){
					p->cb.trangthai = 3;

				}	
				
				}else if( d > p->cb.date.ngay){
					if(p->cb.date.gio < 19){
							p->cb.trangthai == 3;
					}
					else if(p->cb.date.gio == 19)
						checkgio=0;
					else if(p->cb.date.gio == 20)
						checkgio=1;
					else if(p->cb.date.gio == 21)
						checkgio=2;
					else if(p->cb.date.gio == 22)
						checkgio=3;
					else if(p->cb.date.gio == 23)
						checkgio=4;
						
						
						if(h == checkgio && min >= checkphut){
								p->cb.trangthai = 3;
							}else if(h > checkgio){
								p->cb.trangthai = 3;
						}
								
					}
			}else if((m - p->cb.date.thang) == 1 && d == 1){
			
				if(p->cb.date.thang == 1 || p->cb.date.thang == 3 || p->cb.date.thang == 5 || p->cb.date.thang == 7 || p->cb.date.thang == 8 || p->cb.date.thang == 10 || p->cb.date.thang == 12)
				{
					if(p->cb.date.ngay == 31){
					
						if(p->cb.date.gio < 19){
							p->cb.trangthai == 3;
						
					}
					else if(p->cb.date.gio == 19)
						checkgio=0;
					else if(p->cb.date.gio == 20)
						checkgio=1;
					else if(p->cb.date.gio == 21)
						checkgio=2;
					else if(p->cb.date.gio == 22)
						checkgio=3;
					else if(p->cb.date.gio == 23)
						checkgio=4;
						
						
						if(h == checkgio && min >= checkphut){
								p->cb.trangthai = 3;
							}else if(h > checkgio){
								p->cb.trangthai = 3;
						}
					}else 
						p->cb.trangthai = 3;
					
			
			}else if(p->cb.date.thang == 4 || p->cb.date.thang == 6 || p->cb.date.thang == 9 || p->cb.date.thang == 11 ){
				if(p->cb.date.ngay == 30){
						if(p->cb.date.gio < 19){
							p->cb.trangthai == 3;
						
					}
					else if(p->cb.date.gio == 19)
						checkgio=0;
					else if(p->cb.date.gio == 20)
						checkgio=1;
					else if(p->cb.date.gio == 21)
						checkgio=2;
					else if(p->cb.date.gio == 22)
						checkgio=3;
					else if(p->cb.date.gio == 23)
						checkgio=4;
						
							if(h == checkgio && min >= checkphut){
								p->cb.trangthai = 3;
							}else if(h > checkgio){
								p->cb.trangthai = 3;
						}	
					}else 
						p->cb.trangthai = 3;
					
				}else if(p->cb.date.thang == 2){
					if(y % 4 == 0 && y % 100 != 0 || y % 400 ==0){
						if(p->cb.date.ngay == 29){
							
							if(p->cb.date.gio < 19){
							p->cb.trangthai == 3;
						
					}
					else if(p->cb.date.gio == 19)
						checkgio=0;
					else if(p->cb.date.gio == 20)
						checkgio=1;
					else if(p->cb.date.gio == 21)
						checkgio=2;
					else if(p->cb.date.gio == 22)
						checkgio=3;
					else if(p->cb.date.gio == 23)
						checkgio=4;
						
						
							if(h == checkgio && min >= checkphut){
								p->cb.trangthai = 3;
							}else if(h > checkgio){
								p->cb.trangthai = 3;
						}	
					}else 
						p->cb.trangthai = 3;
					}else 
						if(p->cb.date.ngay == 28){
							
							if(p->cb.date.gio < 19){
							p->cb.trangthai == 3;
						
					}
					else if(p->cb.date.gio == 19)
						checkgio=0;
					else if(p->cb.date.gio == 20)
						checkgio=1;
					else if(p->cb.date.gio == 21)
						checkgio=2;
					else if(p->cb.date.gio == 22)
						checkgio=3;
					else if(p->cb.date.gio == 23)
						checkgio=4;
						
						
							if(h == checkgio && min >= checkphut){
								p->cb.trangthai = 3;
							}else if(h > checkgio){
								p->cb.trangthai = 3;
						}	
					}else 
						p->cb.trangthai = 3;
				}
							
			}else if((m - p->cb.date.thang) > 1)
				p->cb.trangthai = 3;
			
	}else if(y > p->cb.date.nam){
		if(m == 1 && p->cb.date.thang == 12){
		if(p->cb.date.ngay == 31){
				if(p->cb.date.gio < 19){
							p->cb.trangthai == 3;
							
					}
					else if(p->cb.date.gio == 19)
						checkgio=0;
					else if(p->cb.date.gio == 20)
						checkgio=1;
					else if(p->cb.date.gio == 21)
						checkgio=2;
					else if(p->cb.date.gio == 22)
						checkgio=3;
					else if(p->cb.date.gio == 23)
						checkgio=4;
						
						
							if(h == checkgio && min >= checkphut){
								p->cb.trangthai = 3;
							}else if(h > checkgio){
								p->cb.trangthai = 3;
						}
		}else 	
			p->cb.trangthai = 3;
		
	}else 
		p->cb.trangthai = 3;
	
}
}
}





	


void NhapDSVE(int day, int dong,Chuyenbay &cb){
	
	int dem=0;
	int kitu=0;
	cb.danhsachve.vecb = new Ve[day*dong];
	for( char i='A';i<='Z';i++){
		if(kitu<day){
			for(int j = 1; j<=dong;j++){
				stringstream ss;
				ss << i;
				string str = ss.str();
				
				stringstream ss1;
				ss1 << j;
				string str1 = ss1.str();
				
				str.append(str1);
				
				cb.danhsachve.vecb[dem].chongoi = str;
				strcpy(cb.danhsachve.vecb[dem].Cmnd,"NOT");

				dem++;
			}
			kitu++;	
		}
	}	
}

void Lietkechongoi(Chuyenbay cb){
	for(int i=0;i<cb.danhsachve.n;i++){
		if(strcmp(cb.danhsachve.vecb[i].Cmnd,"NOT") == 0){
			cout<<cb.danhsachve.vecb[i].chongoi<<" ";		
		}
	}
	system("pause");
}




int NhapDSCB(CBPTR &First,Listmaybay dsmb){
	CBPTR Last,p;
	Chuyenbay cb;
	int n;
	int k;

	  do{
	  	if(dsmb.n == 0){
	  		cout<<"Danh sach may bay rong khong the tao chuyen bay!!!"<<endl;
	  		system("pause");
	  		return 1;
		  }
	  cout<<"Nhap so chuyen bay muon them vao (n>0): ";
	  cin>>n; 
	  if(n == 0)
	  	return 1;
	   }while(n<=0);
	   
		for(int i=1 ;i<=n;i++){
			cout<<"Thong tin chuyen bay "<<i<<" "<<endl;
				Loop:
				system("cls");
				cout<<"                                              NHAP THONG TIN CHUYEN BAY                                      "<<endl;
				NhapChuoiCB("Nhap ma chuyen bay: ",cb.ID);
				if(strcmp(cb.ID,"0")==0) continue;
				if(SearchCBID(First,cb.ID)!=NULL){
					cout<<"Ma chuyen bay bi trung!!!, Nhap lai "<<endl;
					goto Loop;
				}
				fflush (stdin);
				
				cout<<"Nhap dia diem den: "; 
				gets(cb.diadiem);
				cb.trangthai =1;
				NhapDate(cb.date);
				
				for(CBPTR p=First;p!=NULL;p=p->next){
					int h;
					int min = p->cb.date.phut;
			
					if(strcmp(cb.diadiem,p->cb.diadiem) == 0 && p->cb.trangthai == 1){
					cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
					cout<<"Dang co chuyen bay den "<<p->cb.diadiem<<" vao luc "<<p->cb.date.gio<<":"<<p->cb.date.phut<<"  "<<p->cb.date.ngay<<"/"<<p->cb.date.thang<<"/"<<p->cb.date.nam<<". "<<"So hieu may bay la: "<<p->cb.sohieumb<<endl;;	
					cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
					cout<<"Chi duoc set chuyen bay den day sau 3 tieng ke tu thoi diem khoi hanh tren!!!"<<endl;
					system("pause");
						
					if(cb.date.nam == p->cb.date.nam){
						if(cb.date.thang == p->cb.date.thang){
							if(cb.date.ngay == p->cb.date.ngay){
									if((cb.date.gio - p->cb.date.gio) == 3 && cb.date.phut >= p->cb.date.phut){
										goto Loop1;
								}else if((cb.date.gio - p->cb.date.gio) > 3){
									goto Loop1;
								}else 
									goto Loop;	
							}else if(cb.date.ngay > p->cb.date.ngay){
								if(p->cb.date.gio < 21){
									goto Loop1;
								}else if(p->cb.date.gio == 21){
									h = 0;
								}else if(p->cb.date.gio == 22){
									h = 1;
								}else if(p->cb.date.gio == 23){
									h = 2;
								}
								
								if((cb.date.gio - h) == 3 && cb.date.phut >= min ){
									goto Loop1;
								}else if((cb.date.gio - h) > 3){
									goto Loop1;
								}else 
									goto Loop;
							}else
								goto Loop;
			}else if((cb.date.thang - p->cb.date.thang) == 1 && cb.date.ngay == 1){
				if(p->cb.date.thang == 1 || p->cb.date.thang == 3 || p->cb.date.thang == 5 || p->cb.date.thang == 7 || p->cb.date.thang == 8 || p->cb.date.thang == 10 || p->cb.date.thang == 12)
				{
					if(p->cb.date.ngay == 31){
						if(p->cb.date.gio < 21){
							goto Loop1;
					}else if(p->cb.date.gio == 21)
						h=0;
					else if(p->cb.date.gio == 22)
						h=1;
					else if(p->cb.date.gio == 23)
						h=2;
						
				if((cb.date.gio - h) == 3 && cb.date.phut >= min ){
						goto Loop1;
				}else if((cb.date.gio - h) > 3){
					goto Loop1;
				}else 
					goto Loop;
				}else
					goto Loop1;
					
			
			}else if(p->cb.date.thang == 4 || p->cb.date.thang == 6 || p->cb.date.thang == 9 || p->cb.date.thang == 11 ){
				if(p->cb.date.ngay == 30){
						if(p->cb.date.gio < 21){
							goto Loop1;
					}else if(p->cb.date.gio == 21)
						h=0;
					else if(p->cb.date.gio == 22)
						h=1;
					else if(p->cb.date.gio == 23)
						h=2;
						
				if((cb.date.gio - h) == 3 && cb.date.phut >= min ){
						goto Loop1;
				}else if((cb.date.gio - h) > 3){
					goto Loop1;
				}else 
					goto Loop;
				}else 
					goto Loop1;

				}else if(p->cb.date.thang == 2){
					if(p->cb.date.nam % 4 == 0 && p->cb.date.nam % 100 != 0 || p->cb.date.nam % 400 ==0){//nam nhuan
						if(p->cb.date.ngay == 29){
						if(p->cb.date.gio < 21){
							goto Loop1;
					}else if(p->cb.date.gio == 21)
						h=0;
					else if(p->cb.date.gio == 22)
						h=1;
					else if(p->cb.date.gio == 23)
						h=2;
						
					if((cb.date.gio - h) == 3 && cb.date.phut >= min ){
						goto Loop1;
				}else if((cb.date.gio - h) > 3){
					goto Loop1;
				}else 
					goto Loop;
				}else
					goto Loop1;
						
			}else 
				if(p->cb.date.ngay == 28){
					if(p->cb.date.gio < 21){
						goto Loop1;
						
					}else if(p->cb.date.gio == 21)
						h=0;
					else if(p->cb.date.gio == 22)
						h=1;
					else if(p->cb.date.gio == 23)
						h=2;
				
						if((cb.date.gio - h)==3 && cb.date.phut >= min){
							goto Loop1;
						}else if((cb.date.gio - h) > 3){
							goto Loop1;
						}else 
							goto Loop;		
					}else 
						goto Loop1;
				}
			}else if(cb.date.thang < p->cb.date.thang)
				goto Loop;
			else if((cb.date.thang - p->cb.date.thang) > 1)
				goto Loop1;
		}else if(cb.date.nam > p->cb.date.nam){
			if(cb.date.thang == 1 && p->cb.date.thang == 12){
				if(p->cb.date.ngay == 31){
				if(p->cb.date.gio < 21){
						goto Loop1;
					}else if(p->cb.date.gio == 21)
						h=0;
					else if(p->cb.date.gio == 22)
						h=1;
					else if(p->cb.date.gio == 23)
						h=2;
				
					if((cb.date.gio - h) == 3 && cb.date.phut >= min){
							goto Loop1;
						}else if((cb.date.gio - h) > 3){
							goto Loop1;
						}else if((cb.date.gio - h) < 3)
							goto Loop;
							
		}else 	
			goto Loop1;
		
	}else 
		goto Loop1;
	
}

}
				

				// ktra so hieu mb co ton tai
				Loop1:
				cout<<"So hieu cac may bay co trong csdl:"<<endl;
				for(int i=0;i<dsmb.n;i++){
					cout<<dsmb.nodes[i]->sohieu;
					cout<<" ";
				}
				cout<<endl;
				NhapChuoiCB("Nhap so hieu may bay: ",cb.sohieumb);
				int kt = SearchMB(dsmb,cb.sohieumb);
				int ch = CheckAvailable(cb.sohieumb,First);
				if(kt == -1){
					cout<<"So hieu may bay khong ton tai!!!"<<endl;
				    goto Loop1;
				}else if(kt != -1 && ch == 1){
						cout<<"May bay dang thuc hien chuyen bay, Nhap lai!!!"<<endl;
						system("pause");
						goto Loop1;
				}else if(kt != -1 && ch == 0 ){
				
				// thong tin danh sach ve
				cb.danhsachve.n = dsmb.nodes[kt]->soday * dsmb.nodes[kt]->sodong;
		   	    cb.danhsachve.sldb = 0;	
				NhapDSVE(dsmb.nodes[kt]->soday,dsmb.nodes[kt]->sodong,cb);						
				
				
																	
				p = new Nodechuyenbay;	
				p->cb = cb;
				p->next = NULL;
				if (First==NULL){ 
					First = p;
				}else{
					ThemcuoiCB(First,cb);
				}
			
		}	
}
}
}




void Thongtinchuyenbay(Chuyenbay cb){
	cout<<"				                   THONG TIN CHUYEN BAY "<<cb.ID<<endl;
	cout<<" Ma chuyen bay      Dia diem      So hieu may bay     Trang thai      SL Ve      SL Ve ban   Ngay/Thang/Nam    Gio/phut"<<endl;
	gotoxy(wherex()+2,wherey());
	cout<<" "<<cb.ID;
	gotoxy(wherex()+15,wherey());
	cout<<cb.diadiem;
	gotoxy(wherex()+11,wherey());
	cout<<cb.sohieumb;
	gotoxy(wherex()+19,wherey());
	cout<<cb.trangthai;
	gotoxy(wherex()+12,wherey());
	cout<<cb.danhsachve.n;
	gotoxy(wherex()+11,wherey());
	cout<<cb.danhsachve.sldb;
	gotoxy(wherex()+9,wherey());	
	cout<<cb.date.ngay<<"/" ;
	cout<<cb.date.thang<<"/";
	cout<<cb.date.nam;
	gotoxy(wherex()+7,wherey());
	cout<<cb.date.gio<<":"  ;
	cout<<cb.date.phut<<endl;
	
	
}

void XoaDSCB(CBPTR &First){
	CBPTR p = First;
	while(p!=NULL){
		delete p;
	}
	First = NULL;
}


void LietkeDSCB(CBPTR First){
	char ch;
	do{
		system("cls");
		if(First == NULL){
			cout<<"		                    CHUA CO CHUYEN BAY TRONG DANH SACH       ESC : thoat"<<endl;
		}else{
			int dem =0 ;
			cout<<"                                                DANH SACH CHUYEN BAY 			ESC : thoat"<<endl;
			
			cout<<"STT   MA CB      Dia diem      So hieu may bay     Trang thai      SL Ve      SL Ve ban   Ngay/Thang/Nam    Gio/phut   "<<endl;
			for(CBPTR p = First; p!=NULL;p=p->next){
				dem++;
				cout<<" "<<dem;
				gotoxy(6,dem+1);
				cout<<p->cb.ID;
				gotoxy(19,dem+1);
				cout<<p->cb.diadiem;
				gotoxy(36,dem+1);
				cout<<p->cb.sohieumb;
				gotoxy(55,dem+1);
				cout<<p->cb.trangthai;
				gotoxy(68,dem+1);
				cout<<p->cb.danhsachve.n;
				gotoxy(82,dem+1);
				cout<<p->cb.danhsachve.sldb;
				gotoxy(93,dem+1);	
				cout<<p->cb.date.ngay<<"/" ;
				cout<<p->cb.date.thang<<"/";
				cout<<p->cb.date.nam;
				gotoxy(110,dem+1);
				cout<<p->cb.date.gio<<":"  ;
				cout<<p->cb.date.phut<<endl;
				
			}
			
		}
		ch = getch();
		
	}while(ch != 27);


	
}

void LietkeCBYeucau(Chuyenbay cb){
		gotoxy(wherex()+1,wherey());
		cout<<"     "<<cb.ID;;
		gotoxy(wherex()+11,wherey());
		cout<<cb.diadiem;
		gotoxy(wherex()+13,wherey());
		cout<<cb.trangthai;
		gotoxy(wherex()+11,wherey());
		cout<<cb.danhsachve.n - cb.danhsachve.sldb;
		gotoxy(wherex()+9,wherey());
		cout<<cb.date.ngay<<"/" ;
		cout<<cb.date.thang<<"/";
		cout<<cb.date.nam;
		gotoxy(wherex()+6,wherey());
		cout<<cb.date.gio<<":"  ;
		cout<<cb.date.phut<<endl;		

}

void HieuungCB(int t,int f,Chuyenbay cb){
	HANDLE hConsoleColor;
    hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);		
	SetConsoleTextAttribute(hConsoleColor, f); // f la mau
	cout<<" "<<t;
	gotoxy(6,t+1);
	cout<<cb.ID;
	gotoxy(19,t+1);
	cout<<cb.diadiem;
	gotoxy(33,t+1);
	cout<<cb.sohieumb;
	gotoxy(55,t+1);
	cout<<cb.trangthai;
	gotoxy(68,t+1);
	cout<<cb.danhsachve.n;
	gotoxy(82,t+1);
	cout<<cb.danhsachve.sldb;
	gotoxy(93,t+1);	
	cout<<cb.date.ngay<<"/" ;
	cout<<cb.date.thang<<"/";
	cout<<cb.date.nam;
	gotoxy(110,t+1);
	cout<<cb.date.gio<<":"  ;
	cout<<cb.date.phut<<endl;

}

int HieuungthongtinCB(CBPTR First){
	int i=1;
	char ch;

	do{
		system("cls");
		HANDLE hConsoleColor;
   		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);		
		SetConsoleTextAttribute(hConsoleColor, 12);
		cout<<"                                                   DANH SACH CHUYEN BAY 			ESC : thoat"<<endl;
		cout<<"STT   MA CB      Dia diem      So hieu may bay     Trang thai      SL Ve      SL Ve ban   Ngay/Thang/Nam    Gio/phut   "<<endl;

		int t=1;
		for(CBPTR p = First;p!=NULL;p=p->next){
			if(t!=i){
				HieuungCB(t,2,p->cb);
			}else HieuungCB(t,1,p->cb);
			t++;
		}
		do{
	            ch = getch();
	            if (ch==224) ch=getch();
	        } while (!(ch==224||ch==13||ch==27||ch==80||ch==72));
	        if(ch==80){         //ky tu xuong
	             i=i+1; 
	             if (i>(t-1)) i = 1; 
	        }
	        if (ch==72){          //ky tu len
	            i=i-1; 
	            if (i<1) i = t-1; 
	   		}
	   		if(ch == 27){
	   			return -1;
			 }
	}while (!(ch == 13));
			return i;

}

int HieuungthongtinDatve(CBPTR First){
	int i=1;
	char ch;

	do{
		system("cls");
		HANDLE hConsoleColor;
   		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);		
		SetConsoleTextAttribute(hConsoleColor, 12);
		cout<<"                                                   DANH SACH CHUYEN BAY 			ESC : thoat"<<endl;
		cout<<"STT   MA CB      Dia diem      So hieu may bay     Trang thai      SL Ve      SL Ve ban   Ngay/Thang/Nam    Gio/phut   "<<endl;

		int t=1;
		for(CBPTR p = First;p!=NULL;p=p->next){			
			if(p->cb.trangthai == 1){
				if(t!=i){
					HieuungCB(t,2,p->cb);
				}else HieuungCB(t,1,p->cb);
				t++;
			}
		}
		do{
	            ch = getch();
	            if (ch==224) ch=getch();
	        } while (!(ch==224||ch==13||ch==27||ch==80||ch==72));
	        if(ch==80){         //ky tu xuong
	             i=i+1; 
	             if (i>(t-1)) i = 1; 
	        }
	        if (ch==72){          //ky tu len
	            i=i-1; 
	            if (i<1) i = t-1; 
	   		}
	   		if(ch == 27){
	   			return -1;
			 }
	}while (!(ch == 13));
			return i;

}

int HieuungthongtinCBHoatDong(CBPTR First){
	int i=1;
	char ch;

	do{
		system("cls");
		HANDLE hConsoleColor;
   		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);		
		SetConsoleTextAttribute(hConsoleColor, 12);
		cout<<"                                                   DANH SACH CHUYEN BAY 			ESC : thoat"<<endl;
		cout<<"STT   MA CB      Dia diem      So hieu may bay     Trang thai      SL Ve      SL Ve ban   Ngay/Thang/Nam    Gio/phut   "<<endl;

		int t=1;
		for(CBPTR p = First;p!=NULL ;p=p->next){
			if( p->cb.trangthai == 1  || p->cb.trangthai == 2 ){
				if(t!=i){
					HieuungCB(t,2,p->cb);
				}else HieuungCB(t,1,p->cb);
				t++;
			}

		}
		do{
	            ch = getch();
	            if (ch==224) ch=getch();
	        } while (!(ch==224||ch==13||ch==27||ch==80||ch==72));
	        if(ch==80){         //ky tu xuong
	             i=i+1; 
	             if (i>(t-1)) i = 1; 
	        }
	        if (ch==72){          //ky tu len
	            i=i-1; 
	            if (i<1) i = t-1; 
	   		}
	   		if(ch == 27){
	   			return -1;
			 }
	}while (!(ch == 13));
			return i;

}


int Hieuungyesno(string yeucau){
	char ch;
	int i=0;
	char *Xacnhan[3] ={"YES","NO"};
	do{
		system("cls");
		HANDLE hConsoleColor;
   		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);		
		SetConsoleTextAttribute(hConsoleColor, 12);
		cout<<yeucau<<endl;

		for(int t=0 ; t<=1 ; t++){
			if(t==i){
				HANDLE hConsoleColor;
   				hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);		
				SetConsoleTextAttribute(hConsoleColor, 1);
				cout<<Xacnhan[t]<<endl;
			}else{
				HANDLE hConsoleColor;
   				hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);		
				SetConsoleTextAttribute(hConsoleColor, 2);
				cout<<Xacnhan[t]<<endl;
			}
		}
		do{
	            ch = getch();
	            if (ch==224) ch=getch();
	        } while (!(ch==224||ch==13||ch==27||ch==80||ch==72));
	        if(ch==80){         //ky tu xuong
	             i=i+1; 
	             if (i>1) i = 0; 
	        }
	        if (ch==72){          //ky tu len
	            i=i-1; 
	            if (i<0) i = 1; 
	   		}
	   		if(ch == 27){
	   			return -1;
			 }
	}while (!(ch == 13));
			return i;	
}

void XoaCB(CBPTR &First ){
	string yeucau = "Ban co that su muon xoa chuyen bay ?";
	Loop:
	if(First == NULL){
		cout<<"		                CHUA CO CHUYEN BAY TRONG DANH SACH       ESC : thoat"<<endl;
		char ch = getch();
		if( ch == 27) return;
		goto Loop;
	}	
	int ixoacb = HieuungthongtinCB(First);
	if(ixoacb == -1){
		return;
	}
	int t = 1;
	for(CBPTR p = First;p!=NULL;p=p->next){
		// chay den vi tri chon chuyen bay truoc do
		if(t == ixoacb){
			// chuyen bay dang duoc thuc hien
			if(p->cb.trangthai==1 || p->cb.trangthai==2 ){
				system("cls");
				cout<<"Chuyen bay "<<p->cb.ID<<" dang duoc thuc hien, khong the xoa!"<<endl;
				system("pause");
				return;
			}else{
				//Chuyen bay can xoa o dau danh sach
				if(ixoacb == 1){
					// xac nhan muon xoa hay khong ?
					int ixacnhan = Hieuungyesno(yeucau);	
					if(ixacnhan == -1 || ixacnhan == 1){
						return;
					}else{
						p = First ;
			  			First = p ->next ; 
			  			delete p ; 
						return;	
					}			
				}else{
					// vi tri chuyen bay o cho bat ki
					int ixacnhan = Hieuungyesno(yeucau);	
					if(ixacnhan == -1 || ixacnhan == 1){
						return;
					}else{
						t = 1;
						for(p =First; p!=NULL ; p=p->next){
							if(t == (ixoacb-1)){
								CBPTR q = p->next;
								p->next = q->next;
								delete q;
								return;										
							}
							t++;	
						}		
					}
				}		
			}
		}
		
		t++;
	}	
		
}


void SaveVECB(ofstream &fileout,Chuyenbay cb){
	for(int i=0;i<cb.danhsachve.n;i++){
		fileout<<cb.danhsachve.vecb[i].chongoi<<"-";
		fileout<<cb.danhsachve.vecb[i].Cmnd<<",";
	}	
}

void SaveCB(ofstream &fileout,Chuyenbay cb){
	
	fileout<<cb.ID<<",";
	fileout<<cb.diadiem<<",";
	fileout<<cb.sohieumb<<",";
	fileout<<cb.trangthai<<" ";
	fileout<<cb.date.ngay<<" ";
	fileout<<cb.date.thang<<" ";
	fileout<<cb.date.nam<<" ";
	fileout<<cb.date.gio<<" ";
	fileout<<cb.date.phut<<" ";
	fileout<<cb.danhsachve.n<<" ";
	fileout<<cb.danhsachve.sldb<<" ";
	SaveVECB(fileout,cb);
	
}

void SaveDSCB(CBPTR First){
	if(First == NULL){
		return;
	}
	ofstream fileout;
	fileout.open("dschuyenbay.txt",ios_base::out);
	CBPTR p;
	for(p = First;p->next!=NULL;p=p->next){
		SaveCB(fileout,p->cb);
		fileout<<endl;
	}
	SaveCB(fileout,p->cb);	
	fileout.close();
	return;
}

void LoadVECB(ifstream &filein,Chuyenbay &cb){
	cb.danhsachve.vecb = new Ve[cb.danhsachve.n];
	for(int i=0;i<cb.danhsachve.n;i++){
		
		getline(filein,cb.danhsachve.vecb[i].chongoi,'-');
		
		string cmndtam;
		getline(filein,cmndtam,',');
		strcpy(cb.danhsachve.vecb[i].Cmnd,cmndtam.c_str());
	}		
}

void LoadCB(ifstream &filein,Chuyenbay &cb){
	
		//ma cb
		string tamid;
		getline(filein,tamid,',');
		strcpy(cb.ID,tamid.c_str());

		// dia diem
		string dd;
		getline(filein,dd,',');
		strcpy(cb.diadiem,dd.c_str());

		// so hieu mb
		string sh;
		getline(filein,sh,',');
		strcpy(cb.sohieumb,sh.c_str());

		// trang thai
		filein>>cb.trangthai;

		//ngay thang nam
		filein>>cb.date.ngay;
		filein>>cb.date.thang;
		filein>>cb.date.nam;
		filein>>cb.date.gio;
		filein>>cb.date.phut;
		filein>>cb.danhsachve.n;
		filein>>cb.danhsachve.sldb;
		filein.ignore(1);
		// load danh sach ve chuyen bay 

		LoadVECB(filein,cb);
		
		string tam;
		getline(filein,tam);
		
}

void LoadDSCB(CBPTR &First){
	ifstream filein;
	Chuyenbay cb;
	filein.open("dschuyenbay.txt",ios::in);	 
	
    if (First != NULL){
        return;
	}
	
	if (filein.fail()) 
	{ 
	    // file is empty 
	    return;
	} 
	while(!filein.eof()){
					
		LoadCB(filein,cb);			
		ThemcuoiCB(First,cb);
		
	}
	filein.close();
	
	return;
}


void SapXepCBTheoID(CBPTR &First){
 	CBPTR p, q;
	char min[15];
    Chuyenbay cb;
	
	for(p = First; p->next != NULL; p = p->next){
		for(q = p->next; q != NULL; q = q->next){
			if(strcmp(q->cb.ID,p->cb.ID)==-1){
//				strcpy(min,q->cb.ID);
//				pmin = q;
				Chuyenbay tam;
				tam = p->cb;
				p->cb = q->cb;
				q->cb = tam;
				 
			}
		}
	}
}

int LuachonhieuchinhCB(){
	char ch;
	int i=0;
	char *Xacnhan[3] ={"Thong tin chuyen bay","Thoi gian chuyen bay"};
	do{
		system("cls");
		HANDLE hConsoleColor;
   		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);		
		SetConsoleTextAttribute(hConsoleColor, 12);
		cout<<"  Hieu Chinh : "<<endl;

		for(int t=0 ; t<=1 ; t++){
			if(t==i){
				HANDLE hConsoleColor;
   				hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);		
				SetConsoleTextAttribute(hConsoleColor, 1);
				cout<<Xacnhan[t]<<endl;
			}else{
				HANDLE hConsoleColor;
   				hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);		
				SetConsoleTextAttribute(hConsoleColor, 2);
				cout<<Xacnhan[t]<<endl;
			}
		}
		do{
	            ch = getch();
	            if (ch==224) ch=getch();
	        } while (!(ch==224||ch==13||ch==27||ch==80||ch==72));
	        if(ch==80){         //ky tu xuong
	             i=i+1; 
	             if (i>1) i = 0; 
	        }
	        if (ch==72){          //ky tu len
	            i=i-1; 
	            if (i<0) i = 1; 
	   		}
	   		if(ch == 27){
	   			return -1;
			 }
	}while (!(ch == 13));
			return i;	
}


int HieuchinhCB(CBPTR &First){
	Chuyenbay cb;
	while(true){
		int icb = HieuungthongtinCB(First);
		if(icb == -1) return true;
		int k=1;
		for(CBPTR p = First;p!=NULL;p=p->next){
			if(k == icb){
				if(p->cb.trangthai == 1 || p->cb.trangthai == 2){
					int luachon =  LuachonhieuchinhCB();	
					if(luachon == -1) return true; 
					if(luachon == 0){
						system("cls");
						Thongtinchuyenbay(p->cb);
//						NhapChuoi("Nhap dia diem den can hieu chinh: ",cb.diadiem);
//						strcpy(p->cb.diadiem,cb.diadiem);
						cout<<"Chua ho tro hieu chinh thong tin chuyen bay!!!"<<endl;
						system("pause");
						return true;
					}else{
						system("cls");
						Thongtinchuyenbay(p->cb);
						NhapDate(cb.date);
						p->cb.date = cb.date;
						return true;				
					}
				}else{
					system("cls");
					cout<<"Chuyen bay "<<p->cb.ID<<" da hoan tat hoac huy chuyen! khong the hieu chinh"<<endl;
					system("pause");
					return true;								
				}
			}	
			k++;
		}	
		return true;
	}
}


void HuyCB(CBPTR First){
		string yeucau = "Ban co chac muon huy chuyen bay";
	
		if(First == NULL){
			cout<<"		                    CHUA CO CHUYEN BAY TRONG DANH SACH       ESC : thoat"<<endl;
			system("pause");
			return;
		}
		
		int icb = HieuungthongtinCBHoatDong(First);
		if(icb == -1){
			return;
		}
		int k=1;
		for(CBPTR p =First;p!=NULL;p=p->next){
			if(p->cb.trangthai == 1 || p->cb.trangthai == 2){
			if(k == icb){
				int ixacnhan = Hieuungyesno(yeucau);
				if(ixacnhan == -1 || ixacnhan == 1){
					return;
				}else{
					p->cb.trangthai = 0;
					system("cls");
					cout<<" Da huy chuyen bay "<<p->cb.ID<<" hoan tat!!!"<<endl;					
					system("pause");
					return;
				}
			}
			k++;
		}	
	
}
}
//liet ke danh sach chuyen bay theo thoi gian + dia diem
void LietkeDSCBYeuCau(CBPTR First){
	char diadiemden[30];
	int ngay,thang,nam;
		
	Loop:
		system("cls");
		NhapChuoi("Nhap dia diem chuyen bay den: ",diadiemden);		 
		if(SearchCBDD(First,diadiemden) == NULL){
			cout<<"Chua co chuyen bay den "<<diadiemden<<" !!!"<<endl;
			cout<<"ESC de thoat  -  an phim bat ki de tiep tuc"<<endl;
			char ch = getch();
			if(ch == 27) return;
		    goto Loop;		
		}
		
	Loop1:
	system("cls");
	cout<<"Nhap ngay: "; cin>>ngay;
	cout<<"Nhap thang: ";cin>>thang;
	cout<<"Nhap nam: ";cin>>nam;
	if(ngay <= 0 || thang<= 0 || nam <= 0){
		cout<<"Ngay thang nam khong hop le!"<<endl;
		goto Loop1;
	}
	
 	system("cls");
 	int dem = 0;
 	cout<<"				DANH SACH CHUYEN BAY"<<endl;
	cout<<"STT  Ma chuyen bay    "<<"Dia diem     "<<"Trang thai   "<<"So ve trong   "<<"Ngay/Thang/Nam  "<<"Gio/Phut"<<endl;
	for(CBPTR p = First; p!=NULL && (p->cb.trangthai == 1)  ;p=p->next){
		if(strcmp(p->cb.diadiem,diadiemden) == 0 && p->cb.date.ngay == ngay && p->cb.date.thang == thang && p->cb.date.nam == nam) {
			cout<<" "<<dem+1;
			LietkeCBYeucau(p->cb);
			dem++;	
		}
	}
	if(dem != 0){
		system("pause");
		return;
	}else{
		system("cls");
		cout<<"Khong co chuyen bay khoi hanh vao ngay gio nay !"<<endl;
		system("pause");
		return;	
	}
	
}

// liet ke danh sach ghe trong cua mot chuyen bay 

void DSVETrong_Tudong(CBPTR First,Listmaybay dsmb){

	int icb = HieuungthongtinDatve(First);
	if(icb == -1){
		return;
	}
	system("cls");
	int k=1;
	for(CBPTR p = First;p!=NULL && (p->cb.trangthai == 1) ;p=p->next ){
		if(k == icb){
//			cout<<"      DANH SACH VE CON TRONG CUA CHUYEN BAY "<<p->cb.ID<<endl<<endl;
//			Lietkechongoi(p->cb);
//			return;
			string tieude = " DANH SACH VI TRI NGOI ";			
		    Chonchongoi(p->cb,dsmb,tieude);
			return;			
		}
		k++;
	}	
}


void DSVETrong_Macb(CBPTR First,Listmaybay dsmb){
	
	char Macb[16];
	Loop:
	system("cls");
	NhapChuoi("Nhap ma chuyen bay: ",Macb);
	CBPTR IDCB = SearchCBID(First,Macb);
	if( IDCB == NULL || IDCB->cb.trangthai != 1 ){
		cout<<"Ma chuyen bay khong ton tai hoac khong con ghe trong !!!"<<endl;
		cout<<"ESC de thoat  -  an phim bat ki de tiep tuc"<<endl;
		char ch = getch();
		if(ch == 27) return;
		goto Loop;
	}	
	//danh sach vi tri con trong
		string tieude = " DANH SACH VI TRI NGOI ";
		Chonchongoi(IDCB->cb,dsmb,tieude);
		return;
	
//	cout<<"       DANH SACH VE CON TRONG CUA CHUYEN BAY "<<Macb<<endl;
//	Lietkechongoi(IDCB->cb);
}


void LietkeDSVETrong(CBPTR First,Listmaybay dsmb){
	string yeucau = "Liet ke danh sach ve trong thuoc chuyen bay : ";
	int ixacnhan = HieuungluachonLK_DSHK_CB(yeucau);
	if(ixacnhan == -1){
		return;
	}else if(ixacnhan == 0){
		DSVETrong_Macb(First,dsmb);
	}else{		
		DSVETrong_Tudong(First,dsmb);
	}
		
}




int Thongkeluotchuyenbay(CBPTR First,Listmaybay dsmb){
	List_mb_thuchien_chuyenbay dsthuchiencb;
	while(true){
		
		if(dsmb.n == NULL){
		cout<<"CHUA CÓ MAY BAY TRONG HE THONG!!!"<<endl;
		system("pause");
		return true;		
		}
	
		dsthuchiencb.node = new luot_thuc_hien_chuyen_bay[dsmb.n];
		for(int i = 0; i<dsmb.n;i++){
			int dem = 0;		
			strcpy(dsthuchiencb.node[i].sohieumb,dsmb.nodes[i]->sohieu);
			strcpy(dsthuchiencb.node[i].loaimb,dsmb.nodes[i]->loai);
			for(CBPTR p = First;p!= NULL && p->cb.trangthai == 3 ;p=p->next){
				if( strcmp(dsmb.nodes[i]->sohieu,p->cb.sohieumb) == 0){
					dem++;
				}	
			}
			dsthuchiencb.node[i].soluot = dem;
		}
	
		for(int i=0;i<dsmb.n;i++){
			for(int j = i+1;j<dsmb.n;j++){
				if(dsthuchiencb.node[j].soluot>dsthuchiencb.node[i].soluot){
					luot_thuc_hien_chuyen_bay temp;
					temp = dsthuchiencb.node[j];
					dsthuchiencb.node[j] = dsthuchiencb.node[i];
					dsthuchiencb.node[i] = temp;			
				}		
			}
		}
		
		Loop:
		system("cls");
		cout<<"So hieu may bay     ";
		cout<<"Loai may bay          ";
		cout<<" So luot thuc hien chuyen bay         ESC de thoat"<<endl;
		
		for(int i = 0; i<dsmb.n;i++){
			cout<<"  "<<dsthuchiencb.node[i].sohieumb;
			gotoxy(22,i+1);
			cout<<dsthuchiencb.node[i].loaimb;
			gotoxy(55,i+1);
			cout<<dsthuchiencb.node[i].soluot<<endl;
		}
		
		char ch = getch();
		if(ch == 27) return true;
		goto Loop;		
	}
	
}


///////////////// Hanh Khach ////////////////


HKPTR SearchHK(HKPTR &root,char *name){
	HKPTR p;
	p=root;
	while(p!=NULL){
		if(strcmp(p->hk.Cmnd,name)==0){
			return p;
		}
		if(strcmp(p->hk.Cmnd,name)==1){
			p = p->pLeft;
		}else{
			p = p->pRight;
		}	
	}
	return NULL;
}

void NhapChuoiHK (char *tieude, char *S) {
	cout << tieude ;  fflush(stdin);
    do
	  gets(S);
    while (strcmp(S,"")==0)  ;	
}

HKPTR InsertHK(HKPTR &tree,Hanhkhach &hk)
{
    if ( tree == NULL ){   
        HKPTR p;
        p = new NodeHanhkhach();
        p->pLeft = p->pRight = NULL;
        p->hk = hk;
        tree = p;
        return tree;
        
    }
	if(strcmp (hk.Cmnd,tree->hk.Cmnd)==-1){
		InsertHK(tree->pLeft,hk);
	}else if(strcmp (hk.Cmnd,tree->hk.Cmnd)==1){
		InsertHK(tree->pRight,hk);
	}			
    return tree;
}



int NhapHK(HKPTR &tree,Hanhkhach &hk){
	HKPTR p;
		while(true){
			if(tree == NULL){				
				p = new NodeHanhkhach();
				p->hk = hk;
				p->pLeft = p->pRight = NULL;
				tree = p;
				return true;
			}else{
				if(strcmp (hk.Cmnd,tree->hk.Cmnd)==-1){
					tree = tree->pLeft;
				}else if(strcmp (hk.Cmnd,tree->hk.Cmnd)==1){
					tree = tree->pRight;
				}							
			}			
		}	
}



int  NhapDSHK(HKPTR &tree){
	Hanhkhach hk;
	while(1){
		cout<<"Nhap so cmnd: ";
		cin>> hk.Cmnd;
		if(SearchHK(tree,hk.Cmnd)!=NULL){
			cout<<"so cmnd da ton tai"<<endl;
			continue;
		}
		NhapChuoiHK("Nhap ho hanh khach: ",hk.Ho);
		NhapChuoiHK("Nhap ten hanh khach: ",hk.Ten);
		NhapChuoiHK("Nhap gioi tinh(nam/nu): ",hk.Gioitinh);
		
		InsertHK(tree,hk);
			
		return 1;
	}
}


void SaveHK(ofstream &fileout,HKPTR tree){
	if(tree != NULL){
		fileout<<tree->hk.Cmnd<<",";
		fileout<<tree->hk.Ho<<",";
		fileout<<tree->hk.Ten<<",";
		fileout<<tree->hk.Gioitinh<<",";
		SaveHK(fileout,tree->pLeft);
		SaveHK(fileout,tree->pRight);
	}

}

void SaveDSHK(HKPTR tree){
	ofstream fileout;
	fileout.open("dshanhkhach.txt",ios_base::out);
	SaveHK(fileout,tree);
	fileout.close();
	return;
}

void LoadHK(ifstream &filein,Hanhkhach &hk){	
		//cmnd
		string tamcmnd;
		getline(filein,tamcmnd,',');
		strcpy(hk.Cmnd,tamcmnd.c_str());

		// ho
		string ho;
		getline(filein,ho,',');
		strcpy(hk.Ho,ho.c_str());

		// Ten
		string ten;
		getline(filein,ten,',');
		strcpy(hk.Ten,ten.c_str());

		// gioi tinh
		string gt;
		getline(filein,gt,',');
		strcpy(hk.Gioitinh,gt.c_str());
}

void LoadDSHK(HKPTR &tree){
	ifstream filein;
	Hanhkhach hk;
	filein.open("dshanhkhach.txt",ios::in);
	while(!filein.eof()){		
		LoadHK(filein,hk);
		InsertHK(tree,hk);
	}
	filein.close();
	return;
}

void LietkeDSHK(HKPTR &p){
//	if(p == NULL){
//		cout<<"Danh sach rong"<<endl;
//		return;
//	}
	
	if(p != NULL){ 

	  cout<<p->hk.Cmnd<<"     "<<p->hk.Ho<<" "<<p->hk.Ten<<"       "<<p->hk.Gioitinh<<endl;
	  LietkeDSHK(p->pLeft);
      LietkeDSHK(p->pRight);
    }
}


HKPTR rp;
void Xoanode2con(HKPTR &k){
	
	if(k->pLeft!=NULL){
		Xoanode2con(k->pLeft);
		//r la nut cuc trai cua cay con ben phai, nut goc la rp
	}else{
		
		rp->hk = k->hk;
		rp = k;
		k = rp->pRight;
		
	}
}

void Xoahanhkhach(HKPTR &tree,CBPTR First){
	char cmndxoa[16];
	NhapChuoiHK("Nhap cmnd hanh khach can xoa: ",cmndxoa);
	HKPTR p = SearchHK(tree,cmndxoa);
	
	if(p == NULL){ 
	    cout<<"khong tim thay";
	}else{
		rp = p;
		if(rp->pRight == NULL){
		// p la nut la hoac la nut chi co cay con ben trai
			p = rp->pLeft;
		}else if(rp->pLeft == NULL){
		// p la nut co cay con ben phai
			p = rp->pRight;
		}else{
			Xoanode2con(rp->pRight);			
		}
		delete rp;
	}
		
//	if(p == NULL){ 
//	    cout<<"khong tim thay";
//	}else{
//		if(strcmp(p->hk.Cmnd,cmndxoa)==1){
//			Xoahanhkhach(p->pLeft,cmndxoa);
//		}else if(strcmp(p->hk.Cmnd,cmndxoa)==-1){
//			Xoahanhkhach(p->pRight,cmndxoa);
//		}else{
//			rp = p;
//			if(rp->pRight == NULL){
//			// p là nút lá hoac la nut chi co cay con ben trai
//				p = rp->pLeft;
//			}else if(rp->pLeft == NULL){
//			// p là nut co cay con ben phai
//				p = rp->pRight;
//			}else{
//				Xoanode2con(rp->pRight);			
//			}
//			delete rp;
//		}
//		
//	}		

	
}

// liet ke danh sach hanh khach tren chuyen bay

int HieuungluachonLK_DSHK_CB(string yeucau){
	char ch;
	int i=0;
	char *Xacnhan[3] ={"Nhap ma chuyen bay","Danh sach chuyen bay"};
	do{
		system("cls");
		HANDLE hConsoleColor;
   		hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);		
		SetConsoleTextAttribute(hConsoleColor, 12);
		cout<<yeucau<<endl;

		for(int t=0 ; t<=1 ; t++){
			if(t==i){
				HANDLE hConsoleColor;
   				hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);		
				SetConsoleTextAttribute(hConsoleColor, 1);
				cout<<Xacnhan[t]<<endl;
			}else{
				HANDLE hConsoleColor;
   				hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);		
				SetConsoleTextAttribute(hConsoleColor, 2);
				cout<<Xacnhan[t]<<endl;
			}
		}
		do{
	            ch = getch();
	            if (ch==224) ch=getch();
	        } while (!(ch==224||ch==13||ch==27||ch==80||ch==72));
	        if(ch==80){         //ky tu xuong
	             i=i+1; 
	             if (i>1) i = 0; 
	        }
	        if (ch==72){          //ky tu len
	            i=i-1; 
	            if (i<0) i = 1; 
	   		}
	   		if(ch == 27){
	   			return -1;
			 }
	}while (!(ch == 13));
			return i;	
}



void LietkeDSHKCB_Macb(CBPTR First,HKPTR tree){
	char Macb[16];
	HKPTR q;	
	Loop:
	system("cls");
	NhapChuoiCB("Nhap ma chuyen bay: ",Macb);
	CBPTR IDCB = SearchCBID(First,Macb);
	if( IDCB == NULL || IDCB->cb.trangthai == 0 ){
		cout<<"Ma chuyen bay khong ton tai hoac da huy chuyen !!!"<<endl;
		cout<<"ESC de thoat  -  an phim bat ki de tiep tuc"<<endl;
		char ch = getch();
		if(ch == 27) return;
		goto Loop;
	}	
	system("cls");	
	cout<<"      DANH SACH HANH KHACH THUOC CHUYEN BAY "<<IDCB->cb.ID<<endl;
	cout<<"Ngay gio khoi hanh: "<<IDCB->cb.date.ngay<<"/"<<IDCB->cb.date.thang<<"/"<<IDCB->cb.date.nam<<" "<<IDCB->cb.date.gio<<":"<<IDCB->cb.date.phut<<"    ";
	cout<<"Noi den: "<<IDCB->cb.diadiem<<endl;
	cout<<"     "<<"STT"<<"   "<<"SO VE"<<"   "<<"SO CMND"<<"    "<<"HO TEN"<<"    "<<"PHAI"<<endl;
	
	
	int dem = 1;
	int kt = 1;
	for(int i = 0 ; i<IDCB->cb.danhsachve.n;i++){
		if(strcmp(IDCB->cb.danhsachve.vecb[i].Cmnd,"NOT") == 0){
			if(kt == IDCB->cb.danhsachve.n){
				cout<<"				DANH SACH TRONG !!!"<<endl;
				system("pause");
				return;
			}
			kt++;			
		}else{
			cout<<"      "<<dem<<"     ";
			cout<<IDCB->cb.danhsachve.vecb[i].chongoi<<"        ";
			cout<<IDCB->cb.danhsachve.vecb[i].Cmnd<<"          ";
			// in thong tin hanh khach
			q = SearchHK(tree,IDCB->cb.danhsachve.vecb[i].Cmnd);
			if(q != NULL){
				cout<<q->hk.Ho<<" "<<q->hk.Ten<<"     ";
				cout<<q->hk.Gioitinh<<endl;
			}					
			dem++;
		}	
	}
	system("pause");
	return;
}

void LietkeDSHKCB_Tudong(CBPTR First,HKPTR tree){
	HKPTR q;
	int icb = HieuungthongtinCBHoatDong(First);
	if(icb == -1){
		return;
	}
	
	int k = 1;
	for(CBPTR p = First;p!=NULL  && ( (p->cb.trangthai == 1) || (p->cb.trangthai == 2) );p=p->next){
		if(k == icb){
			system("cls");
			cout<<"      DANH SACH HANH KHACH THUOC CHUYEN BAY "<<p->cb.ID<<endl;
			cout<<"Ngay gio khoi hanh: "<<p->cb.date.ngay<<"/"<<p->cb.date.thang<<"/"<<p->cb.date.nam<<" "<<p->cb.date.gio<<":"<<p->cb.date.phut<<"    ";
			cout<<"Noi den: "<<p->cb.diadiem<<endl;
			cout<<"     "<<"STT"<<"   "<<"SO VE"<<"   "<<"SO CMND"<<"    "<<"HO TEN"<<"    "<<"PHAI"<<endl;
			
			int dem = 1;
			int kt = 1;
			for(int i = 0 ; i<p->cb.danhsachve.n;i++){
				if(strcmp(p->cb.danhsachve.vecb[i].Cmnd,"NOT") == 0){
						if(kt == p->cb.danhsachve.n){
							cout<<"				DANH SACH TRONG !!!"<<endl;
							system("pause");
							return;
						}
						kt++;			
				}else{
					cout<<"      "<<dem<<"     ";
					cout<<p->cb.danhsachve.vecb[i].chongoi<<"        ";
					cout<<p->cb.danhsachve.vecb[i].Cmnd<<"          ";
					// in thong tin hanh khach
					q = SearchHK(tree,p->cb.danhsachve.vecb[i].Cmnd);
					if(q != NULL){
						cout<<q->hk.Ho<<" "<<q->hk.Ten<<"     ";
						cout<<q->hk.Gioitinh<<endl;
					}					
					dem++;
				}	
			}
			system("pause");
			return;
		}
		k++;
	}
	
}


void LietkeDSHK_CB(CBPTR First,HKPTR tree){
	string yeucau = "Liet ke danh sach hanh khach thuoc chuyen bay : ";
	int ixacnhan = HieuungluachonLK_DSHK_CB(yeucau);
	if(ixacnhan == -1){
		return;
	}else if(ixacnhan == 0){
		LietkeDSHKCB_Macb(First,tree);
	}else{		
		LietkeDSHKCB_Tudong(First,tree);
	}
	
}


////////////////// Dat Ve /////////////////////



void ve(int i,int f,Chuyenbay cb){
	HANDLE hConsoleColor;
    hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);		
	SetConsoleTextAttribute(hConsoleColor, f); // f la mau
	cout<<cb.danhsachve.vecb[i].chongoi<<" ";
}

void tomauchu(string chu,int f){
	HANDLE hConsoleColor;
    hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);		
	SetConsoleTextAttribute(hConsoleColor, f); // f la mau
	cout<<chu;
}

int Chonchongoi(Chuyenbay cb,Listmaybay dsmb,string tieude){
//	string tieude = "	  CHON VI TRI DAT VE          ESC : Ket thuc ";
	string chucnang = "          ESC : Ket thuc ";
	string ghedadat = "  mau do: da dat";
	string ghechuadat = "mau xanh: chua dat";
	int ktmb = SearchMB(dsmb,cb.sohieumb);
	
	//so day va dong cua may bay
	int soday = dsmb.nodes[ktmb]->soday;
	int sodong = dsmb.nodes[ktmb]->sodong ;	
	
	int i=0; // vi tri cua ghe trong mang
	char ch;
	do{
		system("cls");
		gotoxy((sodong+10),0);
		tomauchu(tieude,11);
		tomauchu(chucnang,11);cout<<endl;
		gotoxy((sodong),1);
		tomauchu(ghedadat,12);cout<<"   ";
		tomauchu(ghechuadat,2);cout<<endl<<endl;
		
		int demdong = 0;
		int demday = 0;
		for(int t=0;t<cb.danhsachve.n;t++){
			demdong++;			
			if (t==i){ 
				ve(t,1,cb);
			}else if(strcmp(cb.danhsachve.vecb[t].Cmnd,"NOT")==0){
				ve(t,2,cb);			
			}else{
				ve(t,12,cb);
			}			
			if(demdong%sodong == 0){
				cout<<endl;
				demday++;	
				if(demday == (soday/2 ) )	cout<< endl;
			} 			
		}
		
		do{
	            ch = getch();
	            if (ch==224) ch=getch();
	        } while (!(ch==224||ch==13||ch==27||ch==80||ch==72||ch==75||ch==77));
	        if(ch==80){         //ky tu xuong
	             i=i+sodong; 
	             if (i>cb.danhsachve.n-1) i = i%(soday*sodong); 
	        }
	        if (ch==72)          //ky tu len
	        {
	            i=i-sodong; 
	            if (i<0) i = (soday*sodong)+i; 
	   		}
	   		if(ch==75){			// ky tu sang trai
			   	i--;
//				if(i<0) i = cb.danhsachve.n-1;
				if((i+1) % sodong ==0 ) i = i+sodong;
			}
			if(ch==77){			// ky tu sang phai
				i++;
//			   if(i>cb.danhsachve.n-1) i=0;
				if(i % sodong == 0 ) i = i-sodong;
			}
			if(ch==27){
				return -1;
			}
	}while (!(ch == 13 ));
	return i;	
}


int Searchchongoi(CBPTR p,char *vitringoi){
		//p là vi tri cua chuyen bay can dat
	for(int i=0;i<p->cb.danhsachve.n;i++){
		if(p->cb.danhsachve.vecb[i].chongoi.compare(vitringoi)==0 ){
//		if(strcmp(p->cb.danhsachve.vecb[i].chongoi,vitringoi)==0 ){
			if(p->cb.danhsachve.vecb[i].Cmnd != NULL){
				cout<<"Vi tri da co hanh khach dat !!!";
			    return -1;
			}else{				
				return i;
			}			
		}
	}
			
	
}

void Datve(CBPTR &First,HKPTR &tree,Listmaybay dsmb){
	char diadiemden[30],Macbdatve[16];
	char Cmnddatve[11];
	char xacnhan[2],vitridat[4];
	while(true){
		
		int icb = HieuungthongtinDatve(First);
		if(icb == -1) return;
		int k = 1;
		for(CBPTR p = First;p!=NULL && (p->cb.trangthai == 1) ;p=p->next){
			
			if(k == icb){
				if(p->cb.danhsachve.sldb == p->cb.danhsachve.n){
					cout<<"Da het ve !!!"<<endl;
					system("pause");
					return;
				}
				
				Loop:
				system("cls");
				Thongtinchuyenbay(p->cb);

				// cmnd hanh khach
				NhapChuoi("So cmnd hanh khach dat ve: ",Cmnddatve);
				if(SearchHK(tree,Cmnddatve)==NULL){
					string yeucau = "So cmnd chua co trong he thong, them thong tin khach hang ? ";
					int ixacnhan = Hieuungyesno(yeucau);
					if(ixacnhan == -1 || ixacnhan == 1){
						return;
					}else{
						system("cls");
						NhapDSHK(tree);
//						int nhaphk = NhapDSHK(tree);
//						if(nhaphk != 1) return;
						goto Loop1;
					}	
				}
				
				// kiem tra hanh khach da dat ve chua . 1 hanh khach chi dc 1 ve
				for(int j=0;j<p->cb.danhsachve.n;j++){
					if(strcmp(p->cb.danhsachve.vecb[j].Cmnd,Cmnddatve)==0){
						cout<<"Moi hanh khach chi duoc dat 1 ve duy nhat"<<endl;
						cout<<"Hanh khach da dat ghe "<<p->cb.danhsachve.vecb[j].chongoi<<" tren chuyen bay "<<p->cb.ID<<endl;
						system("pause");
//						goto Loop;
						return;
					}
				}
				
				// chon vi tri ngoi 
				Loop1:
				system("cls");
				string tieude="CHON VI TRI DAT VE";
				int vitridat = Chonchongoi(p->cb,dsmb,tieude);
				if(vitridat == -1){
					system("cls");
					string yeucau = "Ban muon huy qua trinh dat ve tren chuyen bay ? ";
					int ixacnhan = Hieuungyesno(yeucau);
					if(ixacnhan == -1 || ixacnhan == 1){
						goto Loop1;
					}else{
						return;
					}
				} 
				system("cls");
				if(strcmp(p->cb.danhsachve.vecb[vitridat].Cmnd,"NOT")==0){

					strcpy(p->cb.danhsachve.vecb[vitridat].Cmnd,Cmnddatve);
//					p->cb.danhsachve.vecb[vitridat].Cmnd = Cmnddatve;
					p->cb.danhsachve.sldb++;
					if(p->cb.danhsachve.sldb == p->cb.danhsachve.n){
						p->cb.trangthai = 2;	
					}
					cout<<"Da dat ve hoan tat!!!"<<endl;
					Thongtinchuyenbay(p->cb);
					system("pause");
					return;
									
				}else{

					cout<<"Vi tri ngoi da duoc dat, vui long chon vi tri khac khac !!!"<<endl;
					system("pause");
					goto Loop1;
				}				
			}
			k++;	
		}
		
	}
}	
		
	
void HuyVE(CBPTR First,HKPTR tree){
	string xacnhan = "Cmnd cua hanh khach chua co trong he thong, Nhap lai ?";
	char cmndhuyve[11];
	int icb = HieuungthongtinCBHoatDong(First);
	if(icb == -1){
		return;
	}
	
	int k = 1;
	for(CBPTR p =First;p!=NULL  &&( (p->cb.trangthai == 1) || (p->cb.trangthai == 2) );p=p->next){
		
		if(k == icb){
			//cmnd hanh khach huy ve
			Loop:
			system("cls");	
			NhapChuoi("Nhap so cmnd hanh khach: ",cmndhuyve);
			//kiem tra cmnd hanh khach co trong he thong
			if(SearchHK(tree,cmndhuyve)==NULL){
				int ixacnhan = Hieuungyesno(xacnhan);
				if(ixacnhan == -1 || ixacnhan == 1){
					return;
				}else goto Loop;
			}
			// xem hanh khach co dat ve tren chuyen bay
			for(int j=0;j<p->cb.danhsachve.n;j++){
				if(strcmp(p->cb.danhsachve.vecb[j].Cmnd,cmndhuyve) == 0){
					strcpy(p->cb.danhsachve.vecb[j].Cmnd,"NOT");
					p->cb.danhsachve.sldb--;
					cout<<"Huy ve thanh cong"<<endl;
					system("pause");
					return;		
				}
			}	
			// hanh khach chua dat ve tren chuyen bay		
			cout<<"Hanh khach chua dat ve tren chuyen bay "<<p->cb.ID<<" !!!"<<endl;
			system("pause");
			return;	
		}	
		k++;
	}	
}


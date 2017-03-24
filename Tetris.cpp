#include <iostream>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<cctype>
#include<time.h>

using namespace std;

char arena[25][33];

int icon,h,k,hother[3],kother[3],score=0;
time_t beginning;

void gotoxy(int x, int y) {
	HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(hConsole,coord);
}

/*
void clrscr() {
	gotoxy(14+h,9+k);
	cout<<"\0";
	for (int i=0; i<3; ++i)
		for (int j=0; j<3; ++j) {
			gotoxy(14+h+hother[i],9+k+kother[j]);
			cout<<"\0";
		}
	gotoxy(0,0);
}*/

void display() {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(0,0);
	SetConsoleTextAttribute(hConsole,15);
	cout<<"\n\n\n\t     SCORE : "<<score<<"\t\t\t\t\tTIME : "<<time(0)-beginning;
	cout<<"\n\n\n\n\n\t     ####################################################\n\t     ";
	for (int i=3; i<=32; ++i) {
		SetConsoleTextAttribute(hConsole,15);
		cout<<"#";
		for (int j=0; j<=24; ++j) {
			if (arena[j][i]==' ')	SetConsoleTextAttribute(hConsole,237);
			else if (arena[j][i]=='.')	SetConsoleTextAttribute(hConsole,51);
			else	SetConsoleTextAttribute(hConsole,1);
			cout<<" "<<arena[j][i];
			if (j==24)	cout<<"\b";
		}
		cout<<" ";
		SetConsoleTextAttribute(hConsole,15);
		cout<<"#\n\t     ";
	}
	cout<<"####################################################";

}

void piecedesign(char x) {
	arena[h][k]=arena[h+hother[0]][k+kother[0]]=arena[h+hother[1]][k+kother[1]]=arena[h+hother[2]][k+kother[2]]=x;
}

void piecebuild() {
	switch(icon) {
		case 0 :
		//	arena[h][k]=arena[h+1][k]=arena[h][k-1]=arena[h][k-2]=x;
			hother[0]=1; hother[1]=hother[2]=kother[0]=0; kother[2]=-2; kother[1]=-1;
			break;
		case 1 :
		//	arena[h][k]=arena[h-1][k-1]=arena[h][k-1]=arena[h+1][k]=x;	
			hother[0]=kother[0]=kother[1]=-1; hother[1]=kother[2]=0; hother[2]=1;			
			break;																
		case 2:																
		//	arena[h][k]=arena[h][k-1]=arena[h+1][k-1]=arena[h+1][k]=x;	
			hother[0]=kother[2]=0; hother[1]=hother[2]=1; kother[0]=kother[1]=-1;			
			break;																	
		case 3 :																
		//	arena[h][k]=arena[h][k+1]=arena[h][k-1]=arena[h][k-2]=x;				
			hother[0]=hother[1]=hother[2]=0;kother[0]=1;kother[1]=-1;kother[2]=-2;	
			break;
		case 4 :
		//	arena[h][k]=arena[h][k-1]=arena[h-1][k]=arena[h+1][k]=x;
			hother[0]=kother[1]=kother[2]=0; hother[1]=kother[0]=-1; hother[2]=1;
			break;
		case 5 :
		//	arena[h][k]=arena[h][k-2]=arena[h][k-1]=arena[h-1][k]=x;						//   L	   -	0
			hother[0]=hother[1]=kother[2]=0; hother[2]=kother[1]=-1; kother[0]=-2;
			break;																			//   Z 	   - 	1
		case 6 :																			//   O	   -	2
		//	arena[h][k]=arena[h+1][k-1]=arena[h][k-1]=arena[h-1][k]=x;	
			hother[0]=1; hother[1]=kother[2]=0; hother[2]=kother[0]=kother[1]=-1;			//   |	   -	3
			break;																			//  _|_	   -	4
	}																						//  _|	   -	5
	piecedesign(' ');
}																							//   5	   -	6

void makepiece() {
	icon=rand()%7;
	h=(rand()%23) + 1;
	k=2;
	if (icon==0 || icon==5)
		k=3;
	piecebuild();
}

int arrmin(int a[3]) {
	int val;
	val = a[0]<a[1] ? (a[0]<a[2] ?  a[0] : a[2]) : (a[1]<a[2] ? a[1] : a[2]);
	return val;
}

int arrmax(int a[3]) {
	int val;
	val = a[0]>a[1] ? (a[0]>a[2] ? a[0] : a[2]) : (a[1]>a[2] ? a[1] : a[2]);
}

void input() {								
	piecedesign('\0');
	char x=getch(); 
	x=tolower(x);
	switch(x) {
		case 'a' :
			if (h+arrmin(hother)>=1 && arena[h-1][k]=='\0' && arena[h+hother[0]-1][k+kother[0]]=='\0' && arena[h+hother[1]-1][k+kother[1]]=='\0' && arena[h+hother[2]-1][k+kother[2]]=='\0') 
				--h;
			break;
		case 'd' :
			if (h+arrmax(hother)<=23 && arena[h+1][k]=='\0' && arena[h+hother[0]+1][k+kother[0]]=='\0' && arena[h+hother[1]+1][k+kother[1]]=='\0' && arena[h+hother[2]+1][k+kother[2]]=='\0') 
				++h;
			break;
		case 's' :
			if (!(k+arrmax(kother)==32 || arena[h][k+1]=='.' || arena[h+hother[0]][k+kother[0]+1]=='.' || arena[h+hother[1]][k+kother[1]+1]=='.' || arena[h+hother[2]][k+kother[2]+1]=='.' ))
				++k;
			break;
		case 'e' :
			if (arena[h-kother[0]][k+hother[0]]=='\0' && arena[h-kother[1]][k+hother[1]]=='\0' && arena[h-kother[2]][k+hother[2]]=='\0' && icon!=2 && h-kother[0]>=0 && h-kother[1]>=0 && h-kother[2]>=0 && k+hother[0]>=0 && k+hother[1]>=0 && k+hother[2]>=0 && k+hother[0]<=32 && k+hother[1]<=32 && k+hother[1]<=32 && h-kother[0]<=24 && h-kother[1]<=24 && h-kother[2]<=24) {
				piecedesign('\0');
				for (int i=0; i<=2; ++i) {
					int arr[3];
					arr[i]=hother[i];
					hother[i]=-1*kother[i];
					kother[i]=arr[i];
				}
			}
			break;
		case 'w' :
			if (arena[h+kother[0]][k-hother[0]]=='\0' && arena[h+kother[1]][k-hother[1]]=='\0' && arena[h+kother[2]][k-hother[2]]=='\0' && icon!=2 && h+kother[0]>=0 && h+kother[1]>=0 && h+kother[2]>=0 && k-hother[0]>=0 && k-hother[1]>=0 && k-hother[2]>=0 && k-hother[0]<=32 && k-hother[1]<=32 && k-hother[1]<=32 && h+kother[0]<=24 && h+kother[1]<=24 && h+kother[2]<=24) {
				piecedesign('\0');
				for (int i=0; i<=2; ++i) {
					int arr[3];
					arr[i]=hother[i];
					hother[i]=kother[i];
					kother[i]=-1*arr[i];
				}
			}
			break;
		case 'p' :
			char pause='\0';
			while (pause!='p' && pause!='P') {
				if (kbhit()!=0)
					pause=getch();
			}
		
	}
	piecedesign(' ');
	display();
}
    
void rowclear() {
	int t=1;
	for (int i=32; i>=3; --i) {
		for (int j=0; j<=24; ++j) {
			if (arena[j][i]!='.')
				t=0;
		}
		if (t==1) {
			for (int j=0; j<=24; ++j) { 
				arena[j][i]='\0';
				for (int q=i; q>=1; --q)
					arena[j][q]=arena[j][q-1];
			}
			++score;
			++i;
		}
		t=1;
	}		
}
	    
int gameover() {
	int trig=0;
	int i;
	for (i=0; i<=24; ++i) 
		if (arena[i][2]=='.')	trig=1;
	if (trig==1)	cout<<i;
	return trig;
}	    
		                                                                                            // L Z O | T
int main() {
	
	system("cls");
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,3);
	cout<<"\n\n\n\n\n\n\n\n\n ##########   ##########   ##########   ##########   ##########   ##########\n";
	cout<<" ##########   ##########   ##########   ##########   ##########   ##########\t";
	cout<<"     ##       ##               ##       ##      ##       ##       ##\n";
	cout<<"     ##       ##               ##       ##     ##        ##       ##\n";
	cout<<"     ##       #######          ##       ########         ##       ##########\n";
	cout<<"     ##       #######          ##       #######          ##       ##########\n";
	cout<<"     ##       ##               ##       ##    ##         ##               ##\n";
	cout<<"     ##       ##               ##       ##     ##        ##               ##\n";
	cout<<"     ##       ##########       ##       ##      ##   ##########   ##########\n";
	cout<<"     ##       ##########       ##       ##       ##  ##########   ##########";
	SetConsoleTextAttribute(hConsole,8);
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t      BY NAVEEN UNNIKRISHNAN";
	time_t start, stop;
	start=time(0);
	splashtime:
		stop=time(0);
		if (stop-start<5 && kbhit()==0)	goto splashtime;
	system("cls");
	SetConsoleTextAttribute(hConsole,15);
	char choice;
	do {
		system("cls");
		cout<<"\n\n\t\t\t\tT E T R I S\n\t\t\t\t===========";
		cout<<"\n\n\n\t\t\t     1 . PLAY\n\n\t\t\t     2 . INSTRUCTIONS\n\n\t\t\t     3 . EXIT\n\n\n\t\t\t    < Enter 1, 2 or 3 >";
		choice = getch();
		if (choice=='2') {
			system("cls");
			cout<<"\n\n\t\t\t\tINSTRUCTIONS\n\t\t\t\t===========";
			cout<<"\n\n\n\t\t\tA     -     LEFT\n\n\t\t\tD     -     RIGHT\n\n\t\t\tS     -     DOWN\n\n\t\t\tW     -     Rotate counter-clockwise\n\n\t\t\tE     -     Rotate Clockwise\n\n\t\t\tP     -     PAUSE/PLAY\n\n\n\t\t\t";
			system("pause");
		}
		else if (choice=='3')	exit(0);
	}while(choice!='1');
	system("cls");
	int stat;
	srand(time(0));
	clock_t t1,t2;
	for (int i=0; i<=24; ++i)
		for (int j=3; j<=32; ++j)
			arena[j][i]='\0';
	time_t end;
	beginning=time(0);
	make:
	makepiece();
	play:
	display();
	t1=clock();
	retime:
		t2=clock();
		if (kbhit()!=0)	input();
		if ((float)(t2-t1)*CLOCKS_PER_SEC<100000)	goto retime;
	if (k+arrmax(kother)==32 || arena[h][k+1]=='.' || arena[h+hother[0]][k+kother[0]+1]=='.' || arena[h+hother[1]][k+kother[1]+1]=='.' || arena[h+hother[2]][k+kother[2]+1]=='.' ) {
		piecedesign('.');
		rowclear();
		if (gameover()==1) {
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole,12);
			cout<<"\n\n\t\t\t\tGAME OVER!!!\n\n\t\t\t ";
			SetConsoleTextAttribute(hConsole,15);
			end=time(0);
			unsigned long long int diff=end-beginning;
			cout<<"SCORE : "<<score<<"\tTIME : "<<diff<<"\n\n\t\t\t  ";
			getch();
			SetConsoleTextAttribute(hConsole,8);
			system("pause");
			main();
		}
		else goto make;
	}
	piecedesign('\0');
	++k;
	piecedesign(' ');
	goto play;
	return 0;
}

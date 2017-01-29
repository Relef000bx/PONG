#include <stdio.h>
#include <windows.h>
#include <conio.h>



#define ARRIBA1 72
#define ABAJO1 80
#define ARRIBA2 119
#define ABAJO2 115

void gotoxy(int x, int y){
	HANDLE hCon; 
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	
	SetConsoleCursorPosition(hCon, dwPos);
	
}

void OcultarCursor(){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 2;
	cci.bVisible = FALSE;
	
	SetConsoleCursorInfo(hCon, &cci);
}

void pintar_Limites(){
	for(int i = 2; i < 78; i++){
		gotoxy(i,3); printf("%c",205);
		gotoxy(i,33); printf("%c",205);
	}
	for(int i = 4; i < 33; i++){
		gotoxy(2,i); printf("%c",186);
		gotoxy(77,i); printf("%c",186);
	}
	gotoxy(2,3);  printf("%c",201);
	gotoxy(2,33); printf("%c",200);
	gotoxy(77,3); printf("%c",188);
	gotoxy(77,3); printf("%c",187);
}


class BARRA{
	int x,y;
	
public:
	BARRA(int x_,int y_):x(x_),y(y_){}
	int X(){return x; }
	int Y(){return y; }
	void pintar();
	void borrar();
	void mover(int N);
	
};

void BARRA::pintar(){
	gotoxy(x,y);      printf("%c", 219);
	gotoxy(x,y-1);    printf("%c", 219);
	gotoxy(x,y+1);    printf("%c", 219);
/*	gotoxy(x,y-3);    printf("%c", 219);
	gotoxy(x,y-4);    printf("%c", 219);
	gotoxy(x,y-5);    printf("%c", 219);
	*/
}

void BARRA::borrar(){
	gotoxy(x,y);      printf(" ");
	gotoxy(x,y-1);    printf(" ");
	gotoxy(x,y+1);    printf(" ");
/*	gotoxy(x,y-3);    printf(" ");
	gotoxy(x,y-4);    printf(" ");
	gotoxy(x,y-5);    printf(" ");
	*/	
}

void BARRA::mover(int N){
	if(kbhit()){ 
			char tecla = getch(); 
			borrar();   
		if(N == 1){
			if((tecla == ARRIBA1) && (y > 6)) y--;
			if((tecla == ABAJO1) && (y+2 < 33)) y++;
			pintar(); 
		}
		if (N == 2){
			if((tecla == ARRIBA2) && (y > 6)) y--;
			if((tecla == ABAJO2) && (y+2 < 33)) y++;
			pintar();
		}
	}
}

class BOLA{
	int xBola,yBola;
	int dx, dy;
	
public:
	
	BOLA(int xBola_,int yBola_, int dx_, int dy_):xBola(xBola_),yBola(yBola_), dx(dx_), dy(dy_){}

	void pintarBola();
	void borrarBola();
	void mover(BARRA A, BARRA B);
	void reset(int x_, int y_){ xBola = x_; yBola = y_;}
	
};


void BOLA::pintarBola(){
	gotoxy(xBola,yBola); printf("%c", 184);
}

void BOLA::borrarBola(){
	gotoxy(xBola,yBola); printf("%c",' ');
}

void BOLA::mover(BARRA A, BARRA B ){
	
	borrarBola();
	xBola += dx; yBola +=dy;
	pintarBola();
	if(xBola + dx == 3 || xBola + dx == 76){
		borrarBola();
		reset(36, 14);
		dx = -dx;
		
	}
	if(yBola + dy == 4|| yBola + dy == 33){
		dy = -dy;
	}
	if(xBola + dx == A.X() && yBola >= A.Y() -2 && yBola <= A.Y() +2){ dx = -dx; }
	if(xBola + dx == B.X() && yBola >= B.Y() -2 && yBola <= B.Y() +2){ dx = -dx; }

}

int main(){
	OcultarCursor();
	BARRA B1(7,14);
	BARRA B2(71,14);
	BOLA bola(38, 14, 1, 1);
	
	pintar_Limites();
	B1.borrar();
	B2.borrar();
	B1.pintar();
	B2.pintar();
	
	int N;
	bool game_over = FALSE;
	int count;
	while(!game_over){
	
		B1.mover(2);
		B2.mover(1);
		
		if(!count++) bola.mover(B1, B2);
		if(count > 2) count = 0;
		
		Sleep(30);
		
	}
	return 0;
	
}
	
	
	
	

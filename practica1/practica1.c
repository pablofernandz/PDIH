#include <stdio.h>
#include <dos.h>

#define BYTE unsigned char

unsigned char cfondo=0;
unsigned char ctexto=1;

int caracter;


// Funciones auxiliares

void mi_pausa(){
    union REGS inregs, outregs;
	inregs.h.ah = 8;
	int86(0x21, &inregs, &outregs);
}

void escribir_char_con_color(char caracter) {
    union REGS inregs, outregs;
    inregs.h.ah = 0x09;
    inregs.h.al = caracter;
    inregs.h.bl = cfondo << 4 | ctexto;
    inregs.h.bh = 0x00;
    inregs.x.cx = 1;
    int86(0x10,&inregs,&outregs);
}

int mi_getchar(){
    union REGS inregs, outregs;
    int caracter;
    
    inregs.h.ah = 1;
    int86(0x21, &inregs, &outregs);
    
    caracter = outregs.h.al;
    return caracter;
}

void mi_putchar(char c){
    union REGS inregs, outregs;
    
    inregs.h.ah = 2;
    inregs.h.dl = c;
    int86(0x21, &inregs, &outregs);
}




// ---------- Funcion 1 -----------
void gotoxy(int x, int y){
	union REGS inregs, outregs;
	inregs.h.ah = 0x02;
	inregs.h.bh = 0x00;
	inregs.h.dh = y;
	inregs.h.dl = x;
	int86(0x10,&inregs,&outregs);
	return;
}


// ---------- Funcion 2 -----------
void setcursortype(int tipo_cursor){
	union REGS inregs, outregs;
	inregs.h.ah = 0x01;
	switch(tipo_cursor){
		case 0: //invisible
			inregs.h.ch = 010;
			inregs.h.cl = 000;
			break;
		case 1: //normal
			inregs.h.ch = 010;
			inregs.h.cl = 010;
			break;
		case 2: //grueso
			inregs.h.ch = 000;
			inregs.h.cl = 010;
			break;
	}
	int86(0x10,&inregs,&outregs);
}


// ---------- Funcion 3 -----------
void setvideomode(BYTE modo){
 	union REGS inregs, outregs;
 	inregs.h.ah = 0x00;
 	inregs.h.al = modo;
 	int86(0x10,&inregs,&outregs);
 	return;
}


// ---------- Funcion 4 -----------
int getvideomode() {
    union REGS inregs, outregs;
    inregs.h.ah = 0xF;
    int86(0x10, &inregs, &outregs);
    return outregs.h.al;
}


// ---------- Funcion 5 -----------
void textcolor(unsigned char colorTexto) {
    ctexto = colorTexto;
}


// ---------- Funcion 6 -----------
void textbackground(unsigned char colorFondo) {
    cfondo = colorFondo;
}


// ---------- Funcion 7 -----------
void clrscr() {
	int i;
	
	for (i = 0; i <= 25; i++) {
        printf("\n");
	}
	
	gotoxy(0,0);
}


// ---------- Funcion 8 -----------
void cputchar(char c) {
	textcolor(ctexto);
	escribir_char_con_color(c);
}


// ---------- Funcion 9 -----------
int getche() {
    int caracter = mi_getchar();
    mi_putchar(caracter);
    
    return caracter;
}


// ---------- Ejercicio opcional ----------- 
void dibujaRecuadro(int superior_x, int superior_y, int inferior_x, int inferior_y, unsigned char ctexto, unsigned char cfondo){

    int i;
    caracter = '*';

    textcolor(ctexto);
    textbackground(cfondo);


    //Arista superior 
    for(i = superior_x; i<inferior_x-1; i++){       
        gotoxy(i,superior_y);
        cputchar(caracter);
    }

	//Arista inferior
    for(i = superior_x; i<inferior_x-1; i++){       
        gotoxy(i,inferior_y-1);
        cputchar(caracter);
    }
    
    //Aristas laterales
    for(i = superior_y; i<inferior_y; i++){       
        gotoxy(inferior_x-1,i);
        cputchar(caracter);
        gotoxy(superior_x,i);
        cputchar(caracter);
    }
}



int main(){
	
	// ---------- Funcion 1 -----------
	clrscr();
	gotoxy(50,20);
	printf("*");
    mi_pausa();


	// ---------- Funcion 2 -----------	
	clrscr();
	printf("\nCursor invisible: ");
 	setcursortype(0);
 	mi_pausa();
 	printf("\nCursor grueso: ");
 	setcursortype(2);
 	mi_pausa();
 	printf("\nCursor normal: ");
 	setcursortype(1);
 	mi_pausa();

	
	// ---------- Funcion 3 -----------
	setvideomode(0);
	mi_pausa();
	
	
	// ---------- Funcion 4 -----------
    printf("\nEl modo de video actual es: %d\n", getvideomode());
    mi_pausa();
    
    
    // ---------- Funcion 5 -----------  
    printf("\ncolor de texto=azul => ");
    textcolor(1);
    escribir_char_con_color('@');
	mi_pausa();


	// ---------- Funcion 6 -----------  
    printf("\ncolor de fondo=verde => ");
    textbackground(2);
    escribir_char_con_color('€');
    mi_pausa();
    
    
    // ---------- Funcion 7 -----------
    clrscr();
    mi_pausa();

    
    // ---------- Funcion 8 -----------
    printf("Ingrese un carácter: ");
	caracter = mi_getchar();
    printf("\nEl carácter ingresado con el color de texto actual es: ");
    cputchar(caracter);
    
    
    // ---------- Funcion 9 -----------  
    printf("\nIngresa un carácter: ");
    caracter = getche();
    printf("\nEl carácter ingresado es: %c\n", caracter);
    mi_pausa();
    
    
    // ---------- Ejercicio opcional ----------- 
    clrscr();
    dibujaRecuadro(7,5,20,20,2,6);

    
    
    return 0;
}

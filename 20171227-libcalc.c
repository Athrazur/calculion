/* Complementos para calculador compleja:
	-Debe poder leer cadenas de caracteres y procesar la ecuacion, calculo.
	-Debe poder traducir caracteres a numeros.
	-Debe poder priorizar operaciones aritmeticas.
	-Debe poder priorizar precedencia de parentesis.
	-Debe poder gestionar la memoria.

Funcion de lectura de cifras:
	int getCifra(char * caracter);

Funcion de precedencia de parentesis:

Funcion de asignacion de memoria para parentesis:

Falta determinar como y cuando se devuelven enteros o flotantes,
como se leen estos ultimos.
Falta ver como se van a crear las secciones de memoria para 
contener las variables en juego, en la operacion.

Se me ocurrio que podria agregar una funcion a la que se le ingrese un valor numerico sea float o int y este sea 
convertido en una cadena de caracteres. La voy a llamar getNumString.
*/

#include <stdio.h>
#include <math.h>

// Convierte caracteres decimales a sus valores numericos.
int getCifra(char * caracter){
	switch (*caracter){
		case 48:	return 0;	break;  // Cero		0
		case 49:	return 1;	break;  // Uno		1
		case 50:	return 2;	break;  // Dos		2
		case 51:	return 3;	break;  // Tres		3
		case 52:	return 4;	break;  // Cuatro	4
		case 53:	return 5;	break;  // Cinco	5
		case 54:	return 6;	break;  // Seis		6
		case 55:	return 7;	break;  // Siete	7
		case 56:	return 8;	break;	// Ocho		8
		case 57:	return 9;	break;	// Nueve	9
		default:	return -1;		// Caracter no decimal!
	}
}

//Cuenta espacion antes y despues de la coma.
void getDataFloat(char *cadena, int posicion, int longitud, int *antes_coma, int *despues_coma=NULL){
	bool coma=false;
	int antComa=0;	//Almacena numero de espacios antes de la coma.
	int desComa=0;	//Almacena numero de espacios despues de la coma.
	for(int i=0;i<longitud;i++){
		if(!coma && getCifra(cadena[posicion+i])!=-1)
			antComa++;
		else if(cadena[posicion+i]=='.')
			coma=true;
		else if(coma && getCifra(cadena[posicion+i])!=-1)
			desComa++;
	}
	*antes_coma=antComa;
	if(despues_coma!=NULL)
		*despues_coma=desComa;
}

// Devuelve el valor del numero entero en cadena.
float getNum(char *cadena, int posicion, int longitud){
//	int inum=0;	//Guardara el valor entero del numero a leer;
	float fnum=0;	//Guardara el valor flotante del numero a leer;
	bool punto=false;	// Almacena si se a detectado la coma;
	int antComa=0;	//Almacena numero de espacios antes de la coma.
	//Esta variable por la forma en que esta hecha la funcion mas abajo, termino siendo no usada.
	int desComa=0;	//Almacena numero de espacios despues de la coma.
	getDataFloat(cadena,posicion,longitud,antComa,desComa);	// Determina espacios antes y despues de la coma.
	int l2=antComa-1;
	int l3=antComa+1
	for(int i=0;i<longitud;i++){
		if(getCifra(&cadena[posicion+i])!=-1 && !punto)
			fnum += getCifra( &cadena[posicion+i] ) * pow( 10 , (l2-i) );
		else if(cadena[posicion+i]=='.')
			punto = true;
		else if(punto && getCifra(&cadena[posicion+i])!=-1)
			fnum += getCifra(&cadena[posicion+i]) * pow(10, (antComa-i));
	}
	return fnum;
}

void setPosLong(char *cadena, int largo_cadena, int *posicion, int *longitud, char *comando=NULL){
	static int pos=0;	//posicion de lectura de la cadena actual.
	if(strcmp(comando,"NEWCAD"))	pos=0;	//Reinicia el registro de posicion en caso de una nueva cadena.
	bool num=false; //indica si se a empezado a leer un numero.
	
	//Bucle de lectura de la cadena.
	for(int i=0;i<largo_cadena;i++){
		//Si detecta una cifra y la posicion anterior no es una cifra o esta en la posicion 0
		//Determina que se a empezado a leer un numero y marca su posicion en la cadena.
		if(getCifra(cadena[i])!=-1 && (getCifra(cadena[i-1])==-1 || i==0)){
			num=true;	//Indica que se comenzo a leer el numero.
			*posicion=i;	//Devuelve la posicion del numero leido.
		}
		//Si detecta el fin del numero (posicion actuel no es una cifra y la anterior si lo es)
		//devuelve la longitud en cadena del numero, guarda la posicion de lectura actual de 
		//la funcion y finaliza el bucle.
		else if(getCifra(cadena[i])==-1 && getCifra(cadena[i-1])!=-1 && num){
			*longitud=i;	//Devuelve longitud del numero.
			pos=i;		//Guarda posicion de lectura.
			i=largo_cadena;	//Finaliza el bucle
		}
}

//DEvuelve la posicion de inicio del numero que esta tocando con el cursor.
int getPosNum(char *cadena, int posicion){
	if(getCifra(cadena[posicion])!=-1){
		int i=posicion;
		while(getCifra(cadena[i-1])!=-1)
			i--;
		return i;
	}
}

//strrev() revierte el orden de los caracteres en un string
void strrev(char *begin, char *end){
	char aux;
	while(*end>*begin)
		aux=*end, *end--=*begin, *begin++=aux;
}

/*Funcion que recibe numero y devuelve ascii:
char getNumChar(int *putn){
			switch(*putn){ 
			case 0:	return 48;	break;  // Cero		0
			case 1:	return 49;	break;  // Uno		1
			case 2:	return 50;	break;  // Dos		2
			case 3:	return 51;	break;  // Tres		3
			case 4:	return 52;	break;  // Cuatro	4
			case 5:	return 53;	break;  // Cinco	5
			case 6:	return 54;	break;  // Seis		6
			case 7:	return 55;	break;  // Siete	7
			case 8:	return 56;	break;	// Ocho		8
			case 9:	return 57;	break;	// Nueve	9
			}
*/
//getNumString es una funcion que resive un float o int y devuelve un string con el valor del numero escrito en simbolos decimales.
int getNumString(int value,char *str)
{
	char *wstr=str;
	int sign;

	if((sign=value) < 0) value = -value;

	do{
		*wstr++ = (value%10)+'0';
	}while(value/=10);

	if(sign<0) *wstr++='-';
	*wstr='\0';

	strrev(str,wstr-1);
	return 0;
}

int main(){
	
	
	return 0;
}

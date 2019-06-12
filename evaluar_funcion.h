#include<string.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct NodoNum{
	double numero;
	struct NodoNum* siguiente;
}NodoNum;

typedef struct PilaNum{
	NodoNum* cima;
	short tamano;
}PilaNum;


double raiz_cuadrada(double n);
double valor_absoluto(double n);
double valor_entero(double n);
double factorial(double n);
double permutacion(double n, double r);
double combinacion(double n, double r);
double exponencial(double n);
double logaritmo_natural(double n);
double logaritmo_base10(double n);
double antilogaritmo_base10(double n);
double funcion_seno(double n);
double funcion_coseno(double n);
double funcion_tangente(double n);
void Desapilar_PilaNum(PilaNum* pila_num);
double evaluar_funcion(char* funcion, PilaNum* pila_num,short *ptr3);


double evaluar_funcion(char* funcion, PilaNum* pila_num,short *ptr3){
	double resultado=0;
	short error = 0;
	if(!strcmp(funcion,"raizc")){
		if(pila_num->cima->numero < 0){
			printf("\nMATH ERROR\n");
			error = 1;
		}else{
			resultado = raiz_cuadrada(pila_num->cima->numero);
			Desapilar_PilaNum(pila_num);
		}
	}else if(!strcmp(funcion,"absol")){
		resultado = valor_absoluto(pila_num->cima->numero);
		Desapilar_PilaNum(pila_num);
	}else if(!strcmp(funcion,"entero")){
		resultado = valor_entero(pila_num->cima->numero);
		Desapilar_PilaNum(pila_num);
	}else if(!strcmp(funcion,"factorial")){
		if(pila_num->cima->numero < 0 || (valor_entero(pila_num->cima->numero) != pila_num->cima->numero)){
			printf("\nMATH ERROR\n");
			error = 1;
		}else{
			resultado = factorial(pila_num->cima->numero);
			Desapilar_PilaNum(pila_num);
		}
	}else if(!strcmp(funcion,"exp")){
		resultado = exponencial(pila_num->cima->numero);
		Desapilar_PilaNum(pila_num);
	}else if(!strcmp(funcion,"ln")){
		if(pila_num->cima->numero <= 0){
			printf("\nMATH ERROR\n");
			error = 1;
		}else{
			resultado = logaritmo_natural(pila_num->cima->numero);
			Desapilar_PilaNum(pila_num);
		}
	}else if(!strcmp(funcion,"log")){
		if(pila_num->cima->numero <= 0){
			printf("\nMATH ERROR\n");
			error = 1;
		}else{
			resultado = logaritmo_base10(pila_num->cima->numero);
			Desapilar_PilaNum(pila_num);
		}
	}else if(!strcmp(funcion,"alog")){
		resultado = antilogaritmo_base10(pila_num->cima->numero);
		Desapilar_PilaNum(pila_num);
	}else if(!strcmp(funcion,"seno")){
		resultado = funcion_seno(pila_num->cima->numero);
		Desapilar_PilaNum(pila_num);
	}else if(!strcmp(funcion,"coseno")){
		resultado = funcion_coseno(pila_num->cima->numero);
		Desapilar_PilaNum(pila_num);
	}else if(!strcmp(funcion,"tangente")){
		resultado = funcion_tangente(pila_num->cima->numero);
		Desapilar_PilaNum(pila_num);
	}else{
		printf("\nLa funcion %s no existe\n",funcion);
		*ptr3 = 1;
	}
	if (error == 1)
	{
		*ptr3 = 1;
	}
	else
	{
		*ptr3 = 0;
	}
	//printf("\nValor de puntero --> %i" ,error);
	return resultado;
}

double raiz_cuadrada(double n){
	return(sqrt(n));
}

double valor_absoluto(double n){
	if(n < 0){
		return(n*-1);
	}else
		return(n);
}

double valor_entero(double n){
	if(n < 0){
		return(ceil(n));
	}else{
		return(floor(n));
	}
}

double factorial(double n){
	if(n == 0){
		return 1;
	}else{
		return(factorial(n-1)*n);
	}
}

double permutacion(double n, double r){
	return(factorial(n)/factorial(n-r));
}

double combinacion(double n, double r){
	return(factorial(n)/factorial(n-r)/factorial(r));
}

double exponencial(double n){
	return(exp(n));
}

double logaritmo_natural(double n){
	return(log(n));
}

double logaritmo_base10(double n){
	return(log10(n));
}

double antilogaritmo_base10(double n){
	return(pow(10,n));
}

double funcion_seno(double n){
	return(sin(n));
}

double funcion_coseno(double n){
	return(cos(n));
}

double funcion_tangente(double n){
	return(tan(n));
}


NodoNum* CrearNodoNum(double numero);
void Iniciar_PilaNum(PilaNum* pila_num);
void Apilar_PilaNum(PilaNum* pila_num, NodoNum* nodo_num);
void Desapilar_PilaNum(PilaNum* pila_num);

NodoNum* CrearNodoNum(double numero){
	NodoNum* nodo_num = (NodoNum*) malloc(sizeof(NodoNum));
	nodo_num->numero = numero;
	nodo_num->siguiente = NULL;
}

void Iniciar_PilaNum(PilaNum* pila_num){
	pila_num->cima = NULL;
	pila_num->tamano = 0;
}

void Apilar_PilaNum(PilaNum* pila_num, NodoNum* nodo_num){
	if(pila_num->cima != NULL){
		nodo_num->siguiente = pila_num->cima;
	}
	pila_num->cima = nodo_num;
	pila_num->tamano++;
}

void Desapilar_PilaNum(PilaNum* pila_num){
	if(pila_num->cima != NULL){
		NodoNum* ptr = pila_num->cima;
		pila_num->cima = pila_num->cima->siguiente;
		free(ptr);
		pila_num->tamano--;
	}
}


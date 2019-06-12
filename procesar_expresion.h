#include"evaluar_funcion.h"

typedef struct item{
	char* cadena;
}item;

typedef struct Nodo{
	item elemento;
	struct Nodo* siguiente;
}Nodo;

typedef struct Pila{
	Nodo* cima;
	short tamano;
}Pila;


void Iniciar_Pila(Pila* pila);
Nodo* CrearNodo(item* item);
void Apilar_Pila(Pila* pila,Nodo* nodo);
void Desapilar_Pila(Pila* pila);
int preceexp(char caracter);
int precepila(char caracter);


//Funciones para procesar la expresion ingresada para obtener la expresion en postfija
int dimension_items(char* expresion_infija);
void reducir_expresion_signos(char* expresion_infija,item* items, int cant_item);
void validar(item* items, int cant_item);
void convertir_signo(item* items, int cant_item);
double evaluar_postfija(item* postfija, int i,short *ptr2,float *MEM);
double obtener_valor(char* cadena);
double coma_decimal(int entero, int decimal, int cant_decimal);

int dimension_items(char* expresion_infija){
	int i,m;
	m=0;
	for(i = 0; i < strlen(expresion_infija); i++){   //Obtiene la cantidad cadenas a evaluar, dimension del vector items
		if(isalnum(expresion_infija[i])){
			if(islower(expresion_infija[i]) && !islower(expresion_infija[i+1])){
				m++;
			}else if(isdigit(expresion_infija[i]) && !isdigit(expresion_infija[i+1])){
				m++;
			}else if(isupper(expresion_infija[i])){
				m++;
			}
		}else if((expresion_infija[i] == '+' || expresion_infija[i] == '-') && (expresion_infija[i+1] != '+' && expresion_infija[i+1] != '-')){
			m++;
		}else if(!(expresion_infija[i] == '+' || expresion_infija[i] == '-')){
			m++;
		}
	}
	return m;

}

void reducir_expresion_signos(char* expresion_infija,item* items, int cant_item){
	int i,m,cant_caracter,x,menos,n;
	x=0; menos=0; n=0;

	for(i = 0; i < strlen(expresion_infija); i++){  //Obtiene la cantidad de digitos de cada numero
		m = 0;
		if(isdigit(expresion_infija[i])){
			cant_caracter = 1;
			while(isdigit(expresion_infija[i+m+1])){
				m++;
			}
			cant_caracter = 1 + m;
			items[n].cadena = (char*) malloc(cant_caracter+1);
			for(x = 0; x < cant_caracter; x++){
				items[n].cadena[x] = expresion_infija[i+x];
			}
			items[n].cadena[cant_caracter] = '\0';
		}else if(islower(expresion_infija[i])){
			cant_caracter = 1;
			while(islower(expresion_infija[i+m+1])){
				m++;
			}
			cant_caracter = 1 + m;
			items[n].cadena = (char*) malloc(cant_caracter+1);
			for(x = 0; x < cant_caracter; x++){
				items[n].cadena[x] = expresion_infija[i+x];
			}
			items[n].cadena[cant_caracter] = '\0';
		}else if(expresion_infija[i] == '+' || expresion_infija[i] == '-'){
			menos = 0;
			if(expresion_infija[i] == '-'){
				menos++;
			}
			cant_caracter = 1;
			while(expresion_infija[i+m+1] == '+' || expresion_infija[i+m+1] == '-'){
				if(expresion_infija[i+m+1] == '-'){
				menos++;
				}
				m++;
			}
			items[n].cadena = (char*) malloc(2);
			if(menos%2 == 0){
				items[n].cadena[0] = '+';
			}else{
				items[n].cadena[0] = '-';
			}
			items[n].cadena[cant_caracter] = '\0';
		}else{
			cant_caracter = 1;
			items[n].cadena = (char*) malloc(cant_caracter+1);
			items[n].cadena[0] = expresion_infija[i];
			items[n].cadena[cant_caracter] = '\0';
		}
		n = n + 1;
		i = i + m;
	}
}

void convertir_signo(item* items, int cant_item){
	int x;
	for(x = 0; x < cant_item; x++){
		if(x > 0 && x < cant_item-1){
			if((items[x].cadena[0] == '-' || items[x].cadena[0] == '+') && (isalnum(items[x+1].cadena[0]) || items[x+1].cadena[0] == '(') && (items[x-1].cadena[0] == '*' || items[x-1].cadena[0] == '^' || items[x-1].cadena[0] == '/' || items[x-1].cadena[0] == '(' || items[x-1].cadena[0] == '^' || items[x-1].cadena[0] == '/' || items[x-1].cadena[0] == ',')){
				if(items[x].cadena[0] == '-'){
					items[x].cadena[0] = '$';
				}else if(items[x].cadena[0] == '+'){
					items[x].cadena[0] = '#';
				}
			}
		}else if(x == 0){
			if(items[x].cadena[0] == '-'){
				items[x].cadena[0] = '$';
			}else if(items[x].cadena[0] == '+'){
				items[x].cadena[0] = '#';
			}
		}

	}
}

void infija_a_postfija(item* items, item* post_fija, int cant_item,int* dimension_postfija)
{
	int x,i,size,y;
	size=0; y=0;
	Pila pila;
	Iniciar_Pila(&pila);
	i = 0;
		for(x = 0; x < cant_item; x++)
		{
			if(isdigit(items[x].cadena[0]) || isupper(items[x].cadena[0]))
			{ //Si el primer caracter de items[x].cadena es un digito
				size = strlen(items[x].cadena); //Obtener el numero de caracteres de items[x].cadena
				post_fija[i].cadena = (char*) malloc(size+1); //dimensionar el vector post_fija[i].cadena de acuerdo a la cantidad de caracteres de items[x].cadena
				strcpy(post_fija[i].cadena,items[x].cadena);
				post_fija[i].cadena[strlen(items[x].cadena)] = '\0';
				i++;
			}

			else if(items[x].cadena[0] == '+' || items[x].cadena[0] == '-' || items[x].cadena[0] == '*' 
			
			|| items[x].cadena[0] == '/' || items[x].cadena[0] == '^' || items[x].cadena[0] == ',' 

			|| items[x].cadena[0] == '$' || items[x].cadena[0] == '#')
			{
				if(pila.tamano != 0)
				{
					while(preceexp(items[x].cadena[0]) <= precepila(pila.cima->elemento.cadena[0]) && pila.tamano != 1)
					{
						size = strlen(pila.cima->elemento.cadena); //Obtener el numero de caracteres de items[x].cadena
						post_fija[i].cadena = (char*) malloc(size+1); //dimensionar el vector post_fija[i].cadena de acuerdo a la cantidad de caracteres de items[x].cadena
						strcpy(post_fija[i].cadena,pila.cima->elemento.cadena);
						Desapilar_Pila(&pila);
						i++;
					}
					if(preceexp(items[x].cadena[0]) <= precepila(pila.cima->elemento.cadena[0]))
					{
						size = strlen(pila.cima->elemento.cadena); //Obtener el numero de caracteres de items[x].cadena
						post_fija[i].cadena = (char*) malloc(size+1); //dimensionar el vector post_fija[i].cadena de acuerdo a la cantidad de caracteres de items[x].cadena
						strcpy(post_fija[i].cadena,pila.cima->elemento.cadena);
						Desapilar_Pila(&pila);
						i++;
					}
				}
				Apilar_Pila(&pila,CrearNodo(&items[x]));
			}

			else if(islower(items[x].cadena[0]) || items[x].cadena[0] == '(')
			{
				Apilar_Pila(&pila,CrearNodo(&items[x]));
			}

			else if(items[x].cadena[0] == ')')
			{
				while(pila.cima->elemento.cadena[0] != '(')
				{
					size = strlen(pila.cima->elemento.cadena); //Obtener el numero de caracteres de items[x].cadena
					post_fija[i].cadena = (char*) malloc(size+1); //dimensionar el vector post_fija[i].cadena de acuerdo a la cantidad de caracteres de items[x].cadena
					strcpy(post_fija[i].cadena,pila.cima->elemento.cadena);
					Desapilar_Pila(&pila);
					i++;
				}
				Desapilar_Pila(&pila);
				if(pila.cima != NULL)
				{
					if(islower(pila.cima->elemento.cadena[0]))
					{
						size = strlen(pila.cima->elemento.cadena); //Obtener el numero de caracteres de items[x].cadena
						post_fija[i].cadena = (char*) malloc(size+1); //dimensionar el vector post_fija[i].cadena de acuerdo a la cantidad de caracteres de items[x].cadena
						strcpy(post_fija[i].cadena,pila.cima->elemento.cadena);
						Desapilar_Pila(&pila);
						i++;
					}
				}
			}

			if(x == cant_item-1)
			{
				while(pila.tamano > 1)
				{
					size = strlen(pila.cima->elemento.cadena); //Obtener el numero de caracteres de items[x].cadena
					post_fija[i].cadena = (char*) malloc(size+1); //dimensionar el vector post_fija[i].cadena de acuerdo a la cantidad de caracteres de items[x].cadena
					strcpy(post_fija[i].cadena,pila.cima->elemento.cadena);
					Desapilar_Pila(&pila);
					i++;
				}
				if(pila.tamano == 1)
				{
					size = strlen(pila.cima->elemento.cadena); //Obtener el numero de caracteres de items[x].cadena
					post_fija[i].cadena = (char*) malloc(size+1); //dimensionar el vector post_fija[i].cadena de acuerdo a la cantidad de caracteres de items[x].cadena
					strcpy(post_fija[i].cadena,pila.cima->elemento.cadena);
					Desapilar_Pila(&pila);
					i++;
				}
			}

		}
		*dimension_postfija = i;
}

double evaluar_postfija(item* postfija, int i,short *ptr2,float *MEM){
	short x;
	PilaNum pila_num;
	Iniciar_PilaNum(&pila_num);
	double resultado;
	for(x = 0; x < i; x++){
		if(isdigit(postfija[x].cadena[0])){
			Apilar_PilaNum(&pila_num,CrearNodoNum(obtener_valor(postfija[x].cadena)));
		}else if(postfija[x].cadena[0] == '+' || postfija[x].cadena[0] == '-' || postfija[x].cadena[0] == '/' || postfija[x].cadena[0] == '*' || postfija[x].cadena[0] == '^' || postfija[x].cadena[0] == '$' || postfija[x].cadena[0] == '#'){
			switch(postfija[x].cadena[0]){
				case '+': 	resultado = pila_num.cima->numero + pila_num.cima->siguiente->numero;
							Desapilar_PilaNum(&pila_num);
							Desapilar_PilaNum(&pila_num);
							Apilar_PilaNum(&pila_num,CrearNodoNum(resultado));
							break;

				case '-':	resultado = pila_num.cima->siguiente->numero - pila_num.cima->numero;
							Desapilar_PilaNum(&pila_num);
							Desapilar_PilaNum(&pila_num);
							Apilar_PilaNum(&pila_num,CrearNodoNum(resultado));
							break;

				case '/':	if(pila_num.cima->numero == 0){
								printf("\nMATH ERROR\n");

							}else{
								resultado = pila_num.cima->siguiente->numero / pila_num.cima->numero;
								Desapilar_PilaNum(&pila_num);
								Desapilar_PilaNum(&pila_num);
								Apilar_PilaNum(&pila_num,CrearNodoNum(resultado));
								break;
							}

				case '*':	resultado = pila_num.cima->numero * pila_num.cima->siguiente->numero;
							Desapilar_PilaNum(&pila_num);
							Desapilar_PilaNum(&pila_num);
							Apilar_PilaNum(&pila_num,CrearNodoNum(resultado));
							break;

				case '^':	resultado = pow(pila_num.cima->siguiente->numero,pila_num.cima->numero);
							Desapilar_PilaNum(&pila_num);
							Desapilar_PilaNum(&pila_num);
							Apilar_PilaNum(&pila_num,CrearNodoNum(resultado));
							break;

				case '$':	resultado = 0 - pila_num.cima->numero;
							Desapilar_PilaNum(&pila_num);
							Apilar_PilaNum(&pila_num,CrearNodoNum(resultado));
							break;

				case '#':	break;
				}

			}else if(postfija[x].cadena[0] == ','){
				if(x == i-1){
					resultado = coma_decimal(pila_num.cima->siguiente->numero,pila_num.cima->numero,(double)strlen(postfija[x-1].cadena));
					Apilar_PilaNum(&pila_num,CrearNodoNum(resultado));
				}else{
					if(!strcmp(postfija[x+1].cadena,"permut")){
						if(pila_num.cima->numero > pila_num.cima->siguiente->numero || (valor_entero(pila_num.cima->numero) != pila_num.cima->numero) || (valor_entero(pila_num.cima->siguiente->numero) != pila_num.cima->siguiente->numero)){
							printf("\nMATH ERROR\n");

						}else{
							resultado = permutacion(pila_num.cima->siguiente->numero,pila_num.cima->numero);
							Desapilar_PilaNum(&pila_num);
							Desapilar_PilaNum(&pila_num);
							Apilar_PilaNum(&pila_num,CrearNodoNum(resultado));
							x++;
						}
					}else if(!strcmp(postfija[x+1].cadena,"combin")){
						if(pila_num.cima->numero > pila_num.cima->siguiente->numero || (valor_entero(pila_num.cima->numero) != pila_num.cima->numero) || (valor_entero(pila_num.cima->siguiente->numero) != pila_num.cima->siguiente->numero)){
							printf("\nMATH ERROR\n");

						}else{
							resultado = combinacion(pila_num.cima->siguiente->numero,pila_num.cima->numero);
							Desapilar_PilaNum(&pila_num);
							Desapilar_PilaNum(&pila_num);
							Apilar_PilaNum(&pila_num,CrearNodoNum(resultado));
							x++;
						}
					}else{
						resultado = coma_decimal(pila_num.cima->siguiente->numero,pila_num.cima->numero,(double)strlen(postfija[x-1].cadena));
						Desapilar_PilaNum(&pila_num);
						Desapilar_PilaNum(&pila_num);
						Apilar_PilaNum(&pila_num,CrearNodoNum(resultado));
					}
				}
			}else if(islower(postfija[x].cadena[0])){
				resultado = evaluar_funcion(postfija[x].cadena,&pila_num,ptr2);
				Apilar_PilaNum(&pila_num,CrearNodoNum(resultado));
			}
			else if(isupper(postfija[x].cadena[0])) {
				Apilar_PilaNum(&pila_num, CrearNodoNum(MEM[postfija[x].cadena[0]-'A']));
			}
	}
	if(*ptr2 != 0){
        return 0;
	}else{
	    return resultado;
	}

}



Nodo* CrearNodo(item* item2){
	short size;
	size = strlen(item2->cadena);
	Nodo* nodo = (Nodo*) malloc(sizeof(Nodo));
	nodo->elemento.cadena = (char*) malloc(size+1);
    strcpy(nodo->elemento.cadena,item2->cadena);
    nodo->elemento.cadena[size+1] = '\0';
    nodo->siguiente = NULL;
    return(nodo);
}

void Iniciar_Pila(Pila* pila){
	pila->cima = NULL;
	pila->tamano = 0;
}

void Apilar_Pila(Pila* pila, Nodo* nodo){
	if(pila->cima != NULL){
		nodo->siguiente = pila->cima;
	}
	pila->cima = nodo;
	pila->tamano++;
}

void Desapilar_Pila(Pila* pila){
	if(pila->cima != NULL){
		Nodo* ptr = pila->cima;
		pila->cima = pila->cima->siguiente;
		free(ptr);
		pila->tamano--;
	}
}

int preceexp(char caracter){
	if(caracter == '('){
		return(5);
	}
	if(caracter == '*' || caracter == '/'){
		return(2);
	}
	if(caracter == '+' || caracter == '-'){
		return(1);
	}
	if(caracter == '^'){
		return(4);
	}
	if(caracter == ','){
		return(7);
	}
	if(caracter == '$' || caracter == '#'){
		return(6);
	}
}

int precepila(char caracter){
	if(caracter == '('){
		return(0);
	}
	if(caracter == '*' || caracter == '/'){
		return(2);
	}
	if(caracter == '+' || caracter == '-'){
		return(1);
	}
	if(caracter == '^'){
		return(3);
	}
	if(caracter == ','){
		return(7);
	}
	if(caracter == '$' || caracter == '#'){
		return(6);
	}
}

double obtener_valor(char* cadena){
	int x;
	double valor,num;
	num = 0;
	for(x = 0; x < strlen(cadena); x++){
		valor = (cadena[x] - '0')*(pow(10,strlen(cadena)-x-1));
		num = num + valor;
	}
	return(num);
}

double coma_decimal(int entero, int decimal, int cant_decimal){
	double numero_decimal;
	numero_decimal = entero + decimal/pow(10,cant_decimal);
	return numero_decimal;
}



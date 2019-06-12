#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <allegro.h>
#include <winalleg.h>
#include "procesar_expresion.h"


/*-----------------------CONSTANTES--------------------*/

#define BUFFERSIZE 128
#define ancho 500 // Se define el ancho de la ventana
#define alto 500 // Se define el alto de la ventana
#define WHITE makecol(255, 255, 255)
#define true 1
#define false 0

/*----------------------------------------------------*/

/*---------VARIABLES GLOBALES---------------*/

BITMAP *buffer; // Buffer de carga

BITMAP *pantalla_inicial_con; // Pantalla inicial
BITMAP *pantalla_inicial_sin;

BITMAP *pantalla_instrucciones_con; // Pantalla de instrucciones
BITMAP *pantalla_instrucciones_sin;

BITMAP *pantalla_calculadora; // Pantalla donde se realizan los calculos

BITMAP *pantalla__despedida; // Pantalla de despedida


short error = 0;

/*---------------Prototipado de Funciones con uso de ALLEGRO--------------*/

void allegro_inicio(void);
void init_pantalla(void);
void img_init(void);

void muestra_inicial_con(void);
void muestra_inicial_sin(void);
void pantalla_inicial(void);

void muestra_instruciones_con(void);
void muestra_instruciones_sin(void);
void pantalla_instrucciones(void);

void muestra_despedida(void);
void pantalla_despedida(void);

void impresiones(void);
void calculadora(void);
/*-------------------------------------------------------*/
/*-------------------------------------------------------*/

/*--------------------------------------------------------*/

char edittext[BUFFERSIZE];
char edittext1[BUFFERSIZE];
//ptr_cadena -> x=1
int caret = 0;
int caret1 = 0;

double resultado = 0;

float MEM [12] = {0};

int band_1 ,band_2;

/*---------------------------------------------*/

int main(void){
    allegro_inicio(); // Se inicia la libreria grafica "ALLEGRO 4"
    init_pantalla(); // Se inicia los componentes para mostrar en pantalla
    img_init(); // Se carga las imagenes a mostrar

    pantalla_inicial(); // Pantalla de Bienvenida

    pantalla_instrucciones(); // Pantalla que explica como usar la calculadora

    calculadora(); // Funcion donde se realizan los calculos

    pantalla_despedida(); // Pantalla de despedida

    return 0;
}
END_OF_MAIN() // Se cierra la libreria ("ALLEGRO 4")


void allegro_inicio()
{
    edittext[0]='\0';
    edittext1[0]='\0';


    allegro_init();
    install_keyboard();
}

void init_pantalla()
{
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, ancho, alto, 0, 0);
    buffer = create_bitmap(ancho, alto);
}

void img_init()
{
    pantalla_inicial_con = load_bitmap("img/inicial_con.bmp",NULL);
    pantalla_inicial_sin = load_bitmap("img/inicial_sin.bmp",NULL);

    pantalla_instrucciones_con = load_bitmap("img/instruc_con.bmp",NULL);
    pantalla_instrucciones_sin = load_bitmap("img/instruc_sin.bmp",NULL);

    pantalla_calculadora = load_bitmap("img/calculadora.bmp",NULL);

    pantalla__despedida = load_bitmap("img/despedida.bmp",NULL);
}

/* --------------------------Pantalla de Bienvenida -------------------*/

void muestra_inicial_con()
{
    clear_to_color(buffer,0x2E4638);
    draw_sprite(buffer,pantalla_inicial_con,0,0);
    blit(buffer, screen, 0 , 0 , 0 , 0 , ancho , alto );
}
void muestra_inicial_sin()
{
    clear_to_color(buffer,0x2E4638);
    draw_sprite(buffer, pantalla_inicial_sin,0,0);
    blit(buffer, screen, 0 , 0 , 0 , 0 , ancho , alto );
}
void pantalla_inicial()
{
    do
    {
        muestra_inicial_con();
        Sleep(750);
        muestra_inicial_sin();
        Sleep(750);
    } while (!key[KEY_SPACE]);
}

/*----------------------------------------------------------------------------------*/

/* --------------------------Pantalla de Instrucciones-------------------*/

void muestra_instruciones_con()
{
    clear_to_color(buffer,0x2E4638);
    draw_sprite(buffer,pantalla_instrucciones_con,0,0);
    blit(buffer, screen, 0 , 0 , 0 , 0 , ancho , alto );
}
void muestra_instruciones_sin()
{
    clear_to_color(buffer,0x2E4638);
    draw_sprite(buffer,pantalla_instrucciones_sin,0,0);
    blit(buffer, screen, 0 , 0 , 0 , 0 , ancho , alto );
}
void pantalla_instrucciones()
{
    do
    {
        muestra_instruciones_con();
        Sleep(750);
        muestra_instruciones_sin();
        Sleep(750);

    } while (!key[KEY_SPACE]);
}

/*----------------------------------------------------------------------------------*/

/*-----------------------Pantalla de Despedida-------------------------------*/

void muestra_despedida()
{
    clear_to_color(buffer,0x2E4638);
    draw_sprite(buffer,pantalla__despedida,0,0);
    blit(buffer, screen, 0 , 0 , 0 , 0 , ancho , alto );
}
void pantalla_despedida()
{
    muestra_despedida();
    Sleep(1500);
}

/*--------------------------------------------------------------------------*/

/*--------------Impresiones de la pantalla "Calculadora"-----------------"*/

void impresiones()
{
    clear(buffer);
    draw_sprite(buffer,pantalla_calculadora,0,0);
    textout_ex(buffer, font, edittext, ancho/14, alto/7, WHITE,0x2E4638);
    textout_ex(buffer, font, edittext1, ancho/14, alto/5, WHITE,0x2E4638);
    textprintf_right_ex(buffer,font,ancho-ancho/14, 220,WHITE,0x2E4638,"%.5lf",resultado);
    //textprintf_ex(buffer,font,ancho-ancho/14, 250,WHITE,0x2E4638,"%i",error);

    // Se imprime la Memoria

    textprintf_ex(buffer,font,ancho/8, 310,WHITE,0x2E4638,"%.4f",MEM[0]);//A
    textprintf_ex(buffer,font,ancho/8, 335,WHITE,0x2E4638,"%.4f",MEM[1]);//B

    textprintf_ex(buffer,font,ancho/8, 362,WHITE,0x2E4638,"%.4f",MEM[2]);//C
    textprintf_ex(buffer,font,ancho/8, 389,WHITE,0x2E4638,"%.4f",MEM[3]);//D
    textprintf_ex(buffer,font,ancho/8, 415,WHITE,0x2E4638,"%.4f",MEM[4]);//E
    textprintf_ex(buffer,font,ancho/8, 443,WHITE,0x2E4638,"%.4f",MEM[5]);//F

    textprintf_ex(buffer,font,ancho/2+15, 310,WHITE,0x2E4638,"%.4f",MEM[6]);//G
    textprintf_ex(buffer,font,ancho/2+15, 335,WHITE,0x2E4638,"%.4f",MEM[7]);//H

    textprintf_ex(buffer,font,ancho/2+15, 362,WHITE,0x2E4638,"%.4f",MEM[8]);//I
    textprintf_ex(buffer,font,ancho/2+15, 389,WHITE,0x2E4638,"%.4f",MEM[9]);//J
    textprintf_ex(buffer,font,ancho/2+15, 415,WHITE,0x2E4638,"%.4f",MEM[10]);//K
    textprintf_ex(buffer,font,ancho/2+15, 443,WHITE,0x2E4638,"%.4f",MEM[11]);//L

    blit(buffer, screen, 0 , 0 , 0 , 0 , ancho, alto );
}

/*----------------------------------------------------------------------*/

/*------CALCULADORA-------------------------------------------------------*/

void calculadora()
{
    int cant_item,dimension_postfija;
	item* items;
	item* vector_postfija;

    band_2 = true;
    while(band_2 == true)
    {
        do
        {
            if(keypressed()) // Si se presiona una tecla entra
            {
                int  newkey   = readkey();
                char ASCII    = newkey & 0xff;
                char scancode = newkey >> 8;

                // Si se presiona una tecla se agrega
                if(ASCII >= 33 && ASCII <= 126)
                {   
                    if (ASCII == 60 && caret < BUFFERSIZE - 1 && caret <= 53)
                    {
                        ASCII = 94;
                        edittext[caret] = ASCII;
                        caret++;
                        edittext[caret] = '\0';   
                    }                    
                    else if (ASCII == 60 && caret < BUFFERSIZE - 1 && caret >= 54 && caret < 108)
                    {
                        ASCII = 94;
                        edittext1[caret1] = ASCII;
                        caret++;
                        caret1++;
                        edittext1[caret1] = '\0';  
                    }
                    else if(caret < BUFFERSIZE - 1 && caret <= 53)
                    {
                        edittext[caret] = ASCII;
                        caret++;
                        edittext[caret] = '\0';
                    }
                    else if(caret < BUFFERSIZE - 1 && caret >= 54 && caret < 108)
                    {
                        edittext1[caret1] = ASCII;
                        caret++;
                        caret1++;
                        edittext1[caret1] = '\0';
                    }
                }
                else if(scancode == KEY_BACKSPACE && caret <= 54)
                {
                    if (caret > 0) caret--;
                    edittext[caret] = '\0';
                }
                else if(scancode == KEY_BACKSPACE && caret >= 55)
                {
                    caret--;
                    if (caret1 > 0)
                    {
                        caret1--;
                    }
                edittext1[caret1] = '\0';
                }
            }
            if (caret <= 53)
            {

                impresiones();

            }
                else if (caret >= 54 && caret < 109)
            {
                impresiones();
            }

        }  while(!key[KEY_ENTER]);

        system("cls");

        /*Se concatena la variable final*/
        strcat(edittext,edittext1);
        printf("\nExpresion -> %s\n",edittext);

        cant_item = dimension_items(edittext);
	    items = (item*) malloc(cant_item*sizeof(item)); //Se calcula la cantidad de datos tipo item que tendra el vector items y lo dimensionamos, para juntar todas las funciones, numeros con varios digitos y reducir sugnos concatenados
	    reducir_expresion_signos(edittext,items,cant_item); //juntar todas las funciones, numeros con varios digitos y reducir sugnos concatenados en un vector de tipo item
	    /*validar_expresion(items,cant_item); //Bucar errores de sintaxis para validar la expresion*/
	    convertir_signo(items,cant_item); //Convertir los signos en en otros caracteres para diferenciar de un signo y un operador suma o resta
	    vector_postfija = (item*) malloc(cant_item*sizeof(item));
	    infija_a_postfija(items,vector_postfija,cant_item,&dimension_postfija); //Pasar los valores del vector items que esta en formato infija a un vector del mismo tipo en formato postfija llamado vector_postfija usando Pila tipo cadena
	    resultado = evaluar_postfija(vector_postfija,dimension_postfija,&error,MEM); //Evaluar el vector "vector_postfija" para obtener su valor usando Pila tipo double
        printf("\nResultado -> %.5lf\n\n",resultado);
        //---------------------------------------

        impresiones();

        printf("Presione M para guardar en la memoria\n");
        printf("Si no desea guardar NO presione NADA\n");
        printf("Presione Espacio para salir del programa\n");

        // Si se presiona "M"  se debe a que desea guardar en la memoria

        band_1 = true ;

        while (band_1 == true)
        {
            Sleep(1000);

            if(keypressed()) // Si se presiona una tecla entra
            {
                int  newkey   = readkey();
                char ASCII    = newkey & 0xff;
                char scancode = newkey >> 8;

                if(ASCII == 77 || ASCII == 109)
                {
                    printf("Elija en que memoria guardar\n");
                    while (true)
                    {
                        if(keypressed())
                        {
                            int  newkey   = readkey();
                            char ASCII    = newkey & 0xff;
                            char scancode = newkey >> 8;

                            if(ASCII == 65 || ASCII == 97)//A
                            {
                                printf("Se guardo en la memoria A\n");
                                MEM[0]= resultado;
                                break;
                                break;
                            }
                            else if(ASCII == 66 || ASCII == 98)//B
                            {
                                printf("Se guardo en la memoria B\n");
                                MEM[1]= resultado;
                                break;
                                break;
                            }
                            else if(ASCII == 67 || ASCII == 99)//C
                            {
                                printf("Se guardo en la memoria C\n");
                                MEM[2]= resultado;
                                break;
                                break;
                            }
                            else if(ASCII == 68 || ASCII == 100)//D
                            {
                                printf("Se guardo en la memoria D\n");
                                MEM[3]= resultado;
                                break;
                                break;
                            }
                            else if(ASCII == 69 || ASCII == 101)//E
                            {
                                printf("Se guardo en la memoria E\n");
                                MEM[4]= resultado;
                                break;
                                break;
                            }
                            else if(ASCII == 70 || ASCII == 102)//F
                            {
                                printf("Se guardo en la memoria F\n");
                                MEM[5]= resultado;
                                break;
                                break;
                            }
                            else if(ASCII == 71 || ASCII == 103)//G
                            {
                                printf("Se guardo en la memoria G\n");
                                MEM[6]= resultado;
                                break;
                                break;
                            }
                            else if(ASCII == 72 || ASCII == 104)//H
                            {
                                printf("Se guardo en la memoria H\n");
                                MEM[7]= resultado;
                                break;
                                break;
                            }
                            else if(ASCII == 73 || ASCII == 105)//I
                            {
                                printf("Se guardo en la memoria I\n");
                                MEM[8]= resultado;
                                break;
                                break;
                            }
                            else if(ASCII == 74 || ASCII == 106)//J
                            {
                                printf("Se guardo en la memoria J\n");
                                MEM[9]= resultado;
                                break;
                                break;
                            }
                            else if(ASCII == 75 || ASCII == 107)//K
                            {
                                printf("Se guardo en la memoria K\n");
                                MEM[10]= resultado;
                                break;
                                break;
                            }
                            else if(ASCII == 76 || ASCII == 108)//L
                            {
                                printf("Se guardo en la memoria L\n");
                                MEM[11]= resultado;
                                break;
                                break;
                            }
                            impresiones();
                        }
                    }
                }
                else if(ASCII == 32) // Se presiona espacio se sale del programa
                {
                    printf("Hasta luego, Gracias por usar nuestra calculadora\n");
                    band_2 = false;
                    break;
                    break;
                }
            }
            else
            {
                band_1 = false;
            }
        }
        Sleep(500);
    }
}

/*-------------------------------------------------------------------------------------------------------------------------------*/

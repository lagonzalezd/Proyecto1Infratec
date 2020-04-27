/*
PROYECTO 1 FUNDAMENTOS DE INFRAESTRUCTURA TECNOLOGICA - 201820
Integrante 1 - Codigo integrante 1
Integrante 2 - Codigo integrante 2
Integrante 3 - Codigo integrante 3
*/

#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//-- Definicion de la estructura para los datos del archivo de entrada y el de salida
typedef struct datos
{
	int tamanio;
	unsigned char *informacion;
} Datos;


//-- Prototipos de las funciones
int readFile(Datos * archivo, char *);
void writeFile(Datos * archivoEnBinario, char *);
void convertirABinario(Datos * archivo, Datos * archivoEnBinario);


//-- Funciones

// Esta funcion se encarga de abrir un datos y leerlo en el vector informacion.
// Retorna el numero de bytes leidos.
// No hay que completar nada en esta funcion.
int readFile(Datos * archivo, char * nombreArchivo)
{
	FILE *file;
	int n;

	file = fopen(nombreArchivo, "rb");

	if (!file)
	{
		printf("No se pudo abrir el archivo para leer: %s\n", nombreArchivo);
        system("PAUSE");
		exit(EXIT_FAILURE);
	}
	fseek(file, 0, SEEK_END);
	n = ftell(file);
	fseek(file, 0, SEEK_SET);

	archivo->tamanio = n;
	archivo->informacion = (unsigned char *)calloc(n, sizeof(unsigned char));

	fread(archivo->informacion, sizeof(unsigned char), n, file);

	fclose(file);

	return n;
}


// Esta funcion se encarga de escribir un datos a partir del vector datos.
// El numero de bytes que se deben escribir viene en el parametro n.
// No hay que completar nada en esta funcion.
void writeFile(Datos * archivoEnOctal, char *nombreArchivo)
{
	FILE *file;

	file = fopen(nombreArchivo, "wb");

	if (!file) {
		printf("No se pudo abrir el archivo para escribir: %s\n", nombreArchivo);
        system("PAUSE");
		exit(EXIT_FAILURE);
	}

	fwrite(archivoEnOctal->informacion, sizeof(char), archivoEnOctal->tamanio, file);

	fclose(file);
}


// Esta funcion se encarga de convertir a binario cada uno de los caracteres que se
// encuentran en la estructura datosOct->informacion y asignar los nuevos valores a la estructura datosBin->informacion.
// Deben desarrollar esta funcion en su totalidad.

void convertirABinario(Datos * datosOct, Datos * datosBin)
 {
 	// Tengo que hacer 3 tareas principales
	// 1. Leer la informacion
	// 1.1 Obtener un apuntador sobre el primer char
	unsigned char* primerApuntador = datosOct->informacion;
	unsigned char* escribir = datosBin->informacion;

	// 1.2 Iterar sobre el apuntador
	int longitudInformacion = datosOct->tamanio;
	int tamanioDatosBin = 1;
	int posicion = 0;
	for (int i = 0; i < longitudInformacion; i++) {
		unsigned char caracterActual = *primerApuntador;

		// 2. Transformar la informaci�n
		// 2.1 Convertir al valor binario el valor que nos llega por parametro
		caracterActual = caracterActual - 48;

		// 2.2 Mover los bits a la posicion en donde los tengo que agregar
		unsigned char bitsMovidos;
		if (posicion <= 5) {
			bitsMovidos = caracterActual << (5 - posicion);
		}
		else {
			bitsMovidos = caracterActual >> posicion - 5;
		}

		// 3. Escribir la informaci�n
		// 3.2 Escribir el car�cter
		*escribir |= bitsMovidos;
		if (posicion > 5) {
			escribir++;
			bitsMovidos = caracterActual << 8 - (posicion - 5);
			*escribir = bitsMovidos;
			tamanioDatosBin++;
		}
		posicion = (posicion + 3) % 8;
		if (posicion == 0) {
			escribir++;
			tamanioDatosBin++;
		}
		
		// 3.3 Mover el apuntador si es necesario
		
		primerApuntador++;
	}
	datosBin->tamanio = tamanioDatosBin;

 	}

//-- Funcion main de la aplicacion
// No hay que completar nada en esta funcion.
int main()
{
	// Mensaje inicial
	printf("PROYECTO 1 - INFRATEC (ISIS-1304)");

	// Declaracion de todas las variables necesarias.
	int tamanio;
	int tamanioRepBinario;
	char nombreArchivo[200];
	char nombreArchivoBinario[200];
	Datos * archivoOctal = (Datos *)malloc(sizeof(Datos));
	Datos * archivoEnBinario = (Datos *)malloc(sizeof(Datos));

	printf("\n\nIngrese el nombre del archivo a leer (incluya el formato. i.e. archivo.txt): \n");
	scanf("%s", nombreArchivo);
	tamanio = readFile(archivoOctal, nombreArchivo);
	printf("\nEl tamanio del archivo es de %d bytes\n", tamanio);
	tamanioRepBinario = ((tamanio * 3) / 8) + (((tamanio*3) % 8 == 0)? 0 : 1);
	archivoEnBinario->informacion = (unsigned char *)calloc(tamanioRepBinario, sizeof(unsigned char));
	archivoEnBinario->tamanio = tamanioRepBinario;
	printf("\nIngrese el nombre del archivo para guardar la representacion en octales del archivo origen (incluya el .txt): \n");
	scanf("%s", nombreArchivoBinario);
	convertirABinario(archivoOctal, archivoEnBinario);
	writeFile(archivoEnBinario, nombreArchivoBinario);
	printf("\nEl archivo se transformo en su representacion a octal exitosamente!\n\n");
	printf("Revisa el archivo con nombre '%s' para ver el resultado!\n", nombreArchivoBinario);

	// Terminar
	system("PAUSE");
	return 0;
}

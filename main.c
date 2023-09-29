#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "hashmap.h"
#include "list.h"
//Se declara un tamaño base para los mapas
#define DEFAULTSIZE 20 

//Estructura de un punto de interes
struct PuntoInteres {
  char *nombre;         //Nombre del punto
  char *tipo;           //Tipo del punto 
  char *direccion;      //Direccion del punto
  char *horario;        //Horario del punto
  char *descripcion;    //Descripcion del punto
};

//Estructura de un turista
struct Turista {
  char *pasaporte;          //Pasaporte del turista
  char *nombre;             //Nombre del turista
  char *pais;               //Pais del turista
  List *lugaresFavoritos;     //Lista para todos los lugares favoritos del turista
};

//Main del programa
int main(void) {

  menu();  //Menu con opciones

  return 0;
}

//Menu donde se ven las opciones y se crean los mapas del programa
void menu() {

  int opcion = 0;

  //Se crean los mapas que se usaran durante todo el programa
  HashMap *mapaPuntosInteres = createMap(DEFAULTSIZE);
  HashMap *mapaTurista = createMap(DEFAULTSIZE);
  HashMap *mapaTuristaPais = createMap(DEFAULTSIZE);
  HashMap *mapaPuntoInteresTipo = createMap(DEFAULTSIZE);

  do {

    printf("\nBienvenido gestion de Turistica\n");
    printf("---------------------------------\n");
    printf("\n1.Registrar punto de interes");
    printf("\n2.Mostrar datos de punto de interes");
    printf("\n3.Eliminar punto de interes");
    printf("\n4.Registrar turista");
    printf("\n5.Agregar lugar favorito a turista");
    printf("\n6.Mostrar turistas por pais");
    printf("\n7.Mostrar puntos de interes por tipo");
    printf("\n8.Importa CSV");
    printf("\n9.Exportar CSV");
    printf("\n10.Salir\n");
    printf("\nOpcion: ");
    scanf(" %d", &opcion);

    //Se envia la opcion y los mapas para ser procesados
    proceso(mapaPuntosInteres, mapaTurista, mapaTuristaPais,
            mapaPuntoInteresTipo, opcion);

  } while (opcion != 10);
}

//Funcion para el acceso a todas las funciones principales
void proceso(HashMap *mapaPuntosInteres, HashMap *mapaTurista,
             HashMap *mapaTuristaPais, HashMap *mapaPuntosInteresTipo,
             int opcion) {

  switch (opcion) {
  case 1:
    registrarPuntoInteres(mapaPuntosInteres, mapaPuntosInteresTipo);
    break;
  case 2:
    mostrarDatosPuntoInteres(mapaPuntosInteres);
    break;
  case 3:
    eliminarPuntoInteres(mapaPuntosInteres,mapaPuntosInteresTipo);
    break;
  case 4:
    registrarTurista(mapaTurista, mapaTuristaPais);
    break;
  case 5:
    agregarLugarFavoritoTurista(mapaTurista);
    break;
  case 6:
    mostrarTuristasPorPais(mapaTuristaPais);
    break;
  case 7:
    mostrarPuntosInteresTipo(mapaPuntosInteresTipo);
    break;
  case 8:
    importarCSV(mapaPuntosInteres, mapaTurista, mapaTuristaPais,
                mapaPuntosInteresTipo);
    break;
  case 9:
    exportarCSV(mapaPuntosInteres, mapaTurista);
    break;
  case 10:
    printf("\nAdios\n");
    //Se libera la memoria de los mapas
    freeMap(mapaPuntosInteres);
    freeMap(mapaTurista);
    break;
  default:
    //En caso de que el usario ingrese una opcion no valida se envia un mensaje
    printf("\nOpcion no valida");
    break;
  }
}

// Opcion 1, registrar un punto de interes
void registrarPuntoInteres(HashMap *mapaPuntosInteres,
                           HashMap *mapaPuntosInteresTipo) {

  //Se crea el punto de interes
  PuntoInteres *puntoInteres = (PuntoInteres *)malloc(sizeof(PuntoInteres));

  //Se pide los datos al usuario
  pedirDatosPuntoInteres(puntoInteres);

  //Se inserta al mapa
  insertMap(mapaPuntosInteres, puntoInteres->nombre, puntoInteres);

  //Se inserta al mapa con los puntos de interes por tipo
  registrarPuntoInteresTipo(mapaPuntosInteresTipo, puntoInteres);
}

//Funcion para regisrar el punto al mapa de puntos de interes por tipo
void registrarPuntoInteresTipo(HashMap *mapaPuntosInteresTipo,
                               PuntoInteres *puntoInteres) {

  //Se busca si existe el tipo en el mapa
  Pair *pairTipo = searchMap(mapaPuntosInteresTipo, puntoInteres->tipo);

  if (pairTipo == NULL) {
    //Si no existe se crea una lista
    List *listaTipo = createList();

    //Se inserta al principio
    pushFront(listaTipo, puntoInteres);
    char* nombreTipo = strdup(puntoInteres->tipo);
    //Se inserta la lista al mapa con clave el tipo
    insertMap(mapaPuntosInteresTipo, nombreTipo, listaTipo);
  } else {
    //Si existe, se extrae la lista
    List *listaTipo = (List *)pairTipo->value;

    //Se inserta al final
    pushBack(listaTipo, puntoInteres);
  }
}

//Funcion para pedir los datos al usuario para un punto de interes
void pedirDatosPuntoInteres(PuntoInteres *puntoInteres) {

  //Variables locales para el punto de ineteres
  char nombre[100];
  char tipo[100];
  char direccion[100];
  char horario[20];
  char descripcion[100];

  printf("\n-----------------------\n");
  printf("\nIngrese el nombre del punto de interes\n");
  scanf(" %99[^\n]", nombre);

  //Se guarda con el espacio de momeria necesario
  puntoInteres->nombre = strdup(nombre);

  printf("\nIngrese el tipo del punto de interes\n");
  scanf(" %99[^\n]", tipo);

  //Se guarda con el espacio de momeria necesario
  puntoInteres->tipo = strdup(tipo);

  printf("\nIngrese la direccion del punto de interes\n");
  scanf(" %99[^\n]", direccion);

  //Se guarda con el espacio de momeria necesario
  puntoInteres->direccion = strdup(direccion);

  printf("\nIngrese el horario del punto de interes\n");
  scanf(" %19[^\n]", horario);

  //Se guarda con el espacio de momeria necesario
  puntoInteres->horario = strdup(horario);

  printf("\nIngrese la descripcion del punto de interes\n");
  scanf(" %99[^\n]", descripcion);

  //Se guarda con el espacio de momeria necesario
  puntoInteres->descripcion = strdup(descripcion);
}

// Opcion 2, se muestran los datos de un punto de interes
void mostrarDatosPuntoInteres(HashMap *mapaPuntosInteres) {

  //Se pregunta al usuario el lugar a buscar
  char nombreBuscar[100];

  printf("\nIngrese el nombre del lugar a buscar\n");
  scanf(" %99[^\n]", nombreBuscar);

  Pair *puntoPedido = searchMap(mapaPuntosInteres, nombreBuscar);

  //Si no existe se manda un mensaje y se retorna
  if (puntoPedido == NULL || puntoPedido->value == NULL) {
    printf("\nNo existe el lugar pedido\n");
    return;
  }

  //Si es que existe se muestran los datos
  PuntoInteres *puntoInteres = (PuntoInteres *)puntoPedido->value;

  printf("\nLugar encontrado\n");
  printf("\nNombre: %s", puntoInteres->nombre);
  printf("\nTipo: %s", puntoInteres->tipo);
  printf("\nDireccion: %s", puntoInteres->direccion);
  printf("\nHorario: %s", puntoInteres->horario);
  printf("\nDescripcion\n%s\n", puntoInteres->descripcion);
}

//Opcion 3, elimina el punto de interes pedido por el usuario
void eliminarPuntoInteres(HashMap *mapaPuntosInteres, HashMap *mapaPuntosInteresTipo) {

    //Se busca al elemento
    char nombreEliminar[100];
    printf("\n-----------------------\n");
    printf("\nIngrese el nombre del lugar a eliminar\n");
    scanf(" %99[^\n]", nombreEliminar);

    // Buscar el punto de interés en el mapa
    Pair *puntoEliminar = searchMap(mapaPuntosInteres, nombreEliminar);

    //Si no exite se manda un mensaje y se retorna
    if (puntoEliminar == NULL || puntoEliminar->value == NULL) {
        printf("\nNo existe el lugar pedido\n");
        return;
    }

    PuntoInteres *puntoInteres = (PuntoInteres *)puntoEliminar->value;

    // Obtener la lista de puntos de interés del mismo tipo
    List *listaPuntoInteres = (List *)searchMap(mapaPuntosInteresTipo, puntoInteres->tipo)->value;

    // Buscar y eliminar el punto de interés en la lista
    Node *current = firstList(listaPuntoInteres);

    while (current != NULL) {
      
        if (strcmp((char *)current->data, nombreEliminar) == 0) {
          
            popCurrent(listaPuntoInteres);
            eraseMap(mapaPuntosInteres, nombreEliminar);

            //Se libera su memoria
            free(puntoInteres->nombre);
            free(puntoInteres->tipo);
            free(puntoInteres->direccion);
            free(puntoInteres->horario);
            free(puntoInteres->descripcion);
            free(puntoInteres);

            return;
        }

        current = nextList(listaPuntoInteres);
    }
}

//Opcion 4, se registra a un turista
void registrarTurista(HashMap *mapaTurista, HashMap *mapaTuristaPais) {

  //Se crea un turista
  Turista *turista = (Turista *)malloc(sizeof(Turista));

  //Se le piden los datos al usuario y se guardan en el turista
  pedirDatosTurista(turista);

  //Se inserta al turista al mapa con clave su pasaporte
  insertMap(mapaTurista, turista->pasaporte, turista);

  //Se registra al turista al mapa por pais
  registrarTuristaPorPais(mapaTuristaPais, turista);
}

//Funcion donde se añaden los datos al turista
void pedirDatosTurista(Turista *turista) {

  //Se crea la lista de sus lugares favoritos
  turista->lugaresFavoritos = createList();

  //Variables locales que se copiaran al turista
  char pasaporte[100];
  char nombre[100];
  char pais[100];

  printf("\nIngrese el pasaporte del turista\n");
  scanf(" %99[^\n]", pasaporte);

  turista->pasaporte = strdup(pasaporte);

  printf("\nIngrese el nombre del turista\n");
  scanf(" %99[^\n]", nombre);

  turista->nombre = strdup(nombre);

  printf("\nIngrese el pais del turista\n");
  scanf(" %99[^\n]", pais);

  turista->pais = strdup(pais);
}

//Funcion para registrar al turista al mapa de pais
void registrarTuristaPorPais(HashMap *mapaTuristasPais, Turista *turista) {

  Pair *pairPais = searchMap(mapaTuristasPais, turista->pais);

  //Se busca si exite la lista de pais en el mapa
  if (pairPais == NULL) {
    //Sino, se crea una lista y se añade al mapa
    List *listaPais = createList();

    pushFront(listaPais, turista);

    insertMap(mapaTuristasPais, turista->pais, listaPais);
  } else {
    //Si existe, se extrae la lista y se añade a ella
    List *listaPais = (List *)pairPais->value;

    pushBack(listaPais, turista);
  }
}

//Opcion 5, Se agrega un lugar favorito a un turista
void agregarLugarFavoritoTurista(HashMap *mapaTurista) {

  //Se busca al turista
  char nombreLugarFavorito[100], pasaporteTurista[100];

  printf("\nIngrese pasaporte de turista\n");
  scanf(" %99[^\n]", pasaporteTurista);

  Pair *turistaBuscado = searchMap(mapaTurista, pasaporteTurista);

  //Si no se encuentra se manda un mensaje y se retorna
  if (turistaBuscado == NULL || turistaBuscado->value == NULL) {
    printf("\nNo existe el turista\n");
    return;
  }

  //Si se encuentra se añade el lugar
  Turista *turista = (Turista *)turistaBuscado->value;

  printf("\nIngrese el nombre de lugar favorito de turista\n");
  scanf(" %99[^\n]", nombreLugarFavorito);

  char *lugarFavorito = strdup(nombreLugarFavorito);
  pushFront(turista->lugaresFavoritos, lugarFavorito);
}

//Opcion 6, se muestran a todos los turistas de un pais
void mostrarTuristasPorPais(HashMap *mapaTuristaPais) {

  //Se busca si existe el pais en el mapa
  char nombrePais[100];

  printf("\nIngrese el pais de los turistas\n");
  scanf(" %99[^\n]", nombrePais);

  Pair *pairPais = searchMap(mapaTuristaPais, nombrePais);

  //Si no existe se manda un mensaje y se retorna
  if (pairPais == NULL) {
    printf("\nNo se encuentra el pais\n");
    return;
  }

  //Si existe se, se ira mostrando uno a uno
  List *listaPais = (List *)pairPais->value;

  Node *current = firstList(listaPais);

  while (current != NULL) {

    Turista *turista = (Turista *)current;

    printf("\nPasaporte: %s", turista->pasaporte);
    printf("\nNombre: %s\n", turista->nombre);

    //Se muestran sus lugares favortios
    mostrarLugaresFavoristos(turista);

    current = nextList(listaPais);
  }
}

//Funcion para mostrar los lugares favoritos de un turista
void mostrarLugaresFavoristos(Turista *turista) {

  Node *current = firstList(turista->lugaresFavoritos);

  //Se es que no tiene lugares favoritos se manda un mesaje y retorna
  if (current == NULL) {
    printf("\nNo tiene lugares de favoritos\n");
    return;
  }

  printf("Lugares favoritos\n");

  while (current != NULL) {

    char *lugarFavorito = (char *)current;

    printf("-%s\n", lugarFavorito);

    current = nextList(turista->lugaresFavoritos);
  }
}

//Opcion 7, se muestran todos los puntos de interes de un tipo
void mostrarPuntosInteresTipo(HashMap *mapaPuntosInteresTipo) {

  //Se busca si existe el tipo en el mapa
  char nombreTipo[100];

  printf("\nIngrese el tipo de punto de interes\n");
  scanf(" %99[^\n]", nombreTipo);

  Pair *pairTipo = searchMap(mapaPuntosInteresTipo, nombreTipo);

  //Si no existe se manda un mensaje y se retorna
  if (pairTipo == NULL) {
    printf("\nNo se encuentra el tipo de punto de interes\n");
    return;
  }
  
  //Si existe se muestran
  List *listaTipo = (List *)pairTipo->value;

  Node *current = firstList(listaTipo);

  printf("\nPuntos de interes de tipo %s\n", nombreTipo);

  while (current != NULL) {

    PuntoInteres *puntoInteres = (PuntoInteres *)current;

    printf("-%s\n", puntoInteres->nombre);

    current = nextList(listaTipo);
  }
}

//Opcion 8, se importan CSV a mapas
void importarCSV(HashMap *mapaPuntosInteres, HashMap *mapaTuristas,
                 HashMap *mapaTuristasPais, HashMap *mapaPuntosInteresTipo) {

  //Se pregunta si importar puntos de interes y turistas
  
  int opcion = 0;

  printf("\nQuiere importar datos de puntos de interes?\n");
  printf("Opcion ( 1 = Si, 0 = No )\n");
  scanf(" %d", &opcion);

  if(opcion){
      importarPuntosInteres(mapaPuntosInteres, mapaPuntosInteresTipo);
  }

  opcion = 0;
  
  printf("\nQuiere importar datos de turista?\n");
  printf("Opcion ( 1 = Si, 0 = No )\n");
  scanf(" %d", &opcion);

  if(opcion){
      importarTuristas(mapaTuristas, mapaTuristasPais);
  }
}

//Funcion para importar un CSV con datos para puntos de interes
void importarPuntosInteres(HashMap *mapaPuntosInteres,
                           HashMap *mapaPuntosInteresTipo) {

  //Se pregunta por el nombe y se añade .csv al final
  char nombreArchivo[100];

  printf("\nIngrese el nombre del archivo CSV para importar puntos de "
         "interes(sin .csv)\n");
  scanf(" %95[^\n]", nombreArchivo);

  strcat(nombreArchivo, ".csv");

  //Se abre el archivo
  FILE *archivo = fopen(nombreArchivo, "r");

  if (archivo == NULL) {
    printf("\nError al abrir el archivo\n");
    return;
  }

  char linea[256];

  //Se borra la cabezera
  fgets(linea, sizeof(linea), archivo);

  while (fgets(linea, sizeof(linea), archivo)) {

    //Para evitar lineas vacias
    char *newline = strchr(linea, '\n');
    if (newline != NULL) {
      *newline = '\0';
    }

    //Si la linea esta vacia, se salta
    if (strlen(linea) == 0) {
      continue;
    }

    //Se crea un punto de interes
    PuntoInteres *puntoInteres = (PuntoInteres *)malloc(sizeof(PuntoInteres));
    if (puntoInteres == NULL) {
      printf("\nError al reservar memoria para el punto turistico.\n");
      return;
    }

    char *token;
    int tokenCount = 0;

    token = strtok(linea, ",");

    /*
        0 - nombre
        1 - tipo
        2 - direccion
        3 - horario
        4 - descripcion
    */

    while (token != NULL) {

      switch (tokenCount) {
      case 0:
        puntoInteres->nombre = strdup(token);
        break;
      case 1:
        puntoInteres->tipo = strdup(token);
        break;
      case 2:
        puntoInteres->direccion = strdup(token);
        break;
      case 3:
        puntoInteres->horario = strdup(token);
        break;
      case 4:
        puntoInteres->descripcion = strdup(token);
        break;
      }

      token = strtok(NULL, ",");
      tokenCount++;
    }

    //Se inserta al mapa
    insertMap(mapaPuntosInteres, puntoInteres->nombre, puntoInteres);

    //Se insertal mapa por tipo
    registrarPuntoInteresTipo(mapaPuntosInteresTipo, puntoInteres);
  }

  fclose(archivo);
}

//Funcion para importar un CSV con datos para turista
void importarTuristas(HashMap *mapaTuristas, HashMap *mapaTuristasPais) {

  //Se pregunta por el nombe y se añade .csv al final
  char nombreArchivo[100];

  printf(
      "\nIngrese el nombre del archivo CSV para importar turistas(sin .csv)\n");
  scanf(" %95[^\n]", nombreArchivo);

  strcat(nombreArchivo, ".csv");

  //Se abre el archivo
  FILE *archivo = fopen(nombreArchivo, "r");

  if (archivo == NULL) {
    printf("\nError al abrir el archivo\n");
    return;
  }

  char linea[256];

  //Se salta la cabezera
  fgets(linea, sizeof(linea), archivo);

  while (fgets(linea, sizeof(linea), archivo)) {

    char *newline = strchr(linea, '\n');
    if (newline != NULL) {
      *newline = '\0';
    }

    if (strlen(linea) == 0) {
      continue;
    }

    Turista *turista = (Turista *)malloc(sizeof(Turista));
    if (turista == NULL) {
      printf("\nError al reservar memoria para el turista.\n");
      return;
    }

    //Se crea su lista de lugares favoritos
    turista->lugaresFavoritos = createList();

    char *token;
    int tokenCount = 0;

    token = strtok(linea, ",");

    /*
        0 - pasaporte
        1 - nombre
        2 - pais
        3+ - lugares favoritos
    
    */
    
    while (token != NULL) {

      switch (tokenCount) {
      case 0:
        turista->pasaporte = strdup(token);
        break;
      case 1:
        turista->nombre = strdup(token);
        break;
      case 2:
        turista->pais = strdup(token);
        break;
      default:
        pushBack(turista->lugaresFavoritos, strdup(token));
        break;
      }

      //Se cambia el token por los lugares favoritos
      token = (tokenCount < 2) ? strtok(NULL, ",") : strtok(NULL, ";");
      tokenCount++;
    }

    //Se inserta al mapa
    insertMap(mapaTuristas, turista->pasaporte, turista);

    //Se inserta al mapa de pais
    registrarTuristaPorPais(mapaTuristasPais, turista);
  }

  fclose(archivo);
}

//Opcion 9, exportacion en archivos CSV
void exportarCSV(HashMap *mapaPuntosInteres, HashMap *mapaTuristas) {

  //Se pregunta si exportar puntos de interes y turistas
  
  int opcion = 0;

  printf("\nQuiere exportar datos de puntos de interes?\n");
  printf("Opcion ( 1 = Si, 0 = No )\n");
  scanf(" %d", &opcion);

  if(opcion){
      //Revisa si hay datos en el mapa
      if (firstMap(mapaPuntosInteres) != NULL) exportarPuntosInteres(mapaPuntosInteres);
  }
  
  opcion = 0;

  printf("\nQuiere exportar datos de turista?\n");
  printf("Opcion ( 1 = Si, 0 = No )\n");
  scanf(" %d", &opcion);

  if(opcion){
    //Se revisa su hay datos en el mapa
    if (firstMap(mapaTuristas) != NULL)  exportarTuristas(mapaTuristas);
  }
}

//Funcion para exportar puntos de interes a CSV
void exportarPuntosInteres(HashMap *mapaPuntosInteres) {

  //Se crea el nombre 
  char nombreArchivo[100];

  printf("\nIngrese el nombre del archivo CSV para exportar puntos de "
         "interes(sin .csv)\n");
  scanf(" %95[^\n]", nombreArchivo);

  strcat(nombreArchivo, ".csv");

  FILE *archivo = fopen(nombreArchivo, "w");

  if (archivo == NULL) {
    printf("\nError al abrir el archivo\n");
    return;
  }

  //Se añade la cabezera
  fprintf(archivo, "Nombre,Tipo,Dirección,Horario,Descripción\n");

  Pair *current = firstMap(mapaPuntosInteres);

  while (current != NULL) {

    //Se van añadiendo los datos de cada punto de interes
    PuntoInteres *puntoInteres = (PuntoInteres *)current->value;

    fprintf(archivo, "%s,%s,%s,%s,%s", puntoInteres->nombre, puntoInteres->tipo,
            puntoInteres->direccion, puntoInteres->horario,
            puntoInteres->descripcion);

    fprintf(archivo, "\n");

    current = nextMap(mapaPuntosInteres);
  }

  fclose(archivo);
}

//Funcion para exportar turistas a CSV
void exportarTuristas(HashMap *mapaTuristas) {

  //Se crea el archivo
  char nombreArchivo[100];

  printf(
      "\nIngrese el nombre del archivo CSV para exportar turistas(sin .csv)\n");
  scanf(" %95[^\n]", nombreArchivo);

  strcat(nombreArchivo, ".csv");

  FILE *archivo = fopen(nombreArchivo, "w");

  if (archivo == NULL) {
    printf("\nError al abrir el archivo\n");
    return;
  }

  //Se añade la cabezera
  fprintf(archivo, "Pasaporte,Nombre,País,Lugares Favoritos\n");

  Pair *current = firstMap(mapaTuristas);

  while (current != NULL) {

    //Se van añadiendo turista a turista
    Turista *turista = (Turista *)current->value;

    fprintf(archivo, "%s,%s,%s", turista->pasaporte, turista->nombre,
            turista->pais);

    Node *lugarFavorito = firstList(turista->lugaresFavoritos);

    if (lugarFavorito != NULL) {
      fprintf(archivo, ",%s", (char *)lugarFavorito);
      lugarFavorito = nextList(turista->lugaresFavoritos);
    }

    while (lugarFavorito != NULL) {
      fprintf(archivo, ";%s", (char *)lugarFavorito);
      lugarFavorito = nextList(turista->lugaresFavoritos);
    }

    fprintf(archivo, "\n");

    current = nextMap(mapaTuristas);
  }

  fclose(archivo);
}

// Función para liberar memoria de los mapas
void freeMap(HashMap *map) {
  if (map == NULL)
    return;

  Pair *pair = firstMap(map);
  while (pair != NULL) {
    // Si el valor es un PuntoInteres, liberamos su memoria
    if (pair->value != NULL) {
      PuntoInteres *puntoInteres = (PuntoInteres *)pair->value;
      free(puntoInteres->nombre);
      free(puntoInteres->tipo);
      free(puntoInteres->direccion);
      free(puntoInteres->horario);
      free(puntoInteres->descripcion);
      free(puntoInteres);
    }
    // Si el valor es un Turista, liberamos su memoria
    else if (pair->value != NULL) {
      Turista *turista = (Turista *)pair->value;
      free(turista->pasaporte);
      free(turista->nombre);
      free(turista->pais);

      // Liberar la memoria de los lugares favoritos y la lista
      Node *current = firstList(turista->lugaresFavoritos);
      while (current != NULL) {
        free(current->data); // Liberar cada elemento
        current = nextList(turista->lugaresFavoritos);
      }
      cleanList(turista->lugaresFavoritos);

      free(turista);
    }
    pair = nextMap(map);
  }
  freeMap(map);
}

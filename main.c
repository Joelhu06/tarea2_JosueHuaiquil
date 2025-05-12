#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  char id[100];
  List *artists;
  char album_name[100];
  char track_name[100];
  int tempo;
  char track_genre[100];
} Song;
  
// Función que muestra el menú principal
void mostrarMenuPrincipal()
{
  limpiarPantalla();
  puts("========================================");
  puts("       BASE DE DATOS DE CANCIONES");
  puts("========================================");

  puts("1) CARGAR CANCIONES");
  puts("2) BUSCAR POR GENERO");
  puts("3) BUSCAR POR ARTISTA");
  puts("4) BUSCAR POR TEMPO");
  puts("5) SALIR");

  puts("========================================");
}


// Función para cargar las canciones desde un archivo CSV
void cargarCanciones(HashMap *SBG, HashMap *SBA, HashMap *SBT) 
{
  // Intenta abrir el archivo CSV que contiene los datos de las canciones
  FILE *archivo = fopen("data/song_dataset_.csv", "r");
  if (archivo == NULL)
  {
    perror("Error al abrir el archivo"); // Informa si el archivo no puede abrirse
    return;
  } 

  char **campos;
  // Leer y parsear una línea del archivo CSV. La función devuelve un array de strings, donde cada elemento representa un campo de la línea CSV procesada.
  campos = leer_linea_csv(archivo, ','); // Lee los encabezados del CSV

  // Lee cada línea del archivo CSV hasta el final
  while ((campos = leer_linea_csv(archivo, ',')) != NULL)
  {
    // Se leen los datos del CSV y se guardan
    Song *cancion = (Song *) malloc(sizeof(Song));
    strcpy(cancion->id, campos[0]);
    strcpy(cancion->album_name, campos[3]);
    strcpy(cancion->track_name, campos[4]);
    strcpy(cancion->track_genre, campos[20]);
    cancion->artists = split_string(campos[2], ";");     
    cancion->tempo = atoi(campos[18]);

    // Se inserta en el mapa SBG las canciones por genero
    insertMap(SBG, cancion->track_genre, cancion);

    // Obtiene el primer artista de la lista de artistas de la canción
    char *artista = list_first(cancion->artists);
    // Itera sobre cada artísta de la canción
    while (artista != NULL) {
      // Busca el artísta en el mapa SBA
      Pair *pairArtist = searchMap(SBA, artista);

      // Si el artista no existe en el mapa, se crea una nueva lista y se agrega al mapa
      if (pairArtist == NULL) {
        List *new_list = list_create();
        list_pushBack(new_list, cancion);
        insertMap(SBA, strdup(artista), new_list);
      } else {
        // Si el artista ya existe en el mapa, obtén la lista y se agrega la canción
        List *genre_list = (List *)pairArtist->value;
        list_pushBack(genre_list, cancion);
      }

      // Avanza al siguiente artista en la lista
      artista = list_next(cancion->artists);
    }
    
    // Se insertan en el mapa SBT las canciones según el tempo que tengan
    if (cancion->tempo < 80) insertMap(SBT, "Lentas", cancion);
    else if (cancion->tempo >= 80 && cancion->tempo < 120) insertMap(SBT, "Moderadas", cancion);
    else insertMap(SBT, "Rapidas", cancion);
  }
  fclose(archivo); // Cierra el archivo después de leer todas las líneas
}

void imprimirPrimerasCanciones(HashMap *mapa) {
  Pair *par = firstMap(mapa);
  while (par != NULL) {
    printf("\n=== %s ===\n", (char *)par->key); // Clave del mapa: género, artista o tempo

    List *lista = (List *)par->value;
    int count = 0;

    for (Song *cancion = list_first(lista); cancion != NULL && count < 10; cancion = list_next(lista)) {
      printf("CANCION: %s\n", cancion->track_name);
      printf("ALBUM: %s\n", cancion->album_name);
      printf("TEMPO: %d\n", cancion->tempo);
      printf("ARTISTAS: ");

      // Imprimir artistas
      int primer_artista = 1;
      for (char *artista = list_first(cancion->artists); artista != NULL; artista = list_next(cancion->artists)) {
        if (!primer_artista) printf(", ");
        printf("%s", artista);
        primer_artista = 0;
      }

      printf("\n------------------------\n");
      count++;
    }

    par = nextMap(mapa);
  }
}

// Función que busca las canciones por sus generos
void buscarPorGenero(HashMap *SBG)
{
  limpiarPantalla();
  char genero[100];
  printf("=======================================\n");
  printf("          BUSQUEDA POR GENERO\n");
  printf("=======================================\n");
  printf("INGRESE EL GENERO DE LA CANCION: ");
  scanf("%s", genero); // Lee el genero del teclado

  Pair *par = searchMap(SBG, genero);
  
  if (par != NULL) {
    List* lista = (List *) par->value;
    Song *cancion = list_first(lista);
    long count = 0;

    for (Song *cancion = list_first(lista); cancion != NULL; cancion = list_next(lista)) 
    {
      printf("CANCION: %s\n", cancion->track_name);
      printf("ALBUM: %s\n", cancion->album_name);
      printf("TEMPO: %d\n", cancion->tempo);
      printf("ARTISTAS: ");

      // Imprimir artistas
      int primer_artista = 1;
      for (char *artista = list_first(cancion->artists); artista != NULL; artista = list_next(cancion->artists))
      {
        if (!primer_artista) printf(", ");
        printf("%s", artista);
        primer_artista = 0;
      }

      printf("\n------------------------\n");
      count++;
    }
  }
  printf("========================================\n");
}

void buscarPorArtista(HashMap *SBA)
{
  limpiarPantalla();

  printf("========================================\n");
  printf("          BUSQUEDA POR ARTISTA\n");
  printf("========================================\n");

  char artista[100];

  // Solicita al usuario el ID de la película
  printf("INGRESE EL NOMBRE DEL ARTISTA: ");
  getchar(); // limpia el \n anterior
  fgets(artista, 100, stdin);
  artista[strcspn(artista, "\n")] = '\0'; // elimina salto de línea

  Pair *pair = searchMap(SBA, artista);
  if(pair == NULL) printf("NO SE ENCONTRO EL ARTISTA BUSCADO\n");
  else
  {
    List* lista = pair->value;
    Song *cancion = list_first(lista);
    long count = 0;

    for (Song *cancion = list_first(lista); cancion != NULL; cancion = list_next(lista)) 
    {
      printf("CANCION: %s\n", cancion->track_name);
      printf("ALBUM: %s\n", cancion->album_name);
      printf("TEMPO: %d\n", cancion->tempo);
      printf("ARTISTA BUSCADO: %s", artista);

      printf("\n------------------------\n");
      count++;
    }
  }
  printf("========================================\n");
}

void buscarPorTempo(HashMap *SBT)
{
  limpiarPantalla();

  printf("========================================\n");
  printf("           BUSQUEDA POR TEMPO\n");
  printf("========================================\n");

  char tempo[100];
  printf("INGRESE EL TEMPO DE LA CANCION (Lentas, Moderadas, Rapidas): ");
  getchar();
  scanf("%s", tempo); // Lee el ID del teclado

  Pair *par = searchMap(SBT, tempo);
  
  if (par != NULL) {
    List* lista = (List *) par->value;
    Song *cancion = list_first(lista);
    long count = 0;

    for (Song *cancion = list_first(lista); cancion != NULL; cancion = list_next(lista)) 
    {
      printf("CANCION: %s\n", cancion->track_name);
      printf("ALBUM: %s\n", cancion->album_name);
      printf("TEMPO: %d\n", cancion->tempo);
      printf("ARTISTAS: ");

      // Imprimir artistas
      int primer_artista = 1;
      for (char *artista = list_first(cancion->artists); artista != NULL; artista = list_next(cancion->artists))
      {
        if (!primer_artista) printf(", ");
        printf("%s", artista);
        primer_artista = 0;
      }

      printf("\n------------------------\n");
      count++;
    }
  }
  printf("========================================\n");
}

int main() 
{
  char opcion; //Variable para almacenar una opción ingresada por el usuario

  // Crea los mapas para almacenar las canciones.
  HashMap *songsByGenre = createMap();
  HashMap *songsByArtist = createMap();
  HashMap *songsByTempo = createMap();

  do
  {
    mostrarMenuPrincipal();
    printf("INGRESE SU OPCION: ");
    scanf(" %c", &opcion);

    switch (opcion)
    {
      case '1':
        cargarCanciones(songsByGenre, songsByArtist, songsByTempo);
        break;
      case '2':
        buscarPorGenero(songsByGenre);
        break;
      case '3':
        buscarPorArtista(songsByArtist);
        break;
      case '4':
        buscarPorTempo(songsByTempo);
        break;
    }
    presioneTeclaParaContinuar();
  } while (opcion != '5');

  return 0;
} 
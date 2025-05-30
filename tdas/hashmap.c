#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"
#include "list.h"

#define INITIAL_CAPACITY 100000


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash(char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

void insertMap(HashMap * map, char * key, void * value)
{
    int i = hash(key, map->capacity);

    while (map->buckets[i] != NULL && map->buckets[i]->key != NULL)
    {
        if (is_equal(map->buckets[i]->key, key)) {
            // Ya existe la key → agregar el nuevo value a la lista
            List *lista = (List *) map->buckets[i]->value;
            list_pushBack(lista, value);
            return;
        }
        i = (i + 1) % map->capacity;
    }

    // No existe la key → crear nueva lista con el value
    List *lista = list_create();
    list_pushBack(lista, value);

    Pair *par = createPair(key, lista);
    map->buckets[i] = par;
    map->current = i;
    map->size++;
}

void enlarge(HashMap * map) 
{
    enlarge_called = 1; //no borrar (testing purposes)

    Pair **buckets = (*map).buckets;
    long capacidad = (*map).capacity;

    (*map).capacity *= 2;

    (*map).buckets = (Pair **) calloc ((*map).capacity, sizeof(Pair *));
    (*map).size = 0;
    (*map).current = -1;

    for (long i = 0 ; i < capacidad ; i++)
        if (buckets[i] != NULL && buckets[i]->key != NULL) insertMap(map, buckets[i]->key, buckets[i]->value);

    free(buckets); 
}


HashMap * createMap()
{
    HashMap *newHashMap = (HashMap *) malloc (sizeof(HashMap));
    (*newHashMap).buckets = (Pair **) calloc (INITIAL_CAPACITY, sizeof(Pair *));
    (*newHashMap).capacity = INITIAL_CAPACITY;
    (*newHashMap).current = -1;
    (*newHashMap).size = 0;
    return newHashMap;
}

void eraseMap(HashMap * map,  char * key) 
{    
    Pair *par = searchMap(map, key);
    if (par == NULL) return;
    (*par).key = NULL;
    (*map).size--; 
}

Pair * searchMap(HashMap * map,  char * key) 
{   
    int i = hash(key, (*map).capacity);
    while ((*map).buckets[i] != NULL)
    {
        if ((*map).buckets[i]->key != NULL && is_equal(map->buckets[i]->key, key))
        {
            (*map).current = i;
            return (*map).buckets[i];    
        }
        i = (i + 1) % (*map).capacity;
    }
    return NULL;
}

Pair * firstMap(HashMap * map) 
{
    int i = 0;
    while (i < (*map).capacity)
    {   
        if ((*map).buckets[i] != NULL && (*map).buckets[i]->key != NULL)
        {
            (*map).current = i;
            return (*map).buckets[i];    
        }
        i++;
    }
    return NULL;
}

Pair * nextMap(HashMap * map)
{
    int i = (*map).current + 1;
    while (i < (*map).capacity)
    {   
        if ((*map).buckets[i] != NULL && (*map).buckets[i]->key != NULL)
        {
            (*map).current = i;
            return (*map).buckets[i];    
        }
        i++;
    }
    return NULL;
}
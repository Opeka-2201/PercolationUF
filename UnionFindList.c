#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "UnionFind.h"

typedef struct node_t Node;
typedef struct list_t List;

Node* nodeCreate(List*,Node*,size_t);
List* listCreate(Node*,Node*,size_t);

struct node_t{
  List* list;
  Node* next;
  size_t label;
};

struct list_t{
  Node* start;
  Node* tail;
  size_t length;
};

struct union_find_t{
  List** ensembles;
  Node** nodeTable;
  size_t nbItems;
  size_t nbEnsembles;
};

UnionFind* ufCreate(size_t n_items){
  UnionFind* unionFind = malloc(sizeof(UnionFind));
  if(unionFind == NULL){
    fprintf(stderr, "%s\n","Erreur d allocation de mémoire pour l'unionFind (liste)" );
    abort();
  }

  Node** nodes = malloc(n_items*sizeof(Node*));
  List** lists = malloc(n_items*sizeof(List*));

  if(nodes == NULL || lists == NULL){
    fprintf(stderr, "%s\n","Erreur d allocation de mémoire pour les ensembles ou les noeuds (liste)");
    abort();
  }

  for(size_t i = 0; i < n_items; i++){
    nodes[i] = nodeCreate(NULL,NULL,i);
    lists[i] = listCreate(nodes[i],nodes[i],1);
    nodes[i]->list = lists[i];
  }

  unionFind->ensembles = lists;
  unionFind->nodeTable = nodes;
  unionFind->nbItems = n_items;
  unionFind->nbEnsembles = n_items;

  return unionFind;
}

void ufFree(UnionFind* union_find){
  for (size_t i = 0; i<union_find->nbItems; i++)
  {
    free(union_find->nodeTable[i]);
    free(union_find->ensembles[i]);
  }
  free(union_find->nodeTable);
  free(union_find->ensembles);
  free(union_find);
}

ufStatus ufUnion(UnionFind* union_find, size_t item1, size_t item2){
  List* list1 = union_find->nodeTable[item1]->list;
  List* list2 = union_find->nodeTable[item2]->list;

  size_t length1 = list1->length;
  size_t length2 = list2->length;

  if (list1 == NULL || list2 == NULL)
    return UF_ERROR;

  if (length2 > length1)
    return ufUnion(union_find,item2,item1);

  if (list1 == list2)
    return UF_SAME;

  list1->tail->next = list2->start;
  list1->tail = list2->tail;

  Node* current2 = list2->start;
  while (current2){
    current2->list = list1;
    current2 = current2->next;
  }

  list2->start = NULL;
  list2->tail = NULL;
  list2->length = 0;

  list1->length+=length2;
  union_find->nbEnsembles--;

  return UF_MERGED;
}

size_t ufFind(const UnionFind* union_find, size_t item){
  return union_find->nodeTable[item]->list->start->label;
}

size_t ufComponentsCount(const UnionFind* union_find){
  return union_find->nbEnsembles;
}

Node* nodeCreate(List* list, Node* next, size_t label){
  Node* toReturn = malloc(sizeof(Node));
  if(toReturn == NULL){
    fprintf(stderr, "%s\n","Erreur d allocation de mémoire pour un noeud (liste)" );
    abort();
  }

  toReturn->list = list;
  toReturn->next = next;
  toReturn->label = label;

  return toReturn;
}

List* listCreate(Node* start, Node* tail, size_t length){
  List* toReturn = malloc(sizeof(List));
  if(toReturn == NULL){
    fprintf(stderr, "%s\n","Erreur d allocation de mémoire pour une liste (liste)" );
    abort();
  }

  toReturn->start = start;
  toReturn->tail = tail;
  toReturn->length = length;

  return toReturn;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Percolation.h"
#include "UnionFind.h"

struct percolation_t{
  size_t size;
  UnionFind* unionFind;
  bool** boolMatrix;
}; // typedef percolation_t -> Percolation in .h

Percolation* percCreate(size_t n){
  Percolation* newPerc = (Percolation*)malloc(sizeof(Percolation));
  bool** boolToStock = (bool**)calloc(n,sizeof(bool*));
  for(size_t i = 0; i < n; i++)
    boolToStock[i] = (bool*)calloc(n,sizeof(bool));

  UnionFind* unionToStock = ufCreate(n*n);
  for(size_t i = 0 ; i < n ; i++){
      fprintf(stderr,"%zu\n",i);
      ufUnion(unionToStock,0,i); //On met la premiere ligne dans un ensemble
      fprintf(stderr,"%zu\n",i);
      ufUnion(unionToStock,n*(n-1),n*(n-1) + i); // On met la derniere ligne dans un ensemble
      fprintf(stderr,"%zu\n",i);
  }

  newPerc->boolMatrix = boolToStock;
  newPerc->unionFind = unionToStock;
  newPerc->size = n;
  fprintf(stderr,"Aurevoir la zone 51\n");
  return newPerc;
}

void percFree(Percolation* perc){
  for(size_t i = 0;i<perc->size;i++)
    free(perc->boolMatrix[i]);
  free(perc->boolMatrix);
  ufFree(perc->unionFind);
  free(perc);
}

size_t percSize(const Percolation* perc){
  return perc->size;
}

void percOpenCell(Percolation *perc, size_t row, size_t col){
  UnionFind* unionFind = perc->unionFind;
  size_t size = perc->size;
  int label = row*size + col;
  bool** boolMatrix = perc->boolMatrix;

  if(row > size-1 || col > size-1){
    fprintf(stderr, "%s\n","La cellule n est pas dans le domaine (percOpenCell)" );
    return;
  }

  if(boolMatrix[row][col]==true)
    return;

  boolMatrix[row][col] = true;
  if(row!=0 && percIsCellOpen(perc,row-1,col)) //top
      ufUnion(unionFind,label-size,label);
  if(col!=0 && percIsCellOpen(perc,row,col-1))//left
      ufUnion(unionFind,label-1,label);
  if(row+1<size && percIsCellOpen(perc,row+1,col)) //down
      ufUnion(unionFind,label+size,label);
  if(col+1<size && percIsCellOpen(perc,row,col+1)) //right
      ufUnion(unionFind,label+1,label);
}

bool percIsCellOpen(const Percolation *perc, size_t row, size_t col){
  size_t size = perc->size;
  if(col > size-1 || row > size-1){
    fprintf(stderr, "%s\n","La cellule n est pas dans le domaine (percIsCellOpen)" );
    return false;
  }

    return perc->boolMatrix[row][col];
}

bool percIsCellFull(const Percolation* perc, size_t row, size_t col){
  size_t size = perc->size;

  if(col > size-1 || row > size-1){
    fprintf(stderr, "%s\n","La cellule n est pas dans le domaine (percIsCellFull)" );
    return false;
  }

  if(ufFind(perc->unionFind,0)==ufFind(perc->unionFind,row*size+col) && perc->boolMatrix[row][col])
    return true;
  else
    return false;
}

bool percPercolates(const Percolation *perc){
  if (perc->size == 1 && !perc->boolMatrix[0][0])
    return false;
  if(ufFind(perc->unionFind,0)==ufFind(perc->unionFind,(perc->size)*(perc->size)-1))
    return true;
  else
    return false;
}

void percPrint(const Percolation *perc, FILE *out){
  size_t size = perc->size;
  for(size_t i = 0;i<size;i++){
    fprintf(out,"|");
    for(size_t j = 0;j<size;j++){
        if(percIsCellOpen(perc,i,j)){
          if(percIsCellFull(perc,i,j))
            fprintf(out,"o");
          else
            fprintf(out," ");
        }
        else{
          fprintf(out,"#");
        }
    }
    fprintf(out,"|\n");
  }
}

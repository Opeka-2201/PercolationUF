#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Percolation.h"
#include "UnionFind.h"
#include "Threshold.h"

static void quicksort(double a[], int n);

double* thresholdEstimate(size_t N, size_t T)
{
  int randRow, randCol;
  double* stats=calloc(3,sizeof(double));
  double* results = calloc(T,sizeof(double));
  double countOpen;
  for (size_t i = 0; i < T ; i++)
  {
    Percolation* perc = percCreate(N);
    countOpen = 0;
    while (percPercolates(perc)!=true)
    {
      do {
        randRow=rand()%N;
        randCol=rand()%N;
      }while(percIsCellOpen(perc,randRow,randCol));
      percOpenCell(perc,randRow,randCol);
      countOpen=countOpen+1;
      percPercolates(perc);
    }
    stats[1] += countOpen/(double)(N*N);
    results[i]=countOpen/(double)(N*N);

    percFree(perc);

  }
  quicksort(results,T);
  stats[0]=results[(int)(0.05*T)];
  stats[1]/=T;
  stats[2]=results[(int)(0.95*T)];
  return stats;
}

void quicksort(double a[], int n) {
    if (n <= 1) return;
    double p = a[n/2];
    double b[n], c[n];
    int i, j = 0, k = 0;
    for (i=0; i < n; i++) {
        if (i == n/2) continue;
        if ( a[i] <= p) b[j++] = a[i];
        else            c[k++] = a[i];
    }
    quicksort(b,j);
    quicksort(c,k);
    for (i=0; i<j; i++) a[i] =b[i];
    a[j] = p;
    for (i= 0; i<k; i++) a[j+1+i] =c[i];
  }

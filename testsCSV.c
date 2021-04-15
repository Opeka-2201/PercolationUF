#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Threshold.h"

int main(){
  FILE* output = fopen("tree.csv","aw");
  double* stats;
  clock_t start,stop;
  double deltaT;
  for(int N = 1; N <= 300; N++){
    start = clock();
    stats = thresholdEstimate(N,100);
    stop = clock();
    deltaT = (double)(stop-start)/CLOCKS_PER_SEC;
    fprintf(stdout, "%d\n",N);
    fprintf(output,"%d,%lf,%lf,%lf,%lf\n",N,stats[0],stats[1],stats[2],deltaT);
  }
  fclose(output);
  return 0;
}

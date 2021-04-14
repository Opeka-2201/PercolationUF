/* ------------------------------------------------------------------------- *\
 * NOM
 *      threshold
 * SYNOPSIS
 *      threshold [-s size] [-t num_exp] [-r r_seed]
 * DESCIRPTION
 *      Computes the percolation thresholds
 *      -s size     The size of the percolation grid (the number of cells on a
 *                  side of the grid). Default: 10.
 *      -t num_exp  The number of iterations to estimate the threshold. Default: 100
 *      -r r_seed   The random seed. If not provided, the generator will be set
 *                  by the current time.
 \* ------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Threshold.h"

int main(int argc, char** argv)
{
    //--------------------------- PARSE COMMAND LINE -------------------------
    unsigned seed = (unsigned) time(NULL);

    size_t size = 10;
    size_t numberExp = 100;
    int argi = 1; // Ideally this should be a size_t (historical reasons)
    while(argi < argc)
    {
        if(strcmp(argv[argi], "-s") == 0)
        {
            size_t inputSize;
            if(sscanf (argv[++argi], "%zu", &inputSize) != 1)
            {
                fprintf(stderr, "%s\n", "Aborting; size should be an unsigned "
                                        "integer.");
                exit(EXIT_FAILURE);
            }
            size = inputSize;
        } else if(strcmp(argv[argi], "-t") == 0) {
            size_t inputNumberExp;
            if(sscanf (argv[++argi], "%zu", &inputNumberExp) != 1)
            {
                fprintf(stderr, "%s\n", "Aborting; number of experiments should be an unsigned "
                                        "integer.");
                exit(EXIT_FAILURE);
            }
            numberExp = inputNumberExp;
        } else if(strcmp(argv[argi], "-r") == 0) {
            unsigned inputSeed;
            if(sscanf (argv[++argi], "%u", &inputSeed) != 1)
            {
                fprintf(stderr, "%s\n", "Aborting; the random seed should be an "
                                        "unsigned integer.");
                exit(EXIT_FAILURE);
            }
            seed = inputSeed;
        } else {
            fprintf(stderr, "%s '%s'\n", "Aborting; unknown parameter",
                    argv[argi]);
            fprintf(stderr, "%s %s %s\n", "Usage:", argv[0], "[-s size] "
                    "[-r random_seed] [-f file]");
            exit(EXIT_FAILURE);
        }
        argi++;
    }

    //---------------------------- INITIATE PROGRAM --------------------------
    srand(seed);

    //------------------------ BUILD MAZE AND PRINT IT -----------------------
    double* stats = thresholdEstimate(size, numberExp);

    if(!stats)
    {
        fprintf(stderr, "%s\n", "Error while estimating the threshold.");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout,"Estimated threshold: %lf\n", stats[1]);
    fprintf(stdout,"Centiles:\n");
    fprintf(stdout,"-  5th: %lf\n", stats[0]);
    fprintf(stdout,"- 95th: %lf\n", stats[2]);
    free(stats);

    exit(EXIT_SUCCESS);
}

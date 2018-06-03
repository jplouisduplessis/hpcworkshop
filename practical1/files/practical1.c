#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <assert.h>

/*This is a simple C program that makes use of the OpenMP library to perform computations
in parallel. To compile it, you will need to make use of the -fopenmp flag. */

//The program takes as input the output file name and the number of characters to generate
int main(int argc, char *args[])
{
    assert(argc == 3);
    {
        long charCount;
        sscanf(args[2], "%ld", &charCount);
        char *output = calloc(charCount, sizeof(char));
        char *fname = args[1];
        printf("Generating %ld characters...\n", charCount);
        #pragma omp parallel
        for (int i = 0; i < charCount; i++)
        {
            int t = rand() % 100;
            if (t > 50 && t < 95)
                output[i] = ' ';
            else if (t >= 95)
                output[i] = '\n';
            else
            {
                output[i] = 'a' + rand() % 26;
            }
        }
        //Write output to file
        FILE *fPtr = fopen(fname, "w");
        fprintf(fPtr, "%s", output);
        fclose(fPtr);
    }

    return EXIT_SUCCESS;
}
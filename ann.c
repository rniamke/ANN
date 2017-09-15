#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <math.h>
#include <signal.h>

struct {
    int size;
    int used;
    float *data;
} lv;

struct {
    int size;
    int used;
    int *data;
    void *w;
} layers;

void weightInit() {

}

float sigmoid(float x) {
  return ( 1 / ( 1 + exp( -x ) ) );
}

void readdata(char *file, const char *delim, size_t dim) {
    FILE *f;
    char *line;
    char *tok;

    size_t linesize = 1024;

    f = fopen(file, "r");
    if (!f) {
        perror("Cannot read file ");
        exit(1);
    }

    line = malloc(linesize);
    if (!line) {
        perror("Cannot allocate memory ");
        exit(1);
    }

    lv.size = dim;
    // lv.used = 0;
    lv.data = malloc(dim * sizeof(float));
    if (!lv.data) {
        perror("Cannot read file ");
        exit(1);
    }

    while(1) {
        fpos_t pos;
        int r = fgetpos(f, &pos);
        if (r == 0) { /* succesful */
            if ( fgets(line, linesize, f) == NULL )
                break;
            while ( strlen(line) == linesize-1 ) {
                line = realloc(line, linesize *= 2);
                if (!line) {
                    perror("Cannot allocate memory ");
                    exit(1);
                }
                fsetpos(f, &pos);
                fgets(line, linesize, f);
            }
        }
        /* We have now a line in our buffer "line" */
        /* chopping it up according to line delimiter */
        lv.used = 0;
        tok = strtok(line, delim);
        while (tok != NULL){
            lv.data[lv.used++] = atof(tok);
            tok = strtok(NULL, delim);
        }
        raise(SIGUSR1);
    }
    free(lv.data);
    free(line);
    fclose(f);
}

void neuron(int sig) {
    int i;
    for(i=0; i<lv.size; i++)
        printf("%f\t", lv.data[i]);
    printf("\n");
    return;
}

void perceptron(float *input[]) {

}

void parseCmdLine(int argc, char *argv[]) {
// -I : inputSize
// -a : arch = MLP (the only type of NN right now implemented - fully connected FFNN)
// -h : hidden layers description : comma-separated neurons number per layer. Ex: -h3,2,1 

    int i;
    for (i=1; i<argc; i++) {
        if (strncmp(argv[i], "-I", 2)) {
        }
        if (strncmp(argv[i], "-I", 2)) {
        }
        if (strncmp(argv[i], "-I", 2)) {
        }
    }
    return;
}


int main(int argc, char *argv[])
{
    parseCmdLine(argc, argv);
    weightInit();
    //printf("sigmoid(%d)=%f\n", atoi(argv[3]), sigmoid(atoi(argv[3])));
    if (signal(SIGUSR1, neuron) == SIG_ERR)
    {
        perror("Cannot set signal handler ");
        exit(1);
    }
    readdata(argv[1], argv[2], atoi(argv[3]));
    return 0;
}


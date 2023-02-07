#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AEScontainer {
    char * rawInput;
    char * output;
    long long fileSize;
    int currentBlock;
} Container;

Container * openFile(){
    FILE * fpointer = fopen(".\\test.txt", "r");
    if(fpointer == NULL)
    {
        printf("Null pointer on file open");
        exit(1);
    }

    Container * AES = malloc(sizeof(Container));
    
    fseek(fpointer, 0, SEEK_END);
    AES->fileSize = ftell(fpointer);
    AES->rawInput = malloc(AES->fileSize);
    AES->currentBlock = 0;

    fclose(fpointer);
    return AES;
}

void shiftRows(Container * matrix)
{
    for(int i = 1; i<4; i++)
    {
        printf("%c",matrix->output[0]);
        char temp = matrix->output[matrix->currentBlock+(4*i)];
        matrix->output[matrix->currentBlock+(4*i)] = matrix->output[matrix->currentBlock+(4*i) + (-i % 4)];
        printf("%c",matrix->output[0]);
        printf("%c",matrix->output[0]);
        matrix->output[matrix->currentBlock+(4*i) + 1] = matrix->output[matrix->currentBlock+(4*i) -1 + ((-i) % 4)];

        matrix->output[matrix->currentBlock+(4*i) + 2] = matrix->output[matrix->currentBlock+(4*i) -2 + ((-i) % 4)];
        matrix->output[matrix->currentBlock+(4*i) + 3] = matrix->output[matrix->currentBlock+(4*i) -3 + ((-i) % 4)];
    }
}

void mixColumns(Container * matrix)
{

}

int main()
{
    struct AEScontainer * AES = malloc(sizeof(struct AEScontainer));
    AES->currentBlock = 0;
    
    char array[] = {'A','B','C','D'};
    AES->output = &array; //???
    //AES->
    printf("%c",AES->output[0]);
    shiftRows(AES);


}
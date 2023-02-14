#include "header.h"
typedef struct AEScontainer {
    char * output; 
    long long fileSize;
    int currentBlock; //Block program is currently modifying.
    int blockRange; //How many blocks exist totally.
} Container;

//Opens to be encrypted/decrypted file from memory, NOTE: Load file in its entirety.
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

    //If filesize != appropriate divisible block size, add padding.
    if(AES->fileSize % 128 != 0)
    {
        int insufficiency = AES->fileSize % 128;
        insufficiency = 128 - insufficiency;
        AES->fileSize += insufficiency; 
    }
    AES->blockRange = AES->fileSize / 128;
    AES->output = malloc(AES->fileSize);
    AES->currentBlock = 0;

    fread(AES->output, sizeof(char), AES->fileSize, fpointer);

    fclose(fpointer);

    return AES;
}
 //Substitutes current block with sbox values.
Container * byteSubstitution(Container * matrix)
{
    for(int i=0;i<15;i++)
    {
        //128/8 = 16, 16*currentBlock to reach the working Block.
        matrix->output[16*matrix->currentBlock + i] = sbox[matrix->output[16*matrix->currentBlock + i]]; //swaps value with sbox value.
    }
}

void xor(Container * matrix, Key * key)
{

}

void shiftRows(Container * matrix)
{
    char copiedMatrix[] = [16];
    for(int c=0; c<15; c++)
    {
        copiedMatrix[c] = matrix->output[matrix->currentBlock*16+c]
    }

    for(int i = 0; i<4; i++)
    {
        matrix->output[matrix->currentBlock*16+(((i*4) + 13) % 16)] = copiedMatrix[(i*4) + 1];
        matrix->output[matrix->currentBlock*16+(((i*4) + 13*2) % 16)] = copiedMatrix[(i*4) + 2];
        matrix->output[matrix->currentBlock*16+(((i*4) + 13*3) % 16)] = copiedMatrix[(i*4) + 3]; 
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

/*
        printf("%c",matrix->output[0]);
        char temp = matrix->output[matrix->currentBlock+(4*i)];
        matrix->output[matrix->currentBlock+(4*i)] = matrix->output[matrix->currentBlock+(4*i) + (-i % 4)];

        matrix->output[matrix->currentBlock+(4*i) + 1] = matrix->output[matrix->currentBlock+(4*i) -1 + ((-i) % 4)];
        matrix->output[matrix->currentBlock+(4*i) + 2] = matrix->output[matrix->currentBlock+(4*i) -2 + ((-i) % 4)];
        matrix->output[matrix->currentBlock+(4*i) + 3] = matrix->output[matrix->currentBlock+(4*i) -3 + ((-i) % 4)];
*/

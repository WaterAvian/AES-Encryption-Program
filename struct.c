#include "header.h"
typedef struct AEScontainer {
    unsigned char * output; 
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
        matrix->outpasut[16*matrix->currentBlock + i] = sbox[matrix->output[16*matrix->currentBlock + i]]; //swaps value with sbox value.
    }
}

/*XORs the current plaintext block with the key.*/
void xor(Container * matrix, Key * key)
{
    for(int i=0; i<16; i++)
    {
        matrix->output[matrix->currentBlock*16 + i] ^= key[i];
    }
}

/*Shifts rows according to AES standard.*/
void shiftRows(Container * matrix)
{
    unsigned char copiedMatrix[] = [16];
    for(int c=0; c<15; c++)
    {
        copiedMatrix[c] = matrix->output[matrix->currentBlock*16+c] //debug might need +1?
    }

    for(int i = 0; i<4; i++)
    {
        matrix->output[matrix->currentBlock*16+(((i*4) + 13) % 16)] = copiedMatrix[(i*4) + 1];
        matrix->output[matrix->currentBlock*16+(((i*4) + 13*2) % 16)] = copiedMatrix[(i*4) + 2];
        matrix->output[matrix->currentBlock*16+(((i*4) + 13*3) % 16)] = copiedMatrix[(i*4) + 3]; 
    }
}

int multiplyExor(char matrix, char standard)
{
    unsigned int total = 0; 
    unsigned int mask = 1; 
    unsigned int intermediary;
    for(int i=0; i<8; i++)
    {
        intermediary = matrix * (mask & standard);
        total ^= intermediary;
        mask = mask << 1; //bits shifted IN, if unclean not 0's then errors?
    }
    return total;
}

//TODO: Learn Galois field theory in less than 4 weeks.
void mixColumns(Container * matrix)
{
    unsigned char standardMatrix = {2,1,1,3, 3,2,1,1, 1,3,2,1, 1,1,3,2};
    unsigned char copiedMatrix[4];
    for(int r=0; r<4; r++)
    {
        copiedMatrix[0] = matrix->output[matrix->currentBlock*16+(r*4)]; 
        copiedMatrix[1] = matrix->output[matrix->currentBlock*16+1+(r*4)];
        copiedMatrix[2] = matrix->output[matrix->currentBlock*16+2+(r*4)];
        copiedMatrix[3] = matrix->output[matrix->currentBlock*16+3+(r*4)];
        for(int i=0, i<4;i++)
        {
            matrix->output[matrix->currentBlock*16+i+(4*r))] = multiplyExor(copiedMatrix[i], standardMatrix[r+(4*i)])
        }
    }
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
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
        matrix->output[16*matrix->currentBlock + i] = sbox[matrix->output[16*matrix->currentBlock + i]]; //swaps value with sbox value.
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

//TODO: Learn Galois field theory in less than 4 weeks.
void mixColumns(Container * matrix)
{
    unsigned char standardMatrix = {2,1,1,3, 3,2,1,1, 1,3,2,1, 1,1,3,2};
    
}

int multiplyExor(int matrix, int standard)
{
    unsigned char total = 0; // m0, m1, m2, m3, m4, m5, m6, m7 = matrix;
    unsigned char mask = 1; // mask2 = 2, mask4 = 4, mask8 = 8, mask16 = 16, mask32 = 32, mask64, mask128; //bit shift in for loop
    unsigned char intermediary;
    for(int i=0; i<8; i++)
    {   
        intermediary = matrix * (mask & standard);
        mask = mask << 1; //bits shifted IN, if unclean not 0's then errors?
        total = total ^ matrix;
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
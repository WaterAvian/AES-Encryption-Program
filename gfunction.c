#include "header.h"

//Substitutes w0 of key with sbox values.
char * subWord(char * subWord)
{
    subWord[0] = sbox[subWord[0]];
    subWord[1] = sbox[subWord[1]];
    subWord[2] = sbox[subWord[2]];
    subWord[3] = sbox[subWord[3]];
    return;
}

char * gfunction(struct Key *key){
    static int round = 0;
    short roundConst[] = {1,2,4,8,16,32,64,128,27,54}; 
    char * gArray = (char*)malloc(sizeof(char)*4); 
    
    //creates array of last 4 bytes of key.
    for(int i = 0, j = 12; i < 4; i++, j++)
    {
        gArray[i] = key->bytes[j]; //w3
    }

    //circular left shift by 1
    char temp = (char)gArray[0];
    gArray[0] = gArray[3];
    gArray[3] = temp; //rotword complete 

    subWord(gArray);

    //XOR's gArray with roundConstant
    gArray[0] = gArray[0] ^ (char)roundConst[round];
    
    return gArray;
}

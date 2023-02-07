#include "header.h"

char * subWord(char * subWord)
{
    subWord[0] = sbox[subWord[0]];
    subWord[1] = sbox[subWord[1]];
    subWord[2] = sbox[subWord[2]];
    subWord[3] = sbox[subWord[3]];
    return;
}

char * gfunction(struct Key *key){ //creates g functions from key
    static int round = 0;
    short roundConst[] = {1,2,4,8,16,32,64,128,27,54}; 
    char * gArray = (char*)malloc(sizeof(char)*4); 

    for(int i = 0, j = 12; i < 4; i++, j++) //creates array of last 4 bytes of key.
    {
        gArray[i] = key->bytes[j]; //w3 (j1 j2 etc = 1 byte/8)
    }

    char temp = (char)gArray[0]; //shifts by 1, circular left shift
    gArray[0] = gArray[3];
    gArray[3] = temp; //rotword completed here

    //Sbox function:
    subWord(gArray);

    //XOR's gArray with roundConstant
    gArray[0] = gArray[0] ^ (char)roundConst[round];  //??? Why *gArray[i] and not gArray[i] doesn't [] already dereference?
    
    return gArray;
}

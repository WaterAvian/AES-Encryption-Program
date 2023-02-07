#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Key {
    unsigned char bytes[16]; //128 bits
} Key;

static int round = 0;

Key * createRound(Key * key, Key * roundkey){ //takes last key and creates new key, returns new key


    char * rotWord = g(key);


    for(int i=0; i<4; i++)
    {
        roundkey->bytes[i] = rotWord[i] ^ (char)key->bytes[i];
        printf("round:%c , rot:%c ^ key:%c\n", roundkey->bytes[i], rotWord[i], key->bytes[i]);
    }

    for(int i=0;i<3;i++)
    {
        for(int j=(i*4)+4; j<(i*4)+8; j++)
        {
             roundkey->bytes[j] = roundkey->bytes[j-1] ^ key->bytes[j];
        }
    }
    free(rotWord);

    return roundkey;
}


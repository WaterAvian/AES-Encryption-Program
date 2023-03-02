
#include "header.h"
typedef struct Key {
    unsigned char bytes[16]; //128 bits
} Key;

 //takes last key and creates new key, returns new key
 //Each Key has 4: 32 (8*4) bit words. w0 -> first 32 bits, w1 -> next 32 bits, etc. 
Key * createRound(Key * key){

    struct Key * roundkey = calloc(sizeof(struct Key));
    char * rotWord = gfunction(key); //XOR's 

    //combines rotword with index 0 of key -> creates new index 0 of new key
    for(int i=0; i<4; i++)
    {
        roundkey->bytes[i] = rotWord[i] ^ (char)key->bytes[i];
        printf("round:%c , rot:%c ^ key:%c\n", roundkey->bytes[i], rotWord[i], key->bytes[i]);
    }

    /*
    i runs for 3  | w5, w6, w7
    j + 4         | starts at w5-etc
    j < (i*4) + 8 | creates run of only 4 byte difference.
    roundkey[i] = | assignment
    roundkey[j-4] | previous column XOR
    key[j]        | past key, place equivalent column XOR
    */
    for(int i=0;i<3;i++)
    {
        for(int j=(i*4)+4; j<(i*4)+8; j++) 
        {
             roundkey->bytes[j] = roundkey->bytes[j-4] ^ key->bytes[j];
        }
    }

    free(rotWord);
    free(key);
    return roundkey;
}


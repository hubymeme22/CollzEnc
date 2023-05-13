/*
    MIT License
    Copyright (c) 2023 HueHueberry

    - A simple library for collatz conjecture for encryption algorithm
    - Works on any files, binaries and any ASCII texts, as long as it
    can be read byte by byte.
*/

#include <stdlib.h>
#include "List.h"

////////////////////////
//  helper functions  //
////////////////////////
int setKeySeed(char* key, int size);

char ROTR(char a, char s);
char ROTL(char a, char s);

///////////////////////
//  Encryption part  //
///////////////////////
char singleEncrypt(char a, char k, char collatzFactor, char s);
char singleDecrypt(char e, char k, char collatzFactor, char s);

char* bufferEncrypt(char* buffer, long bufferSize, char* key, long keySize);
char* bufferDecrypt(char* buffer, long bufferSize, char* key, long keySize);

////////////////////
//  redefinition  //
////////////////////

// char a would be the charater that will be shifted
// char s will be the number of shifts that will be done
// the shift will be any number from 0-7 since, the rest
// will only affect the same way
char ROTR(char a, char s) {
    return ((a >> (s % 8)) ^ (a << (8 - (s % 8)))) & 0xFF;
}

char ROTL(char a, char s) {
    return ((a << (s % 8)) ^ (a >> (8 - (s % 8)))) & 0xFF;
}

// generate the seed from the key
int setKeySeed(char* key, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++)
        sum += key[i] & 0xFF;
    return sum;
}

// the collatz factor will be any number from 0x00 - 0xFF
// this will serve as additional layer for encryption and avalanche effect
// a - character to be encrypted
// k - character key
// s - number of shifts
char singleEncrypt(char a, char k, char collatzFactor, char s) {
    return ROTR(ROTL(a, s) ^ collatzFactor, s) ^ ((k * collatzFactor) & 0xFF);
}

char singleDecrypt(char e, char k, char collatzFactor, char s) {
    return ROTR(ROTL(((k * collatzFactor) & 0xFF) ^ e, s) ^ collatzFactor, s);
}
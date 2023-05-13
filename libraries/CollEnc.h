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
int setKeySeed(const char* key);

char ROTR(char a, char s);
char ROTL(char a, char s);

///////////////////////
//  Encryption part  //
///////////////////////
char singleEncrypt(char a, char b);
char singleDecrypt(char a, char b);

char* bufferEncrypt(char* a, char* b);
char* bufferDecrypt(char* a, char* b);
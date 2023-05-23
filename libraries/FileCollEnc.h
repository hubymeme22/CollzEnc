#include <stdio.h>
#include "CollEnc.h"

#ifndef FILECOLLENC_H
#define FILECOLLENC_H

long CURRENT_FILE_SIZE;

////////////////////////
//  helper functions  //
////////////////////////
char* getFileBytes(char fname[]);
void writeFileBytes(char fname[], char* bufffer, long bufferSize);

//////////////////////////////////////
//  file encrytion functionalities  //
//////////////////////////////////////
void encryptFile(char fname[], char* key, int keySize);
void decryptFile(char fname[], char* key, int keySize);


////////////////////////////
//  Function definitions  //
////////////////////////////
// reads the file bytes of the filename
char* getFileBytes(char fname[]) {
    FILE* fp = fopen(fname, "r");
    if (fp == NULL) {
        puts("NonexistentFileError");
        exit(1);
    }

    // gets the file size by pointing to the end byte
    fseek(fp, 0L, SEEK_END);
    CURRENT_FILE_SIZE = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    // gets the filebytes
    char* buffer = malloc(sizeof(char) * CURRENT_FILE_SIZE);
    fread(buffer, CURRENT_FILE_SIZE, sizeof(char), fp);

    return buffer;
}

// writes the file bytes provided by the user
void writeFileBytes(char fname[], char* buffer, long bufferSize) {
    FILE* fp = fopen(fname, "wb");
    if (fp == NULL) {
        puts("NullFileError");
        exit(1);
    }

    fwrite(buffer, bufferSize, 1, fp);
    fclose(fp);
}

// encrypts the file bytes of the given file name
void encryptFile(char fname[], char* key, int keySize) {
    // retrieve and encrypt fbytes
    char* fbytes = getFileBytes(fname);
    fbytes = bufferEncrypt(fbytes, CURRENT_FILE_SIZE, key, keySize);

    // write the encrypted bytes
    writeFileBytes(fname, fbytes, CURRENT_FILE_SIZE);
}

// decrypts the file bytes of the given file name
void decryptFile(char fname[], char* key, int keySize) {
    // retrieve and encrypt fbytes
    char* fbytes = getFileBytes(fname);
    fbytes = bufferDecrypt(fbytes, CURRENT_FILE_SIZE, key, keySize);

    // write the encrypted bytes
    writeFileBytes(fname, fbytes, CURRENT_FILE_SIZE);
}

#endif
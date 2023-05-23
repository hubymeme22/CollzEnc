#include "../libraries/FileCollEnc.h"

int main() {
    char key[] = "helloworld";
    encryptFile("../README.md", key, 10);
}
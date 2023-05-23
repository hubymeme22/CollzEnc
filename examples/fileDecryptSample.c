#include "../libraries/FileCollEnc.h"

int main() {
    char key[] = "helloworld";
    decryptFile("../README.md", key, 10);
}
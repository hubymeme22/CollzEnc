#include "../libraries/CollEnc.h"

int main() {
    char a = 'a';
    char k = 'B';
    char f = 32;
    char s = 2;

    char out = singleEncrypt(a, k, f, s);
    char bak = singleDecrypt(out, k, f, s);

    printf("Normal: %c\n", a);
    printf("Encrypted: %c\n", out);
    printf("Decrypted: %c\n\n", bak);

    printf("Normal: %d\n", a);
    printf("Right: %d\n", ROTR(a, s));
    printf("Back: %d\n\n", ROTL(ROTR(a, s), s));

    char word[] = "My name is Hubert\0";
    char key[] = "ricknmorty";

    char* encrypted = bufferEncrypt(word, 17, key, 10);
    char* decrypted = bufferDecrypt(encrypted, 17, key, 10);

    printf("Normal: %s\n", word);
    printf("Decrypted: %s", decrypted);
}
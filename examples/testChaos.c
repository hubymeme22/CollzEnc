#include "../libraries/CollEnc.h"
#include <stdio.h>

int main() {
    char normal[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    char key[] = "ricknmorty";
    char keyTypo[] = "ricknmorta";

    int normalSize = 445;
    int keySize = 10;

    char* encrypted1 = bufferEncrypt(normal, normalSize, key, keySize);
    char* encrypted2 = bufferEncrypt(normal, normalSize, keyTypo, keySize);

    int changes = 0;

    for (int i = 0; i < normalSize; i++) {
        printf("%d    %d", (unsigned int)encrypted1[i], (unsigned int)encrypted2[i]);
        if (encrypted1[i] != encrypted2[i]) {
            printf(" -- Changed!");
            changes++;
        }

        puts("");
    }

    float percentage = ((float)changes / (float)normalSize) * 100;
    printf("Changes: %d out of %d or %0.2f percent\n", changes, normalSize, percentage);
    return 0;
}
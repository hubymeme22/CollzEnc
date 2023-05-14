# CollzEnc
A simple **symmetric encryption** written in C using the Collatz conjecture. The purpose of this algorithm is to perform a ***light computation*** for symetric encryption, similar to xor encryption but resulting in more chaotic cipher text and, thus, a higher avalanche effect.

# Encryption library
Currently, there's only one (1) encryption library `libraries/CollEnc.h` which is a simple encryption library that performs encryption and decryption to `char` buffers. Encryption libraries for files and folders will be added soon.

### CollEnc.h
The ff. are functions inside the `CollEnc.h` encryption library:
- `bufferEncrypt` - Used for encrypting `char` buffers, by the use of `key`.
    - parameters: `char* buffer`, `char bufferSize`, `char* key`, `char keySize`
    - Time Complexity: `O(n + m)` where n is the size of buffer and m as size of the key.
    - sample implementation:
    ```C
    #include "libraries/CollEnc.h"

    int main() {
        char buffer[] = "Encrypt this text please";
        char key[] = "key123";

        char* encryptedText = bufferEncrypt(buffer, 24, key, 6);
        return 0;
    }
    ```
- `bufferDecrypt` - Used for decrypting the `char` buffers, encrypted by the `bufferEncrypt` function.
    - Time Complexity: `O(n + m)` where n is the size of buffer and m as size of the key.
    - parameters: `char* buffer`, `char bufferSize`, `char* key`, `char keySize`
    - sample implementation:
    ```C
    #include "libraries/CollEnc.h"

    int main() {
        char buffer[] = "Encrypt this text please";
        char key[] = "key123";

        char* encryptedText = bufferEncrypt(buffer, 24, key, 6);
        char* decryptedText = bufferDecrypt(encryptedText, 24, key, 6);

        printf("%s", decryptedText);
        return 0;
    }
    ```

# Algorithm
The encryption algorithm only used `bit rotation`, `xor` logical operator, and `collatz sequence`. The equation for encryption will be documented here soon.
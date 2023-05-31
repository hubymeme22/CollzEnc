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
## FileCollEnc.h
The ff. are functions inside the `FileCollEnc.h` file encryption library:
- `encryptFile` - Encrypts the file specified in the parameter.
    - parameters: `char fname[]`, `char* key`, `int keySize`
    - sample implementation:
    ```C
    #include "libraries/FileCollEnc.h"

    int main() {
        // encrypts the hello.txt file:
        char key[] = "key123";
        encryptFile("hello.txt", key, 6);
    }
    ```

- `decryptFile` - Decrypts the file specified in the parameter.
    - parameters: `char fname[]`, `char* key`, `int keySize`
    - note: Make sure that the filebuffer is encrypted as this function cannot determine whether the file is encrypted or not, which may result in corrupted file.
    - sample implementation:
    ```C
    #include "libraries/FileCollEnc.h"

    int main() {
        // decrypts the encrypted hello.txt file:
        char key[] = "key123";
        decryptFile("hello.txt", key, 6);
    }
    ```


# Algorithm
The encryption algorithm only used `bit rotation`, `xor` logical operator, and `collatz sequence`. Since the algorithm is designed to be lightweight and fast, it is then based to `xor encryption` but has less linear pattern, and more avalanche effect.

### XOR Encryption
- The xor encryption is designed to encrypt and decrypt bytes in simple operation (just like addition and subtraction):
    ```
    A ⊕ K = E
    E ⊕ K = A
    ```
- This logic makes the xor encryption lighter than the other block ciphers since it is more straightforward and literally uses only the xor operation.
- **PROBLEMS**
    - It has linear pattern when applied to a series of bytes
    - Say we have the following implementation of xor encryption:
        ```C
        for (int i = 0; i < bufferSize; i++) {
            buffer[i] = buffer[i] ^ key[i % keysize];
        }
        ```
    - We can see that there's even a linear pattern here where `xor` operation is being performed on every byte in the following illustration:
        ```
        | k1 | k2 | k3 | .. | kn | k1  | k2  | ...
                        (xor)
        | b1 | b2 | b3 | .. | bn | bn1 | bn2 | ...
                          =
        | e1 | e2 | e3 | .. | en | en1 | en2 | ...
        ```
    - With this information, we can even derive the key length and even guess the entire key by bruteforcing and carefully analyzing the results (e1, e2, ..., en) of output (which can be done by searching specific strings in the output and so on).

### CollzEnc
- To avoid the problems mentioned above, I added more factors when encrypting the bytes. And here's where the collatz sequence comes in handy.
- I designed the collatz sequence to depend on the sum of the key, so that when encrypting the bytes, I do not only use the key itself but also the collatz sequence:
    ```
    Sk = SUM({k1, k2, k3, .. , kn});
    Cs(Sk) = {c1, c2, c3, ... , cn};
    ```
- By this we can see that there's another layer of factor that is needed when encrypting the bytes:
    ```
    | c1 | c2 | c3 | .. | cn | cn1 | cn2 | ...
                    (operation)
    | k1 | k2 | k3 | .. | kn | k1  | k2  | ...
                    (operation)
    | b1 | b2 | b3 | .. | bn | bn1 | bn2 | ...
                        =
    | e1 | e2 | e3 | .. | en | en1 | en2 | ...
    ```
- **Note** that most of the time, the size of the collatz sequence **is not** the same as the size of the key which makes it mroe secured than the xor encryption. Additionally, the sum of the keys varies depending on characters that are being used, which makes it harder for the attackers to look for patterns.
- Using the factors above, i decide to make it even harder to decrypt by performing `bit rotation` and not just `xor`, the encryption per byte will look something like the following:
    ```
    by letting s be the number of shifts, k be the element of the string key, and c be an element of the collatz sequence:

    E = ROTL(ROTR(A ⊕ K, s) ^ ((c * K) & 0xFF), s);
    ```
    - ps. This can be also done in simple `xor` encryption, but hey... I like it overkill
- We can decrypt the Encrypted byte above by reversing the process:
    ```
    A = ROTL(ROTR(E, s) ⊕ ((c * K) & 0xFF), s) ⊕ k
    ```

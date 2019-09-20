#pragma comment(lib, "crypt32.lib")

#include "unif01.h"
#include "bbattery.h"
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <Wincrypt.h>
#define bit 32
#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)
void MyHandleError(char *s);
HCRYPTPROV hCryptProv;
BYTE pbData[4];
int b_i;
unsigned int data;

unsigned int cryptgenrandom(void){
    if(CryptGenRandom(hCryptProv, 4, pbData)){
        for(b_i = 0; b_i<4; ++b_i){
            data = (data << 8) | pbData[b_i];
        }
    }else{
        MyHandleError("Error during CryptGenRandom.");
    }
    return data;
}

int main(void){
    if(CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)){
    }else{
        MyHandleError("Error during CryptAcquireContext!\n");
    }
    unif01_Gen *gen;  // RNG Object
    gen = unif01_CreateExternGenBits ("CryptGenRandom", cryptgenrandom);

    // Tests
    long int nb = pow(2, 30);
    int times = 100;
    int i;
    printf("=== SmallCrush ===\n");
    for(i = 0; i<times; ++i)
        bbattery_SmallCrush(gen);
    printf("=== Rabbit ===\n");
    for(i = 0; i<times; ++i)
        bbattery_Rabbit(gen, nb);
    printf("=== Alphabit ===\n");
    for(i = 0; i<times; ++i)
        bbattery_Alphabit(gen, nb, 0, bit);
    // End tests

    // Clean up.
    unif01_DeleteExternGen01 (gen);
    if(hCryptProv)
        if (!CryptReleaseContext(hCryptProv, 0))
            MyHandleError("Failed CryptReleaseContext\n");

    return 0;
}


void MyHandleError(char *s)
{
    printf("An error occurred in running the program.\n");
    printf("%s\n",s);
    printf("Error number %x\n.",GetLastError());
    printf("Program terminating.\n");
    exit(1);
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int my_func001(char* var); // filled
int my_func002(char* string, void* char2); // prefixe
int my_func003(char* string, double* var1, int var2); // filled
int my_func004(char* string, short* var1, int var2); // key
int my_func005(char* string, int var); // first char
long my_func006(char* string, int var1, char* var2); // filled
void my_func007(const char *string1, const char *string2, unsigned char *string3, int var); // Xor encrypt
char* my_func008(char* string, long var); // home
char* my_func009(char* string, char* varenv); // home env var
int my_func010(char* string, long var); // filled
void my_func011(char* string, int* var1, short var2); // second char
float my_func012(char* string, char* var); // TODO
long *my_func013(const char *string1, int var, char *string2, const char *string3); // Xor decrypt
int my_func014(char* string, char* var); // TODO

int main(int argc, char** argv) {
    char password[255] = "";

    void* var1;
    short var2 = 0xc5ec;
    int var3[5] = {0xc, 0x0, 0x5, 0xe, 0xc};
    double* var4;
    char var5[255] = "";
    
    int check_sum = my_func001(password);
    my_func002(password, var1);
    my_func003(password, var4, check_sum);
    my_func005(password, 0x8c);
    my_func006(password, var3[3], var5);
    my_func008(var5, 0x8);
    my_func009(password, var5);
    my_func010(password, var3[0]);
    my_func011(password, var3, var2);

    printf("password : %s\n", password);
    printf("argv[1] : %s\n", argv[1]);
    printf("strcmp : %d\n", strcmp(password, argv[1]));
    if(!strcmp(password, argv[1])) {
        printf("========== OK ==========\n");
    }
    return 0;
}

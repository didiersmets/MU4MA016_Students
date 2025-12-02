#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(){
    char s[50] = "salut bébé";
    char h[50] = "salut toi";
    char a[34] = "salut bébé";
    if (strcmp(s,h)==0) printf("0\n");
    if (strcmp(s,h)!=0) printf("autre\n");
    if (strcmp(s,s)==0) printf("0 test 2\n");
    if (strcmp(s,a)==0) printf("0 test 3\n");
    
}
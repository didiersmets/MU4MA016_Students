#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *f = fopen("salut","w");
    fprintf(f,"Le chat et la souris\nLe chien ne mange pas  la tortue\naabcd \n\nok");
    fclose(f);

    f = fopen("salut","r");
    char buffer[256];
    char* res = fgets(buffer, sizeof(buffer),f);
    char dest[256];
    sscanf(buffer, "%s %s %s", dest, dest ,dest);
    fprintf(stdout,"%s\n", dest);
    fclose(f);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vertex{
    double x;
    double y;
}Vertex;



int main(){

    FILE *f = fopen("salut","r");
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return 1;
    }

    char buffer[256];
    char str[256]="";
    int j;
    int k=0;
    strcpy(str,"");
    
    Vertex point;

        j=0;
        fgets(buffer, 256, f);
        while (buffer[j] != '\0' && j < 256) {
            while((buffer[j] != ' ')&&(buffer[j] != '\0')){
                printf("%c",buffer[j]);
                str[strlen(str)]=buffer[j];
                j++;
            }
            str[strlen(str)]='\0';
            printf("%s\n",str);
            if (k==1){
                sscanf(str, "%lf",&point.y);
                strcpy(str,"");
            }
            if (k==0) {
                sscanf(str, "%lf",&point.x);
                strcpy(str,"");
            }
            k = (k==0) ? 1 : 0;
            j++;
        }

}
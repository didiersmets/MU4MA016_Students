#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

void timer_start(struct timeval *tv){ gettimeofday(tv,NULL);}

unsigned int timer_stop(const struct timeval *tv, const char *str){
    struct timeval now;
    gettimeofday(&now,NULL);
    unsigned int mus = 1000000 * (now.tv_sec - tv->tv_sec);
    mus += (now.tv_usec - tv->tv_usec);
    if (str[0]){
        printf("Temps %s : ", str);
        if (mus >= 100000){
            printf("%.3f s\n", (float)mus/ 1000000);
        } else {
            printf("%.3f ms\n", (float)mus/ 1000);
        }
    }
    return (mus);
}

void Bubble_sort(int* a, int N){
    if (N<2) return;
    int temp;
    for(int j=N-1; j>0; j--){
        for(int i=0; i<j; i++){
            if (a[i]>a[i+1]){
                temp = a[i+1];
                a[i+1] = a[i];
                a[i] = temp;
            }
        }
    }
}

void Insertion_sort(int* a, int N){
    if (N<2) return;
    int temp;
    for(int i = 1; i<N ; i++){
        while(a[i]<a[i-1]){
            temp=a[i-1];
            a[i-1]=a[i];
            a[i]=temp;
            i--;
            if (i<1) break; //je ne veux pas que le while test a[-1]
        }
    }
}



void Merge(int *T, int p, int q, int r){
    printf("/////////////////////////////////\n");
    int taille1 = q - p; //de p à q - 1
    int taille2 = r - q + 1; //de q à r
    printf("taille 1 : %d | taille 2 : %d \np=%d | q=%d | r=%d\n", taille1,taille2,p,q,r);


    int *tableau = malloc(sizeof(int)*r);

    int i = 0;
    int j = 0;
    int count = 0;

  //int array4[10]={10,9,8,7,6,5,4,3,2,1};

    while(i<taille1 && j<taille2){
        if (T[p+i]<=T[q+j]){
            tableau[count]=T[p+i];
            printf("I = T[p(%d)+i(%d)]=%d | T[q(%d)+j(%d)]=%d | tableau = %d\n ",p,i,T[p+i],q,j,T[q+j], tableau[count]);
            i++;
        } else {
            tableau[count]=T[q+j];
            printf("J = T[p(%d)+i(%d)]=%d | T[q(%d)+j(%d)]=%d | tableau = %d\n",p,i,T[p+i],q,j,T[q+j],tableau[count]);
            j++;
        }
        count++;
    }

    while (i<taille1){
        tableau[count+1]=T[p+i];
        i++;
    }

    while (j<taille2){
        tableau[count+1]=T[q+j];
        j++;
    }

    printf("count = %d\n",count);

    for(int k=p; k<=r; k++){
        T[k]=tableau[k-p];
        //printf("%d = %d\n",T[k],tableau[k-p]);
    }

    free(tableau);

}

void MergeSort(int *T, int p, int r){
    if (p<r){
        int q = (int) (p+r)/2;
        MergeSort(T,p,q);
        MergeSort(T,q+1,r);
        Merge(T,p,q,r);
    }
}


int main(int argc, char* argv[]){
    struct timeval chrono;

    srand(time(NULL));
    int N;
    argc<2 ? printf("Veuillez entrer un entier\n"), scanf("%d",&N) : (N=atoi(argv[1]));
    int *array = (int *)malloc(sizeof(int)*N);
    int *array2 = (int *)malloc(sizeof(int)*N);
    int *array3 = (int *)malloc(sizeof(int)*N);



    printf("\nTableau de base : ["); //affiche le contenu du tableau en création (j'en crée plusieurs comme demandé dans l'exercice)
    for(int i=0; i<N-1; i++){
        array[i]=rand()%(N+1);
        array2[i]=array[i];
        array3[i]=array[i];
        printf("%d,", array[i]);
    }
    array[N-1]=rand()%11;
    array2[N-1]=array[N-1];
    array3[N-1]=array[N-1];
    printf("%d]\n\n",array[N-1]);

    timer_start(&chrono);
    Bubble_sort(array,N);
    timer_stop(&chrono, "du bubble sort");

    printf("Bubble sort : [");
    for(int i=0; i<N-1; i++){
        printf("%d,",array[i]);
    }
    printf("%d]\n\n", array[N-1]);


    timer_start(&chrono);
    Insertion_sort(array2,N);
    timer_stop(&chrono, "du insertion sort");

    printf("Insertion sort : [");
    for(int i=0; i<N-1; i++){
        printf("%d,",array2[i]);
    }
    printf("%d]\n\n", array2[N-1]);

    timer_start(&chrono);
    MergeSort(array3,0,N-1);
    timer_stop(&chrono, "du merge sort");

    printf("Merge sort : [");
    for(int i=0; i<N-1; i++){
        printf("%d,",array3[i]);
    }
    printf("%d]\n\n", array3[N-1]);

    /*int array4[10]={10,9,8,7,6,5,4,3,2,1};
    Merge(array4, 0,4,8);

    printf("Merge sort : [");
    for(int i=0; i<10-1; i++){
        printf("%d,",array4[i]);
    }
    printf("%d]\n\n", array4[9]);*/

    free(array);
    free(array2);
    free(array3);
    
    
    return 0;
}
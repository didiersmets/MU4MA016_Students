#include <stdio.h> 

/*first try, very space-consuming...*/
int main(){
    int n;
    printf("how many lines?");
    scanf("%d",&n);

    int tr[n][n];
    for(int i = 0; i < n; i++){
        for (int j = 0; j <= i ; j++){
            if(i == 0 || j == i || j == 0){
                tr[i][j] = 1;
            }
            else{
                tr[i][j] = tr[i-1][j] + tr[i-1][j-1];
            }
            printf("%4d", tr[i][j]);
        }
        printf("\n");
    }
    
}




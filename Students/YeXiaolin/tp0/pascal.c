#include <stdio.h>
int pascal(int i,int j){
     if( j>0 && j<i ){
        return Pascal_formula(i-1,j-1)+Pascal_formula(i-1,j);
    }
    else{
        return 1;
    }
}


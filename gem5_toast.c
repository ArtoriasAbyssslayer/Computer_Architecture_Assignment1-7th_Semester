#include <stdio.h>
#include <stdlib.h>


int main(){
    double x = rand()%10;
    if ( x > 5){
        printf("Random number is greater than 5\n");
    }else
    {
        printf("Random number is less than 5\n");
    }
    printf("\n");
    printf("%f\n",x);
    
    return 0;
}

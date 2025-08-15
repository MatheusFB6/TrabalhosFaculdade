#include <stdio.h>

    float calcularMedia(float n1,float n2){
        return(n1 + n2)/2;
    } 

int main(){
    float n1, n2, mf;
    printf("Digite a nota 1: ");
    scanf("%f", &n1);

    printf("Digite a nota 2: ");
    scanf("%f", &n2);

    mf = calcularMedia(n1,n2);

    printf("Media final: %.2f\n", mf);
    return 0;
    
}
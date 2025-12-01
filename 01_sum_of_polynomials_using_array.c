#include <stdio.h>
struct Term{
    int coeff,exp;
};

int main(){
    int n1,n2,nres;
    printf("Enter number of terms in poly 1 : ");
    scanf("%d",&n1);
    printf("Enter number of terms in poly 2 : ");
    scanf("%d",&n2);

    struct Term p1[n1],p2[n2],res[40];

    printf("Enter terms of Poly1 : \n");
    for(int i = 0 ; i < n1 ; i++){
        scanf("%d %d",&p1[i].coeff,&p1[i].exp);
    }

    printf("Enter terms of Poly 2 : \n");
    for(int j = 0 ; j < n2 ; j++){
        scanf("%d %d",&p2[j].coeff,&p2[j].exp);
    }

    int i = 0 , j = 0 , k = 0;
    while (i<n1 && j<n2){
        if(p1[i].exp == p2[j].exp){
            res[k].coeff = p1[i].coeff + p2[j].coeff;
            res[k].exp = p1[i].exp;
            i++; j++; k++;
        }
        else if (p1[i].exp > p2[j].exp){
            res[k] = p1[i];
            i++; k++;
        }
        else{
            res[k] = p2[j];
            j++; k++;
        }
    }

    while(i<n1) res[k++] = p1[i++];
    while(j<n2) res[k++] = p2[j++];

    nres = k;

    printf("\n1st poly: ");
    for(int i = 0 ; i < n1 ; i++){
        printf("%dx^%d",p1[i].coeff,p1[i].exp);
        if(i!=n1-1) printf(" + ");
    }

    printf("\n2nd poly: ");
    for(int j = 0 ; j < n2 ; j++){
        printf("%dx^%d",p2[j].coeff,p2[j].exp);
        if(j!=n2-1) printf(" + ");
    }

    printf("\nResult: ");
    for(int k = 0 ; k < nres ; k++){
        printf("%dx^%d",res[k].coeff,res[k].exp);
        if(k!=nres-1) printf(" + ");
    }
    printf("\n");
}

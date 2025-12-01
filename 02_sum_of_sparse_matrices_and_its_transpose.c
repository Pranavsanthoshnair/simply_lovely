#include <stdio.h>

int main() {
    int m1[10][10], m2[10][10];
    int sm1[100][3], sm2[100][3], sum[100][3];
    int r, c, n1 = 0, n2 = 0;

    printf("Enter rows and cols: ");
    scanf("%d%d", &r, &c);

    printf("Enter elements of Matrix 1:\n");
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++) {
            scanf("%d", &m1[i][j]);
            if(m1[i][j] != 0) n1++;
        }

    printf("Enter elements of Matrix 2:\n");
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++) {
            scanf("%d", &m2[i][j]);
            if(m2[i][j] != 0) n2++;
        }

    sm1[0][0] = r; sm1[0][1] = c; sm1[0][2] = n1;
    int k = 1;
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
            if(m1[i][j] != 0) {
                sm1[k][0] = i;
                sm1[k][1] = j;
                sm1[k][2] = m1[i][j];
                k++;
            }

    sm2[0][0] = r; sm2[0][1] = c; sm2[0][2] = n2;
    int p = 1;
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
            if(m2[i][j] != 0) {
                sm2[p][0] = i;
                sm2[p][1] = j;
                sm2[p][2] = m2[i][j];
                p++;
            }

    printf("\nSparse of Matrix 1:\n");
    for(int i = 0; i <= n1; i++)
        printf("%d\t%d\t%d\n", sm1[i][0], sm1[i][1], sm1[i][2]);

    printf("\nSparse of Matrix 2:\n");
    for(int i = 0; i <= n2; i++)
        printf("%d\t%d\t%d\n", sm2[i][0], sm2[i][1], sm2[i][2]);

    printf("\nSum Sparse Matrix:\n");
    int i = 1, j = 1, m = 1;
    sum[0][0] = r;
    sum[0][1] = c;

    while(i <= n1 && j <= n2) {
        if(sm1[i][0] < sm2[j][0] || (sm1[i][0] == sm2[j][0] && sm1[i][1] < sm2[j][1])) {
            sum[m][0] = sm1[i][0];
            sum[m][1] = sm1[i][1];
            sum[m][2] = sm1[i][2];
            i++; m++;
        }
        else if(sm1[i][0] > sm2[j][0] || (sm1[i][0] == sm2[j][0] && sm1[i][1] > sm2[j][1])) {
            sum[m][0] = sm2[j][0];
            sum[m][1] = sm2[j][1];
            sum[m][2] = sm2[j][2];
            j++; m++;
        }
        else {
            sum[m][0] = sm1[i][0];
            sum[m][1] = sm1[i][1];
            sum[m][2] = sm1[i][2] + sm2[j][2];
            i++; j++; m++;
        }
    }

    while(i <= n1) {
        sum[m][0] = sm1[i][0];
        sum[m][1] = sm1[i][1];
        sum[m][2] = sm1[i][2];
        i++; m++;
    }
    while(j <= n2) {
        sum[m][0] = sm2[j][0];
        sum[m][1] = sm2[j][1];
        sum[m][2] = sm2[j][2];
        j++; m++;
    }

    sum[0][2] = m - 1;

    for(int x = 0; x < m; x++)
        printf("%d\t%d\t%d\n", sum[x][0], sum[x][1], sum[x][2]);

    printf("\nTranspose of Sum (Sparse):\n");
    int tr[100][3];
    tr[0][0] = sum[0][1];
    tr[0][1] = sum[0][0];
    tr[0][2] = sum[0][2];

    int t = 1;
    for(int col = 0; col < c; col++)
        for(int x = 1; x < m; x++)
            if(sum[x][1] == col) {
                tr[t][0] = sum[x][1];
                tr[t][1] = sum[x][0];
                tr[t][2] = sum[x][2];
                t++;
            }

    for(int x = 0; x < t; x++)
        printf("%d\t%d\t%d\n", tr[x][0], tr[x][1], tr[x][2]);

    return 0;
}

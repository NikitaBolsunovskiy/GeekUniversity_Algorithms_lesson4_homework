#include <stdio.h>
#include <string.h>

#define SizeX 5
#define SizeY 7

void solution1();

void solution2();

int main() {

    //solution1();
    solution2();

    return 0;
}

void print(int n, int m, int a[SizeX][SizeY]){
    int i,j;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%4d", a[i][j]);
        }
        printf("\n");
    }
}

void printMatrix(int n, int m, int * a,char *str1, char*str2){
    int i,j;

    printf("        ");
    for (int j = 1; j < m; ++j) {
        printf("%4c", str2[j-1]);
    }
    printf("\n");


    for (int i = 0; i < n; ++i) {
        if(i>0){
            printf("%4c", str1[i-1]);
        } else {
            printf("    ");
        }
        for (int j = 0; j < m; ++j) {
            printf("%4d", a[i*m+j]);
        }
        printf("\n");
    }
}

void readMap(int map[SizeX][SizeY], char path[]){

    FILE *in;
    in = fopen(path,"r");
    int n,m;
    fscanf(in,"%i",&n);
    fscanf(in,"%i",&m);

    for(int i = 0; i<n; i++){
        for (int j = 0; j < m; ++j) {
            fscanf(in,"%i ",&map[i][j]);
        }
    }
    fclose(in);

}

void solution1(){

//    1. *Количество маршрутов с препятствиями. Реализовать чтение массива с препятствием и
//    нахождение количество маршрутов.
//            Например, карта:
//    3 3
//    1 1 1
//    0 1 0
//    0 1 0

    int a[SizeX][SizeY];
    int map[SizeX][SizeY];

    readMap(map,"D:\\Java_projects_Study\\05_Algorithms_and_data_structures\\04\\homework4\\Map.txt");
    printf("Карта препятствий:\n");
    print(SizeX,SizeY,map);

    int i,j;
    if(map[0][0]==0){
        for (int i = 0; i < SizeX; ++i) {
            for (int j = 0; j < SizeY; ++j) {
                a[i][j]=0;
            }
        }
    } else{
        a[0][0]=map[0][0];
        for(j=1;j<SizeY;j++){
            a[0][j]=map[0][j]*(a[0][j-1]==0)?0:map[0][j];
        }
        for(i=1;i<SizeX;i++){
            a[i][0] = map[i][0]*(a[i-1][0]==0)?0:map[i][0];
            for(j=1;j<SizeY;j++){
                a[i][j] = (a[i][j-1] + a[i-1][j])*map[i][j];
            }
        }
    }

    printf("Карта количества возможных путей:\n");
    print(SizeX,SizeY,a);
}

int max(int a, int b){
    return (a>=b)?a:b;
}

int lcs_length(char *a,char *b){

    int n = strlen(a) + 1;
    int m = strlen(b) + 1;

    printf("Первая строка: %s\n",a);
    printf("Длина: %d\n",n);
    printf("Вторая строка: %s\n",b);
    printf("Длина: %d\n",m);

    int matrix[n][m];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = 0;
        }
    }

    printMatrix(n,m,matrix,a,b);

    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            if(a[i-1]=='\0'||b[j-1]=='\0') {
                matrix[i][j] = 0;
            } else {
                if (a[i - 1] == b[j - 1]) {
                    matrix[i][j] = 1 + matrix[i - 1][j - 1];
                } else {
                    matrix[i][j] = max(matrix[i][j - 1], matrix[i - 1][j]);
                }
            }
        }
    }

    //puts("Рассчитанная карта чисел:");
    //print(n,m,matrix);

}

void solution2(){

    //2. Решить задачу о нахождении длины максимальной последовательности с помощью матрицы.

    int lcs_l = 0;

    lcs_l = lcs_length("geekminds","geekbrains");


}
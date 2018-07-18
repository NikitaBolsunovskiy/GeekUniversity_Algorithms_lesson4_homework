#include <stdio.h>

#define SizeX 5
#define SizeY 7

void solution1();


int main() {

    solution1();

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
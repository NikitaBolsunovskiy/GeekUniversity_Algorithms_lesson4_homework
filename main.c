#include <stdio.h>
#include <string.h>

#define SizeX 5
#define SizeY 7
#define ChessBoardSizeX 12
#define ChessBoardSizeY 12

int board[ChessBoardSizeX][ChessBoardSizeY];

void solution1();
void solution2();
void solution3();

int main() {

    //solution1();
    //solution2();
    solution3();

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
    printf("Вторая строка: %s\n",b);

    int matrix[n][m];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = 0;
        }
    }

    printMatrix(n,m,matrix,a,b);

    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            if(a[i-1]==b[j-1]){
                matrix[i][j] = 1 + matrix[i-1][j-1];
            } else {
                matrix[i][j] = max(matrix[i-1][j],matrix[i][j-1]);
            }
        }
    }

    puts("Рассчитанная карта чисел:");
    printMatrix(n,m,matrix,a,b);

    return matrix[n-1][m-1];

}

void solution2(){

    //2. Решить задачу о нахождении длины максимальной последовательности с помощью матрицы.

    int lcs_l = 0;

    lcs_l = lcs_length("algorithms","knowledge");

    printf("Длина наибольшей общей последовательности: %d\n",lcs_l);


}

void Zero(int n, int m, int a[ChessBoardSizeX][ChessBoardSizeY]){
    int i, j;
    for (i=0; i<n; i++)
        for (j=0; j<m; j++)
            a[i][j] = 0;
}

void printBoard(int n, int m, int a[ChessBoardSizeX][ChessBoardSizeY]){
    int i,j;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%4d", a[i][j]);
        }
        printf("\n");
    }
}

int CheckBoard() {

}

int movePossible(int x, int y){

    // Если выходим за границы поля...
    if (x<0 || x >= ChessBoardSizeX || y < 0 || y >= ChessBoardSizeY){
        return 0;
    }
    //Если по клетке не ходили...
    if (board[x][y] == 0) {
        return 1;
    }
    return 0;
}

int countFreeSpasesForMove(int x, int y){

    int counter = 0;

    if (x<0 || x >= ChessBoardSizeX || y < 0 || y >= ChessBoardSizeY){
        return 1000;
    }

    if(movePossible(x-2,y-1)) counter++;
    if(movePossible(x-2,y+1)) counter++;
    if(movePossible(x-1,y+2)) counter++;
    if(movePossible(x+1,y+2)) counter++;
    if(movePossible(x+2,y-1)) counter++;
    if(movePossible(x+2,y+1)) counter++;
    if(movePossible(x-1,y-2)) counter++;
    if(movePossible(x+1,y-2)) counter++;
    return counter;
}

void analyzePossibleMoves(int x, int y, int possMoves[8][3]){
    possMoves[0][0] = x-2;
    possMoves[0][1] = y-1;
    possMoves[0][2] = countFreeSpasesForMove(x-2,y-1);
    possMoves[1][0] = x-2;
    possMoves[1][1] = y+1;
    possMoves[1][2] = countFreeSpasesForMove(x-2,y+1);
    possMoves[2][0] = x-1;
    possMoves[2][1] = y+2;
    possMoves[2][2] = countFreeSpasesForMove(x-1,y+2);
    possMoves[3][0] = x+1;
    possMoves[3][1] = y+2;
    possMoves[3][2] = countFreeSpasesForMove(x+1,y+2);
    possMoves[4][0] = x+2;
    possMoves[4][1] = y-1;
    possMoves[4][2] = countFreeSpasesForMove(x+2,y-1);
    possMoves[5][0] = x+2;
    possMoves[5][1] = y+1;
    possMoves[5][2] = countFreeSpasesForMove(x+2,y+1);
    possMoves[6][0] = x-1;
    possMoves[6][1] = y-2;
    possMoves[6][2] = countFreeSpasesForMove(x-1,y-2);
    possMoves[7][0] = x+1;
    possMoves[7][1] = y-2;
    possMoves[7][2] = countFreeSpasesForMove(x+1,y-2);
}

void sortPossibleMoves(int possMoves[8][3]){
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 7; ++j) {
            if(possMoves[j][2]>possMoves[j+1][2]){
                int temp[3] = {possMoves[j][0],possMoves[j][1],possMoves[j][2]};
                possMoves[j][0] = possMoves[j+1][0];
                possMoves[j][1] = possMoves[j+1][1];
                possMoves[j][2] = possMoves[j+1][2];
                possMoves[j+1][0] = temp[0];
                possMoves[j+1][1] = temp[1];
                possMoves[j+1][2] = temp[2];
            }
        }
    }
}

int SearchSolution(int n,int x, int y){

    // Если ход следующий после количества клеток, то все удалось...
    if (n== ChessBoardSizeY*ChessBoardSizeX + 1) return 1;

    int result = 0;

    // Массив, в который положим возможные координаты и количество возможных ходов для них...
    int possibleMoves[8][3];
    analyzePossibleMoves(x,y,possibleMoves);
    sortPossibleMoves(possibleMoves);

    for (int i = 0; i < 8; ++i) {
        if(movePossible(possibleMoves[i][0],possibleMoves[i][1])){
            board[possibleMoves[i][0]][possibleMoves[i][1]] = n;
            if(SearchSolution(n+1,possibleMoves[i][0],possibleMoves[i][1])){
                return 1;
            }
            board[possibleMoves[i][0]][possibleMoves[i][1]] = 0;
        }
    }

    return 0;
}

void solution3(){

//    3. ***Требуется обойти конём шахматную доску размером NxM, пройдя через все поля доски по
//    одному разу. Здесь алгоритм решения такой же как и в задаче о 8 ферзях. Разница только в проверке
//    положения коня.
//    Для коня суть в том, что на каждом шаге конь может сходить в строго оределенные клетки, получается на кажой итерации SearchSolution нужно передавать где сейчас конь и может ли он куда-то сходить...
//    Будем считать, что если в ячейке Board стоит 0 - то конь там еще не был, если не ноль, то был. Записывать в ячейку будем номер текущего хода, чтобы потом наглядно проверить...


    //    Результаты тестирования: на поле 5 на 5 быстро нашелся вариант.
    //      на поле 6 на 6 быстро нашелся вариант.
    // на поле 7 на 7 не дождался реузльтата, почитав про правило Варнсдорфа решил попробовать применить его.
    // https://forany.xyz/a-16?pg=8
    // применил правило Варнсдорфа и заработало...

    Zero(ChessBoardSizeX,ChessBoardSizeY,board);
    printBoard(ChessBoardSizeX,ChessBoardSizeY,board);
    int i,j;
    int result = 0;
    for (int i = 0; i < ChessBoardSizeX; i++) {
        for (int j = 0; j < ChessBoardSizeY; j++) {
            board[i][j] = 1;
            if (SearchSolution(2,i,j)) {
                result = 1;
                break;
            } else {
                printf("\n\n");
                printBoard(ChessBoardSizeX,ChessBoardSizeY,board);
                board[i][j] = 0;
            }
        }
        if (result == 1){
            break;
        }
    }

    printf("\n\n");
    printBoard(ChessBoardSizeX,ChessBoardSizeY,board);

}
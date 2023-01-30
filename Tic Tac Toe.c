#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// Developed by Ruwan Rohitha 2020T00904

char mapDef[10] = {' ','1','2','3','4','5','6','7','8','9'};
char map[10] = {' ','1','2','3','4','5','6','7','8','9'};
int defColor = 96;
int playerMap[10] = {90,90,90,90,90,90,90,90,90,90};
int level = 0;
int mask = 0;

struct Player{
    char name[50];
    char style;
    int arr[5];
}p1,p2;

void saveDataToFile(int gameType, int win){
    FILE *ptr;
    ptr = fopen("gameData.txt","a");
    if(ptr == NULL){
      printf("File could not be found !\n");
      return;
    }
    if(gameType == 0){
        fprintf(ptr,"Game Type: Player vs Player\n");
    } else if(gameType == 1){
        fprintf(ptr,"Game Type: Player vs Computer (Easy)\n");
    } else if(gameType == 2){
        fprintf(ptr,"Game Type: Player vs Computer (Hard)\n");
    }else if(gameType == 3){
        fprintf(ptr,"Game Type: Player vs Computer (Insane)\n");
    }
    fprintf(ptr,"Player 1 : %s (%c)\n",p1.name,p1.style);
    fprintf(ptr,"Player 2 : %s (%c)\n",p2.name,p2.style);
    fprintf(ptr,"Game moves -> \n");
    for(int i = 0; i < 5; i++){
        if(p1.arr[i] != 0){
            fprintf(ptr,"    Player 1 : %d\n",p1.arr[i]);
        }
        if(p2.arr[i] != 0){
            fprintf(ptr,"    Player 2 : %d\n",p2.arr[i]);
        }
    }
    if(win == 0){
        fprintf(ptr,"Match has drawn");
    } else if (win == 1){
        fprintf(ptr,"Player 1 has won the match");
    } else if (win == 2){
        fprintf(ptr,"Player 2 has won the match");
    }
    fprintf(ptr,"\n_____________________________________\n\n");
    fclose(ptr);
}

void resetMap(){
    for(int i = 0; i < 10; i++){
        map[i] = mapDef[i];
        playerMap[i] = 90;
    }
    level = 0;
    for(int i = 0; i < 5; i++){
        p1.arr[i] = 0;
        p2.arr[i] = 0;
    }

}

void setWinBoard(int a,int b, int c, int color, int state){
    for(int i = 0; i < 10; i++){
            if(playerMap[i] == 42){
                playerMap[i] = 32;
            } else if(playerMap[i] == 43){
                playerMap[i] = 33;
            }
    }
    if(state == 0){
        playerMap[a] = color;
        playerMap[b] = color;
        playerMap[c] = color;
    }
}

int checkWin(){
    char wonMark = ' ';
    if(map[1] == map[2] && map[2] == map[3]){
        setWinBoard(1,2,3,playerMap[1],0);
        wonMark = map[1];
    } else if(map[4] == map[5] && map[5] == map[6]){
        setWinBoard(4,5,6,playerMap[4],0);
        wonMark = map[4];
    } else if(map[7] == map[8] && map[8] == map[9]){
        setWinBoard(7,8,9,playerMap[7],0);
        wonMark = map[7];
    } else if(map[1] == map[4] && map[4] == map[7]){
        setWinBoard(1,4,7,playerMap[1],0);
        wonMark = map[1];
    } else if(map[2] == map[5] && map[5] == map[8]){
        setWinBoard(2,5,8,playerMap[2],0);
        wonMark = map[2];
    } else if(map[3] == map[6] && map[6] == map[9]){
        setWinBoard(3,6,9,playerMap[3],0);
        wonMark = map[3];
    } else if(map[1] == map[5] && map[5] == map[9]){
        setWinBoard(1,5,9,playerMap[1],0);
        wonMark = map[1];
    } else if(map[3] == map[5] && map[5] == map[7]){
        setWinBoard(3,5,7,playerMap[1],0);
        wonMark = map[3];
    } else if(map[1] != '1' && map[2] != '2' && map[3] != '3' && map[4] != '4' && map[5] != '5' && map[6] != '6' && map[7] != '7' && map[8] != '8' && map[9] != '9'){
        setWinBoard(1,1,1,playerMap[1],1);
        return 3;
    } else {
        return 4;
    }
    if(wonMark == 'O'){
        return 1;
    } else if(wonMark == 'X'){
        return 2;
    }
}

void catchPhrase(int n){
    system("cls");
    printf("[34m=============================================================[0m\n");
    printf("[34m                 --------TIC TAC TOE---------               [0m\n");
    if(n == 0){
        printf("[36m               --------PLAY WITH FRIEND---------             [0m\n");
    } else if(n == 1){
        printf("[36m          --------PLAY WITH COMPUTER (EASY)---------         [0m\n");
    } else if(n == 2){
        printf("[36m          --------PLAY WITH COMPUTER (HARD)---------         [0m\n");
    } else if(n == 3){
        printf("[36m         --------PLAY WITH COMPUTER (INSANE)---------        [0m\n");
    } else if(n == 4){
        printf("[36m                --------INSTRUCTIONS---------                [0m\n");
    } else if(n == 5){
        printf("[36m              --------PREVIOUS RECORDS---------              [0m\n");
    }
    printf("[34m=============================================================[0m\n");
    printf("\n");
}

int getPointEasy(){
    if(mask == 1){
        if (map[4] == map[5] && map[5] == 'X' && map[6] == '6'){
            return 6;
        } else if (map[7] == map[8] && map[8] == 'X' && map[9] == '3'){
            return 9;
        } else if (map[5] == map[6] && map[6] == 'X' && map[4] == '4'){
            return 4;
        } else if (map[1] == map[3] && map[3] == 'X' && map[2] == '2'){
            return 2;
        } else if (map[5] == map[8] && map[8] == 'X' && map[2] == '2'){
            return 2;
        } else if (map[2] == map[8] && map[8] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[9] == map[5] && map[5] == 'X' && map[1] == '1'){
            return 1;
        } else if (map[3] == map[7] && map[7] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[7] == map[8] && map[8] == 'O' && map[9] == '3'){
            return 9;
        } else if (map[2] == map[5] && map[5] == 'O' && map[8] == '8'){
            return 8;
        } else if (map[5] == map[6] && map[6] == 'O' && map[4] == '4'){
            return 4;
        } else if (map[4] == map[7] && map[7] == 'O' && map[1] == '1'){
            return 1;
        } else if (map[6] == map[9] && map[9] == 'O' && map[3] == '3'){
            return 3;
        } else if (map[1] == map[5] && map[5] == 'O' && map[9] == '9'){
            return 9;
        }
    } else if (mask == 2){
        if(map[5] == '5'){
            return 5;
        } else if (map[7] == map[8] && map[8] == 'X' && map[9] == '3'){
            return 9;
        } else if (map[2] == map[5] && map[5] == 'X' && map[8] == '8'){
            return 8;
        } else if (map[4] == map[6] && map[6] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[1] == map[7] && map[7] == 'X' && map[4] == '4'){
            return 4;
        } else if (map[3] == map[5] && map[5] == 'X' && map[7] == '7'){
            return 7;
        } else if (map[4] == map[5] && map[5] == 'O' && map[6] == '6'){
            return 6;
        } else if (map[3] == map[6] && map[6] == 'O' && map[9] == '9'){
            return 9;
        } else if (map[5] == map[6] && map[6] == 'O' && map[4] == '4'){
            return 4;
        } else if (map[4] == map[6] && map[6] == 'O' && map[5] == '5'){
            return 5;
        } else if (map[2] == map[8] && map[8] == 'O' && map[5] == '5'){
            return 5;
        } else if (map[3] == map[9] && map[9] == 'O' && map[6] == '6'){
            return 6;
        } else if (map[3] == map[7] && map[7] == 'O' && map[5] == '5'){
            return 5;
        } else if (map[7] == map[5] && map[5] == 'O' && map[3] == '3'){
            return 3;
        }
    } else {
        if(map[5] == '5'){
            return 5;
        } else if (map[1] == map[2] && map[2] == 'X' && map[3] == '3'){
            return 3;
        } else if (map[1] == map[3] && map[3] == 'X' && map[2] == '2'){
            return 2;
        } else if (map[2] == map[8] && map[8] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[9] == map[5] && map[5] == 'X' && map[1] == '1'){
            return 1;
        } else if (map[2] == map[5] && map[5] == 'O' && map[8] == '8'){
            return 8;
        } else if (map[5] == map[6] && map[6] == 'O' && map[4] == '4'){
            return 4;
        } else if (map[8] == map[9] && map[9] == 'O' && map[7] == '7'){
            return 7;
        } else if (map[5] == map[8] && map[8] == 'O' && map[2] == '2'){
            return 2;
        } else if (map[1] == map[7] && map[7] == 'O' && map[4] == '4'){
            return 4;
        } else if (map[3] == map[9] && map[9] == 'O' && map[6] == '6'){
            return 6;
        } else if (map[9] == map[5] && map[5] == 'O' && map[1] == '1'){
            return 1;
        } else if (map[3] == map[5] && map[5] == 'O' && map[7] == '7'){
            return 7;
        } else if (map[7] == map[5] && map[5] == 'O' && map[3] == '3'){
            return 3;
        }
    }
    while(1){
        int r = rand() % 9;
        if(r != 0 && map[r] != 'O' && map[r] != 'X'){
            return r;
        }
    }
}

int getPointHard(){
    if(mask == 1){
        if(map[5] == '5'){
            return 5;
        } else if (map[1] == map[2] && map[2] == 'X' && map[3] == '3'){
            return 3;
        } else if (map[4] == map[5] && map[5] == 'X' && map[6] == '6'){
            return 6;
        } else if (map[7] == map[8] && map[8] == 'X' && map[9] == '3'){
            return 9;
        } else if (map[1] == map[4] && map[4] == 'X' && map[7] == '7'){
            return 7;
        } else if (map[3] == map[6] && map[6] == 'X' && map[9] == '9'){
            return 9;
        } else if (map[2] == map[3] && map[3] == 'X' && map[1] == '1'){
            return 1;
        } else if (map[5] == map[6] && map[6] == 'X' && map[4] == '4'){
            return 4;
        } else if (map[1] == map[3] && map[3] == 'X' && map[2] == '2'){
            return 2;
        } else if (map[4] == map[6] && map[6] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[7] == map[9] && map[9] == 'X' && map[8] == '8'){
            return 8;
        } else if (map[4] == map[7] && map[7] == 'X' && map[1] == '1'){
            return 1;
        } else if (map[5] == map[8] && map[8] == 'X' && map[2] == '2'){
            return 2;
        } else if (map[6] == map[9] && map[9] == 'X' && map[3] == '3'){
            return 3;
        } else if (map[2] == map[8] && map[8] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[3] == map[9] && map[9] == 'X' && map[6] == '6'){
            return 6;
        } else if (map[1] == map[5] && map[5] == 'X' && map[9] == '9'){
            return 9;
        } else if (map[9] == map[5] && map[5] == 'X' && map[1] == '1'){
            return 1;
        } else if (map[3] == map[5] && map[5] == 'X' && map[7] == '7'){
            return 7;
        } else if (map[3] == map[7] && map[7] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[7] == map[5] && map[5] == 'X' && map[3] == '3'){
            return 3;
        } else if (map[1] == map[2] && map[2] == 'O' && map[3] == '3'){
            return 3;
        } else if (map[4] == map[5] && map[5] == 'O' && map[6] == '6'){
            return 6;
        } else if (map[7] == map[8] && map[8] == 'O' && map[9] == '3'){
            return 9;
        } else if (map[2] == map[5] && map[5] == 'O' && map[8] == '8'){
            return 8;
        } else if (map[3] == map[6] && map[6] == 'O' && map[9] == '9'){
            return 9;
        } else if (map[5] == map[6] && map[6] == 'O' && map[4] == '4'){
            return 4;
        } else if (map[4] == map[6] && map[6] == 'O' && map[5] == '5'){
            return 5;
        } else if (map[7] == map[9] && map[9] == 'O' && map[8] == '8'){
            return 8;
        } else if (map[4] == map[7] && map[7] == 'O' && map[1] == '1'){
            return 1;
        } else if (map[6] == map[9] && map[9] == 'O' && map[3] == '3'){
            return 3;
        } else if (map[1] == map[7] && map[7] == 'O' && map[4] == '4'){
            return 4;
        } else if (map[3] == map[9] && map[9] == 'O' && map[6] == '6'){
            return 6;
        } else if (map[1] == map[9] && map[9] == 'O' && map[5] == '5'){
            return 5;
        } else if (map[3] == map[5] && map[5] == 'O' && map[7] == '7'){
            return 7;
        } else if (map[3] == map[7] && map[7] == 'O' && map[5] == '5'){
            return 5;
        }
    } else if (mask == 2){
        if(map[5] == '5'){
            return 5;
        } else if (map[4] == map[5] && map[5] == 'X' && map[6] == '6'){
            return 6;
        } else if (map[7] == map[8] && map[8] == 'X' && map[9] == '3'){
            return 9;
        } else if (map[2] == map[5] && map[5] == 'X' && map[8] == '8'){
            return 8;
        } else if (map[3] == map[6] && map[6] == 'X' && map[9] == '9'){
            return 9;
        } else if (map[2] == map[3] && map[3] == 'X' && map[1] == '1'){
            return 1;
        } else if (map[8] == map[9] && map[9] == 'X' && map[7] == '7'){
            return 7;
        } else if (map[1] == map[3] && map[3] == 'X' && map[2] == '2'){
            return 2;
        } else if (map[7] == map[9] && map[9] == 'X' && map[8] == '8'){
            return 8;
        } else if (map[4] == map[7] && map[7] == 'X' && map[1] == '1'){
            return 1;
        } else if (map[6] == map[9] && map[9] == 'X' && map[3] == '3'){
            return 3;
        } else if (map[1] == map[7] && map[7] == 'X' && map[4] == '4'){
            return 4;
        } else if (map[3] == map[9] && map[9] == 'X' && map[6] == '6'){
            return 6;
        } else if (map[1] == map[5] && map[5] == 'X' && map[9] == '9'){
            return 9;
        } else if (map[9] == map[5] && map[5] == 'X' && map[1] == '1'){
            return 1;
        } else if (map[3] == map[5] && map[5] == 'X' && map[7] == '7'){
            return 7;
        } else if (map[7] == map[5] && map[5] == 'X' && map[3] == '3'){
            return 3;
        } else if (map[1] == map[2] && map[2] == 'O' && map[3] == '3'){
            return 3;
        } else if (map[7] == map[8] && map[8] == 'O' && map[9] == '3'){
            return 9;
        } else if (map[1] == map[4] && map[4] == 'O' && map[7] == '7'){
            return 7;
        } else if (map[3] == map[6] && map[6] == 'O' && map[9] == '9'){
            return 9;
        } else if (map[2] == map[3] && map[3] == 'O' && map[1] == '1'){
            return 1;
        } else if (map[8] == map[9] && map[9] == 'O' && map[7] == '7'){
            return 7;
        } else if (map[1] == map[3] && map[3] == 'O' && map[2] == '2'){
            return 2;
        } else if (map[4] == map[6] && map[6] == 'O' && map[5] == '5'){
            return 5;
        } else if (map[4] == map[7] && map[7] == 'O' && map[1] == '1'){
            return 1;
        } else if (map[5] == map[8] && map[8] == 'O' && map[2] == '2'){
            return 2;
        } else if (map[6] == map[9] && map[9] == 'O' && map[3] == '3'){
            return 3;
        } else if (map[1] == map[7] && map[7] == 'O' && map[4] == '4'){
            return 4;
        } else if (map[3] == map[9] && map[9] == 'O' && map[6] == '6'){
            return 6;
        } else if (map[1] == map[5] && map[5] == 'O' && map[9] == '9'){
            return 9;
        } else if (map[1] == map[9] && map[9] == 'O' && map[5] == '5'){
            return 5;
        } else if (map[9] == map[5] && map[5] == 'O' && map[1] == '1'){
            return 1;
        } else if (map[3] == map[5] && map[5] == 'O' && map[7] == '7'){
            return 7;
        } else if (map[3] == map[7] && map[7] == 'O' && map[5] == '5'){
            return 5;
        } else if (map[7] == map[5] && map[5] == 'O' && map[3] == '3'){
            return 3;
        }
    } else {
        if (map[1] == map[2] && map[2] == 'X' && map[3] == '3'){
            return 3;
        } else if (map[7] == map[8] && map[8] == 'X' && map[9] == '3'){
            return 9;
        } else if (map[1] == map[4] && map[4] == 'X' && map[7] == '7'){
            return 7;
        } else if (map[2] == map[5] && map[5] == 'X' && map[8] == '8'){
            return 8;
        } else if (map[3] == map[6] && map[6] == 'X' && map[9] == '9'){
            return 9;
        } else if (map[5] == map[6] && map[6] == 'X' && map[4] == '4'){
            return 4;
        } else if (map[8] == map[9] && map[9] == 'X' && map[7] == '7'){
            return 7;
        } else if (map[1] == map[3] && map[3] == 'X' && map[2] == '2'){
            return 2;
        } else if (map[4] == map[6] && map[6] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[4] == map[7] && map[7] == 'X' && map[1] == '1'){
            return 1;
        } else if (map[5] == map[8] && map[8] == 'X' && map[2] == '2'){
            return 2;
        } else if (map[1] == map[7] && map[7] == 'X' && map[4] == '4'){
            return 4;
        } else if (map[2] == map[8] && map[8] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[1] == map[5] && map[5] == 'X' && map[9] == '9'){
            return 9;
        } else if (map[1] == map[9] && map[9] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[3] == map[5] && map[5] == 'X' && map[7] == '7'){
            return 7;
        } else if (map[3] == map[7] && map[7] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[1] == map[2] && map[2] == 'O' && map[3] == '3'){
            return 3;
        } else if (map[4] == map[5] && map[5] == 'O' && map[6] == '6'){
            return 6;
        } else if (map[7] == map[8] && map[8] == 'O' && map[9] == '3'){
            return 9;
        } else if (map[1] == map[4] && map[4] == 'O' && map[7] == '7'){
            return 7;
        } else if (map[2] == map[5] && map[5] == 'O' && map[8] == '8'){
            return 8;
        } else if (map[3] == map[6] && map[6] == 'O' && map[9] == '9'){
            return 9;
        } else if (map[5] == map[6] && map[6] == 'O' && map[4] == '4'){
            return 4;
        } else if (map[8] == map[9] && map[9] == 'O' && map[7] == '7'){
            return 7;
        } else if (map[1] == map[3] && map[3] == 'O' && map[2] == '2'){
            return 2;
        } else if (map[7] == map[9] && map[9] == 'O' && map[8] == '8'){
            return 8;
        } else if (map[4] == map[7] && map[7] == 'O' && map[1] == '1'){
            return 1;
        } else if (map[5] == map[8] && map[8] == 'O' && map[2] == '2'){
            return 2;
        } else if (map[1] == map[7] && map[7] == 'O' && map[4] == '4'){
            return 4;
        } else if (map[2] == map[8] && map[8] == 'O' && map[5] == '5'){
            return 5;
        } else if (map[3] == map[9] && map[9] == 'O' && map[6] == '6'){
            return 6;
        } else if (map[1] == map[5] && map[5] == 'O' && map[9] == '9'){
            return 9;
        } else if (map[9] == map[5] && map[5] == 'O' && map[1] == '1'){
            return 1;
        } else if (map[3] == map[5] && map[5] == 'O' && map[7] == '7'){
            return 7;
        }
    }
    while(1){
        int r = rand() % 9;
        if(r != 0 && map[r] != 'O' && map[r] != 'X'){
            return r;
        }
    }
}

int getPointInsane(){
    int even[4] = {1,3,7,9};
    if(map[5] == '5'){
        return 5;
    } else if(map[1] == '1' && map[2] == '2' && map[3] == '3' && map[4] == '4' && map[5] != '5' && map[6] == '6' && map[7] == '7' && map[8] == '8' && map[9] == '9'){
         int g = rand() % 4;
         return even[g];
    } else if (map[1] == map[2] && map[2] == 'X' && map[3] == '3'){
        return 3;
    } else if (map[7] == map[8] && map[8] == 'X' && map[9] == '3'){
        return 9;
    } else if (map[1] == map[4] && map[4] == 'X' && map[7] == '7'){
        return 7;
    } else if (map[3] == map[6] && map[6] == 'X' && map[9] == '9'){
        return 9;
    } else if (map[2] == map[3] && map[3] == 'X' && map[1] == '1'){
        return 1;
    } else if (map[8] == map[9] && map[9] == 'X' && map[7] == '7'){
        return 7;
    } else if (map[4] == map[6] && map[6] == 'X' && map[5] == '5'){
        return 5;
    } else if (map[4] == map[7] && map[7] == 'X' && map[1] == '1'){
        return 1;
    } else if (map[6] == map[9] && map[9] == 'X' && map[3] == '3'){
        return 3;
    } else if (map[2] == map[8] && map[8] == 'X' && map[5] == '5'){
        return 5;
    } else if (map[1] == map[5] && map[5] == 'X' && map[9] == '9'){
        return 9;
    } else if (map[1] == map[9] && map[9] == 'X' && map[5] == '5'){
        return 5;
    } else if (map[9] == map[5] && map[5] == 'X' && map[1] == '1'){
        return 1;
    } else if (map[3] == map[5] && map[5] == 'X' && map[7] == '7'){
        return 7;
    } else if (map[3] == map[7] && map[7] == 'X' && map[5] == '5'){
        return 5;
    } else if (map[7] == map[5] && map[5] == 'X' && map[3] == '3'){
        return 3;
    } else if (map[4] == map[5] && map[5] == 'X' && map[6] == '6'){
        return 6;
    } else if (map[2] == map[5] && map[5] == 'X' && map[8] == '8'){
        return 8;
    } else if (map[5] == map[6] && map[6] == 'X' && map[4] == '4'){
        return 4;
    } else if (map[1] == map[3] && map[3] == 'X' && map[2] == '2'){
        return 2;
    } else if (map[7] == map[9] && map[9] == 'X' && map[8] == '8'){
        return 8;
    } else if (map[5] == map[8] && map[8] == 'X' && map[2] == '2'){
        return 2;
    } else if (map[1] == map[7] && map[7] == 'X' && map[4] == '4'){
        return 4;
    } else if (map[3] == map[9] && map[9] == 'X' && map[6] == '6'){
        return 6;
    } else if (map[4] == map[5] && map[5] == 'X' && map[6] == '6'){
        return 6;
    } else if (map[2] == map[5] && map[5] == 'X' && map[8] == '8'){
        return 8;
    } else if (map[5] == map[6] && map[6] == 'X' && map[4] == '4'){
        return 4;
    } else if (map[1] == map[3] && map[3] == 'X' && map[2] == '2'){
        return 2;
    } else if (map[7] == map[9] && map[9] == 'X' && map[8] == '8'){
        return 8;
    } else if (map[5] == map[8] && map[8] == 'X' && map[2] == '2'){
        return 2;
    } else if (map[1] == map[7] && map[7] == 'X' && map[4] == '4'){
        return 4;
    } else if (map[3] == map[9] && map[9] == 'X' && map[6] == '6'){
        return 6;
    } else if (map[1] == map[2] && map[2] == 'O' && map[3] == '3'){
        return 3;
    } else if (map[7] == map[8] && map[8] == 'O' && map[9] == '3'){
        return 9;
    } else if (map[1] == map[4] && map[4] == 'O' && map[7] == '7'){
        return 7;
    } else if (map[3] == map[6] && map[6] == 'O' && map[9] == '9'){
        return 9;
    } else if (map[2] == map[3] && map[3] == 'O' && map[1] == '1'){
        return 1;
    } else if (map[8] == map[9] && map[9] == 'O' && map[7] == '7'){
        return 7;
    } else if (map[4] == map[6] && map[6] == 'O' && map[5] == '5'){
        return 5;
    } else if (map[4] == map[7] && map[7] == 'O' && map[1] == '1'){
        return 1;
    } else if (map[6] == map[9] && map[9] == 'O' && map[3] == '3'){
        return 3;
    } else if (map[2] == map[8] && map[8] == 'O' && map[5] == '5'){
        return 5;
    } else if (map[1] == map[5] && map[5] == 'O' && map[9] == '9'){
        return 9;
    } else if (map[1] == map[9] && map[9] == 'O' && map[5] == '5'){
        return 5;
    } else if (map[9] == map[5] && map[5] == 'O' && map[1] == '1'){
        return 1;
    } else if (map[3] == map[5] && map[5] == 'O' && map[7] == '7'){
        return 7;
    } else if (map[3] == map[7] && map[7] == 'O' && map[5] == '5'){
        return 5;
    } else if (map[7] == map[5] && map[5] == 'O' && map[3] == '3'){
        return 3;
    } else if (map[4] == map[5] && map[5] == 'O' && map[6] == '6'){
        return 6;
    } else if (map[2] == map[5] && map[5] == 'O' && map[8] == '8'){
        return 8;
    } else if (map[5] == map[6] && map[6] == 'O' && map[4] == '4'){
        return 4;
    } else if (map[1] == map[3] && map[3] == 'O' && map[2] == '2'){
        return 2;
    } else if (map[7] == map[9] && map[9] == 'O' && map[8] == '8'){
        return 8;
    } else if (map[5] == map[8] && map[8] == 'O' && map[2] == '2'){
        return 2;
    } else if (map[1] == map[7] && map[7] == 'O' && map[4] == '4'){
        return 4;
    } else if (map[3] == map[9] && map[9] == 'O' && map[6] == '6'){
        return 6;
    } else {
        while(1){
            int r = rand() % 9;
            if(r != 0 && map[r] != 'O' && map[r] != 'X'){
                return r;
            }
        }
    }
}

void updateBoard(){
        printf("                     _________________\n");
        printf("                    |[%dm     [0m|[%dm     [0m|[%dm     [0m|\n",playerMap[1],playerMap[2],playerMap[3]);
        printf("                    |[%dm  %c  [0m|[%dm  %c  [0m|[%dm  %c  [0m|\n",playerMap[1], map[1], playerMap[2], map[2], playerMap[3], map[3]);
        printf("                    |[%dm_____[0m|[%dm_____[0m|[%dm_____[0m|\n",playerMap[1],playerMap[2],playerMap[3]);
        printf("                    |[%dm     [0m|[%dm     [0m|[%dm     [0m|\n",playerMap[4],playerMap[5],playerMap[6]);
        printf("                    |[%dm  %c  [0m|[%dm  %c  [0m|[%dm  %c  [0m|\n",playerMap[4], map[4], playerMap[5], map[5], playerMap[6], map[6]);
        printf("                    |[%dm_____[0m|[%dm_____[0m|[%dm_____[0m|\n",playerMap[4],playerMap[5],playerMap[6]);
        printf("                    |[%dm     [0m|[%dm     [0m|[%dm     [0m|\n",playerMap[7],playerMap[8],playerMap[9]);
        printf("                    |[%dm  %c  [0m|[%dm  %c  [0m|[%dm  %c  [0m|\n",playerMap[7], map[7], playerMap[8], map[8], playerMap[9], map[9]);
        printf("                    |[%dm_____[0m|[%dm_____[0m|[%dm_____[0m|\n",playerMap[7],playerMap[8],playerMap[9]);
        printf("\n");
}

void challengePC(){
    catchPhrase(level);
    printf("[32mEnter Player Name (O) : [0m");
    scanf("%s", &p1.name);
    p1.style = 'O';
    strcpy(p2.name,"Computer");
    p2.style = 'X';
    while(1){
        catchPhrase(level);
        printf("[32m%s[0m play as \'[42m O [0m\' & [33m%s[0m play as \'[43m X [0m\'\n\n",p1.name,p2.name);
        updateBoard();
        int mark;
        int player;
        if(map[0] == 'X' || map[0] == ' '){
            printf("[32m%s Enter a number : [0m", p1.name);
            player = 1;
            scanf("%d", &mark);
            if(mark > 9 || mark < 1){
                printf("[31mInvalid point look at the board idiot![0m\n");
                system("pause");
                continue;
            }
        } else {
            if(level == 1){
                mark = getPointEasy();
            } else if(level == 2){
                mark = getPointHard();
            } else if(level == 3){
                mark = getPointInsane();
            }
            player = 2;
        }

        if(map[mark] != 'O' && map[mark] != 'X'){
            if(player == 1){
                map[mark] = 'O';
                playerMap[mark] = 42;
                for(int i = 0; i < 5; i++){
                    if(p1.arr[i] == 0){
                       p1.arr[i] = mark;
                       break;
                    }
                }
                map[0] = 'O';
            } else {
                map[mark] = 'X';
                playerMap[mark] = 43;
                for(int i = 0; i < 5; i++){
                    if(p2.arr[i] == 0){
                       p2.arr[i] = mark;
                       break;
                    }
                }
                map[0] = 'X';
            }
        } else {
            printf("[31mYou can't use a marked point. Try another ![0m\n");
            system("pause");
            continue;
        }
        if(checkWin() == 4){
            continue;
        } else {
            catchPhrase(level);
            printf("[32m%s[0m play as \'[42m O [0m\' & [33m%s[0m play as \'[43m X [0m\'\n\n",p1.name,p2.name);
            updateBoard();
            if(checkWin() == 3){
                printf("[36m\nNo one wins Match has draw[0m\n");
                saveDataToFile(level,0);
                break;
            } else if(checkWin() == 1){
                printf("[32m\n%s has won the match[0m\n", p1.name );
                saveDataToFile(level,1);
                break;
            } else if(checkWin() == 2){
                printf("[33m\%s has won the match[0m\n", p2.name );
                saveDataToFile(level,2);
                break;
            }
        }
    }
    system("pause");
}

void playGameWithHuman(){
    catchPhrase(0);
    printf("[32mEnter Player 1 Name (O) : [0m");
    scanf("%s", &p1.name);
    p1.style = 'O';
    printf("[33mEnter Player 2 Name (X) : [0m");
    scanf("%s", &p2.name);
    p2.style = 'X';
    while(1){
        catchPhrase(0);
        printf("[32m%s[0m play as \'[42m O [0m\' & [33m%s[0m play as \'[43m X [0m\'\n\n",p1.name,p2.name);
        updateBoard();
        int mark;
        int player;
        if(map[0] == 'X' || map[0] == ' '){
            printf("[32m%s Enter a number : [0m", p1.name);
            player = 1;
        } else {
            printf("[33m%s Enter a number : [0m", p2.name);
            player = 2;
        }
        scanf("%d", &mark);
        if(mark > 9 || mark < 1){
            printf("[31mInvalid point look at the board idiot![0m\n");
            system("pause");
            continue;
        }
        if(map[mark] != 'O' && map[mark] != 'X'){
            if(player == 1){
                map[mark] = 'O';
                playerMap[mark] = 42;
                for(int i = 0; i < 5; i++){
                    if(p1.arr[i] == 0){
                       p1.arr[i] = mark;
                       break;
                    }
                }
                map[0] = 'O';
            } else {
                map[mark] = 'X';
                playerMap[mark] = 43;
                for(int i = 0; i < 5; i++){
                    if(p2.arr[i] == 0){
                       p2.arr[i] = mark;
                       break;
                    }
                }
                map[0] = 'X';
            }
        } else {
            printf("[31mYou can't use a marked point. Try another ![0m\n");
            system("pause");
            continue;
        }
        if(checkWin() == 4){
            continue;
        } else {
            catchPhrase(0);
            printf("[32m%s[0m play as \'[42m O [0m\' & [33m%s[0m play as \'[43m X [0m\'\n\n",p1.name,p2.name);
            updateBoard();
            if(checkWin() == 3){
                printf("[36m\nNo one wins Match has draw[0m\n");
                saveDataToFile(0,0);
                break;
            } else if(checkWin() == 1){
                printf("[32m\n%s has won the match[0m\n", p1.name );
                saveDataToFile(0,1);
                break;
            } else if(checkWin() == 2){
                printf("[33m\%s has won the match[0m\n", p2.name );
                saveDataToFile(0,2);
                break;
            }
        }
    }
    system("pause");
}

void displayInstructions(){
    catchPhrase(4);
    printf("[32m1. Select a game mode.[0m\n");
    printf("[32m2. Give player names.[0m\n");
    printf("[32m3. Use point numbers to add your mark.[0m\n");
    printf("[32m4. Play until win or draw.[0m\n\n");
    printf("[91mDeveloped by [0m[101mRuwan Rohitha 2020T00904[0m\n\n");
    printf("[31mNote : for better view change console font size to 32[0m\n");
    system("pause");
}

void previousRecords(){
    catchPhrase(5);
    char  row[255];
    FILE  *fp;
    fp = fopen( "gameData.txt", "r" );
    if ( fp == NULL ) {
        printf("No previous data !\n");
        system("pause");
        return;
    }
    while ( fgets( row, sizeof( row ), fp ) != NULL ) {
            char a[100] = "[101m";
            char b[100] = "[32m";
            char c[100] = "[33m";
            char d[100] = "[34m";
            char e[100] = "[31m";
            char g[100] = "[36m";
            char f[] = "[0m";

            if(strstr(row,"Game Type")){
                strcat(a,row);
                strcat(a,f);
                printf(a);
            } else if(strstr(row,"won the match") || strstr(row,"Match has draw")){
                strcat(e,row);
                strcat(e,f);
                printf(e);
            } else if(strstr(row,"(O)")){
                strcat(b,row);
                strcat(b,f);
                printf(b);
            } else if(strstr(row,"(X)")){
                strcat(c,row);
                strcat(c,f);
                printf(c);
            } else if(strstr(row,":")){
                strcat(g,row);
                strcat(g,f);
                printf(g);
            } else if(strstr(row,"Game moves")){
                strcat(d,row);
                strcat(d,f);
                printf(d);
            } else {
                printf(row);
            }

    }
    fclose( fp );
    system("pause");
}

void clearPreviousRecords(){
    if (remove("gameData.txt") == 0){
      printf("Previous Records Cleared Successfully\n");
    } else {
      printf("Unable to Clear Data\n");
    }
    system("pause");
}

void menu(){
    while(1){
        int n;
        resetMap();
        system("cls");
        printf("[34m=============================================================[0m\n");
        printf("[34m                  --------TIC TAC TOE---------               [0m\n");
        printf("[34m=============================================================[0m\n");
        printf("\n");
        printf("[33m1. INSTRUCTIONS[0m\n");
        printf("[33m2. PLAY WITH A FRIEND[0m\n");
        printf("[33m3. PLAY WITH COMPUTER (EASY) 90%% WIN RATE[0m\n");
        printf("[33m4. PLAY WITH COMPUTER (HARD) 50%% WIN RATE[0m\n");
        printf("[33m5. PLAY WITH COMPUTER (INSANE) 1%% WIN RATE[0m\n");
        printf("[33m6. VIEW PREVIOUS RECORDS[0m\n");
        printf("[33m7. CLEAR PREVIOUS RECORDS[0m\n");
        printf("[33m8. EXIT[0m\n");
        printf("\n");
        printf("[32mEnter Menu Number : [0m");
        scanf("%d", &n);
        if(n == 1){
            displayInstructions();
        } else if (n == 2){
            playGameWithHuman();
        } else if(n == 3){
            level = 1;
            mask = rand() % 3;
            challengePC();
        } else if(n == 4){
            level = 2;
            mask = rand() % 3;
            challengePC();
        } else if(n == 5){
            level = 3;
            challengePC();
        } else if(n == 6){
            previousRecords();
        } else if(n == 7){
            clearPreviousRecords();
        } else if(n == 8){
            system("cls");
            exit(0);
        } else {
            printf("[31mInvalid Menu Number! Try Again...[0m\n");
            fflush(stdin);
            system("pause");
        }
    }
}

int main(){
    system("color 7");
    time_t t;
    srand((unsigned) time(&t));
    menu();
}

















#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

#define MAPWIDTH 10
#define MAPHEIGHT 10
#define SNAKELENGTH (MAPWIDTH-2)*(MAPHEIGHT-2)
#define SLEEP 30



// Struct for defining the Fruit: a couple of coordinates
typedef struct{

    int r;
    int c;

}Fruit;

// Struct for defining the Snake: two arrays => #SNAKELENGTH couples of coordinates
typedef struct{

    int r[SNAKELENGTH];
    int c[SNAKELENGTH];

}Snake;


// Defines some global variables, used in the following functions
Fruit fruit;
Snake snake;

int moveMade=0;
int length=1;   // actual length of the snake
int score=0;
int gameover=0;
int dead=0;
int last_snakeR=0;
int last_snakeC=0;


// Function for creating the map
void setMap(int map[MAPHEIGHT][MAPWIDTH]){

        for(int i=0; i< MAPHEIGHT; i++){
            for(int j=0; j<MAPWIDTH; j++){

                if(i==0 || i==(MAPHEIGHT-1)){
                    map[i][j]=1;
                }
                else if(j==0 || j==(MAPWIDTH-1)){
                    map[i][j]=1;
                }
                else{
                    map[i][j]=0;
                }

            }

            printf("\n");
        }

    return;
}


// Function for printing the map, while positioning the fruit and the snake in it
void printMap(int map[MAPHEIGHT][MAPWIDTH], int r, int c, int s_r[], int s_c[]){

    system("cls");
    for(int i=0; i< MAPHEIGHT; i++){
            for(int j=0; j<MAPWIDTH; j++){

                    // Check if in that cell there is the snake
                    int snake=0;
                    for(int k=0; k<length; k++){
                        if(s_r[k]==i && s_c[k]==j){
                            snake=1;
                            break;
                        }

                    }


                    if(map[i][j]==1){
                        printf("oo");
                    }
                    else if(i==r && j==c){
                        printf("xx");
                    }
                    else if(snake){
                        printf("[]");
                    }
                    else{
                        printf("  ");
                    }

            }

            printf("\n");
        }

    return;
}

// Function to print the rules on the right
void gotoxy(int x, int y){
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// Prints the game's rules
void GameExplain(){
	gotoxy(70, 10);
	puts("MOVE: a(left),w(up),d(right),s(down)");

	gotoxy(70, 11);
	puts("Exit : e");

	gotoxy(70, 13);
	puts("~ Game over if head touches the body or the wall");

	gotoxy(70, 14);
	puts("~ The score +1 point if you eat the Fruit xx");


}

// Function for computing the new position of the fruit
Fruit setup(Fruit fruit){

    int snakeOccupied;

    // Checks if the cell is already occupied by the snake
    do{
        snakeOccupied=0;
        fruit.r = rand()%(MAPHEIGHT-2)+1;
        fruit.c= rand()%(MAPWIDTH-2)+1;
        for(int i=0; i<length;i++){
            if(snake.r[i]==fruit.r && snake.c[i]==fruit.c){
                snakeOccupied=1;
                break;
            }
        }
    }while(snakeOccupied);

    return fruit;
}

// Function to make the snake move: moves every part of the body forward of 1 cell, except the head
// The cell in position n, after this function, will be were the cell n1 was before
void updateSnake(){

    for(int i=length-1; i>0; i--){
        snake.r[i]= snake.r[i-1];
        snake.c[i]= snake.c[i-1];
    }

    return;
}

// Function for verifying if the snake has bitten himself
bool snakeTouchHimself(){

    bool touch=false;

    for(int i=1; i<length;i++){

        if(snake.r[0]==snake.r[i] && snake.c[0]==snake.c[i]){
            touch=true;
            break;
        }
    }

    return touch;
}

// Function to take in input the move of the player
int input(){

    int move;

    // To catch an interrupt from the keyboard
	if (_kbhit()){

        // Only if the user press the correct buttons, i understand that the snake has to  move, by putting moveMade=1
        int key = _getch();
        switch(key){

        case 'a':
            moveMade=1;
            move=1;
            break;
        case 'w':
            moveMade=1;
            move=2;
            break;
        case 'd':
            moveMade=1;
            move=3;
            break;
        case 's':
            moveMade=1;
            move=4;
            break;
        case 'e':
            move=0;
            break;

        }
    }
    else{
        moveMade=0;
    }
    return move;
}

// Function to compute how the snake will move
void logic(int move){   // Check if the game is ended, if not i make the snake move

    if(move==0){
        gameover=1;
        return;
    }

    if(moveMade){   // If the snake has moved, calls the function
        updateSnake();
    }


    // Decides where to move the head of the snake, based on which command has been insert
    switch(move){

    case 1:// a: left
        snake.c[0]--;
        break;
    case 2:// w:up
        snake.r[0]--;
        break;
    case 3:// d: right
        snake.c[0]++;
        break;
    case 4://  s: down
        snake.r[0]++;
        break;
    }


    return;
}


// main function to play the game
void main(){

    int map[MAPHEIGHT][MAPWIDTH];

    printf("score: %d ", score);

    //Initialize the map with the borders
    setMap(map);

    // Initialize snake's parameters
    snake.r[0]= MAPHEIGHT/2;
    snake.c[0]=MAPWIDTH/2;

    // Initialize fruit's parameter
    fruit= setup(fruit);


    while(!gameover){

        printf("score: %d \n", score);

        // Saves the position of the last cell, to be able to update the snake
        last_snakeR=snake.r[length-1];
        last_snakeC=snake.c[length-1];

        // Print map to video
        printMap(map,fruit.r, fruit.c, snake.r, snake.c);

        GameExplain();


        // Catches the user move
        logic(input());


        if( snake.r[0]== fruit.r && snake.c[0]==fruit.c){

            // Setup of the fruit within the bounds
            fruit= setup(fruit);
            // Increments the score and the length of the snake
            score++;
            length++;
            // Add one position to the snake at the end
            snake.r[length-1]=last_snakeR;
            snake.c[length-1]=last_snakeC;
        }

        // If the snake touches the border of the map => GAMEOVER & CONTINUE (skips all the other commands after this)
        if( snake.r[0]==0 || snake.r[0]==(MAPHEIGHT-1) || snake.c[0]==0 || snake.c[0]==(MAPWIDTH-1)){

            dead=1;
            gameover=1;
            continue;

        }

        // If the snake bites himself => GAMEOVER & CONTINUE (skips all the other commands after this)
        if( snakeTouchHimself()){
            dead=1;
            gameover=1;
            continue;

        }


        // Condition for winning => print a message for the user
        if(length==SNAKELENGTH-1){
            printf("Congratulation, you WIN!");
            return;
        }
        Sleep(SLEEP);


    }

    if(dead){
        printf("You are DEAD, try again!");
    }

    return;
}







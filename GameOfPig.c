#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int get_Target();
void displayDice(int number);
int diceRoll();
void gameLoop(int * turn, int winScore, int p1Total, int p2Total, int p1Score, int p2Score);
int moveOrHold(int * turn);
void displayDice(int number);

int main()
{ 
    /*This will store the dice values until player hangs up*/
    int p1Score = 0;
    int p2Score = 0;

    /*This will add the values of player one and two to their final score*/
    int p1Total = 0; 
    int p2Total = 0;

    /*1 is player 1's turn, 2 is player 2's turn*/
    int * turn = malloc(sizeof(int) * 1); 
    *turn = 1;

    /*This is the predecided final score needed to win the game */
    int winScore = 0; 
    

    winScore = get_Target();
    gameLoop(turn, winScore, p1Total, p2Total, p1Score, p2Score);

    return 0;
}

void gameLoop(int * turn, int winScore, int p1Total, int p2Total, int p1Score, int p2Score)
{
    printf("\n(Player Total) Player 1: %d | Player 2: %d\n", p1Total, p2Total);
    printf("Player %d's turn\n", *turn);
    int diceNum = 0;
    if(p1Total >= winScore || p2Total >= winScore)
    {
        printf("\n** PLAYER %d WON **\n", *turn);
        free(turn);
        exit(1);
    }


    int move = 0;
    move = moveOrHold(turn);
        
    if(move == 1)
    {
        diceNum = diceRoll();
        switch(diceNum)
        {
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                if(*turn == 1)
                {
                    p1Score = p1Score + diceNum;
                    printf("player 1 score: %d\n", p1Score);

                    if(p1Score >= winScore)
                    {
                        printf("\n** PLAYER 1 WON **\n");
                        free(turn);
                        exit(1);
                    }

                    gameLoop(turn, winScore, p1Total, p2Total, p1Score, p2Score);
                }

                else
                {
                    p2Score = p2Score + diceNum;
                    printf("player 2 score: %d\n", p2Score);

                    if(p2Score >= winScore)
                    {
                        printf("\n** PLAYER 2 WON **\n");
                        free(turn);
                        exit(1);
                    }

                    gameLoop(turn, winScore, p1Total, p2Total, p1Score, p2Score);
                }     
            break;

            case 1:
                if(*turn == 1)
                {
                    p1Score = 0;
                    *turn = 2; //hand the dice to other player
                    gameLoop(turn, winScore, p1Total, p2Total, p1Score, p2Score);
                }

                else
                {
                    p2Score = 0;
                    *turn = 1;
                    gameLoop(turn, winScore, p1Total, p2Total, p1Score, p2Score);
                }
                    
            break;
            }
        }

        if(move == 2)
        {
            if(*turn == 1)
            {
                p1Total = p1Total + p1Score;
                *turn = 2;
            }
            else
            {
                p2Total = p2Total + p2Score;
                *turn = 1;
            }
            
            gameLoop(turn, winScore, p1Total, p2Total, p1Score, p2Score);
        }
}


int moveOrHold(int * turn)
{
    int move = 0;
    char userInput[100] = {0};
    bool found_alpha = false;

    do{
        printf("Pick a move:\n(1)play\n(2)hold\n"); 
        fgets(userInput, 100, stdin);

        for(int i = 0; i < strlen(userInput); i++)
        {
            if(isdigit(userInput[i]) == -1)
            {
                move = 3;
                found_alpha = true;
            }
        }

        if(found_alpha == false)
        {
            move = atoi(userInput);
        }


        if(move != 2 && move != 1)
        {
            printf("Wrong option, please try again\n");
        }
    }while(move != 1 && move != 2);


    return move;
}

int get_Target()
{
    int winScore = 0;
    char win[100] = {0};
    bool number = true;
    printf("-- Welcome to the game of pig --\n");
    
    do{
        
        printf("Set the target score: ");
        fgets(win, 100, stdin);
        printf("\n\n");

        for(int i = 0; i < strlen(win); i++)
        {
            if(isdigit(win[i]) == -1)
            {
                winScore = -1;
                number = false;
            }
        }

        if(number == true)
        {
            winScore = atoi(win);
        }
        

        if(winScore <= 0){
            printf("** Please choose a valid number [Greater than 0]**\n");
        }

    }while(winScore <= 0);   
    return winScore;
}


int diceRoll()
{
    /*this will store the dice value*/
    srand(time(NULL));
    int dice_num = rand() % 6 + 1;
    displayDice(dice_num);
    return dice_num;
}



void displayDice(int number)
{

    char dice1[5][5] = {
        {"-----"},
        {"|   |"},
        {"| o |"},
        {"|   |"},
        {"-----"}
    };

    char dice2[5][5] = {
        {"-----"},
        {"|o  |"},
        {"|   |"},
        {"|  o|"},
        {"-----"}
    };

    char dice3[5][5] = {
        {"-----"},
        {"|o  |"},
        {"| o |"},
        {"|  o|"},
        {"-----"}
    };

    char dice4[5][5] = {
        {"-----"},
        {"|o o|"},
        {"|   |"},
        {"|o o|"},
        {"-----"}
    };

    char dice5[5][5] = {
        {"-----"},
        {"|o o|"},
        {"| o |"},
        {"|o o|"},
        {"-----"}
    };

    char dice6[5][5] = {
        {"-----"},
        {"|o o|"},
        {"|o o|"},
        {"|o o|"},
        {"-----"}
    };


    switch(number)
    {
        case 1:
            for(int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    printf("%c", dice1[i][j]);
                }
            printf("\n");
            }
        break;

        case 2:
            for(int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    printf("%c", dice2[i][j]);
                }
            printf("\n");
            }
        break;

        case 3:
            for(int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    printf("%c", dice3[i][j]);
                }
            printf("\n");
            }
        break;

        case 4:
            for(int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    printf("%c", dice4[i][j]);
                }
            printf("\n");
            }
        break;

        case 5:
            for(int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    printf("%c", dice5[i][j]);
                }
            printf("\n");
            }
        break;

        case 6:
            for(int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    printf("%c", dice6[i][j]);
                }
            printf("\n");
            }
        break;
    }

    return;
}
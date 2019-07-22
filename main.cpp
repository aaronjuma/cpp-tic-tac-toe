#include <iostream>
#include "boardControl.h" //Includes the boardControl external cpp file, file is in the folder or in the directory
using namespace std; //Makes definitons visible


//Remove this and repleace each pause function wiht system("PAUSE");
void pause()
{
    cout << "Press any button....";
    cin.get();
}

int main()
{
    //Creates enum variables to tell what each player is 
    Player first_player;
    Player second_player;

    //Variable definitons
    int turns;
    bool playAgain = false;

    /*
     * This do-while loop will continue until the user
     * inputs no when asked if they'd like to play again
     */
    do
    {
        //Resets the board and the turns
        turns = 0;

        //The enums, X or O, will be set to these variables based on the user's input
        first_player = gameIntroduction();
        second_player = whatIsSecondPlayer(first_player);

        //Before starting the game, the board will set the winner to invalid so that it keeps looping
        Winner winner = INVALID;

        while(winner == INVALID)
        {
            //The function is called in the beginning to check if there is a tie
            winner = checkForWinner(turns);

            //Asks player one 
            printBoard();
            askFor(first_player);
            turns++;
            
            //Checks if player one wins
            if(checkForWinner(turns) != INVALID)
            {
                winner = checkForWinner(turns);
                break;
            }

            //Asks player two
            printBoard();
            askFor(second_player);
            turns++;

            //Checks if player two wins
            if(checkForWinner(turns) != INVALID)
            {
                winner = checkForWinner(turns);
                break;
            }
        }
        //Calls the function to announce the winner
        announceWinner(winner, first_player, second_player);

        //Asks user if he/she would like to play again
        playAgain = anotherGame();

    }while(playAgain == true);
    
    
    /*ENDING PROGRAM*/ 
    pause(); //TODO: change to system("PAUSE");
    return 0;  
}


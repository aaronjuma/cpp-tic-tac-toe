#ifndef BOARDCONTROL_H_
#define BOARDCONTROL_H_

/*
 * This is an external cplusplus file
 * which controls the tic tac toe board
 * This file will be included in the main file
 */
#include <iostream>
#include <string>
using namespace std;

/*CONSTANTS*/
const int boardRows = 3;
const int boardColumns = 3;
const int maxTurns = 9;
const int maxSlots = 9;






/* 
 * ############################################
 * ##            BOARD SETUP                 ##
 * ############################################
 */

/*TIC TAC TOE BOARD*/
char Board[boardRows][boardColumns] = 
{
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
};

//Creates pointers to make setting each points easier
char * setpoint[maxSlots] =
{
    &Board[0][0],   //Slot 1
    &Board[0][1],   //Slot 2
    &Board[0][2],   //Slot 3
    &Board[1][0],   //Slot 4
    &Board[1][1],   //Slot 5
    &Board[1][2],   //Slot 6
    &Board[2][0],   //Slot 7
    &Board[2][1],   //Slot 8
    &Board[2][2]    //Slot 9
};


//Function to set a slot to a piece
void setSlot(int slot, char piece)
{
    int actualSlot = slot-1;
    *setpoint[actualSlot] = piece;
}

//Function to get the piece of a slot
char getSlot(int slot)
{
    int actualSlot = slot-1;
    return *setpoint[slot-1];
}








/* 
 * ############################################
 * ##            ENUMERATIONS                ##
 * ############################################
 */

/*Player Enum*/
enum Player
{
    X,
    O
};

/*Winner Enum*/
enum Winner
{
    INVALID = 0,
    x = 1,
    o = 2,
    TIE = 3
};












/* 
 * ############################################
 * ##            CONSOLE CONTROL             ##
 * ############################################
 */

/*Clears the console*/
void clearConsole() 
{
    system("clear"); //TODO: system("CLS")
}

/*RESETS THE BOARD*/
void resetBoard()
{
    char number = 48;
    for(int rows=0; rows<boardRows; rows++)
    {
        for(int columns=0; columns<boardColumns; columns++)
        {
            Board[rows][columns] = ++number;
        }
    }
}

/*PRINTS THE BOARD*/
void printBoard()
{
    clearConsole();

    /*
     * Prints the title of the board
     */
    cout << "\12\11TIC TAC TOE BOARD" << endl;
    cout << "\11";
    for(int count = 0;count<17;count++)
    {
        cout.put('*');
    }
    cout << endl << endl;

    /*
     * Prints each row and column
     */
    int slot = 0;
    for(int rows=0;rows<boardRows;rows++)
    {
        //Prints each column
        cout << "\11  ";
        for(int columns=0;columns<boardColumns;columns++)
        {
            cout << " ";
            cout.put(getSlot(++slot));
            cout << " ";

            //Puts a seperation line in between columns
            if(columns != 2)
            {
                cout.put('|');
            }
        }
        cout << endl;

        //Puts a seperation line in between rows
        cout << "\11  ";
        if(rows != 2)
        {
            for(int count = 0;count<10;count++)
            {
                cout << "-";
            }
        }
        cout << endl;
    }
}












/* 
 * ############################################
 * ##     Introduction/Ending Functions      ##
 * ############################################
 */

/*Function that introduces the user and figures out what Player One will be*/
Player gameIntroduction()
{
    clearConsole();
    bool status = 1;
    cout << "Welcome to C++ Tic Tac Toe!" << endl;
    
    string player;
    Player returnPlayer;

    while(status == 1){
        cout << "What would Player One like to play as? (X/O): ";
        getline(cin, player);
        if(cin.fail())
        {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl << "That is an invalid input!" << endl;
                status = 1;
        }
        else
        {
            if(player == "X" || player == "x")
            {
                returnPlayer = X;
                status = 0;
            }
            else if(player == "O" || player == "o")
            {
                returnPlayer = O;
                status = 0;
            }
            else
            {
                cout << endl << "That is an invalid input!" << endl;
                status = 1;
            }
        }
    }

    return returnPlayer;
}

/*Function that returns what Player Two will be after Player One chooses*/
Player whatIsSecondPlayer(Player firstPlayer)
{
    return (firstPlayer== X) ? O:X;
}

/*Function that asks user to play another game*/
bool anotherGame()
{
    //Variable declaration
    bool playAgain;
    bool status = true;
    string yes_no;

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while(status == true)
    {
        cout << "Would you like to play again? (Yes/No): ";
        getline(cin, yes_no);
        
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Invalid input!";
            status = true;
        }
        else
        {
            if(yes_no == "Yes" || yes_no == "yes" || yes_no == "Y" || yes_no == "y")
            {
                playAgain = true;
                resetBoard();
                status = false;
            }
            else if(yes_no == "No" || yes_no == "no" || yes_no == "N" || yes_no == "n")
            {
                playAgain = false;
                clearConsole();
                cout << "Well then, Thank you for playing and see you again soon!" << endl;
                status = false;
            }
            else
            {
                cout << "Invalid input!" << endl;
                status = true;
            }
        }
    }
    return playAgain;
}















/* 
 * ############################################
 * ##            PLAY CONTROLS               ##
 * ##  X/O CONTROLS AND WINNER INDENTIFIER   ##
 * ############################################
 */

/*Function that identify the winner*/
Winner checkForWinner(int turns)
{
    Winner winner;
    bool weHaveAWinner = false;
    
    //CHECKS FOR X
    if(
        (getSlot(1) == 'X' && getSlot(2) == 'X' && getSlot(3) == 'X') || //Checks Row 1
        (getSlot(4) == 'X' && getSlot(5) == 'X' && getSlot(6) == 'X') || //Checks Row 2
        (getSlot(7) == 'X' && getSlot(8) == 'X' && getSlot(9) == 'X') || //Checks Row 3
        (getSlot(1) == 'X' && getSlot(4) == 'X' && getSlot(7) == 'X') || //Checks Column 1
        (getSlot(2) == 'X' && getSlot(5) == 'X' && getSlot(8) == 'X') || //Checks Column 2
        (getSlot(3) == 'X' && getSlot(6) == 'X' && getSlot(9) == 'X') || //Checks Column 3
        (getSlot(1) == 'X' && getSlot(5) == 'X' && getSlot(9) == 'X') || //Checks Diagonal 1
        (getSlot(3) == 'X' && getSlot(5) == 'X' && getSlot(7) == 'X')    //Checks Diagonal 2
    )
        {
            winner = x;
            weHaveAWinner = true;
        }
    
    //CHECKS FOR O
    else if(
        (getSlot(1) == 'O' && getSlot(2) == 'O' && getSlot(3) == 'O') || //Checks Row 1
        (getSlot(4) == 'O' && getSlot(5) == 'O' && getSlot(6) == 'O') || //Checks Row 2
        (getSlot(7) == 'O' && getSlot(8) == 'O' && getSlot(9) == 'O') || //Checks Row 3
        (getSlot(1) == 'O' && getSlot(4) == 'O' && getSlot(7) == 'O') || //Checks Column 1
        (getSlot(2) == 'O' && getSlot(5) == 'O' && getSlot(8) == 'O') || //Checks Column 2
        (getSlot(3) == 'O' && getSlot(6) == 'O' && getSlot(9) == 'O') || //Checks Column 3
        (getSlot(1) == 'O' && getSlot(5) == 'O' && getSlot(9) == 'O') || //Checks Diagonal 1
        (getSlot(3) == 'O' && getSlot(5) == 'O' && getSlot(7) == 'O')    //Checks Diagonal 2
    )
        {
            winner = o;
            weHaveAWinner = true;
        }

    //CHECKS FOR TIE
    else if(turns == 9 && weHaveAWinner == false)
        {
            winner = TIE;
        }
    
    //IF THERE IS NO WINNER, IT RETURNS INVALID
    else
        {
            winner = INVALID;
        }

    return winner;
}


/*Function that asks the user to place their piece on the board*/
void askFor(Player player)
{
    string boardNum;
    int actualBoardNum;
    bool status = true;
    bool alreadyPrintedError = false;

    while(status == true)
    {
        (player == X) ? cout << "X, Select a number to put your piece in: ":cout << "O, Select a number to put your piece in: ";
        getline(cin, boardNum);
        alreadyPrintedError = false;

        //If the user input failes
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printBoard();
            cout << "Invalid input!" << endl;
            alreadyPrintedError = true;
            status = true;
        }

        //If the user input succeeds
        else
        {
            //If it is a double digit input
            if(input[1] != char(0))
            {
                cout << "WRONG!" << endl;
            }
            
            else
            {
                if(isdigit(input[0]))
                {
                    actualBoard = input[0] - '0';
                    cout << actualBoard << endl;
                }  
                else
                {
                    cout << "WRONG!" << endl;
                }
            }          
            //If the user input is outside the setpoint range
            if((boardNum>9 || boardNum<1) || alreadyPrintedError == false)
            {
                printBoard();
                cout << "Invalid input!" << endl;
                alreadyPrintedError = true;
                status = true;
            }

            if(boardNum<=9 || boardNum>=1)
            {
                /*
                 * The input is turned into an int and multiplied by 10
                 * This is because switch statements don't accept doubles
                 * and because it checks if the input has a decimal
                 */
                switch(int(boardNum*10.0)) 
                {
                    //Checks for the 1 slot
                    case 10:
                        if(getSlot(1) == 'X' || getSlot(1) == 'O') 
                        {
                            printBoard();
                            cout << "Invalid input!" << endl;
                            status = true;
                        }
                        else
                        {
                            if(player == X)
                            {
                                setSlot(1, 'X');
                                status = false;
                            }
                            else
                            {
                                setSlot(1, 'O');
                                status = false;
                            }
                        }
                        break;
                    //Checks for the 2 slot
                    case 20:
                        if(getSlot(2) == 'X' || getSlot(2) == 'O')
                        {
                            printBoard();
                            cout << "Invalid input!" << endl;
                            status = true;
                        }
                        else
                        {
                            if(player == X)
                            {
                                setSlot(2, 'X');
                                status = false;
                            }
                            else
                            {
                                setSlot(2, 'O');
                                status = false;
                            }
                        }
                        break;
                    //Checks for the 3 slot
                     case 30:
                        if(getSlot(3) == 'X' || getSlot(3) == 'O')
                        {
                            printBoard();
                            cout << "Invalid input!" << endl;
                            status = true;
                        }
                        else
                        {
                            if(player == X)
                            {
                                setSlot(3, 'X');
                                status = false;
                            }
                            else
                            {
                                setSlot(3, 'O');
                                status = false;
                            }
                        }
                        break;
                    //Checks for the 4 slot
                    case 40:
                        if(getSlot(4) == 'X' || getSlot(4) == 'O') 
                        {
                            printBoard();
                            cout << "Invalid input!" << endl;
                            status = true;
                        }
                        else
                        {
                            if(player == X)
                            {
                                setSlot(4, 'X');;
                                status = false;
                            }
                            else
                            {
                                setSlot(4, 'O');
                                status = false;
                            }
                        }
                        break;
                    //Checks for the 5 slot
                    case 50:
                        if(getSlot(5) == 'X' || getSlot(5) == 'O') 
                        {
                            printBoard();
                            cout << "Invalid input!" << endl;
                            status = true;
                        }
                        else
                        {
                            if(player == X)
                            {
                                setSlot(5, 'X');;
                                status = false;
                            }
                            else
                            {
                                setSlot(5, 'O');
                                status = false;
                            }
                        }
                        break;
                    //Checks for the 6 slot
                    case 60:
                        if(getSlot(6) == 'X' || getSlot(6) == 'O')
                        {
                            printBoard();
                            cout << "Invalid input!" << endl;
                            status = true;
                        }
                        else
                        {
                            if(player == X)
                            {
                                setSlot(6, 'X');
                                status = false;
                            }
                            else
                            {
                                setSlot(6, 'O');
                                status = false;
                            }
                        }
                        break;
                    //Checks for the 7 slot
                    case 70:
                        if(getSlot(7) == 'X' || getSlot(7) == 'O')
                        {
                            printBoard();
                            cout << "Invalid input!" << endl;
                            status = true;
                        }
                        else
                        {
                            if(player == X)
                            {
                                setSlot(7, 'X');
                                status = false;
                            }
                            else
                            {
                                setSlot(7, 'O');
                                status = false;
                            }
                        }
                        break;
                    //Checks for the 8 slot
                    case 80:
                        if(getSlot(8) == 'X' || getSlot(8) == 'O')
                        {
                            printBoard();
                            cout << "Invalid input!" << endl;
                            status = true;
                        }
                        else
                        {
                            if(player == X)
                            {
                                setSlot(8, 'X');
                                status = false;
                            }
                            else
                            {
                                setSlot(8, 'O');
                                status = false;
                            }
                        }
                        break;
                    //Checks for the 9 slot
                    case 90:
                        if(getSlot(9) == 'X' || getSlot(9) == 'O')
                        {
                            printBoard();
                            cout << "Invalid input!" << endl;
                            status = true;
                        }
                        else
                        {
                            if(player == X)
                            {
                                setSlot(9, 'X');
                                status = false;
                            }
                            else
                            {
                                setSlot(9, 'O');
                                status = false;
                            }
                        }
                        break;
                    //If the input is something else
                    default:
                        if(alreadyPrintedError == false)
                        {
                            printBoard();
                            cout << "Invalid Input!" << endl;
                            status = true;
                            break;
                        }
                }
            }
        }
        
    }
}

/*Function that checks who the winner is and announces them*/
void announceWinner(Winner winner, Player firstPlayer, Player secondPlayer)
{
    printBoard();
    if(winner == x)
    {
        if(firstPlayer == X)
        {
            cout << "Player One (X) Wins!" << endl;
        }
        else if(secondPlayer == X)
        {
            cout << "Player Two (X) Wins!" << endl;
        }
    }
    else if (winner == o)
    {
        if(firstPlayer == O)
        {
            cout << "Player One (O) Wins!" << endl;
        }
        else if(secondPlayer == O)
        {
            cout << "Player Two (O) Wins!" << endl;
        }
    }
    else if (winner == TIE)
    {
        cout << "TIE!" << endl;
    }
}

#endif

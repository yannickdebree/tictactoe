#include <iostream>
#include <stdlib.h>
using namespace std;

int player = 2, round = 0, choice;
char square[10] = {'0', '1', '2', '3', '4', '5' , '6', '7', '8', '9'};

bool caseEvenChoosen();
bool hasWin();
char returnSymbol();
void iATurn();
void playerTurn();
void vue();

int main()
{
    do{
        player = (player == 1) ? 2 : 1;
        (player == 1) ? round++ : false;
        vue();
        choice = -1;
        switch(player)
        {
            case 1:
                playerTurn();
                break;
            case 2:
                iATurn();
                break;
        }
        square[choice] = returnSymbol();
    }
    while(!hasWin() && !(round == 5 && player == 1));
    system("clear");
    vue();
    string message;
    if(hasWin())
    {
        switch(player)
        {
            case 1:
                message = "You won !";
                break;
            case 2:
                message = "IA won...";
                break;
        }
    }
    else
    {
        message = "Equality !";
    }
    cout << message;

    return 0;
}

bool caseEvenChoosen()
{
    if(square[choice] == 'X' || square[choice] == 'O')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool hasWin()
{
    char symbol = returnSymbol();

    bool firstRowCompleted = (symbol == square[1] && square[1] == square[2] && square[2] == square[3] );
    bool secondRowCompleted = (symbol == square[4] && square[4] == square[5] && square[5] == square[6] );
    bool thirdRowCompleted = (symbol == square[7] && square[7] == square[8] && square[8] == square[9] );

    bool firstColumnCompleted = (symbol == square[1] && square[1] == square[4] && square[4] == square[7] );
    bool secondColumnCompleted = (symbol == square[2] && square[2] == square[5] && square[5] == square[8] );
    bool thirdColumnCompleted = (symbol == square[3] && square[3] == square[6] && square[6] == square[9] );

    bool topToBottomDiagonalCompleted = (symbol == square[1] && square[1] == square[5] && square[5] == square[9] );
    bool bottomToTopDiagonalCompleted = (symbol == square[3] && square[3] == square[5] && square[5] == square[7] );

    if(
        firstRowCompleted ||
        secondRowCompleted ||
        thirdRowCompleted ||
        firstColumnCompleted ||
        secondColumnCompleted ||
        thirdColumnCompleted ||
        topToBottomDiagonalCompleted ||
        bottomToTopDiagonalCompleted
    )
    {
        return true;
    }
    else
    {
        return false;
    }
}

char returnSymbol()
{
    return (player == 1) ? 'X' : 'O';
}

void iATurn()
{
    bool err = true;
    while(err)
    {
        choice = (rand() % 9) + 1;
        if(!caseEvenChoosen())
        {
            err = false;
        }
    }
}

void playerTurn()
{
    bool err = true;
    while(err){
        cout << "Player, make your choice : ";
        cin >> choice;
        if(cin.fail()) {
            cout << "Enter an integer number !"<<endl;
            cin.clear();
            cin.ignore(256,'\n');
        }
        else if(choice > 9 || choice < 1)
        {
            cout << "Enter a number between 1 and 9 ! " << endl;
        }
        else if(caseEvenChoosen())
        {
            cout << "The case has even been choosen ! " << endl;
        }
        else
        {
            err = false;
        }
    }
}

void vue()
{
    system("clear");
	cout << "Tic Tac Toe" << endl;
	cout << "Round " << round << endl;
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            cout << square[i * 3 + j + 1];
        }
        cout << endl;
    }
}

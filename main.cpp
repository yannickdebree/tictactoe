#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

int player = 2, round = 0, choice;
// char square[10] = {'0', '1', '2', '3', '4', '5' , '6', '7', '8', '9'};
char square[10] = {'0', 'X', 'O', 'X', '4', 'O' , '6', 'X', '8', '9'};

bool caseEvenChoosen();
bool hasWin();
bool hasWin(int p);
char returnSymbol();
char returnSymbol(int p);
int Min(char state[10], int deep);
int Max(char state[10], int deep);
int returnStateValue(char state[10]);
int twoSeriesNumber(char state[10]);
int twoSeriesNumber(char state[10], int player);
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
                message = "You're the winner !";
                break;
            case 2:
                message = "You're the looser...";
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
    hasWin(player);
}

bool hasWin(int p)
{
    char symbol = returnSymbol(p);

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
    return returnSymbol(player);
}

char returnSymbol(int p)
{
    // return (p == 1) ? 'X' : 'O';
    return (p == 1) ? 'O' : 'X';
}

int Min(char state[10], int deep)
{
    if(deep == 0 || hasWin() || hasWin(1))
    {
        return returnStateValue(state);
    }
    int min = 10000, temp;
    char tempSymbol;
    for(int i = 1; i < 10; ++i)
    {
        choice = i;
        if(!caseEvenChoosen())
        {
            tempSymbol = state[choice];
            state[choice] = returnSymbol();
            temp = Max(state, deep - 1);
            if(temp < min)
            {
                min = temp;
            }
            state[choice] = tempSymbol;
        }
    }
    return min;
}

int Max(char state[10], int deep)
{
    if(deep == 0 || hasWin() || hasWin(1))
    {
        return returnStateValue(state);
    }
    int max = -10000, temp;
    char tempSymbol;
    for(int i = 1; i < 10; ++i)
    {
        choice = i;
        if(!caseEvenChoosen())
        {
            tempSymbol = state[choice];
            state[choice] = returnSymbol();
            temp = Min(state, deep - 1);
            if(temp > max)
            {
                max = temp;
            }
            state[choice] = tempSymbol;
        }
    }
    return max;
}

int returnStateValue(char state[10])
{
    int turnsPlayed = 0;
    for(int i = 1; i < 10; ++i)
    {
        if(state[i] == returnSymbol() || state[i] == returnSymbol(1))
        {
            turnsPlayed++;
        }
    }
    bool playerWin = hasWin(1);
    bool iAWin = hasWin();
    if(playerWin)
    {
        return -10000 + turnsPlayed;
    }
    else if(iAWin)
    {
        return 10000 - turnsPlayed;
    }
    else if(!playerWin && !iAWin && turnsPlayed == 9 )
    {
        return 0;
    }
    return twoSeriesNumber(state) - twoSeriesNumber(state, 1);
}

int twoSeriesNumber(char state[10])
{
    return twoSeriesNumber(state, player);
}

int twoSeriesNumber(char state[10], int p)
{
    int seriesNumber = 0;
    char symbol = returnSymbol(p);

    for(int i = 1; i < 10; ++i)
    {
        if(i != 1 && i != 4 && i != 7)
        {
            if(symbol == state[i - 1] && state[i - 1] == state[i])
            {
                seriesNumber++;
            }
        }
        if(i != 3 && i != 6 && i != 9)
        {
            if(symbol == state[i] && state[i] == state[i + 1])
            {
                seriesNumber++;
            }
        }
        if(i != 1 && i != 2 && i != 3)
        {
            if(symbol == state[i - 3] && state[i - 3] == state[i])
            {
                seriesNumber++;
            }
        }
        if(i != 7 && i != 8 && i != 9)
        {
            if(symbol == state[i] && state[i] == state[i + 3])
            {
                seriesNumber++;
            }
        }
    }
    return seriesNumber;
}

void iATurn()
{
    cout << "Tour de l'IA" << endl;
    char tempSquare[10];
    copy(begin(square), end(square), begin(tempSquare));
    int deep = 10, max_val = -10000, temp;
    char tempSymbol;
    vector<int> bestChoices;

    // for(int i = 1; i < 10; ++i)
    for(int i = 1; i < 2; ++i)
    {
        cout << "- Pour choice = i = " << i << " : " << endl;
        choice = i;
        if(!caseEvenChoosen())
        {
            cout << "Ca marche" << endl;
            tempSymbol = tempSquare[choice];
            tempSquare[choice] = returnSymbol();
            temp = Min(tempSquare, deep - 1);
            cout << "temp : " << temp;
        /*
            if(temp > max_val)
            {
                max_val = temp;
                bestChoice = choice;
            }
            tempSquare[choice] = tempSymbol;
        */
            bestChoices.push_back(choice);
        }
        else
        {
            // cout << "Déjà pris..." << endl;
        }
    }
    // choice = bestChoice;
    string test;
    cout << "Meilleurs choix pour l'IA : " << endl;
    int bestChoicesNbr = bestChoices.size();
    for(int i = 0; i < bestChoicesNbr; ++i)
    {
        cout << " - " << bestChoices[i] << endl;
    }
    cout << "Entrez le mot 'suivant' : ";
    cin >> test;

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
        cout << "Player " << returnSymbol() << ", make your choice : ";
        cin >> choice;
        if(cin.fail()) {
            cout << "Enter an integer number !" << endl;
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

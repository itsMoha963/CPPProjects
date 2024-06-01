#include <iostream>
#include <cstdlib>

using namespace std;

enum enGameChoice
{
    Stone = 1,
    Paper = 2,
    Scissors = 3
};

enum enWinner
{
    Player1 = 1,
    Computer = 2,
    Draw = 3
};

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResult
{
    short TotalRounds = 0;
    short Player1WinTimes = 0;
    short Computer2WinTimes = 0;
    short Drawtimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

int RandomNumber(int From, int To)
{
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

string WinnerName(enWinner Winner)
{
    /* if (Winner == enWinner::Computer)
     {
         return "Computer";
     }
     else if (Winner == enWinner::Player1)
     {
         return "Player1";
     }
     else
         return "Draw";*/

    string arrWinnerName[3] = {"Player1", "Computer", "Draw"};
    return arrWinnerName[Winner - 1];
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
    {
        return enWinner::Draw;
    }

    switch (RoundInfo.PlayerChoice)
    {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;

    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }
        break;
    }
    return enWinner::Player1;
}

string ChoiceName(enGameChoice Choice)
{
    string arrChoiceName[3] = {"Stone", "Paper", "Scissors"};
    return arrChoiceName[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
    if (WinnerName(Winner) == "Computer")
        system("color 4F");
    else if (WinnerName(Winner) == "Player1")
        system("color 2F");
    else
        system("color 6F");
}

void PrintRoundResluts(stRoundInfo RoundInfo)
{
    cout << "\n____________Round[" << RoundInfo.RoundNumber << "] ___________\n\n";
    cout << "Player1 Choice : " << ChoiceName(RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "] \n";
    cout << "___________________________________________________________\n"
         << endl;

    SetWinnerScreenColor(RoundInfo.Winner);
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes)
        return enWinner::Player1;
    else if (Player1WinTimes < ComputerWinTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

stGameResult FillGameResult(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResult GameResults;

    GameResults.TotalRounds = GameRounds;
    GameResults.Player1WinTimes = Player1WinTimes;
    GameResults.Computer2WinTimes = ComputerWinTimes;
    GameResults.Drawtimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);
    return GameResults;
}

enGameChoice ReadPlayer1Choice()
{
    short choice = 1;
    do
    {
        cout << "\nYour choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
        cin >> choice;
    } while (choice < 1 || choice > 3);
    return (enGameChoice)choice;
}

enGameChoice GetComputerChoice()
{
    short choice = RandomNumber(1, 3);
    return (enGameChoice)choice;
}

stGameResult PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.PlayerChoice = ReadPlayer1Choice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player1)
            Player1WinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else if (RoundInfo.Winner == enWinner::Draw)
            DrawTimes++;

        PrintRoundResluts(RoundInfo);
    }
    return FillGameResult(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

string Tabs(short NumberOfTabs)
{
    string t = "";
    for (int i = 0; i < NumberOfTabs; i++)
    {
        t += "\t";
    }
    return t;
}

void ShowGameOverScreen()
{
    cout << Tabs(2) << "_____________________________________________________\n\n";
    cout << Tabs(2) << "                +++ G a m e   O v e r +++                \n";
    cout << Tabs(2) << "_____________________________________________________\n\n";
}

void ShowFinalGameResults(stGameResult GameResults)
{

    cout << Tabs(2) << "___________________[Game Results]____________________\n";
    cout << Tabs(2) << "Game Rounds       : " << GameResults.TotalRounds << endl;
    cout << Tabs(2) << "Player1 Won Times : " << GameResults.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer Won times: " << GameResults.Computer2WinTimes << endl;
    cout << Tabs(2) << "Draw Times        : " << GameResults.Drawtimes << endl;
    cout << Tabs(2) << "Final Winner      : " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "______________________________________________________";
    SetWinnerScreenColor(GameResults.GameWinner);
}

short ReadHowManyRounds()
{
    short Gameround = 1;
    do
    {
        cout << "How Many Rounds 1 to 10? \n";
        cin >> Gameround;

    } while (Gameround < 1 || Gameround > 10);

    return Gameround;
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        stGameResult GameResult = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResult);

        cout << endl
             << Tabs(2) << "Do You want to play again? ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}

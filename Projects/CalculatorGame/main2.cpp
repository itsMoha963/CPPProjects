#include <iostream>
#include <cstdlib>

using namespace std;

enum enQuestionLevel
{
    Easy = 1,
    Med = 2,
    Hard = 3,
    mix = 4
};

enum enOperationType
{
    Add = 1,
    Sub = 2,
    Mul = 3,
    Div = 4,
    Mix = 5
};

string GetOpTypeSymbol(enOperationType optype)
{
    switch (optype)
    {
    case enOperationType::Add:
        return "+";
    case enOperationType::Sub:
        return "-";
    case enOperationType::Mul:
        return "*";
    case enOperationType::Div:
        return "/";
    default:
        return "Mix";
    }
}

string GetQuestionLevel(enQuestionLevel level)
{
    string arrQuestionLevelTExt[4] = {"Easy", "Med", "Hard", "Mix"};
    return arrQuestionLevelTExt[level - 1];
}

int RandomNumber(int From, int To)
{
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

void SetScreenColor(bool result)
{
    if (result)
        system("color 2F");
    else
        system("color 4F");
}

short ReadHowManyQuestions()
{
    short GameRounds;
    do
    {
        cout << "How Many Questions Do you want? ";
        cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds > 10);

    return GameRounds;
}

enQuestionLevel ReadDifficulty()
{
    short difficultyType = 0;
    do
    {
        cout << "Enter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> difficultyType;
    } while (difficultyType < 1 || difficultyType > 4);
    return (enQuestionLevel)difficultyType;
}

enOperationType ReadOperationType()
{
    short OpType;
    do
    {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> OpType;
    } while (OpType < 1 || OpType > 5);
    return (enOperationType)OpType;
}

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationType;
    enQuestionLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionLevel QuestionLevel;
    enOperationType OpType;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnsers = 0;
    bool isPass = false;
};

int SimpleCalculator(int num1, int num2, enOperationType opType)
{
    switch (opType)
    {
    case enOperationType::Add:
        return num1 + num2;
    case enOperationType::Sub:
        return num1 - num2;
    case enOperationType::Mul:
        return num1 * num2;

    case enOperationType::Div:
        return num1 / num2;
    default:
        return num1 + num2;
    }
}

enOperationType GetRandomOperationType()
{
    int Op = RandomNumber(1, 4);
    return (enOperationType)Op;
}

stQuestion GenerateQuestion(enQuestionLevel level, enOperationType OpType)
{
    stQuestion Question;

    if (level == enQuestionLevel::mix)
        level = (enQuestionLevel)RandomNumber(1, 3);

    if (OpType == enOperationType::Mix)
        OpType = GetRandomOperationType();

    Question.OperationType = OpType;

    switch (level)
    {
    case enQuestionLevel::Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        break;
    case enQuestionLevel::Med:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);

        break;
    case enQuestionLevel::Hard:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        break;
    }
    if (Question.OperationType == enOperationType::Sub && Question.Number1 < Question.Number2 || Question.OperationType == enOperationType::Div && Question.Number1 < Question.Number2)
    {
        swap(Question.Number1, Question.Number2); // Swap numbers if subtraction result is negative
    }
    Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
    Question.QuestionLevel = level;
    return Question;
}

void GenerateQuizzQuizzQuestion(stQuizz &Quizz)
{
    for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
    {
        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);
    }
}

int ReadQuestionAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer;
}

void PrintTheQuestion(stQuizz quizz, short QuestionNumber)
{
    cout << "\nQuestion [" << QuestionNumber + 1 << "/" << quizz.NumberOfQuestions << "]\n";
    cout << quizz.QuestionList[QuestionNumber].Number1 << "\n";
    cout << quizz.QuestionList[QuestionNumber].Number2 << "  ";

    cout << GetOpTypeSymbol(quizz.QuestionList[QuestionNumber].OperationType);
    cout << "\n___________________________________________________\n";
}

void CorrectTheQuestionAnswer(stQuizz &Quizz, short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnsers++;

        cout << "Wrong Answer :-( \n";
        cout << "The Right Answer Is: " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswers++;
    }
    cout << endl;
    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndcorrectQuestionListAnswers(stQuizz &Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        PrintTheQuestion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
    }

    Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnsers);
}

string GetFinalResultsText(bool pass)
{
    if (pass)
        return "PASS :-)";
    else
        return "FAIL :-(";
}

void PrintQuizzResults(stQuizz Quizz)
{
    cout << "\n";
    cout << "__________________________\n\n";
    cout << " Final Results is " << GetFinalResultsText(Quizz.isPass);
    cout << "\n__________________________\n\n";

    cout << "Number Of Questions: " << Quizz.NumberOfQuestions << endl;
    cout << "Questions Level     : " << GetQuestionLevel(Quizz.QuestionLevel) << endl;
    cout << "OpType              : " << GetOpTypeSymbol(Quizz.OpType) << endl;
    cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
    cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnsers << endl;
    cout << "_____________________________________\n";
}

void PlayGame()
{
    stQuizz Quizz;
    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    Quizz.QuestionLevel = ReadDifficulty();
    Quizz.OpType = ReadOperationType();

    GenerateQuizzQuizzQuestion(Quizz);
    AskAndcorrectQuestionListAnswers(Quizz);
    PrintQuizzResults(Quizz);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char Yes = 'Y';
    do
    {
        ResetScreen();
        PlayGame();

        cout << "Do You want to play again? ";
        cin >> Yes;
    } while (Yes == 'y' || Yes == 'Y');
}
int main()
{
    srand((unsigned)time(NULL));
    StartGame();

    return 0;
}
#include "debugmalloc.h"
#include "fileManage.h"
#include "econio.h"
#include "game.h"
#include <time.h>

extern level levels[15];
player currentGame = {0,0,0,true,true};

int chooseLevel(){
    printf("Choose a level to start from (1-15)");
    econio_normalmode();
    int currentLevel;
    scanf("%d",&currentLevel);
    econio_rawmode();
    currentGame.timeStart = time(NULL);
    return currentLevel;
}

void win(){
    econio_clrscr();
    printf("Congratulations, you have won the game! Please enter your username to save your score.");
    char input[16];
    scanf("%s",input);
    writeTopList(input);
    //majd menti az időt és hogy hány kérdést teljesített a dicsőségfalra
}
void halfAnwsers(){
    printf("felez");
    currentGame.canCrowdVote = false;
}
void crowdVote(){
    printf("szavaz");
    currentGame.canCrowdVote = false;
}
void wrongAnwser(){
    printf("rossz");
}
questions *randomQuestion(questions *currentQuestion, int currentLevel) {
    int randomQuestionNumber = rand() %(levels[currentLevel-1].currentQuestionsSum);
    for (int i = 0; i < randomQuestionNumber; ++i)
        currentQuestion = currentQuestion->nextQuestionPointer;
    return currentQuestion;
}

void newLevel(int currentLevel) {
    econio_clrscr();
    questions *currentQuestion = randomQuestion(levels[currentLevel - 1].currentLevelQuestions, currentLevel);
    printf("%d%s\n%s\n%s\n%s\n%s\n%c",currentLevel, currentQuestion->question, currentQuestion->a, currentQuestion->b,
           currentQuestion->c, currentQuestion->d, currentQuestion->correct);
    char input = econio_getch();
    bool currentQuestionCorrect = currentQuestion->correct == input;
    if (currentQuestionCorrect && currentLevel == 15) win();
    else if (currentQuestionCorrect) newLevel(++currentLevel);
    else if (input == 'F' && currentGame.canHalfAnwsers) halfAnwsers();
    else if (input == 'K' && currentGame.canCrowdVote) crowdVote();
    else if (input == 'T')     writeTopList();
    else wrongAnwser();
}
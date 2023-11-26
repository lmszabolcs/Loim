#ifndef manageQuestions
#define manageQuestions
//Láncolt lista a kérdések tárolására
typedef struct questions {
    int level;
    char *question;
    char *a;
    char *b;
    char *c;
    char *d;
    char correct;
    char *topic;
    struct questions *nextQuestionPointer;
} questions;

//Struktúra a szintekhez tartozó kérdések és mennyiségének tárolására
typedef struct level {
    int currentQuestionsSum;
    questions *currentLevelQuestions;
} level;

//Struktúra a játékos adatainak tárolására
typedef struct player {
    int levelsAnwsered;
    time_t timeStart;
    time_t timeEnd;
    bool canHalfAnwsers;
    bool canCrowdVote;
} player;

//Struktúra a dicsőségfal tárolására, rendezésének elősegítésére.
typedef struct toplist{
    char username[16];
    int score;
    int time[2];
}toplist;
questions *questionsNext(questions *, char *);

void readAllQuestions(level *);

void printAllQuestions(level *);

void freeAllQuestionsAndLevels(level *);

void writeTopList(char*);

void readTopList();

void sortTopByScore(toplist *, toplist);

void sortTopByTime(toplist *, toplist);


#endif
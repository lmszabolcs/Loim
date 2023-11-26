#include "debugmalloc.h"
#include "fileManage.h"
#include <time.h>
#include <math.h>

extern player currentGame;
//Új elem hozzáadása a láncolt listához a beolvasott adatokkal.
questions *questionsNext(questions *questionsHead, char *currentLine) {
    questions *newQuestion = malloc(sizeof(questions));
    currentLine = strtok(currentLine, ";");
    newQuestion->level = atoi(currentLine);
    currentLine = strtok(NULL, ";");
    newQuestion->question = malloc(strlen(currentLine) + 1);
    strcpy(newQuestion->question, currentLine);
    currentLine = strtok(NULL, ";");
    newQuestion->a = malloc(strlen(currentLine) + 1);
    strcpy(newQuestion->a, currentLine);
    currentLine = strtok(NULL, ";");
    newQuestion->b = malloc(strlen(currentLine) + 1);
    strcpy(newQuestion->b, currentLine);
    currentLine = strtok(NULL, ";");
    newQuestion->c = malloc(strlen(currentLine) + 1);
    strcpy(newQuestion->c, currentLine);
    currentLine = strtok(NULL, ";");
    newQuestion->d = malloc(strlen(currentLine) + 1);
    strcpy(newQuestion->d, currentLine);
    currentLine = strtok(NULL, ";");
    newQuestion->correct = currentLine[0];
    currentLine = strtok(NULL, ";");
    newQuestion->topic = malloc(strlen(currentLine) + 1);
    strcpy(newQuestion->topic, currentLine);

    newQuestion->nextQuestionPointer = NULL;

    if (questionsHead == NULL) {
        return newQuestion;
    } else {
        questions *currentQuestion = questionsHead;
        while (currentQuestion->nextQuestionPointer != NULL) {
            currentQuestion = currentQuestion->nextQuestionPointer;
        }
        currentQuestion->nextQuestionPointer = newQuestion;
        return questionsHead;
    }
}

//Beolvassa az összes sort és folyamatosan bővíti a láncolt listákat
void readAllQuestions(level *levels) {
    FILE *loimFile = fopen("loim.csv", "r");
    if (loimFile == NULL) {
        printf("loimFile error");
        exit(1);
    }
    char currentLine[256];
    while (!feof(loimFile)) {
        int currentLineLevel;
        fgets(currentLine, 256, loimFile);
        sscanf(currentLine, "%d;", &currentLineLevel);
        if (currentLineLevel >= 1 && currentLineLevel <= 15) {
            levels[currentLineLevel - 1].currentLevelQuestions = questionsNext(
                    levels[currentLineLevel - 1].currentLevelQuestions, currentLine);
        }
        levels[currentLineLevel - 1].currentQuestionsSum++;
    }
    fclose(loimFile);
}

//Kiirja az összes kérdést szintek szerint csoportosítva.
void printAllQuestions(level *levels) {
    for (int i = 0; i < 15; i++) {
        questions *currentQuestion = levels[i].currentLevelQuestions;
        printf("Level %d Questions:\n", i);

        while (currentQuestion != NULL) {
            printf("Level: %d\nQuestion: %s\nA: %s\nB: %s\nC: %s\nD: %s\nCorrect Answer: %c\nTopic: %s\n\n",
                   currentQuestion->level, currentQuestion->question, currentQuestion->a, currentQuestion->b,
                   currentQuestion->c, currentQuestion->d, currentQuestion->correct, currentQuestion->topic);

            currentQuestion = currentQuestion->nextQuestionPointer;
        }
    }
}

//Felhaszabadítja a kérdéseknek lefoglalt memóriát.
void freeAllQuestionsAndLevels(level *levels) {
    for (int i = 0; i < 15; i++) {
        questions *currentQuestion = levels[i].currentLevelQuestions;
        while (currentQuestion != NULL) {
            questions *next = currentQuestion->nextQuestionPointer;
            free(currentQuestion->question);
            free(currentQuestion->a);
            free(currentQuestion->b);
            free(currentQuestion->c);
            free(currentQuestion->d);
            free(currentQuestion->topic);
            free(currentQuestion);
            currentQuestion = next;
        }
    }
}

//Megjeleníti a dicsőségfalat, ha létezik.
void readTopList() {
    FILE *toplistFile = fopen("loimtoplist.csv", "r");
    if (toplistFile == NULL) {
        printf("Toplist is currently empty or it doesn't exist.");
        return;
    }
    toplist top[11];
    int index = 0;
    while (!feof(toplistFile) && index < 10) {
        char currentLine[32];
        fgets(currentLine, 32, toplistFile);
        char *token = strtok(currentLine, ";");
        strcpy(top[index].username, token);
        token = strtok(NULL, ";");
        top[index].score = atoi(token);
        token = strtok(NULL, ";");
        top[index].time[0] = atoi(token);
        token = strtok(NULL, ";");
        top[index].time[1] = atoi(token);
        index++;
    }
    fclose(toplistFile);
    //sortTopByScore(top, NULL);
    //sortTopByTime(top, NULL);
    printf("Toplist:\n");
    for (int i = 0; i < index; ++i)
        printf("%s %d %d:%d\n", top[i].username, top[i].score, top[i].time[0], top[i].time[1]);
}

//Buborákrendező algoritmus a pontok szerinti rendezéshez.
void sortTopByScore(toplist *top, toplist new) {
    for (int i = 9; i > 0; --i)
        for (int j = 0; j < i; ++j)
            if (top[j].score < top[j + 1].score) {
                toplist temp = top[j];
                top[j] = top[j + 1];
                top[j + 1] = temp;
            }


}

//Buborákrendező algoritmus az idő szerinti rendezéshez.
void sortTopByTime(toplist *top, toplist new) {
    for (int i = 9; i > 0; --i)
        for (int j = 0; j < i; ++j)
            if (top[j].score == top[j + 1].score && top[j].time[0] > top[j + 1].time[0]) {
                toplist temp = top[j];
                top[j] = top[j + 1];
                top[j + 1] = temp;
            } else if (top[j].score == top[j + 1].score && top[j].time[0] == top[j + 1].time[0])
                if (top[j].time[1] > top[j + 1].time[1]) {
                    toplist temp = top[j];
                    top[j] = top[j + 1];
                    top[j + 1] = temp;
                }


}

void writeTopList(char* username){
    currentGame.timeEnd = time(NULL);
    toplist new;
    new.time[1] = currentGame.timeEnd-currentGame.timeStart;
    new.time[0] = new.time[1] / 60;
    new.time[1] = new.time[1] % 60;

}

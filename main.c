#include "debugmalloc.h"
#include "econio.h"
#include "fileManage.h"
#include "game.h"

level levels[15] = {0};

int main() {
    readAllQuestions(levels);
    econio_rawmode();
    int choice;
    do {
        printf("Welcome to Who Wants to Be a Millionaire?\n");
        printf("1. New Game\n");
        printf("2. Toplist\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        choice = econio_getch()-'0';
        switch (choice) {
            case 1:
                econio_clrscr();
                printf("Starting a New Game...\n");
                newLevel(chooseLevel());
                break;
            case 2:
                econio_clrscr();
                printf("Toplist:\n");
                readTopList();
                break;
            case 3:
                econio_clrscr();
                printf("Goodbye!\n");
                freeAllQuestionsAndLevels(levels);
                break;
            default:
                econio_clrscr();
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}
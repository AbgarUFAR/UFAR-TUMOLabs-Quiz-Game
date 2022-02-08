#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "menu_service.h"
#include "../helper/game_starter.h"
#include "../helper/config.h"
#include "../helper/utility.h"
#include "../comparators/results_comparator.h"
#include "file_service.h"

void displayMenu() {
	printf(
		"\t\t-------------------------------------\n"
		"\t\t  -> Press P to start the game\n"
		"\t\t  -> Press V to view the highest score\n"
		"\t\t  -> Press R to reset score\n"
		"\t\t  -> Press H for help\n"
		"\t\t  -> Press Q to quit\n"
		"\t\t-------------------------------------\n"
	);
}

void greetUser() {
	printf(
		"\t\t-------------------------------------\n"
		"\t\t\t\tWELCOME\n"
		"\t\t\t\t  TO\n"
		"\t\t\t       QUIZ GAME\n"
		"\t\t-------------------------------------\n"
		"\t\t-------------------------------------\n"
		"\t\t     TEST YOUR GK..SET HIGHSCORE\n"
		"\t\t-------------------------------------\n"
	);
}

char getMenuInput() {
	char result;
	do {
		printf("\nEnter option: ");
		scanf("%c", &result);
		eatBuffer();
		result = toupper(result);
	} while(!('P' == result || 'V' == result || 'R' == result || 'H' == result || 'Q' == result));
	return result;
}

void play() {
	startGame();
}

void showHighestScore() {
	FILE *fos;
	if (!(fos = fopen(RESULTS_FILE_PATH, "r"))) {
		fprintf(stderr, "Cannot open the file %s\n", RESULTS_FILE_PATH);
		exit(1);
	}
	char line[1024];
	PlayerResults highestScores[10];
	int ptr = -1;
	int maxScore = -1;
	while (fscanf(fos, "%1023[^\n]\n", line) == 1) {
		char *temp = line;
		char *username = strtok(line, ";");
		char *scoreStr = strtok(NULL, ";");
		int score = 0;
		if (scoreStr[0] != '0') {
			for (int i = 0; scoreStr[i] != '\0'; i++) {
				score = score * 10 + (scoreStr[i] - '0');
			}
		}
		if (score > maxScore) {
			ptr = -1;
			maxScore = score;
		}
		if (score == maxScore && ptr != 9) {
			strcpy(highestScores[++ptr].username, username);
			highestScores[ptr].score = score;
		}
	}
	if (ptr == -1) {
		puts("No data record");
	} else {
		printf("\tTHE HIGHEST SCORE IS %d\n", maxScore);
		qsort(highestScores, ptr + 1, sizeof(PlayerResults), resultsComparator);
		for (int i = 0; i <= ptr; i++) {
			printf("%2d. %s\n", i + 1, highestScores[i].username);
		}
	}
}

void resetScore() {
	short int option = -1;
	while (option != 1 && option != 2 && option != 3) {
		printf("1. Reset All Scores\n"
		"2. Reset Specific User's Score(s)\n"
		"3. Exit to main menu\n"
		"Enter your option(1/2/3): ");
		scanf("%hd", &option);
		eatBuffer();
	}
	if (option == 1) {
		emptyFile(RESULTS_FILE_PATH);
	} else if (option == 2) {
		char username[25];
		printf("Enter username: ");
		scanf("%24[^\n]%*c", username);
		deleteSpecificLine(RESULTS_FILE_PATH, username);
	}
}

void showHelp() {
	printf("\n\n"
		"***********************************************************************************************\n"
		"\t\t__HOW TO PLAY THE GAME__\n"
    	"-> Press P:"
    	" When pressing the P option, the Quiz-game starts.\n"
        "\t\t First you enter your username and then start to play.\n"
        "\t\t There are 3 levels of questions: Easy, Medium and Hard\n"
        "\t\t With every correctly answered question, questions become harder.\n"
        "\t\t The answer of question can be chosen by typing 1/2/3/4. \n\n"
    	"-> Press V:"
        " By pressing the V option, you can view the highest scores.\n\n"
    	"-> Press R:"
	    " By pressing the R option, the user can clear all the recorded scores.\n\n"
	    "-> Press H:"
	    " By pressing the H option you opened me :)\n\n"
	    "-> Press Q:"
	    " By pressing the Q option you finish the game.\n\n"
	    "__WARNING__\n"
	    "-> any wrongly typed letters will be ignored\n"
	    "__GOOD LUCK__\n"
	    "***********************************************************************************************\n\n");
}

void quit() {
	printf("\n\nexiting!!\n\n");
	exit(0);
}

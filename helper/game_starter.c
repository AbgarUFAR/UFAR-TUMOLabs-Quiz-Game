#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game_starter.h"
#include "config.h"
#include "utility.h"
#include "../services/file_service.h"
#include "../models/player_results.h"

void startGame() {
	printf("Your name : ");
	char username[25];
	scanf("%24[^\n]", username);
	getchar();
	srand(time(0));
	int easyQuestionsIndices[NUM_OF_EASY_QUESTIONS];
	int mediumQuestionsIndices[NUM_OF_MEDIUM_QUESTIONS];
	int hardQuestionsIndices[NUM_OF_HARD_QUESTIONS];

	fillQuestionsArray(easyQuestionsIndices, NUM_OF_EASY_QUESTIONS);
	fillQuestionsArray(mediumQuestionsIndices, NUM_OF_MEDIUM_QUESTIONS);
	fillQuestionsArray(hardQuestionsIndices, NUM_OF_HARD_QUESTIONS);

	randomizeQuestions(easyQuestionsIndices, NUM_OF_EASY_QUESTIONS);
	randomizeQuestions(mediumQuestionsIndices, NUM_OF_MEDIUM_QUESTIONS);
	randomizeQuestions(hardQuestionsIndices, NUM_OF_HARD_QUESTIONS);

	int numOfAnsweredQuestions = 0;
	int indexOfEasyQuestion = 0;
	int indexOfMediumQuestion = 0;
	int indexOfHardQuestion = 0;
	char fileName[64];
	char tmpNum[3];

	char hasPlayerWon = TRUE;

	while (numOfAnsweredQuestions != 7) {
		strcpy(fileName, "");
		strcpy(tmpNum, "");

		if (numOfAnsweredQuestions >= 0 && numOfAnsweredQuestions < 4) {
			strcpy(fileName, EASY_FILE_PATH);
			sprintf(tmpNum, "%d", easyQuestionsIndices[indexOfEasyQuestion++]);
		} else if (numOfAnsweredQuestions >= 4 && numOfAnsweredQuestions <= 5) {
			strcpy(fileName, MEDIUM_FILE_PATH);
			sprintf(tmpNum, "%d", mediumQuestionsIndices[indexOfMediumQuestion++]);
		} else {
			strcpy(fileName, HARD_FILE_PATH);
			sprintf(tmpNum, "%d", hardQuestionsIndices[indexOfHardQuestion++]);
		}
		strcat(fileName, tmpNum);
		strcat(fileName, ".txt");
		
		int rightAns = printQuestion(fileName);
		char ans = 'H';
		do {
			printf("answer(1/2/3/4): ");
			scanf("%c", &ans);
			eatBuffer();
		} while ('1' > ans || '4' < ans);
		if (ans - '0' == rightAns) {
			++numOfAnsweredQuestions;
		} else {
			hasPlayerWon = FALSE;
			break;
		}
	}

	if (hasPlayerWon) {
		puts("YOU WIN!");
	} else {
		puts("Wrong answer! You failed!");
	}
	printf("final score: %d\n", numOfAnsweredQuestions);
	PlayerResults result;
	strcpy(result.username, username);
	result.score = numOfAnsweredQuestions;

	saveResults(&result, RESULTS_FILE_PATH);
}

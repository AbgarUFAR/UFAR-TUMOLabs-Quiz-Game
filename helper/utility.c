#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utility.h"

static void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void clearTerminal() {
	system("@cls||clear");
}

void printCurrentTime() {
	time_t t;
	time(&t);
	printf("============================================================================\n");
	printf("Current Date and Time : %s", ctime(&t));
	printf("============================================================================\n");
}

void randomizeQuestions(int questionsIndices[], int n) {
	srand(time(0));
	for (int i = n - 1; i >= 0; i--) {
		int j = rand() % (i + 1);
		swap(&questionsIndices[i], &questionsIndices[j]);
	}
}

void fillQuestionsArray(int questionsArr[], int n) {
	for (int i = 0; i < n; i++) {
		questionsArr[i] = i + 1;
	}
}

void eatBuffer() {
	int dummyCharBuffer;
	while ( (dummyCharBuffer = getchar()) != '\n' && dummyCharBuffer != EOF);
}

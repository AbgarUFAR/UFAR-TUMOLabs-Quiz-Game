#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_service.h"
#include "../helper/config.h"

int printQuestion(const char *FILE_NAME) {
	FILE *fis;
	if (!(fis = fopen(FILE_NAME, "r"))) {
		fprintf(stderr, "Can't open the file %s\n", FILE_NAME);
		exit(1);
	}
	int ch;

	int rightAns = -1;
	unsigned char isRightAnsTurn = 0;
	while ((ch = fgetc(fis)) != EOF) {
		if (ch == '@') {
			isRightAnsTurn = 1;
		} else if (isRightAnsTurn) {
			rightAns = ch;
			isRightAnsTurn = 0;
		} else {
			printf("%c", (char) ch);
		}
	}
	fclose(fis);
	return rightAns - '0';
}

void saveResults(PlayerResults *result, const char *FILE_NAME) {
	FILE *fos;
	if (!(fos = fopen(FILE_NAME, "a"))) {
		fprintf(stderr, "Can't open the file %s\n", FILE_NAME);
		exit(1);
	}
	fprintf(fos, "%s;%d;\n", result->username, result->score);
	fclose(fos);
}

void emptyFile(const char *FILE_NAME) {
	FILE *fos;
	if (!(fos = fopen(FILE_NAME, "w"))) {
		fprintf(stderr, "Can't open the file %s\n", FILE_NAME);
		exit(1);
	}
	fclose(fos);
}

void deleteSpecificLine(const char *FILE_NAME, const char *userName) {
	FILE *oldFile;
	FILE *newFile = fopen("temp_file.txt", "w");
	if (!(oldFile = fopen(FILE_NAME, "r"))) {
		fprintf(stderr, "Cannot open the file %s\n", FILE_NAME);
		exit(1);
	}
	char line[1024];
	while (fscanf(oldFile, "%1023[^\n]\n", line) == 1) {
		char *temp = line;
		char *currentUserName = strtok(line, ";");
		if (strcmp(currentUserName, userName)) {
			while (currentUserName != NULL) {
		        fprintf(newFile, "%s;", currentUserName);
		        currentUserName = strtok(NULL, ";");
		    }
			fprintf(newFile, "\n"); // (..., temp);
		}
	}
	fclose(oldFile);
	fclose(newFile);
	remove(FILE_NAME);
	rename("temp_file.txt", FILE_NAME);
}

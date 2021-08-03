#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#pragma warning(disable:4996)

// Initial day's data
const int INI_DAY = 9;
const int INI_NEW_CASES = 9;
const int INI_TOTAL_CASES = 100;
const int INI_TOTAL_DEATHS = 2;
const int INI_TOTAL_RECOVERED = 10;

// Line breaks
const char LINE1[] = "--------------------------------------------------";
const char LINE2[] = "==================================================";
const int PAGE_WIDTH = 72;

// Declare User-defined Functions
void programTitle(void);
void menuScreen(void);
void optionScreen(void);
int inputInt(char question[]);
char inputYorN(char question[]);
void centerAlign(char input[]);
void optionScreen(void);

// Global Variables
int toTitle;

int main() {

	int preNew, preTotal, preDeaths, preRecovered, preTreatment;
	int newLocals, newImported, newTotal, newDeaths, newRecovered;
	int totalCases, totalDeaths, totalRecovered, totalTreatment;
	float preDeathRate, preRecoveryRate, preTreatmentRate;
	float deathRate, recoveryRate, treatmentRate;
	int atTitle = 0;

	do {
		toTitle = 0;
		programTitle();
		menuScreen();
		if (atTitle) {
			centerAlign("You are already at the title screen.");
			printf("\n");
		}
		atTitle = 0;
		optionScreen();
		int menuSelect = inputInt("");
		if (menuSelect == -69) {
			atTitle = 1;
			goto mainTitle;
		}


		newLocals = inputInt("Enter the number of local cases > ");
		if (newLocals == -69)
			goto mainTitle;
		


	mainTitle:
		if (toTitle)
			system("cls");
	} while(toTitle);
}

///* TITLE SCREEN *///
// Instantly prints program title
void programTitle(void) {
	printf("\n");
	printf("*  *  *  *  *  *[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]*  *  *  *  *  *\n");
	printf("  *  *  *  *  * ]    COVID-19 CASES TRACKING SYSTEM    [  *  *  *  *  * \n");
	printf("*  *  *  *  *  *[                                      ]*  *  *  *  *  *\n");
	printf("                 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
}

// Instantly prints menu screen
void menuScreen(void) {
	centerAlign("========================================");
	printf("\n");
	centerAlign("||  1 - Create New Report             ||");
	printf("\n");
	centerAlign("||  2 - Show Previous day's Summary   ||");
	printf("\n");
	centerAlign("||  3 - Exit Application              ||");
	printf("\n");
	centerAlign("========================================");
	printf("\n\n");
}


int inputInt(char question[]) {
	char input[10], validateQuit;
	int correctInput;
	do {
		correctInput = 1;

		printf("%s", question);
		rewind(stdin);
		scanf("%s", input);

		if (strlen(input) == 1 && tolower(input[0]) == 'x') {
			centerAlign("[ Are you sure you want to quit? (Y/N) ]");
			printf("\n");
			validateQuit = inputYorN("[ You will lose ALL DATA you had inputted. ]");
			if (validateQuit == 'y') {
				toTitle = 1;
				return -69;
			}
			else
				correctInput = 0;
		}
		else {
			for (int i = 0; i < strlen(input); i++) {
				if (!(isdigit(input[i]))) {
					correctInput = 0;
					centerAlign("[ Invalid Input, Please Try Again. ]");
					printf("\n");
					break;
				}
			}
		}

	} while (!correctInput);

	return atoi(input);
}

char inputYorN(char question[]) {
	char input[10];
	int correctInput;

	do {
		correctInput = 1;

		centerAlign(question);
		printf("\n");
		centerAlign("<   >");
		printf("\b\b\b");
		rewind(stdin);
		scanf("%s", input);

		if (strlen(input) != 1)
			correctInput = 0;
		else if (tolower(input[0]) != 'y' && tolower(input[0]) != 'n')
			correctInput = 0;

		if (!correctInput) {
			centerAlign("Wrong Input! Please Re-enter");
			printf("\n");
		}
	} while (!correctInput);

	return(tolower(input[0]));
}

void centerAlign(char input[]) {
	int length = strlen(input);
	int indent = (PAGE_WIDTH - length) / 2;
	for (int i = 0; i < indent; i++) {
		printf(" ");
	}
	printf("%s", input);
}


// Ask for options in menu screen
void optionScreen(void) {
	centerAlign("[ Enter your option. ]");
	printf("\n");
	centerAlign("<   >");
	printf("\b\b\b");
}
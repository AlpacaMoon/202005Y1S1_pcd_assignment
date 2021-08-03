#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#pragma warning(disable:4996)



/*==================== DECLARE USER-DEFINED FUNCTIONS ====================*/

// Main Functions
void centerAlign(char str[]);	// Center aligns any given string, but refuses escape characters such as '\n' 
void optionScreen(void);			// [Input] Display the layout to get option input from user
int inputInt(int atTitle);			// [Input] Get and validate integer input
char inputAlpha(int atTitle);		// [Input] Get and validate character input (Y/N)
int returnTitle(int atTitle);		// [Input] Double confirm if user wants to quit to the title
void reportMenu(int viewCount);		// [Report] Ask to print which report
void dangerLevel(float deathRate);	// [Ending] Danger level according to death rate 

// Title Screen Functions
void programTitle(void);		// Instantly prints Program Title at the title screen
void menuScreen(void);			// Instantly prints Menu Screen at the title screen
void titleAnimation(void);						// Title scroll in animation on startup
void menuAnimation(void);						// Menu dropdown animation on startup
void printReverse(char line[], int def, int i);	// Scroll in Animation for each line
void waitTimer(int timer);						// A timer that waits for a given time

// Report Functions
void centerAlignInt(int data, int width, int haveBrackets);		// Center align integers in a given width
void centerAlignFloat(float data, int width, int haveBrackets);	// Center align floats in a given width
void centerAlignData(char str[], int width, int haveBrackets);	// Main center align function for both functions above
void pdrHeader(void);			// Prints Header of Previous Day's Report
void dsrHeader(void);           // Prints Header of Daily Summary Report
void dcrHeader(void);           // Prints Header of Daily Comparative Report
void dcrLine(void);             // Prints Line Breaks of Daily Comparative Report

// Other Functions
void dayBreak(void);			// Prints line breaks between days
void fill(int count, char ch);	// Prints a given amount of the given character



/*==================== CONSTANTS ====================*/

// Initial Day's Data
const int INI_NEW_CASES = 9;
const int INI_TOTAL_CASES = 100;
const int INI_DEATHS = 2;
const int INI_RECOVERED = 10;
const int INI_DAY = 9;

// Page width fixed to 72
const int PAGE_WIDTH = 72;

// Line breaks
const char LINE1[] = "--------------------------------------------------";
const char LINE2[] = "==================================================";



/*==================== MAIN FUNCTION ====================*/

int main() {
	/*==================== VARIABLES ====================*/

	// Data variables
	int preNew, preTotal, preDeaths, preRecovered, preTreatment;    // Previous day's data
	float preDeathRate, preRecoveredRate, preTreatmentRate;         // Previous day's rates
	int newLocals, newImported, newTotal, newDeaths, newRecovered;  // Today's data
	int totalCases, totalDeaths, totalRecovered, totalTreatment;    // Total of (All Previous + Today) data
	float deathRate, recoveredRate, treatmentRate;                  // Today's rates
	int newChanges;                             // Today's new cases - Previous day's new cases
	int currentDay, daycount;                   // Day variables
	int highest, lowest, highestDay, lowestDay; // The highest and lowest cases and their respective days

	// Option selections
	int menuSelect, reportSelect;	// Get option selections for the title menu and the report menu
	char contiLoopDay;				// Get Option selection for "Continue to next day? (Y/N)"

	// Report variables
	int viewCount;		// Counts how many times the user had viewed the report

	// Title screen variables
	int atTitle = 0;	// Whether the user is at the title screen.



	/*==================== DATA INITIALIZATION ====================*/

	/* Previous day's data = Initial day's data */
	currentDay = INI_DAY;
	preNew = INI_NEW_CASES;
	preTotal = INI_TOTAL_CASES;
	preDeaths = INI_DEATHS;
	preRecovered = INI_RECOVERED;
	preTreatment = preTotal - preDeaths - preRecovered;

	/* Initialize Highest and lowest value */
	highest = INI_NEW_CASES;
	lowest = INI_NEW_CASES;
	highestDay = currentDay;
	lowestDay = currentDay;

	/* Calculations for Initial day's data */
	preDeathRate = (float)preDeaths / preTotal * 100;
	preRecoveredRate = (float)preRecovered / preTotal * 100;
	preTreatmentRate = (float)preTreatment / preTotal * 100;


	/*==================== INTRO ANIMATION ====================*/
	// Title Logo
	titleAnimation();
	system("cls");
	programTitle();

	// Menu Options
	menuAnimation();
	system("cls");


	// User who enters 'x' or reaches the ending screen will be brought back to here 
	// THE ONLY WAY to quit the program is by selecting "3 - Quit Application" at the title screen
	///* RETURN TO TITLE LOOP STARTS HERE *///
	while (1) {	// Loop is always true 


		/*================================= MENU SCREEN ========================================*/

		// Prints the Logo and Menu screen Instantly (Primes the menu loop below)
		programTitle();
		menuScreen();

		// Prints when user enters 'x' at title screen
		if (atTitle) {
			centerAlign("[ Already at Title Screen. ]");
			printf("\n");
		}

		// Indicate the user is at the title screen
		atTitle = 1;


		///* TITLE SCREEN LOOP STARTS HERE *///
		do {

			// Prompt and get menu option selection from user
			do {
				optionScreen();
				menuSelect = inputInt(atTitle); // Get and validate input

				if (menuSelect == -999) {
					system("cls");
					programTitle();
					menuScreen();
					centerAlign("[ Invalid Input. Please Try Again. ]");
					printf("\n");
				}

				// If user enters 'x'
				if (menuSelect == -69)
					goto mainTitle;			// Quit to title if choose 'y'

			} while (menuSelect < 0);	// Ask again if user enters invalid input / if user enters 'n' after entering 'x'


			switch (menuSelect)
			{
				/* 1 - Start inputting data */
			case 1:
				printf("\n");
				centerAlign("[ Creating New Report... ]");
				printf("\n");
				centerAlign("[ Enter X to quit to Title. ]");
				printf("\n");
				break;

				/* 2 - Display Previous day's Report */
			case 2:

				// Break Line
				printf("\n%.24s< Yesterday's Summary >%.25s\n\n", LINE2, LINE2);
				centerAlign("[ Day   ]");
				fill(3, '\b');
				printf("%d ]\n", currentDay);

				// Header
				printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);
				printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Yesterday's ", " Total", " Total", " Total", " Under");
				printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Cases       ", " Cases", " Deaths", " Recovered", " Treatment");

				// Main Data
				printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);
				printf(" |%18d  |", preNew);
				centerAlignInt(preTotal, 10, 0);
				printf("|");
				centerAlignInt(preTotal, 11, 0);
				centerAlignInt(preRecovered, 11, 0);
				centerAlignInt(preTreatment, 11, 0);
				printf("\n");

				// Rates
				printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);
				printf(" %32s||", "");
				centerAlignFloat(preDeathRate, 11, 0);
				centerAlignFloat(preRecoveredRate, 11, 0);
				centerAlignFloat(preTreatmentRate, 11, 0);
				printf("\n");
				printf(" %32s++%.11s+%.11s+%.11s+\n\n", "", LINE1, LINE1, LINE1);

				//Ending Line
				printf("\n%.22s< Press any key to go back >%.22s\n\n\n", LINE2, LINE2);
				centerAlign("Press any key to continue . . .");
				fill(32, '\b');
				system("pause");

				// Return to title screen
				system("cls");
				programTitle();
				menuScreen();
				break;

				/* 3 - Exit the program */
			case 3:
				printf("\n");
				centerAlign("[ Quiting Application... ]");
				printf("\n\n");
				exit(1);
				break;

				/* Invalid Input (Integer not in options ) */
			default:
				system("cls");
				programTitle();
				menuScreen();
				centerAlign("[ Invalid Input. Please Try Again. ]");
				printf("\n");
				break;
			}

		} while (menuSelect != 1);
		///* TITLE SCREEN LOOP ENDS HERE *///


		// User is no longer at the title;
		atTitle = 0;


		///* DAY LOOP STARTS HERE *///
		do {
			// New Day
			currentDay++;
			dayBreak();
			printf("\n\n%.23s< START OF DAY %d REPORT >%.23s\n\n", LINE2, currentDay, LINE2);


			/*================================== Input Section =======================================*/

			// Input: New local cases
			centerAlign("[ Enter today's data ]");
			printf("\n");
			do {
				centerAlign("Number of new local cases    >    ");
				fill(3, '\b');
				newLocals = inputInt(atTitle);

				// If user enters 'x' and chooses 'y'
				if (newLocals == -69)
					goto mainTitle;

			} while (newLocals < 0);	// Ask again if input is invalid or entered 'n' at quit to title double confirmation

			// Input: New Imported cases
			do {
				centerAlign("Number of new imported cases >    ");
				fill(3, '\b');
				newImported = inputInt(atTitle);

				// If user enters 'x' and chooses 'y'
				if (newImported == -69)
					goto mainTitle;

			} while (newImported < 0);	// Ask again if input is invalid or entered 'n' at quit to title double confirmation


			// Short Summary of First two Input
			newTotal = newLocals + newImported;  // Total new cases
			newChanges = newTotal - preNew;      // Changes

			// Print changes
			printf("\n");
			centerAlign("[ Total number of new cases =    ]");
			fill(4, '\b');
			printf("%d ] \n", newTotal);
			if (newChanges == 0) {
				centerAlign("( Same as yesterday. )", ' ');
			}
			else {
				if (newChanges > 0) {
					centerAlign("( Increased by xx from yesterday. )");
				}
				else {
					centerAlign("( Decreased by xx from yesterday. )");
				}

				fill(20, '\b');
				printf("%d from yesterday. ) ", newChanges);
			}
			printf("\n\n");

			// Input: New Deaths
			do {
				centerAlign("Number of new deaths         >    ");
				fill(3, '\b');
				newDeaths = inputInt(atTitle);

				// If user enters 'x' and chooses 'y'
				if (newDeaths == -69)
					goto mainTitle;

			} while (newDeaths < 0);	// Ask again if input is invalid or entered 'n' at quit to title double confirmation

			// Input: New recoveries
			do {
				centerAlign("Number of new recoveries     >    ");
				fill(3, '\b');
				newRecovered = inputInt(atTitle);

				// If user enters 'x' and chooses 'y'
				if (newRecovered == -69)
					goto mainTitle;

			} while (newRecovered < 0);	// Ask again if input is invalid or entered 'n' at quit to title double confirmation
			printf("\n");


			/*================================== Calculations =======================================*/

			// Main data calculation
			totalCases = preTotal + newTotal;
			totalDeaths = preDeaths + newDeaths;
			totalRecovered = preRecovered + newRecovered;
			totalTreatment = totalCases - totalDeaths - totalRecovered;

			// Rates calculation
			deathRate = (float)totalDeaths / totalCases * 100;
			recoveredRate = (float)totalRecovered / totalCases * 100;
			treatmentRate = (float)totalTreatment / totalCases * 100;

			// Check for highest cases
			if (newTotal > highest) {
				highest = newTotal;
				highestDay = currentDay;
			}

			// Check for lowest cases
			if (newTotal < lowest) {
				lowest = newTotal;
				lowestDay = currentDay;
			}


			/*=================================== Printing Report ======================================*/

			viewCount = 1;			// Reset view 
			reportMenu(viewCount);	// Show the report options

			///* REPORT LOOP STARTS HERE *///
			do {

				// Ask to print which report
				optionScreen();						// Ask for input
				reportSelect = inputInt(atTitle);	// Get and validate input

				// If user enters 'x' and choose 'y'
				if (reportSelect == -69)
					goto mainTitle;

				// If user enters 'x' and choose 'n'
				else if (reportSelect == -70)
					reportMenu(viewCount);


				/* 1 - Displays "Daily Summary Report" --> Re-enter Input */
				else if (reportSelect == 1) {
					// ================================ DSR Table Visualized ================================
					// +------------------+-------------++--------------+-----------------+-----------------+
					// |   Today's cases  | Total cases || Total Deaths | Total Recovered | Under Treatment |
					// +------------------+-------------++--------------+-----------------+-----------------+
					// | local    (D1)    |             ||              :                 :                 |
					// | imported (D2)    |             ||              :                 :                 |
					// |          (Total) |    ( D3 )   ||              :      ( D4 )     :                 |
					// +------------------+-------------++--------------+-----------------+-----------------+
					//                                  ||              :    ( RATES )    :                 |
					//                                  ++--------------+-----------------+-----------------+

					// Header
					dsrHeader();

					// Main Data
					printf(" | local      %-8d|%10s||%11s|%11s|%11s|\n", newLocals, "", "", "", "");	// (D2)
					printf(" | imported   %-8d|%10s||%11s|%11s|%11s|\n", newImported, "", "", "", "");	// (D1)
					printf(" |    Total   %6d  |", newTotal);	// Total

					// (D3)
					centerAlignInt(totalCases, 10, 0);
					printf("|");

					// (D4)
					centerAlignInt(totalDeaths, 11, 0);
					centerAlignInt(totalRecovered, 11, 0);
					centerAlignInt(totalTreatment, 11, 0);
					printf("\n");

					// (RATES)
					printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);
					printf(" %32s||", "");
					centerAlignFloat(deathRate, 11, 0);
					centerAlignFloat(recoveredRate, 11, 0);
					centerAlignFloat(treatmentRate, 11, 0);
					printf("\n %32s++%.11s+%.11s+%.11s+\n\n", "", LINE1, LINE1, LINE1);

					// Prints the menu for the next loop
					viewCount++;
					reportMenu(viewCount);
				}

				/* 2 - Displays "Daily Comparative Report" --> Re-enter input */
				else if (reportSelect == 2) {
					// ================== DCR Table Visualized ==================
					//                 +-----------+-----------++---------------+
					//                 | Yesterday |   Today   ||   Difference  |
					// +---------------+-----------+-----------++---------------+
					// | New Cases     |    C1R1   |    C2R1   ||  [+- C3R1  ]  |
					// +---------------+-----------+-----------++---------------+
					// | Total Cases   |    C1R2   |    C2R2   ||  [+- C3R2  ]  |
					// +---------------+-----------+-----------++---------------+
					// | Death Rate    |    C1R3 % |    C2R3 % ||  [+- C3R3 %]  |
					// +---------------+-----------+-----------++---------------+
					// | Recovery Rate |    C1R4 % |    C2R4 % ||  [+- C3R4 %]  |
					// +---------------+-----------+-----------++---------------+

					// Header
					dcrHeader();
					printf("   %26s|   Day%4d  |   Day%4d  ||%12s|\n", "", currentDay - 1, currentDay, "");
					dcrLine();

					// Row 'New Cases'
					printf("   | New Cases%15s|", "");
					centerAlignInt(preNew, 12, 0);			// (C1R1)
					centerAlignInt(newTotal, 12, 0);		// (C2R1)
					printf("|");							// '|'
					centerAlignInt(newChanges, 12, 1);		// (C3R1)
					dcrLine();								// ----Line Break----

					// Row 'Total Cases'
					printf("   | Total Cases%13s|", "");
					centerAlignInt(preTotal, 12, 0);				// (C1R2)
					centerAlignInt(totalCases, 12, 0);				// (C2R2)
					printf("|");									// '|'
					centerAlignInt(totalCases - preTotal, 12, 1);	// (C2R3)
					dcrLine();										// ----Line Break----

					// Row 'Death Rate'
					printf("   | Death Rate%14s|", "");
					centerAlignFloat(preDeathRate, 12, 0);				// (C1R3)
					centerAlignFloat(deathRate, 12, 0);					// (C2R3)
					printf("|");										// '|'
					centerAlignFloat(deathRate - preDeathRate, 12, 1);	// (C3R3)
					dcrLine();											// ----Line Break----

					// Row 'Recovery Rate'
					printf("   | Recovery Rate%11s|", "");
					centerAlignFloat(preRecoveredRate, 12, 0);					// (C1R4)
					centerAlignFloat(recoveredRate, 12, 0);						// (C2R4)
					printf("|");												// '|'
					centerAlignFloat(recoveredRate - preRecoveredRate, 12, 1);	// (C3R4)
					dcrLine();													// ----Line Break----
					printf("\n");

					// Prints the menu for the next loop
					viewCount++;
					reportMenu(viewCount);
				}

				/* 3 - Quit viewing reports */
				else if (reportSelect == 3) {
					printf("\n");
					if (viewCount == 1)
						centerAlign("[ Quit to view any reports. ]");
					else
						centerAlign("[ Quit to view more reports. ]");
				}

				/* Wrong Input --> Re-enter Input */
				else if (reportSelect != -999 && reportSelect != -70) {
					printf("\n");
					centerAlign("[ Invalid Input. Please Try Again. ]");
					printf("\n");
				}

			} while (reportSelect != 3);	// Always repeat unless user choose quit
			///* REPORT LOOP ENDS HERE *///

			// End of day
			printf("\n\n\n%.24s< End of Day %d Report >%.24s\n\n\n", LINE2, currentDay, LINE2);



			/*================================ Ask to Continue =========================================*/

			// Ask for continuation
			centerAlign("[ Continue to next day? (Y/N) ]");
			printf("\n");
			do {
				// Get user option selection
				optionScreen();
				contiLoopDay = inputAlpha(atTitle);

				// If user enters 'x'
				if (contiLoopDay == 'x')
					goto mainTitle;

			} while (contiLoopDay == 'z');	// 'z' == Invalid input
			/* Only 'y' and 'n' are allowed to exit loop */


			/* Today's data --> Previous day's data */
			preNew = newTotal;
			preTotal = totalCases;
			preDeaths = totalDeaths;
			preRecovered = totalRecovered;
			preTreatment = totalTreatment;
			preDeathRate = deathRate;
			preRecoveredRate = recoveredRate;
			preTreatmentRate = treatmentRate;

			// 'Y' = Continue to next day; 'N' = Go to Ending
		} while (contiLoopDay == 'y');
		///* DAY LOOP ENDS HERE *///

		/*================================ Ending =========================================*/

		// Line Break
		dayBreak();
		printf("\n\n%.31s< Ending >%.31s\n\n\n", LINE2, LINE2);

		// Total days recorded (singular or plural)
		if (currentDay - INI_DAY == 1)
			printf("\t Total Days Recorded              : %d day (Day %d to Day %d)\n", currentDay - INI_DAY, INI_DAY, currentDay);
		else
			printf("\t Total Days Recorded              : %d days (Day %d to Day %d)\n", currentDay - INI_DAY, INI_DAY, currentDay);
		printf("\t Highest no. of cases on record   : %d Cases (Day %d)\n", highest, highestDay);
		printf("\t Lowest no. of cases on record    : %d Cases (Day %d)\n\n", lowest, lowestDay);

		// Statistics
		printf("\t Total no. of cases all time      : %d Cases\n", totalCases);
		printf("\t Total no. of recoveries all time : %d Recoveries\n", totalRecovered);
		printf("\t Total no, of deaths all time     : %d Deaths\n", totalDeaths);
		printf("\t Current Death Rate               : %.2f%%\n\n", deathRate);

		// Danger Level
		dangerLevel(deathRate);

		// Pleasant Ending
		printf("\n\n");
		centerAlign("Thank you for the data. Stay Safe!");
		printf("\n\n");
		printf("%.50s%.22s\n\n", LINE2, LINE2);

		// Tell user the data inputted are saved and will be redirected back to title
		centerAlign("[ All data have been saved! ]");
		printf("\n");
		centerAlign("[ Enter any key to return to the title. ]");
		printf("\n\n\n");
		centerAlign("Press any key to continue . . .");
		fill(32, '\b');
		system("pause");

		// User who enters 'x' at any input and 'y' at double confirmation will skip everything and jump to this postition
	mainTitle:
		system("cls");
	}
	///* RETURN TO TITLE LOOP ENDS HERE *///
	// The only way to quit the program is via "3 - Exit Application" in the title screen


	/*=============================== End of Program ==========================================*/
}




/*================================ User-Defined Functions =========================================*/

/*=============== MAIN FUNCTIONS ===============*/
// Center aligns any given string, but refuses escape characters such as '\n'
void centerAlign(char str[]) {
	int length = strlen(str);
	int indent = (PAGE_WIDTH - length) / 2;
	fill(indent, ' ');
	printf("%s", str);
}

// [Input] Display the layout to get option input from user
void optionScreen(void) {
	centerAlign("[ Enter your option. ]");
	printf("\n");
	centerAlign("<   >");
	fill(3, '\b');
}

// [Input] Get and validate integer input
int inputInt(int atTitle) {
	char input[13];
	int i;			// Empty
	int quitToTitle;

	/* RETURN TYPES
	** input = Valid input, Range(0, infinite)
	** -999  = Invalid Input - Input too long / Contain not integers
	** -69   = Entered X --> Double confirm --> Input 'y'
	** -70	 = Entered X -- > Double confirm --> Input 'n'
	** -420  = Out of Range (When inputting option selections)
	*/

	// Get input in string form
	rewind(stdin);
	scanf("%s", input);

	// If user enters 'x'
	if (strlen(input) == 1 && tolower(input[0]) == 'x') {
		quitToTitle = returnTitle(atTitle);
		if (quitToTitle)
			return -69;
		else
			return -70;
	}

	// Validate if the input is an positive integer
	for (i = 0; i < strlen(input); i++) {
		if ((!(isdigit(input[i])))) {
			printf("\n");
			if (!atTitle) {
				centerAlign("[ Invalid Input. Please Try Again. ]");
			}
			printf("\n");

			return -999;	// Indicates invalid input
		}
	}

	// If everything is ok, 
	// Convert input string to integer and return
	return atoi(input);
}

// [Input] Get and validate character input
char inputAlpha(int atTitle) {
	char input[13], invalid = 'z';
	int quitToTitle;

	/* RETURN TYPES
	** 'y' = Choosed Yes
	** 'n' = Choosed No
	** 'x' = Entered X --> Double confirm --> Quit to Title
	** 'z' = Invalid Input, when entered anything else then y, n or x
	*/

	// Get input in string form
	rewind(stdin);
	scanf("%s", input);

	// Validate and only allow 'y', 'n' or 'x' to be inputted
	if (strlen(input) == 1) {
		if (tolower(input[0]) == 'y')
			return 'y';
		else if (tolower(input[0]) == 'n')
			return 'n';
		else if (tolower(input[0]) == 'x') {
			quitToTitle = returnTitle(atTitle);
			if (quitToTitle)
				return 'x';
			else {
				// Asked again if user entered invalid input
				centerAlign("[ Continue to next day? (Y/N) ]");
				printf("\n");
				return 'z';
			}
		}
	}

	// User will be prompted again if entered invalid input
	printf("\n");
	centerAlign("[ Invalid Input, Please Try Again. ]");
	printf("\n");
	return 'z';
}

// [Input] Double confirm if user wants to quit to the title
int returnTitle(int atTitle) {
	char option, input[13];
	int valid = 0;

	// Clear the screen if user is already at the title
	if (atTitle) {
		system("cls");
		return 1;
	}

	// Ask for double confirmation if user really wants to quit to the title screen
	printf("\n");
	centerAlign("[ Are you sure you want to quit? (Y/N) ]");
	printf("\n");
	centerAlign("[ You will lose all the unsaved data. ]");
	printf("\n");
	optionScreen();
	rewind(stdin);
	scanf("%s", input);

	// If user user enters 'y' or 'n'
	if (strlen(input) == 1 && (tolower(input[0]) == 'y' || tolower(input[0]) == 'n')) {
		valid = 1;
	}

	// Ask again if user entered invalid input
	while (!valid) {
		printf("\n");
		centerAlign("[ Please enter Y or N. ]");
		printf("\n");
		optionScreen();
		rewind(stdin);
		scanf("%s", input);

		// Only exit the loop if user had entered 'y' or 'n'
		if (strlen(input) == 1 && (tolower(input[0]) == 'y' || tolower(input[0]) == 'n')) {
			valid = 1;
		}
	}

	printf("\n");

	// 1 = Quit to title; 0 = Don't quit to title;
	if (tolower(input[0]) == 'y')
		return 1;
	else
		return 0;
}

// [Report] Ask to print which report
void reportMenu(int viewCount) {
	if (viewCount == 1) {
		printf("\n");
		centerAlign("Which report you want to view?");
		printf("\n");
		centerAlign("======================================");
		printf("\n");
		centerAlign("||  1 - Daily Summary Report        ||");
		printf("\n");
		centerAlign("||  2 - Daily Comparative Report    ||");
		printf("\n");
		centerAlign("||  3 - Quit Viewing Reports        ||");
		printf("\n");
		centerAlign("======================================");
		printf("\n\n");
	}
	else {
		centerAlign("Which report you want to view next?");
		printf("\n");
	}
}

// [Ending] Displays danger level according to Death Rate
void dangerLevel(float deathRate) {
	char dangerLevel[20], output[50] = "<<< Current Danger Level: ";

	if (deathRate < 0.1)
		strcpy(dangerLevel, "Extremely Low");
	else if (deathRate < 0.25)
		strcpy(dangerLevel, "Remarkably Low");
	else if (deathRate < 0.5)
		strcpy(dangerLevel, "Very Low");
	else if (deathRate < 1)
		strcpy(dangerLevel, "Low");
	else if (deathRate < 3)
		strcpy(dangerLevel, "Low-medium");
	else if (deathRate < 5)
		strcpy(dangerLevel, "Medium");
	else if (deathRate < 7)
		strcpy(dangerLevel, "Medium-high");
	else if (deathRate < 10)
		strcpy(dangerLevel, "High");
	else if (deathRate < 30)
		strcpy(dangerLevel, "Very High");
	else if (deathRate < 50)
		strcpy(dangerLevel, "Remarkably High");
	else if (deathRate < 75)
		strcpy(dangerLevel, "Extremely High");
	else
		strcpy(dangerLevel, "God Save The Earth");

	strcat(output, dangerLevel);
	strcat(output, " >>>");

	centerAlign(output);
}




/*=============== TITLE SCREEN FUNCTIONS ===============*/
// Instantly prints program title at the title screen
void programTitle(void) {
	printf("\n");
	printf("*  *  *  *  *  *[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]*  *  *  *  *  *\n");
	printf("  *  *  *  *  * ]    COVID-19 CASES TRACKING SYSTEM    [  *  *  *  *  * \n");
	printf("*  *  *  *  *  *[                                      ]*  *  *  *  *  *\n");
	printf("                 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
}

// Instantly prints menu screen at the title screen
void menuScreen(void) {
	printf("\t\t========================================\n");
	printf("\t\t||  1 - Create New Report             ||\n");
	printf("\t\t||  2 - Show Previous day's Summary   ||\n");
	printf("\t\t||  3 - Exit Application              ||\n");
	printf("\t\t========================================\n\n");
}

// Title scroll in animation on startup
void titleAnimation(void)
{
	// Title string
	char line1[] = "*  *  *  *  *  *[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]*  *  *  *  *  *";
	char line2[] = "  *  *  *  *  * ]    COVID-19 CASES TRACKING SYSTEM    [  *  *  *  *  * ";
	char line3[] = "*  *  *  *  *  *[                                      ]*  *  *  *  *  *";
	char line4[] = "                 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                 ";

	int length = strlen(line1); // Length of title
	int i = length;             // Position to start printing title
	int blinkStart = 3;         // Time before start blinking
	int blinkInterval = 2;      // Time intervals when blinking
	int blinkEnd = 8;          // Time after end blinking

	while (i != -1) {

		// Title scroll in from right
		printf("\n");
		printReverse(line1, length, i);
		printReverse(line2, length, i);
		printReverse(line3, length, i);
		printReverse(line4, length, i);

		// Title blinking animation
		if (i == 0) {
			waitTimer(blinkStart);

			// Blink 3 times
			for (int n = 1; n <= 3; n++) {
				system("cls");
				printf("\n\n\n\n\n");
				waitTimer(blinkInterval);
				system("cls");
				printf("\n%s\n%s\n%s\n%s\n", line1, line2, line3, line4);
				waitTimer(blinkInterval);
			}
			waitTimer(blinkEnd);
			break;
		}
		// Clear screen for this frame
		system("cls");
		i--;
	}
}

// Menu dropdown animation on startup
void menuAnimation(void)
{
	// Menu options string
	char line1[] = "========================================";
	char line2[] = "||  1 - Create New Report             ||";
	char line3[] = "||  2 - Show Previous day's Summary   ||";
	char line4[] = "||  3 - Exit Application              ||";
	char line5[] = "========================================";

	int length = strlen(line1); // Length of menu string
	int timerInterval = 3;      // Time interval between animation
	int i;						// Empty variable

	// Line 1
	printf("\t\t%s", line1);
	waitTimer(timerInterval);

	// Line 1, 5
	printf("\n\t\t%s", line5);
	waitTimer(timerInterval);

	// Line 1, 2, 5
	fill(length, '\b');
	printf("%s", line2);
	printf("\n\t\t%s", line5);
	waitTimer(timerInterval);

	// Line 1, 2, 3, 5
	fill(length, '\b');
	printf("%s", line3);
	printf("\n\t\t%s", line5);
	waitTimer(timerInterval);

	// Line 1, 2, 3, 4, 5
	fill(length, '\b');
	printf("%s", line4);
	printf("\n\t\t%s", line5);
	waitTimer(timerInterval);
}

// Scroll in Animation for Each Line
void printReverse(char line[], int len, int i) {
	// Print blank spaces
	for (int n = 0; n < i; n++)
		printf(" ");

	// Print title
	for (int n = 0; n <= len - i; n++)
		printf("%c", line[n]);

	printf("\n");
}

// A timer that waits for a given time
void waitTimer(int timer) {
	timer *= 100000000;

	// Waste time by doing meaningless calculations
	while (timer != 0)
		timer--;
}



/*=============== REPORT FUNCTIONS ===============*/
// Center align integers in a given width
void centerAlignInt(int data, int width, int haveBrackets) {
	char str[13];

	// Convert data into string form
	if (haveBrackets && data > 0)
		sprintf(str, "+%d", data);
	else
		sprintf(str, "%d", data);

	// Pass the string into center align function
	centerAlignData(str, width, haveBrackets);
}

// Center align floats in a given width
void centerAlignFloat(float data, int width, int haveBrackets) {
	char str[13];
	int check = (data * 10 + 0.5);

	// Convert data into string form
	if (haveBrackets && data > 0.0)		// "+" prefix for positive floats 
		sprintf(str, "+%.1f%%", data);
	else if (check == 0)				// Prevent "+0.0" or "-0.0"
		sprintf(str, "%.1f%%", abs(data));
	else
		sprintf(str, "%.1f%%", data);

	// Pass the string into center align function
	centerAlignData(str, width, haveBrackets);
}

// Main center align function for both functions above
void centerAlignData(char str[], int width, int haveBrackets) {
	int length = strlen(str);

	// For printing data without brackets
	if (!haveBrackets) {
		// Calculate left and right spaces
		int rightSpaces = (width - length) / 2;
		int leftSpaces = rightSpaces;
		if ((width % 2 == 0 && length % 2 == 1) || (width % 2 == 1 && length % 2 == 0))
			leftSpaces++;

		// Print the data
		fill(leftSpaces, ' ');
		printf("%s", str);
		fill(rightSpaces, ' ');
		printf("|");
	}
	// For printing data with brackets
	else {
		// Calculate the left and right spaces
		int outerSpace = 2;

		if (strlen(str) > 8)
			outerSpace = 0;
		else if (strlen(str) > 6)
			outerSpace = 1;
		// The minimum width of bracket is set to 6

		int innerWidth = width - 2 - (2 * outerSpace);
		int innerLeft = (innerWidth - length) / 2;
		int innerRight = innerLeft;
		if (length % 2 == 1)
			innerLeft++;

		// Print the data
		fill(outerSpace, ' ');
		printf("[");
		fill(innerLeft, ' ');
		printf("%s", str);
		fill(innerRight, ' ');
		printf("]");
		fill(outerSpace, ' ');
		printf("|\n");
	}
}

// Prints Header of Previous Day's Report
void pdrHeader(void) {
	printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);
	printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Yesterday's ", " Total", " Total", " Total", " Under");
	printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Cases       ", " Cases", " Deaths", " Recovered", " Treatment");
	printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);
}

// Prints Header of Daily Summary Report
void dsrHeader(void) {
	printf("\n%.24s< DAILY SUMMARY REPORT >%.24s\n\n", LINE1, LINE1);
	printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);
	printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Today's ", " Total", " Total", " Total", " Under");
	printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Cases   ", " Cases", " Deaths", " Recovered", " Treatment");
	printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);
}

// Prints Header of Daily Comparative Report
void dcrHeader(void) {
	printf("\n%.22s< DAILY COMPARATIVE REPORT >%.22s\n\n", LINE1, LINE1);
	printf("   %26s+%.12s+%.12s++%.12s+\n", "", LINE1, LINE1, LINE1);
	printf("   %26s|  YESTERDAY |    TODAY   || DIFFERENCE |\n", "");
}

// Prints Line Breaks of Daily Comparative Report
void dcrLine(void) {
	printf("   +%.25s+%.12s+%.12s++%.12s+\n", LINE1, LINE1, LINE1, LINE1);
}


/*=============== OTHER FUNCTIONS ===============*/
// Prints line breaks between days
void dayBreak(void) {
	int i;
	printf("\n");
	for (i = 1; i <= 18; i++) {
		printf("/\\  ");
	}
	printf("\n");
	for (i = 1; i <= 18; i++) {
		printf("  \\/");
	}
	printf("\n");
}

// Prints the given amount of the given character
void fill(int count, char ch) {
	int i;
	for (i = 0; i < count; i++)
		printf("%c", ch);
}
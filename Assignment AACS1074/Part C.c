#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#pragma warning(disable:4996)



/*==================== CONSTANTS ====================*/

// Initial Day's Data
const int INI_NEW_CASES = 9;
const int INI_TOTAL_CASES = 100;
const int INI_DEATHS = 2;
const int INI_RECOVERED = 10;
const int INI_TREATMENT = 88;
const int INI_DAY = 9;

// Line breaks
const char LINE1[] = "--------------------------------------------------";
const char LINE2[] = "==================================================";



/*==================== DECLARE USER-DEFINED FUNCTIONS ====================*/

// Intro Animation
void titleAnimation(void);                      // Title animation on startup
void printReverse(char line[], int def, int i); // Scroll Animation
void waitTimer(int timer);                      // Timer
void menuAnimation(void);                       // Menu animation on startup

// Title Screen
void programTitle(void);         // Display Program title in title screen
void menuScreen(void);           // Display Menu in title screen

// Main Functions
void optionScreen(void);             // Prints "Get user option" screen
int inputInt(int menu);              // Get and validate integer input
char inputAlpha(int isTitle);               // Get and validate character input
void reportMenu(int viewCount, int viewMenu);  // [Report] Ask to print which report
void quitViewReport(int viewCount);            // [Report] Quit printing reports
void dangerLevel(float deathRate);   // [Ending] Danger level according to death rate 

// Previous Day's report Function
void introHeader(void);         // Prints Header

// "Daily Summary Report" Functions
void dsrHeader(void);           // Prints Header
void dsrCol2(int totalCases);   // Center-align text function

// "Daily Comparative Report" Functions
void dcrHeader(void);           // Prints Header
void dcrLine(void);             // Prints line breaks
void dcrData(char str[20]);     // (-------------------)
void dcrCaseData(int i);        // ( Center-align Text )
void dcrRateData(float f);      // (   Functions for   )
void dcrDiff(char str[20]);     // (       "DCR"       )
void dcrCaseDiff(int i);        // (                   )
void dcrRateDiff(float f);      // (-------------------)

// Other Functions
void dayBreak(void);            // Break line between days
void printSpaces(int spaces);	// Used to print spaces in text-align functions
int returnTitle(int isTitle);   // Validate user confirmation to quit to title or not



/*==================== MAIN FUNCTION ====================*/
void main() {

	/*==================== Variables ====================*/

	// Data variables
	int preNew, preTotal, preDeaths, preRecovered, preTreatment;    // Previous day's data
	int newLocals, newImported, newTotal, newDeaths, newRecovered;  // Today's data
	int totalCases, totalDeaths, totalRecovered, totalTreatment;    // Total of (Previous + Today) data
	float preDeathRate, preRecoveredRate, preTreatmentRate;         // Rates of previous day
	float deathRate, recoveredRate, treatmentRate;                  // Rates of today
	int currentDay, daycount;                   // Day variables
	int newChanges;                             // Today's cases - Previous day's cases
	int highest, lowest, highestDay, lowestDay; // Highest and lowest

	// Option selections
	int menuSelect, reportSelect; // Menu, Report
	char contiLoopDay;            // Continue to next day

	// Other variables
	int viewCount, viewMenu;        // Used in report asking
	int returnTitleVal, atTitle = 0;// Validate quit to title



	///* RETURN TO TITLE LOOP STARTS HERE *///
	// User who enters 'x' is brought back to here
	do {
		/*==================== DATA INITIALIZATION ====================*/

		/* Initial day --> Previous day */
		currentDay = INI_DAY;
		preNew = INI_NEW_CASES;
		preTotal = INI_TOTAL_CASES;
		preDeaths = INI_DEATHS;
		preRecovered = INI_RECOVERED;
		preTreatment = INI_TREATMENT;

		/* Default Highest and lowest value */
		highest = INI_NEW_CASES;
		lowest = INI_NEW_CASES;
		highestDay = currentDay;
		lowestDay = currentDay;

		/* Calculations for Previous day's data */
		preDeathRate = (float)preDeaths / preTotal * 100;
		preRecoveredRate = (float)preRecovered / preTotal * 100;
		preTreatmentRate = (float)preTreatment / preTotal * 100;



		/*================================= MENU SCREEN ========================================*/

		// Intro Animation, Plays on startup or when user quit to title
		/*
		if (atTitle == 0) {
			titleAnimation();
			system("cls");
			programTitle();
			menuAnimation();
			system("cls");
		}
		*/
		// Primes menu loop
		programTitle();   // Display Title Screen
		menuScreen();

		if (atTitle == 1)
			printf("\t\t      [ Already at Title Screen. ]\n");

		/* Reset Quit to Title Variables */
		atTitle = 0;
		returnTitleVal = 0;

		///* TITLE SCREEN LOOP STARTS HERE *///
		do {
			// Get user option selection
			do {
				optionScreen();
				menuSelect = inputInt(1); // Get and validate input

				// If user enters 'x'
				if (menuSelect == -69) {
					printf("potato");
					// Validate confirmation to quit to title
					returnTitleVal = returnTitle(1);
					if (returnTitleVal == 1) {
						atTitle = 1;
						goto mainTitle; // Quit to title
					}
					else if (returnTitleVal == 0)
						menuSelect = -999; // Else re-enter input
				}
			} while (menuSelect == -999);


			/* 1 - Start inputting data */
			if (menuSelect == 1) {
				printf("\n\t\t       [ Creating New Report.... ]\n");
				printf("\t\t [ Enter X to emergency quit to Title ]\n");
				break;
			}
			/* 2 - Display Previous day's Report */
			else if (menuSelect == 2) {

				// Break Line
				printf("\n%.24s< Yesterday's Summary >%.25s\n\n", LINE2, LINE2);
				printf("\t\t\t\t[ Day %d ] \n", currentDay);

				// Header
				printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);
				printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Yesterday's ", " Total", " Total", " Total", " Under");
				printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Cases       ", " Cases", " Deaths", " Recovered", " Treatment");

				// Main Data
				printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);
				printf(" |%18d  |%7d   ||%8d   |%8d   |%8d   |\n", preNew, preTotal, preDeaths, preRecovered, preTreatment);

				// Rates
				printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);
				printf(" %32s||%8.1f%%  |%8.1f%%  |%8.1f%%  |\n", "", preDeathRate, preRecoveredRate, preTreatmentRate);
				printf(" %32s++%.11s+%.11s+%.11s+\n\n", "", LINE1, LINE1, LINE1);

				//Ending Line
				printf("\n%.22s< Press any key to go back >%.22s\n\n\n", LINE2, LINE2);
				system("pause");
				system("cls");
			}
			/* 3 - Exit the program */
			else if (menuSelect == 3) {
				printf("\n\t\t       [ Quiting Application... ]\n\n");
				exit(1);
			}
			/* Invalid Input (Integer not in options ) */
			else {
				printf("\n\t\t  [ Invalid Input, Please Try Again. ] \n");
				menuSelect = -420;
			}

			// Display Title Screen
			if (menuSelect != -420) {
				programTitle();
				menuScreen();
			}

		} while (menuSelect != 1);
		///* TITLE SCREEN LOOP ENDS HERE *///

		// Indicate user is no longer at the title screen
		atTitle = 0;

		///* DAY LOOP STARTS HERE *///
		do {
			// New Day
			currentDay++;
			dayBreak();
			printf("\n\n%.23s< START OF DAY %d REPORT >%.23s\n\n", LINE2, currentDay, LINE2);


			/*================================== Input Section =======================================*/

			// Input: New local cases
			printf("\t\t\t[ Enter today's data ] \n");
			do {
				printf("\t\t   Number of new local cases    > ");
				newLocals = inputInt(2);

				// If user enters 'x'
				if (newLocals == -69) {
					// Validate confirmation to quit to title
					returnTitleVal = returnTitle(0);
					if (returnTitleVal == 1)
						goto mainTitle; // Quit to title
					else
						newLocals = -999; // Else re-enter input
				}
			} while (newLocals == -999);

			// Input: New Imported cases
			do {
				printf("\t\t   Number of new imported cases > ");
				newImported = inputInt(2);

				// If user enters 'x'
				if (newImported == -69) {
					// Validate confirmation to quit to title
					returnTitleVal = returnTitle(0);
					if (returnTitleVal == 1)
						goto mainTitle; // Quit to title
					else
						newImported = -999; // Else re-enter Input
				}
			} while (newImported == -999);


			// Short Summary of First two Input
			newTotal = newLocals + newImported;  // Total new cases
			newChanges = newTotal - preNew;      // Changes

			// Print changes
			printf("\n\t\t   [ Total number of new cases = %d ]\n\t\t", newTotal);
			if (newChanges > 0)
				printf("   ( Increased by %d from yesterday. )\n\n", newChanges);
			else if (newChanges < 0)
				printf("   ( Decreased by %d from yesterday. )\n\n", abs(newChanges));
			else
				printf("         ( Same as yesterday. )\n\n");


			// Input: New Deaths
			do {
				printf("\t\t   Number of new deaths         > ");
				newDeaths = inputInt(2);

				// If user enters 'x'
				if (newDeaths == -69) {
					// Validate confirmation to quit to title
					returnTitleVal = returnTitle(0);
					if (returnTitleVal == 1)
						goto mainTitle; // Quit to title
					else
						newDeaths = -999; // Else re-enter input
				}
			} while (newDeaths == -999);

			// Input: New recoveries
			do {
				printf("\t\t   Number of new recoveries     > ");
				newRecovered = inputInt(2);

				// If user enters 'x'
				if (newRecovered == -69) {
					// Validate confirmation to quit to title
					returnTitleVal = returnTitle(0);
					if (returnTitleVal == 1)
						goto mainTitle; // Quit to title
					else
						newRecovered = -999; // Else re-enter input
				}
			} while (newRecovered == -999);
			printf("\n");


			/*================================== Calculations =======================================*/

			// Main data
			totalCases = preTotal + newTotal;
			totalDeaths = preDeaths + newDeaths;
			totalRecovered = preRecovered + newRecovered;
			totalTreatment = totalCases - totalDeaths - totalRecovered;

			// Rates
			deathRate = (float)totalDeaths / totalCases * 100;
			recoveredRate = (float)totalRecovered / totalCases * 100;
			treatmentRate = (float)totalTreatment / totalCases * 100;

			/* Check for highest cases */
			if (newTotal > highest) {
				highest = newTotal;
				highestDay = currentDay;
			}

			/* Check for lowest cases */
			if (newTotal < lowest) {
				lowest = newTotal;
				lowestDay = currentDay;
			}


			/*=================================== Printing Report ======================================*/

			viewCount = 1;  // Reset view count
			viewMenu = 1;   // Default to view the menu options

			///* REPORT LOOP STARTS HERE *///
			do {
				// Ask to print which report

				reportMenu(viewCount, viewMenu);  // Show menu options
				optionScreen();                   // Ask for input
				reportSelect = inputInt(3);       // Get and validate input

				// If user enters 'x'
				if (reportSelect == -69) {
					// Validate confirmation to quit to title
					returnTitleVal = returnTitle(0);
					if (returnTitleVal == 1)
						goto mainTitle; // Quit to title
				}


				/* 1 - Displays "Daily Summary Report" --> Re-enter Input */
				else if (reportSelect == 1) {
					//                            ===== DSR Table Visualized =====
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
					printf(" | local      %-8d|%10s||%11s|%11s|%11s|\n", newLocals, "", "", "", "");   // D2
					printf(" | imported   %-8d|%10s||%11s|%11s|%11s|\n", newImported, "", "", "", ""); // D1
					printf(" |    Total   %6d  |", newTotal);                                          // Total
					dsrCol2(totalCases);                                                               // D3
					printf("||%8d   |%8d   |%8d   |\n", totalDeaths, totalRecovered, totalTreatment);  // D4

					// Rates
					printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);
					printf(" %32s||%8.1f%%  |%8.1f%%  |%8.1f%%  |\n", "", deathRate, recoveredRate, treatmentRate); // RATES
					printf(" %32s++%.11s+%.11s+%.11s+\n\n", "", LINE1, LINE1, LINE1);

					// Show menu options on next loop
					viewMenu = 1;
					viewCount++;
				}

				/* 2 - Displays "Daily Comparative Report" --> Re-enter input */
				else if (reportSelect == 2) {
					//              ===== DCR Table Visualized =====
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
					dcrCaseData(preNew);          // (C1R1)
					dcrCaseData(newTotal);        // (C2R1)
					printf("|");                  // '|'
					dcrCaseDiff(newChanges);      // (C3R1)
					dcrLine();                    // ----Line Break----

					// Row 'Total Cases'
					printf("   | Total Cases%13s|", "");
					dcrCaseData(preTotal);                // (C1R2)
					dcrCaseData(totalCases);              // (C2R2)
					printf("|");                          // '|'
					dcrCaseDiff(totalCases - preTotal);   // (C2R3)
					dcrLine();                            // ----Line Break----

					// Row 'Death Rate'
					printf("   | Death Rate%14s|", "");
					dcrRateData(preDeathRate);            // (C1R3)
					dcrRateData(deathRate);               // (C2R3)
					printf("|");                          // '|'
					dcrRateDiff(deathRate - preDeathRate);// (C3R3)
					dcrLine();                            // ----Line Break----

					// Row 'Recovery Rate'
					printf("   | Recovery Rate%11s|", "");
					dcrRateData(preRecoveredRate);        // (C1R4)
					dcrRateData(recoveredRate);           // (C2R4)
					printf("|");                          // '|'
					dcrRateDiff(recoveredRate - preRecoveredRate); // (C3R4)
					dcrLine();                            // ----Line Break----
					printf("\n");

					// Prints the menu on the next loop
					viewMenu = 1;
					viewCount++;
				}

				/* 3 - Quit viewing reports */
				else if (reportSelect == 3) {
					quitViewReport(viewCount);
				}

				/* Wrong Input --> Re-enter Input */
				else {
					printf("\n\t\t  [ Invalid Input, Please Try Again. ]\n");

					// Disable showing menu options on the next loop
					viewMenu = 0;
				}

			} while (reportSelect != 3);	// Always repeat unless user choose quit
			///* REPORT LOOP ENDS HERE *///

			// End of day
			printf("\n\n\n%.24s< End of Day %d Report >%.24s\n\n\n", LINE2, currentDay, LINE2);



			/*================================ Ask to Continue =========================================*/

			// Reset Sentinel Value
			contiLoopDay = 'x';

			// Ask for continuation
			printf("\t\t      Continue to next day? (Y/N)\n");
			do {
				// Get user option selection
				optionScreen();
				contiLoopDay = inputAlpha(0);

				// Invalid Input
				if (contiLoopDay == 'z')
					printf("\n\t\t  [ Invalid Input, Please Try Again. ]\n");

				// If user enters 'x'
				if (contiLoopDay == 'x') {
					// Validate confirmation to quit to title
					returnTitleVal = returnTitle(0);
					if (returnTitleVal == 1)
						goto mainTitle; // Quit to title
					else
						contiLoopDay = 'z'; // Else re-enter input
				}
			} while (contiLoopDay == 'z');
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

			// 'Y'= Continue to next day; 'N'= Go to Ending
		} while (contiLoopDay == 'y');
		///* DAY LOOP ENDS HERE *///


	///* User jumps to here if user enters 'x' *///
	mainTitle:
		if (returnTitleVal == 1) {
			system("cls"); // Reset everthing, jump to top of page
		}

		// Only if user enters 'x' will repeat loop
	} while (returnTitleVal == 1);
	///* RETURN TO TITLE LOOP ENDS HERE *///


	/*================================ Ending =========================================*/

	// Line Break
	dayBreak();
	printf("\n\n%.29s< Statistics >%.29s\n\n\n", LINE2, LINE2);

	// Total days recorded (singular or plural)
	if (currentDay - INI_DAY == 1)
		printf("\t  Total Days Recorded\t\t : %d day (Day 9 to Day 10)\n", currentDay - INI_DAY);
	else
		printf("\t  Total Days Recorded\t\t : %d days (Day 9 to Day %d)\n", currentDay - INI_DAY, currentDay);

	// Statistics
	printf("\t  Total no. of cases all time      : %d Cases\n", totalCases);
	printf("\t  Total no. of recoveries all time : %d Recoveries\n", totalRecovered);
	printf("\t  Total no, of deaths all time     : %d Deaths\n\n", totalDeaths);

	printf("\t  Highest no. of cases on record   : %d Cases (Day %d)\n", highest, highestDay);
	printf("\t  Lowest no. of cases on record    : %d Cases (Day %d)\n", lowest, lowestDay);
	printf("\t  Current Death Rate               : %.2f%%\n", deathRate);

	// Danger Level
	printf("\n\t\t<<< Current Danger Level : ");
	dangerLevel(deathRate);
	printf(" >>>");

	/* Pleasant Ending */
	printf("\n\n\t\t  Thank you for the data. Stay Safe! \n\n");
	printf("%.50s%.22s\n\n", LINE2, LINE2);



	/*=============================== End of Program ==========================================*/
	system("pause");
}





/*================================ User-Defined Functions =========================================*/

///* INTRO ANIMATION *///
// Title Animation in Title Screen
void titleAnimation(void)
{
	// Title string
	char line1[] = "*  *  *  *  *  *[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]*  *  *  *  *  *";
	char line2[] = "  *  *  *  *  * ]    COVID-19 CASES TRACKING SYSTEM    [  *  *  *  *  * ";
	char line3[] = "*  *  *  *  *  *[                                      ]*  *  *  *  *  *";
	char line4[] = "                 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                 ";

	int length = strlen(line1); // Length of title
	int i = length;             // Position to start printing title
	int n;                      // Empty
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
			for (n = 1; n <= 3; n++) {
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

// Scrolling Animation for title animation
void printReverse(char line[], int len, int i) {
	int n;

	// Print blank spaces
	for (n = 0; n < i; n++)
	{
		printf(" ");
	}
	// Print title
	for (n = 0; n <= len - i; n++)
	{
		printf("%c", line[n]);
	}
	printf("\n");
}

// Waits for a given time
void waitTimer(int timer) {
	timer *= 100000000;
	while (timer != 0)
	{
		timer--;
	}
}

// Menu animation in Title Screen
void menuAnimation(void)
{
	// Menu options string
	char line1[] = "========================================";
	char line2[] = "||  1 - Create New Report             ||";
	char line3[] = "||  2 - Show Previous day's Summary   ||";
	char line4[] = "||  3 - Exit Application              ||";
	char line5[] = "========================================";

	int length = strlen(line1); // Length of menu string
	int i;                      // Empty
	int timerInterval = 3;      // Time interval between animation

	// Line 1
	printf("\t\t%s", line1);
	waitTimer(timerInterval);

	// Line 1, 5
	printf("\n\t\t%s", line5);
	waitTimer(timerInterval);

	// Line 1, 2, 5
	for (i = 0; i < length; i++) {
		printf("\b");
	}
	printf("%s", line2);
	printf("\n\t\t%s", line5);
	waitTimer(timerInterval);

	// Line 1, 2, 3, 5
	for (i = 0; i < length; i++) {
		printf("\b");
	}
	printf("%s", line3);
	printf("\n\t\t%s", line5);
	waitTimer(timerInterval);

	// Line 1, 2, 3, 4, 5
	for (i = 0; i < length; i++) {
		printf("\b");
	}
	printf("%s", line4);
	printf("\n\t\t%s", line5);
	waitTimer(timerInterval);
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
	printf("\t\t========================================\n");
	printf("\t\t||  1 - Create New Report             ||\n");
	printf("\t\t||  2 - Show Previous day's Summary   ||\n");
	printf("\t\t||  3 - Exit Application              ||\n");
	printf("\t\t========================================\n\n");
}



///* MAIN FUNCTIONS*///
// Ask for options in menu screen
void optionScreen(void) {
	int i;

	// Ask for option
	printf("\t\t\t [ Enter your option. ]\n");
	printf("\t\t\t\t <   >");

	// Move cursor to position
	for (i = 0; i <= 2; i++) {
		printf("\b");
	}
}

// Get and validate integer input
int inputInt(int menu) {
	char input[10];
	int i;

	/* RETURN TYPES
	** -999  = Invalid Input - Input too long / Contain Not integers
	** -69   = Entered X --> Quit to Title
	** input = Valid input, Range(0, infinite)
	** -420  = Invalid Input, Out of Range (used in menu and report choice)
	*/

	// Get input in string form
	rewind(stdin);
	scanf("%s", input);

	if (strlen(input) == 1 && tolower(input[0]) == 'x') {
		return -69;
	}

	// Validate if input length = 1 and is an integer
	for (i = 0; i <= strlen(input) - 1; i++) {
		if ((!(isdigit(input[i])))) {
			if (menu == 1)
				printf("\n\t\t  [ Invalid Input, Please Try Again. ] \n");
			else if (menu == 2)
				printf("\t\t  [ Invalid Input, Please Try Again. ]\n\n");
			return -999;
		}
	}
	// Convert input to integer and return
	return atoi(input);
}

// Get and validate character input
char inputAlpha(int isTitle) {
	char input[10], invalid = 'z';
	int i;

	/* RETURN TYPES
	** 'y' = Choosed Yes
	** 'n' = Choosed No
	** 'x' = Quit to Title
	** 'z' = Invalid Input, when entered anything else then y, n or x
	*/

	// Get input in string form
	rewind(stdin);
	scanf("%s", input);

	// Filter and only allow 'y', 'n', 'x' to be returned
	if (strlen(input) != 1)
		return invalid;

	if (tolower(input[0]) == 'y')
		return 'y';
	else if (tolower(input[0]) == 'n')
		return 'n';
	else if (tolower(input[0]) == 'x' && isTitle == 0)
		return 'x';
	else
		return invalid;
}

// Ask to print which report
void reportMenu(int viewCount, int viewMenu) {

	// Don't show menu if last input is invalid
	if (viewMenu == 1) {
		// Ask for option
		if (viewCount == 1) {
			printf("\t     Which report you want to view? (Choose number) \n");
			printf("\t\t======================================\n");
			printf("\t\t||  1 - Daily Summary Report        ||\n");
			printf("\t\t||  2 - Daily Comparative Report    ||\n");
			printf("\t\t||  3 - Quit Viewing                ||\n");
			printf("\t\t======================================\n\n");
		}
		else
			printf("\t   Which report you want to view next? (Choose number) \n");
	}
}

// Quit to view reports
void quitViewReport(int viewCount) {
	if (viewCount == 1)
		printf("\n\t\t      [ Quit to view any reports. ]");
	else
		printf("\n\t\t     [ Quit to view more reports. ]");
}

// Displays danger level according to Death Rate
void dangerLevel(float deathRate) {
	if (deathRate < 0.1)
		printf("Extremely Low");
	else if (deathRate < 0.25)
		printf("Remarkably Low");
	else if (deathRate < 0.5)
		printf("Very Low");
	else if (deathRate < 1)
		printf("Low");
	else if (deathRate < 3)
		printf("Low-medium");
	else if (deathRate < 5)
		printf("Medium");
	else if (deathRate < 7)
		printf("Medium-high");
	else if (deathRate < 10)
		printf("High");
	else if (deathRate < 30)
		printf("Very High");
	else if (deathRate < 50)
		printf("Remarkably High");
	else if (deathRate < 75)
		printf("Extremely High");
	else
		printf("God Save The Earth");
}



///* PREVIOUS DAY'S REPORT FUNCTION *///
// Prints Header of Previous day's report
void introHeader(void) {
	printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);
	printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Yesterday's ", " Total", " Total", " Total", " Under");
	printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Cases       ", " Cases", " Deaths", " Recovered", " Treatment");
	printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);
}



///* "DAILY SUMMARY REPORT" FUNCTION *///
// Prints Header of DSR
void dsrHeader(void) {
	printf("\n%.24s< DAILY SUMMARY REPORT >%.24s\n\n", LINE1, LINE1);
	printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);
	printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Today's ", " Total", " Total", " Total", " Under");
	printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Cases   ", " Cases", " Deaths", " Recovered", " Treatment");
	printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);
}

// Center-align text for 2nd column in DSR
void dsrCol2(int totalCases) {
	char str[20];

	// Convert int to string
	sprintf(str, "%d", totalCases);
	int length = strlen(str);

	// Center-align
	if (length <= 4) {
		printf("%7s", str);
		printSpaces(3);
	}
	else
		switch (length)
		{
		case 5:
		case 6:
			printf("%8s", str);
			printSpaces(2);
			break;
		case 7:
		case 8:
			printf("%9s", str);
			printSpaces(1);
			break;
		case 9:
		case 10:
			printf("%10s", str);
			break;
		default:
			break;
		}
}



///* "DAILY COMPARATIVE REPORT" FUNCTIONS *///
// Prints the Header of DCR
void dcrHeader(void) {
	printf("\n%.22s< DAILY COMPARATIVE REPORT >%.22s\n\n", LINE1, LINE1);
	printf("   %26s+%.12s+%.12s++%.12s+\n", "", LINE1, LINE1, LINE1);
	printf("   %26s|  YESTERDAY |    TODAY   || DIFFERENCE |\n", "");
}

// Prints line breaks for DCR tables
void dcrLine(void) {
	printf("   +%.25s+%.12s+%.12s++%.12s+\n", LINE1, LINE1, LINE1, LINE1);
}

// Specific text align function for Row='Case', Column='Data' cells
void dcrCaseData(int i) {
	char str[20];

	// Convert int to string
	sprintf(str, "%d", i);
	dcrData(str);
}

// Specific text align function for Row='Rate', Column='Data' cells
void dcrRateData(float f) {
	char str[20];

	// Convert float to string
	sprintf(str, "%.1f%%", f);
	dcrData(str);
}

//Generic text align function for Column='Data' cells
void dcrData(char str[20]) {
	// Set initial left and right spacing to 5
	int spaces = 5;

	// Left Spacing
	switch (strlen(str))
	{
	case 1:
	case 2:
		printSpaces(spaces);
		printf("%2s", str);
		break;
	case 3:
	case 4:
		spaces = 4;
		printSpaces(spaces);
		printf("%4s", str);
		break;
	case 5:
	case 6:
		spaces = 3;
		printSpaces(spaces);
		printf("%6s", str);
		break;
	case 7:
	case 8:
		spaces = 2;
		printSpaces(spaces);
		printf("%8s", str);
		break;
	case 9:
	case 10:
		spaces = 1;
		printSpaces(spaces);
		printf("%10s", str);
		break;
	case 11:
	case 12:
		spaces = 0;
		printSpaces(spaces);
		printf("%12s", str);
		break;
	default:
		break;
	}

	// Right Spacing
	printSpaces(spaces);
	printf("|");
}

// Specific text align function for Row='Case', Column='Difference' cells
void dcrCaseDiff(int i) {
	char str[20];

	// Convert int to string
	if (i > 0)
		sprintf(str, "+%d", i);
	else
		sprintf(str, "%d", i);
	dcrDiff(str);
}

// Specific text align function for Row='Rate', Column='Difference' cells
void dcrRateDiff(float f) {
	char str[20];

	// Convert int to string
	if (f > 0)
		sprintf(str, "+%.1f%%", f);
	else
		sprintf(str, "%.1f%%", f);
	dcrDiff(str);
}

// Generic text align function for Column='Difference' cells
void dcrDiff(char str[20]) {
	// Set initial left and right spacing to 2
	int spaces = 2;

	// Left Spacing
	if (strlen(str) > 6 && strlen(str) <= 8)
		spaces = 1;
	else if (strlen(str) > 8)
		spaces = 0;
	printSpaces(spaces);

	// Middle text
	if (strlen(str) < 6)
		printf("[%5s ]", str);
	else
		switch (strlen(str)) {
		case 6:
			printf("[%6s]", str);
			break;
		case 7:
			printf("[%7s ]", str);
			break;
		case 8:
			printf("[%8s]", str);
			break;
		case 9:
			printf("[%9s ]", str);
			break;
		case 10:
			printf("[%10s]", str);
			break;
		default:
			break;
		}

	//Right Spacing
	printSpaces(spaces);
	printf("|\n");
}



///* OTHER FUNCTIONS *///
// Line Break between Days
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

// Used to print spaces in text-align functions
void printSpaces(int spaces) {
	int printSp;
	for (printSp = 1; printSp <= spaces; printSp++)
		printf(" ");
}

int returnTitle(int isTitle) {
	char validate;
	if (isTitle == 1) {
		system("cls");
		return 1;
	}

	printf("\n\t\t[ Are you sure you want to quit? (Y/N) ]\n");
	printf("\t      \n");
	optionScreen();
	validate = inputAlpha(1);
	do {
		if (validate == 'z') {
			printf("\n\t\t\t[ Please Enter Y or N. ]\n");
			optionScreen();
			validate = inputAlpha(1);
		}
	} while (validate == 'z');

	printf("\n");

	if (validate == 'y')
		return 1;
	else if (validate == 'n')
		return 0;
}
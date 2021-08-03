#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)



/* Define Constants */
const int INI_NEW_CASES = 9;		// (-----------)
const int INI_TOTAL_CASES = 100;	// (  Initial  )
const int INI_DEATHS = 2;			// (   Day's   )
const int INI_RECOVERED = 10;		// (   Data    )
const int INI_TREATMENT = 88;		// (-----------)
const char LINE1[50] = "-------------------------------------------------";	// Used as line breaks and in tables



/* Declare User-defined Functions */
void programTitle(void);		// Displays the program title "Covid-19 Cases Tracking System"
void introHeader(void);			// Prints header of the opening report
void askReportChoice(void);		// Asks which report to print
void dsrHeader(void);			// Prints header of "Daily Summary Report"
void dcrHeader(void);			// Prints header of "Daily Comparative Report"
void dcrLine(void);				// Prints line break for "Daily Comparative Report"

void dcrData(void);				// (------------------------------)
void dcrCaseData(int i);		// (     Text-align Functions     )
void dcrRateData(float f);		// (             for              )
void dcrDiff(void);				// (  "Daily Comparative Report"  )
void dcrCaseDiff(int i);		// (                              )
void dcrRateDiff(float f);		// (------------------------------)

int strleng(char s[]);			// Used to determine the length of strings
void printSpaces(int spaces);	// Used to print spaces in text-align functions



/* Declare Global Variables */
char str[20];					// Used in user-defined functions


/* Main function */
main() {

	/*================================ Variables =========================================*/

	int days = 9;													// Initial day count
	int preNew, preTotal, preDeaths, preRecovered, preTreatment;	// Previous day's data
	int newLocals, newImported, newTotal, newDeaths, newRecovered;	// Today's data
	int totalCases, totalDeaths, totalRecovered, totalTreatment;	// Total of ALL data (Previous + Today)
	float preDeathRate, preRecoveredRate, preTreatmentRate;			// Rates of previous day
	float deathRate, recoveredRate, treatmentRate;					// Rates of today
	int newChanges;													// Changes of the number of new cases compared with previous day's new cases
	int reportChoice;												// Used to determine which report to view



	/*================================= Opening (Initial Day) ========================================*/

	/* Assign Initial day's value to their respective variables */
	preNew = INI_NEW_CASES;
	preTotal = INI_TOTAL_CASES;
	preDeaths = INI_DEATHS;
	preRecovered = INI_RECOVERED;
	preTreatment = INI_TREATMENT;

	/* Calculations for Initial day */
	preDeathRate = (float)preDeaths / preTotal * 100;			// Calculate previous day's: Death Rate
	preRecoveredRate = (float)preRecovered / preTotal * 100;	//							 Recovered Rate
	preTreatmentRate = (float)preTreatment / preTotal * 100;	//							 Under Treatment Rate

	/* Display Intro Screen (Previous day's Report) */
	programTitle();													//Displays the program title / logo
	printf("%5sYesterday's summary - (Day %d): \n", "", days);		//Indicate previous day
	printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);														// +-----------+
	printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Yesterday's ", " Total", " Total", " Total", " Under");								// |  Header   |
	printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Cases       ", " Cases", " Deaths", " Recovered", " Treatment");						// |           |
	printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);														// +-----------+
	printf(" |%18d  |%7d   ||%8d   |%8d   |%8d   |\n", preNew, preTotal, preDeaths, preRecovered, preTreatment);						// | Main Data |
	printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);														// +-----------+
	printf(" %32s||%8.1f%%  |%8.1f%%  |%8.1f%%  |\n", "", preDeathRate, preRecoveredRate, preTreatmentRate);							// |   Rates   |
	printf(" %32s++%.11s+%.11s+%.11s+\n\n", "", LINE1, LINE1, LINE1);																		// +-----------+

	/* Indicate New Day */
	days++;															// Increase day by 1
	printf("\n%.31s< DAY %d >%.31s\n\n", LINE1, days, LINE1);			// Start of new day



	/*================================== Input Section =======================================*/

	/* First Input */
	printf(" Enter today's data: \n");
	printf("\tNumber of new local cases    > ");	// Input: New local cases
	scanf("%d", &newLocals);
	printf("\tNumber of new imported cases > ");	//        New Imported cases
	scanf("%d", &newImported);

	/* Short Summary of First Input */
	newTotal = newLocals + newImported;				// Calculate total of new cases
	newChanges = newTotal - preNew;					// Calculate cases increased or decreased from yesterday
	printf("   [ Total number of new cases = %d ]\n", newTotal);
	if (newChanges > 0)
		printf("   ( Increased by %d from yesterday. )", newChanges);			// Print if new cases are: increased from previous day
	else if (newChanges < 0)
		printf("   ( Decreased by %d from yesterday. )", abs(newChanges));		//						   decreased from previous day
	else
		printf("   ( Same as yesterday. )");									//						   unchanged from previous day

	/* Second Input */
	printf("\n\tNumber of new deaths         > ");	// Input: New deaths
	scanf("%d", &newDeaths);
	printf("\tNumber of new recoveries     > ");	//		  New recoveries
	scanf("%d", &newRecovered);



	/*================================== Calculations =======================================*/

	totalCases = preTotal + newTotal;							// Calculate total of: all cases
	totalDeaths = preDeaths + newDeaths;						//					   all deaths
	totalRecovered = preRecovered + newRecovered;				//					   all recoveries
	totalTreatment = totalCases - totalDeaths - totalRecovered;	//					   all under treatments

	deathRate = (float)totalDeaths / totalCases * 100;			// Calculate rates of: all deaths
	recoveredRate = (float)totalRecovered / totalCases * 100;	//					   all recoveries
	treatmentRate = (float)totalTreatment / totalCases * 100;	//					   all under treatments



	/*=================================== Printing Report ======================================*/

	/* Ask for which report to print */
	askReportChoice();
	scanf("%d", &reportChoice);

	/* Displays "Daily Summary Report" */
	if (reportChoice == 1)
	{
		dsrHeader();																			// Print Header ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~ +-------------+
		printf(" | local      %-8d|%10s||%11s|%11s|%11s|\n", newLocals, "", "", "", "");														// |			 |
		printf(" | imported   %-8d|%10s||%11s|%11s|%11s|\n", newImported, "", "", "", "");														// |  Main Data  |
		printf(" |    total   %6d  |%7d   ||%8d   |%8d   |%8d   |\n", newTotal, totalCases, totalDeaths, totalRecovered, totalTreatment);		// |			 |
		printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);															// +-------------+
		printf(" %32s||%8.1f%%  |%8.1f%%  |%8.1f%%  |\n", "", deathRate, recoveredRate, treatmentRate);											// |    Rates    |
		printf(" %32s++%.11s+%.11s+%.11s+\n", "", LINE1, LINE1, LINE1);																			// +-------------+
	}

	/* or Displays "Daily Comparative Report" */
	else if (reportChoice == 2)
	{
		dcrHeader();																// +--------+		//				   +---------------++---------------------+
		printf(" %26s|   Day%4d  |   Day%4d  ||%12s|\n", "", days - 1, days, "");	// | Header |		//				   | Column 'Data' || Column 'Difference' |
		dcrLine();																	// +--------+		// +---------------+-------+-------++---------------------+
		printf(" | New Cases%15s|", "");		// Row 'Cases' A										// | Row 'Cases' A |  C1R1 |  C2R1 ||        C3R1         |
		dcrCaseData(preNew);					// (C1R1)												// +---------------+-------+-------++---------------------+
		dcrCaseData(newTotal);					// (C2R1)												// | Row 'Cases' B |  C1R2 |  C2R2 ||        C3R2         |
		printf("|");							// [Vertical Division Line]								// +---------------+-------+-------++---------------------+
		dcrCaseDiff(newChanges);				// (C3R1)												// | Row 'Rates' A |  C1R3 |  C2R3 ||        C3R3         |
		dcrLine();								// ----Line Break----									// +---------------+-------+-------++---------------------+
		printf(" | Total Cases%13s|", "");		// Row 'Cases' B										// | Row 'Rates' B |  C1R4 |  C2R4 ||        C3R4         |
		dcrCaseData(preTotal);					// (C1R2)												// +---------------+-------+-------++---------------------+
		dcrCaseData(totalCases);				// (C2R2)
		printf("|");							// [Vertical Division Line]
		dcrCaseDiff(totalCases - preTotal);		// (C2R3)
		dcrLine();								// ----Line Break----
		printf(" | Death Rate%14s|", "");		// Row 'Rates' A
		dcrRateData(preDeathRate);				// (C1R3)
		dcrRateData(deathRate);					// (C2R3)
		printf("|");							// [Vertical Division Line]
		dcrRateDiff(deathRate - preDeathRate);	// (C3R3)
		dcrLine();								// ----Line Break----
		printf(" | Recovery Rate%11s|", "");	// Row 'Rates' B
		dcrRateData(preRecoveredRate);			// (C1R4)
		dcrRateData(recoveredRate);				// (C2R4)
		printf("|");							// [Vertical Division Line]
		dcrRateDiff(recoveredRate - preRecoveredRate); // (C3R4)
		dcrLine();								// ----Line Break----
	}

	/* or Skip the printing report part */
	else
		printf("\n  [ You didn't choose any of the options. ]\n");

	/*================================ Ending =========================================*/

	printf("\n%.24s< End of Day %d Report >%.24s\n\n\n", LINE1, days, LINE1);		// Displays the ending line



	/*=============================== End of Program ==========================================*/
	system("pause");
}




/*================================ User-Defined Functions =========================================*/

/* Prints the title/logo of the Program */
void programTitle(void) {
	printf("\n");
	printf("*  *  *  *  *  *[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]*  *  *  *  *  *\n");
	printf("  *  *  *  *  * ]    COVID-19 CASES TRACKING SYSTEM    [  *  *  *  *  * \n");
	printf("*  *  *  *  *  *[                                      ]*  *  *  *  *  *\n");
	printf("                 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n\n");
}

//Prints the Header of the opening's report
void introHeader(void) {
	printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);										// +-----------+
	printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Yesterday's ", " Total", " Total", " Total", " Under");				// |  Header   |
	printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Cases       ", " Cases", " Deaths", " Recovered", " Treatment");		// |           |
	printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);										// +-----------+
}

/* Asks Which report to print */
void askReportChoice(void) {
	printf("\n\n\t=====================================\n");
	printf("\t||  1 - Daily Summary Report       ||\n");
	printf("\t||  2 - Daily Comparative Report   ||\n");
	printf("\t=====================================\n");
	printf("\n What type of report you want to view? (Choose 1 or 2) --> ");
}

		///* DAILY SUMMARY REPORT *///
// Prints the Header of DSR
void dsrHeader(void) {
	printf("\n\n%.24s< DAILY SUMMARY REPORT >%.24s\n\n", LINE1, LINE1);
	printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);								// +----------+
	printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Today's ", " Total", " Total", " Total", " Under");			// |  Header  |
	printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Cases   ", " Cases", " Deaths", " Recovered", " Treatment");	// |          |
	printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);								// +----------+
}

		///* DAILY COMPARATIVE REPORT *///
//Prints the Header of DCR
void dcrHeader(void) {
	printf("\n\n%.22s< DAILY COMPARATIVE REPORT >%.22s\n\n", LINE1, LINE1);
	printf(" %26s+%.12s+%.12s++%.12s+\n", "", LINE1, LINE1, LINE1);
	printf(" %26s|  YESTERDAY |    TODAY   || DIFFERENCE |\n", "");
}

// Prints the line break for DCR tables
void dcrLine(void) {
	printf(" +%.25s+%.12s+%.12s++%.12s+\n", LINE1, LINE1, LINE1, LINE1);
}

// Specific text align function for Row='Case', Column='Data' cells
void dcrCaseData(int i) {
	sprintf(str, "%d", i);
	dcrData();
}

// Specific text align function for Row='Rate', Column='Data' cells
void dcrRateData(float f) {
	sprintf(str, "%.1f", f);
	dcrData();
}

//Generic text align function for Column='Data' cells
void dcrData(void) {
	int spaces = 5, a, x;		// Set initial left and right spacing to 5

	/* Reduce left and right spacing for every 2 increments in string length */
	/* Prints the left spacing */
	switch (strleng(str))
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

	printSpaces(spaces);		// Prints the right spacing
	printf("|");				// Prints the vertical division line
}

// Specific text align function for Row='Case', Column='Difference' cells
void dcrCaseDiff(int i) {
	if (i > 0)
		sprintf(str, "+%d", i);		// Transfer integer to string form; Add a '+' sign to positive values; 
	else
		sprintf(str, "%d", i);		// Transder integer to string form;
	dcrDiff();
}

// Specific text align function for Row='Rate', Column='Difference' cells
void dcrRateDiff(float f) {
	if (f > 0)
		sprintf(str, "+%.1f%%", f);	// Transfer integer to string form; Add a '+' sign to positive values; 
	else
		sprintf(str, "%.1f%%", f);	// Transfer integer to string form;
	dcrDiff();
}

// Generic text align function for Column='Difference' cells
void dcrDiff(void) {
	int spaces = 2, a;						// Set initial left and right spacing to 2

	if (strleng(str) > 6 && strleng(str) <= 8)
		spaces = 1;							// Reduce left and right spacing to 1 for string lengths 7 and 8
	else if (strleng(str) > 8)
		spaces = 0;							// Remove left and right spacing for string lengths > 8

	printSpaces(spaces);					// Prints the left spacing

	/* Give appropriate printing space for each length of string */
	if (strleng(str) < 6)
		printf("[%5s ]", str);
	else
		switch (strleng(str)) {
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

	printSpaces(spaces);				// Prints the right spacing
	printf("|\n");						// Prints the vertical division line
}


		///* Other functions *///
// Used to print spaces in text-align functions
void printSpaces(int spaces) {
	int a;
	for (a = 1; a <= spaces; a++)
		printf(" ");
}

// Used to determine the length of string in certain functions
int strleng(char s[]) {
	int i = 0;
	while (s[i] != '\0')
		i++;
	return i;
}

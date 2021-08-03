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
void dsrHeader(void);			// Prints header of "Daily Summary Report"



/* Main function */
main() {

	/*================================ Variables =========================================*/

	int days = 9;													// Initial day count
	int preNew, preTotal, preDeaths, preRecovered, preTreatment;	// Previous day's data
	int newLocals, newImported, newTotal, newDeaths, newRecovered;	// Today's data
	int totalCases, totalDeaths, totalRecovered, totalTreatment;	// Total of ALL data (Previous + Today)
	float preDeathRate, preRecoveredRate, preTreatmentRate;			// Rates of previous day
	float deathRate, recoveredRate, treatmentRate;					// Rates of today
	


	/*================================= Opening (Initial Day) ========================================*/

	/* Assign Initial day's value to their respective variables */
	preNew = INI_NEW_CASES;
	preTotal = INI_TOTAL_CASES;
	preDeaths = INI_DEATHS;
	preRecovered = INI_RECOVERED;
	preTreatment = INI_TREATMENT;

	/* Calculations for Initial day */
	preDeathRate = (float)preDeaths / preTotal * 100;				// Calculate previous day's: Death Rate
	preRecoveredRate = (float)preRecovered / preTotal * 100;		//							 Recovered Rate
	preTreatmentRate = (float)preTreatment / preTotal * 100;		//							 Under Treatment Rate

	/* Display Intro Screen (Previous day's Report) */
	programTitle();													//Displays the program title / logo
	printf("%5sYesterday's summary - (Day %d): \n", "", days);		//Indicate previous day
	introHeader();													// Print Header ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  +-----------+
	printf(" |%18d  |%7d   ||%8d   |%8d   |%8d   |\n", preNew, preTotal, preDeaths, preRecovered, preTreatment);		// | Main Data |
	printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);										// +-----------+
	printf(" %32s||%8.1f%%  |%8.1f%%  |%8.1f%%  |\n", "", preDeathRate, preRecoveredRate, preTreatmentRate);			// |   Rates   |
	printf(" %32s++%.11s+%.11s+%.11s+\n\n", "", LINE1, LINE1, LINE1);														// +-----------+

	/* Indicate New Day */
	days++;															// Increase day by 1
	printf("\n%.31s< DAY %d >%.31s\n\n", LINE1, days, LINE1);			// Start of new day



	/*================================== Input Section =======================================*/

	printf(" Enter today's data: \n");
	printf("\tNumber of new local cases    > ");	// Input: New local cases
	scanf("%d", &newLocals);
	printf("\tNumber of new imported cases > ");	//        New Imported cases
	scanf("%d", &newImported);
	printf("\tNumber of new deaths         > ");	//		  New deaths
	scanf("%d", &newDeaths);
	printf("\tNumber of new recoveries     > ");	//		  New recoveries
	scanf("%d", &newRecovered);



	/*================================== Calculations =======================================*/

	newTotal = newLocals + newImported;							// Calculate total of: new cases
	totalCases = preTotal + newTotal;							//					   all cases
	totalDeaths = preDeaths + newDeaths;						//					   all deaths
	totalRecovered = preRecovered + newRecovered;				//					   all recoveries
	totalTreatment = totalCases - totalDeaths - totalRecovered;	//					   all under treatments

	deathRate = (float)totalDeaths / totalCases * 100;			// Calculate rates of: all deaths
	recoveredRate = (float)totalRecovered / totalCases * 100;	//					   all recoveries
	treatmentRate = (float)totalTreatment / totalCases * 100;	//					   all under treatments



	/*=================================== Printing Report ======================================*/

	/* Output "Daily Summary Report" */
	dsrHeader();																		// Print Header ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~ +-------------+
	printf(" | local      %-8d|%10s||%11s|%11s|%11s|\n", newLocals, "", "", "", "");													// |			 |
	printf(" | imported   %-8d|%10s||%11s|%11s|%11s|\n", newImported, "", "", "", "");													// |  Main Data  |
	printf(" |    total   %6d  |%7d   ||%8d   |%8d   |%8d   |\n", newTotal, totalCases, totalDeaths, totalRecovered, totalTreatment);	// |			 |
	printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);														// +-------------+
	printf(" %32s||%8.1f%%  |%8.1f%%  |%8.1f%%  |\n", "", deathRate, recoveredRate, treatmentRate);										// |    Rates    |
	printf(" %32s++%.11s+%.11s+%.11s+\n\n", "", LINE1, LINE1, LINE1);																		// +-------------+
	


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
	printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);									// +-----------+
	printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Yesterday's ", " Total", " Total", " Total", " Under");			// |  Header   |
	printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Cases       ", " Cases", " Deaths", " Recovered", " Treatment");	// |           |
	printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);									// +-----------+
}

// Prints the Header of "Daily Summary Report"
void dsrHeader(void) {
	printf("\n\n%.24s< DAILY SUMMARY REPORT >%.24s\n\n", LINE1, LINE1);
	printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);									// +----------+
	printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Today's ", " Total", " Total", " Total", " Under");				// |  Header  |
	printf(" |%20s|%-10s||%-11s|%-11s|%-11s|\n", "Cases   ", " Cases", " Deaths", " Recovered", " Treatment");		// |          |
	printf(" +%.20s+%.10s++%.11s+%.11s+%.11s+\n", LINE1, LINE1, LINE1, LINE1, LINE1);									// +----------+
}
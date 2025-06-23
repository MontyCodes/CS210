#include <iostream> // Used for console input/output 
#include <iomanip>  // Used for formatting output 
#include <fstream>  // Used for file output 
#include <string>   // Used for string manipulation 

using namespace std;

// This function is used for calculating the interest earned on the current balance for 1 month.
double CalculateMonthlyInterest(double currentBalance, double annualInterestRate) {
    // Conversion of annual interest rate from percentage to decimal and then to a monthly rate
    double monthlyInterestRate = (annualInterestRate / 100.0) / 12.0;
    return currentBalance * monthlyInterestRate;
}

// This function is used for performing the year by year calculations and prints those results to both the console and a file.
void CalculateAndDisplayInvestmentData(
    double initialInvestment,
    double monthlyDeposit,
    double annualInterestRate,
    int numberOfYears,
    bool includeMonthlyDeposits,
    ofstream& outputFile // Pass the output file stream by reference
) {
    double currentBalance = initialInvestment;
    double yearEndInterest;
    const int monthsInYear = 12;

    // Prints the table headers to the console
    cout << "Year\t\t" << "Opening Balance\t" << "Deposited Amount\t"
        << "Interest Earned\t" << "Closing Balance" << endl;
    cout << string(80, '-') << endl; // Used to seperate lines

    // Print table headers to file
    outputFile << "Year\t\t" << "Opening Balance\t" << "Deposited Amount\t"
        << "Interest Earned\t" << "Closing Balance" << endl;
    outputFile << string(80, '-') << endl; // Used to seperate lines

    // Loop through each year
    for (int year = 1; year <= numberOfYears; ++year) {
        double yearOpeningBalance = currentBalance;
        yearEndInterest = 0; // Resets the year end interest for the new year

        // Loop for each month in this year
        for (int month = 1; month <= monthsInYear; ++month) {
            // Calculates the monthly interest based on users current balance
            double monthInterest = CalculateMonthlyInterest(currentBalance, annualInterestRate);

            // Accumulate the year end interest
            yearEndInterest += monthInterest;

            // Add a monthly deposit if it's applicable and then add earned interest to the balance
            if (includeMonthlyDeposits) {
                currentBalance += monthlyDeposit;
            }
            currentBalance += monthInterest;
        }

        // Output the results for current year
        cout << fixed << setprecision(2); // Formats to 2 decimal places
        cout << year << "\t\t" << yearOpeningBalance << "\t\t"
            << (includeMonthlyDeposits ? (monthlyDeposit * monthsInYear) : 0.0) << "\t\t\t"
            << yearEndInterest << "\t\t" << currentBalance << endl;

        outputFile << fixed << setprecision(2); // Format for file as well
        outputFile << year << "\t\t" << yearOpeningBalance << "\t\t"
            << (includeMonthlyDeposits ? (monthlyDeposit * monthsInYear) : 0.0) << "\t\t\t"
            << yearEndInterest << "\t\t" << currentBalance << endl;
    }
    cout << endl; // Blank line after the table to help with readability
    outputFile << endl; // Blank line after table in file to help with readability
}

int main() {
    // Declare all variables for input
    double initialInvestmentAmount;
    double monthlyDeposit;
    double annualInterestRate;
    int numberOfYears;

    // Used to pen a file for output while overwriting the file if it exists, or create a new one.
    ofstream outputFile("InvestmentSummary.txt");
    if (!outputFile.is_open()) { // Check if file was opened successfully
        cerr << "Error: Could not open InvestmentSummary.txt for writing." << endl; // Indicate an error in program
        return 1; 
    }

    // 1. Greets the user and gets their inputs
    cout << "Welcome to the Airgead Banking Investment Calculator!" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "Enter initial investment amount (e.g., 1000.00): $";
    cin >> initialInvestmentAmount;
    cout << "Enter monthly deposit amount (e.g., 50.00): $";
    cin >> monthlyDeposit;
    cout << "Enter annual interest rate (e.g., 5 for 5%): ";
    cin >> annualInterestRate;
    cout << "Enter number of years to invest: ";
    cin >> numberOfYears;
    cout << endl; // Blank line to help with readability

    // 2. Shows User Investment Growth Without Monthly Deposits
    cout << "--- Investment Summary (No Monthly Deposits) ---" << endl;
    outputFile << "--- Investment Summary (No Monthly Deposits) ---" << endl;
    CalculateAndDisplayInvestmentData(initialInvestmentAmount, 0.0, annualInterestRate, numberOfYears, false, outputFile);

    // 3. Shows User Investment Growth With Monthly Deposits
    cout << "--- Investment Summary (With Monthly Deposits) ---" << endl;
    outputFile << "--- Investment Summary (With Monthly Deposits) ---" << endl;
    CalculateAndDisplayInvestmentData(initialInvestmentAmount, monthlyDeposit, annualInterestRate, numberOfYears, true, outputFile);

    // Closing message to user
    cout << "Thank you for using the Investment Calculator!" << endl;
    cout << "Detailed results have also been saved to InvestmentSummary.txt." << endl;

    // Used to close the output file
    outputFile.close();

    return 0; // Indicate successful execution of program
}
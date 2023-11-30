#include "financial_operations.h"
#include "financial_operations.cpp"
#include "fstream"
#using namespace std;
int main() {
    char repeat; // For running the code again in-console.
    int size = 0; // Variable for how many rows/lines in the file
    int rates;     // Variable for how many highest and lowest N days to be displayed
    double mean;    // The mean
    std::string name = "stockdates.txt"; // The output file
    std::ofstream output; // This variable will be used to access and write to the output file
    output.open(name);

    do {
        // FinancialRecord array that will formulate our heap (array of structs)
        FinancialRecord* financialArray = nullptr;

        // Array used for the Maximum Subsequence Sum problem (array of structs)
        FinancialRecord* subsequenceArray = nullptr;

        // Inserts file info into the array
        fileToArray(financialArray, "financials.txt", size);

        // Copies content of the main array to the subsequent sum one
        copyArray(financialArray, subsequenceArray, size);

        // Gets the mean
        mean = calculateMean(financialArray, size);

        std::cout << "How much exchange rates would you like to see?" << std::endl;
        std::cin >> rates;

        // Gets the highest N days
        getHighestDays(financialArray, rates, size, mean, "stockdates.txt", output);

        // Gets the lowest N days
        getLowestDays(financialArray, rates, size, mean, "stockdates.txt", output);

        // Gets the Maximum Subsequence Sum, in addition to the start and end dates
        maximumSubsequenceSum(subsequenceArray, size, mean, "stockdates.txt", output);

        // Deallocate the dynamic memory
        delete[] financialArray;
        delete[] subsequenceArray;

        std::cout << "=====================================" << std::endl;
        std::cout << "Do you want to continue (Y/N)?" << std::endl;
        std::cin >> repeat; // For user interactivity and repetition.
    } while (repeat == 'Y' || repeat == 'y');

    output.close();
    return 0;
}

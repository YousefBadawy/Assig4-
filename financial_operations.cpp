#include "financial_operations.h"

// Function to heapify for max heap
void heapifyMax(FinancialRecord arr[], int N, int i) {
    int largest = i;
    int l = 2 * i + 1; // left child
    int r = 2 * i + 2; // right child

    // If left child is larger than its parent
    if (l < N && arr[l].price > arr[largest].price)
        largest = l;

    // If right child is larger than largest as of now
    if (r < N && arr[r].price > arr[largest].price)
        largest = r;

    // If the largest element is not root
    if (largest != i) {
        // Use the built-in swap function to switch them, putting the largest in the root
        std::swap(arr[i], arr[largest]);

        // Recursively repeat
        heapifyMax(arr, N, largest);
    }
}

// Function to heapify for min heap
void heapifyMin(FinancialRecord A[], int N, int i) {
    int l = 2 * i + 1; // left child
    int r = 2 * i + 2; // right child
    int smallest = i;

    // If left child is smaller than its parent
    if (l < N && A[l].price < A[i].price)
        smallest = l;

    // If right child is smaller than the smallest element as of now
    if (r < N && A[r].price < A[smallest].price)
        smallest = r;

    // If the smallest element is not the root
    if (smallest != i) {
        // Make a swap (smallest will go up to root)
        std::swap(A[i], A[smallest]);

        // Recursively repeat
        heapifyMin(A, N, smallest);
    }
}

// Function to build max heap
void buildMaxHeap(FinancialRecord A[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyMax(A, n, i); // This builds the max heap

    for (int i = n - 1; i >= 0; i--) {
        // This is for readjustment after deletion
        std::swap(A[0], A[i]);
        heapifyMax(A, i, 0);
    }
}

// Function to build min heap
void buildMinHeap(FinancialRecord A[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyMin(A, n, i); // This builds the min heap

    for (int i = n - 1; i >= 0; i--) {
        // This is for readjustment after deletion
        std::swap(A[0], A[i]);
        heapifyMin(A, i, 0);
    }
}

// Function to get the number of lines in a file
void getNumLines(std::string name, int& size) {
    std::ifstream f;
    std::string date;
    f.open(name); // Opening the file

    if (f.is_open()) {
        // If the file was successfully opened
        while (!f.eof()) {
            // While there is still data in the file
            getline(f, date); // Read until end of the line
            size++;            // Increment size variable
        }
    }
    else {
        std::cout << "File wasn't opened" << std::endl; // If file didn't open as expected
    }

    f.close(); // Close the file
}

// Function to read file content into an array
void fileToArray(FinancialRecord* f, std::string name, int size) {
    int c = 0; // Variable for traversing the array
    std::ifstream in;
    in.open(name); // Opening the file

    if (in.is_open()) {
        // If the file was successfully opened
        while (c < size && in >> f[c].date >> f[c].price) {
            // Read the data into the array (as long as we haven't exceeded the size and that there is still data to be read)
            c++; // Increment the index variable
        }
    }
    else {
        std::cout << "File wasn't opened" << std::endl; // If file didn't open as expected
    }

    in.close(); // Close the file
}

// Function for potential future implementation
void append() {
    // To be implemented if needed
}

// Function to calculate the mean of financial data
double calculateMean(FinancialRecord A[], int size) {
    double temp = 0; // Our sum variable

    for (int i = 0; i < size; i++) {
        temp += A[i].price; // Sum all values in the array
    }

    return temp / size; // Divide by the size of the array (number of lines) and return it
}

// Function to get N highest exchange rate days
void getHighestDays(FinancialRecord A[], int nrates, int size, double mean, std::string name, std::ofstream& output) {
    int temp = 0; // Variable for traversing the array
    buildMinHeap(A, size); // Building the heap

    std::cout << "The highest " << nrates << " days are : " << std::endl;
    output << "The highest " << nrates << " days are : " << std::endl; // Simply writing the same console output to a file

    while (temp < size && temp < nrates) {
        // While we are still in the array, and we haven't printed more than the number of days the user wants to display
        if (A[temp].price - mean > 0) {
            // If price minus mean is positive
            std::cout << A[temp].date << " " << A[temp].price - mean << std::endl; // Print it
            output << A[temp].date << " " << A[temp].price - mean << std::endl;      // Simply writing the same console output to a file
        }

        temp++; // Go to next element in array
    }

    std::cout << "----------------------------------------------\n" << std::endl;
    output << "-------------------------------------------------\n" << std::endl;
}

// Function to get N lowest exchange rate days
void getLowestDays(FinancialRecord A[], int nrates, int size, double mean, std::string name, std::ofstream& output) {
    int temp = 0; // Variable for traversing the array
    buildMaxHeap(A, size); // Building the heap

    std::cout << "The lowest " << nrates << " days are : " << std::endl;
    output << "The lowest " << nrates << " days are : " << std::endl; // Simply writing the same console output to a file

    while (temp < size && temp < nrates) {
        // While we are still in the array, and we haven't printed more than the number of days the user wants to display
        if (A[temp].price - mean < 0) {
            // If price minus mean is negative
            std::cout << A[temp].date << " " << A[temp].price - mean << std::endl; // Print it
            output << A[temp].date << " " << A[temp].price - mean << std::endl;      // Simply writing the same console output to a file
        }

        temp++; // Go to next element in array
    }

    std::cout << "----------------------------------------------\n" << std::endl;
    output << "-------------------------------------------------\n" << std::endl;
}

// Function for implementing the Maximum Subsequence Sum problem
double maximumSubsequenceSum(FinancialRecord A[], int size, double mean, std::string name, std::ofstream& output) {
    for (int x = 0; x < size; x++) {
        // Changing all values in the array to remove the mean (to get both negative and positive values)
        A[x].price = A[x].price - mean;
    }

    int i = 1;
    double Sij = 0;
    double Smax = 0; // Our max sum variable
    int im = 0;      // Our start index variable
    int jm = 0;      // Our end index variable

    for (int j = 1; j < size; j++) {
        Sij = Sij + A[j].price;

        if (Sij > Smax) {
            Smax = Sij;
            im = i;
            jm = j;
        }
        else if (Sij < 0) {
            i = j + 1;
            Sij = 0;
        }
    }

    std::cout << "The start index is " << im << " and the stop index is " << jm << std::endl;
    std::cout << "The start date is " << A[im].date << " and the end date is " << A[jm].date << std::endl;
    std::cout << "The maximum subsequent sum is " << Smax << std::endl;

    output << "The start index is " << im << " and the stop index is " << jm << std::endl;
    output << "The start date is " << A[im].date << " and the end date is " << A[jm].date << std::endl;
    output << "The maximum subsequent sum is " << Smax << std::endl;
    output << "----------------------------------------------" << std::endl;

    return Smax;
}

// Function to copy an array
void copyArray(FinancialRecord A[], FinancialRecord F[], int size) {
    for (int x = 0; x < size; x++) {
        F[x] = A[x];
    }
}

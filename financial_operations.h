#pragma once
#ifndef FINANCIAL_OPERATIONS_H
#define FINANCIAL_OPERATIONS_H

#include <iostream>
#include <fstream>
#include <ostream>
#include <cmath>

// Structure to hold financial information (date and price)
struct FinancialRecord {
    std::string date;
    double price;
};

// Function declarations for heap operations
void heapifyMax(FinancialRecord arr[], int N, int i);
void heapifyMin(FinancialRecord A[], int N, int i);
void buildMaxHeap(FinancialRecord A[], int n);
void buildMinHeap(FinancialRecord A[], int n);

// Function declarations for file operations
void getNumLines(std::string name, int& size);
void fileToArray(FinancialRecord* f, std::string name, int size);
void append();

// Function declarations for financial calculations
double calculateMean(FinancialRecord A[], int size);
void getHighestDays(FinancialRecord A[], int nrates, int size, double mean, std::string name, std::ofstream& output);
void getLowestDays(FinancialRecord A[], int nrates, int size, double mean, std::string name, std::ofstream& output);
double maximumSubsequenceSum(FinancialRecord A[], int size, double mean, std::string name, std::ofstream& output);
void copyArray(FinancialRecord A[], FinancialRecord F[], int size);

#endif
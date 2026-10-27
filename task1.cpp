/*
 * Course: CS250 - Data Structures and Algorithms
 * Class: BSDS 2A
 * Lab 8: Algorithmic Complexity
 * Student Name: Laraib Fatima
 * CMS ID: 542052
 * Task 1: 2D Peak Element
 * Course Instructor: Dr. Fahad Ahmed Satti
 * Lab Engineer: Hassan Mohtashim
 */

#include <iostream>

using namespace std;

// Find row index containing max element in mid_col
int findMaxRowInColumn(int** mat, int mid_col, int rows) {
    int max_row = 0;
    for (int r = 1; r < rows; r++) {
        if (mat[r][mid_col] > mat[max_row][mid_col]) {
            max_row = r;
        }
    }
    return max_row;
}

// Binary Search across columns for O(N log N) time complexity
void find2DPeak(int** mat, int rows, int cols) {
    int start_col = 0;
    int end_col = cols - 1;

    while (start_col <= end_col) {
        int mid_col = start_col + (end_col - start_col) / 2;

        // Find max element in mid column
        int max_row = findMaxRowInColumn(mat, mid_col, rows);

        // Check left and right neighbors
        bool left_is_greater = (mid_col - 1 >= 0) && (mat[max_row][mid_col - 1] > mat[max_row][mid_col]);
        bool right_is_greater = (mid_col + 1 < cols) && (mat[max_row][mid_col + 1] > mat[max_row][mid_col]);

        if (!left_is_greater && !right_is_greater) {
            cout << "\nPeak element found at position (" << max_row << ", " << mid_col 
                 << ") with value: " << mat[max_row][mid_col] << endl;
            return;
        }
        // Move to left half
        else if (left_is_greater) {
            end_col = mid_col - 1;
        }
        // Move to right half
        else {
            start_col = mid_col + 1;
        }
    }

    cout << "\nNo peak element found." << endl;
}

int main() {
    int rows, cols;
    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;

    // Dynamically allocate 2D array
    int** mat = new int*[rows];
    for (int i = 0; i < rows; i++) {
        mat[i] = new int[cols];
    }

    cout << "Enter values for " << rows << "x" << cols << " matrix:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "Element [" << i << "][" << j << "]: ";
            cin >> mat[i][j];
        }
    }

    find2DPeak(mat, rows, cols);

    // Free memory
    for (int i = 0; i < rows; i++) {
        delete[] mat[i];
    }
    delete[] mat;

    return 0;
}
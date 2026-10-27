/*
 * Course: CS250 - Data Structures and Algorithms
 * Class: BSDS 2A
 * Lab 8: Algorithmic Complexity
 * Student Name: Larainb Fatima
 * CMS ID: 542052
 * Task 2: Knight's Tour
 * Course Instructor: Dr. Fahad Ahmed Satti
 * Lab Engineer: Hassan Mohtashim
 */

#include <iostream>

using namespace std;

// All 8 potential move offsets for a knight on a chessboard
const int dx[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
const int dy[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

// Helper structure for Warnsdorff heuristic
struct Move {
    int x;
    int y;
    int degree;
};

// Check
bool isValid(int x, int y, int N, int** board) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

// Calculate number of legal onward moves from position (x, y)
int getDegree(int x, int y, int N, int** board) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if (isValid(x + dx[i], y + dy[i], N, board)) {
            count++;
        }
    }
    return count;
}

// Selection Sort to order moves by minimum degree
void sortMoves(Move moves[], int count) {
    for (int i = 0; i < count - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < count; j++) {
            if (moves[j].degree < moves[min_idx].degree) {
                min_idx = j;
            }
        }
        Move temp = moves[i];
        moves[i] = moves[min_idx];
        moves[min_idx] = temp;
    }
}

// Task 2 Part 1 & 2: Optimized Backtracking Algorithm with O(N^2) average execution
bool solveKnightsTour(int x, int y, int moveCount, int N, int** board) {
    board[x][y] = moveCount;

    // Base case: visited all N*N squares on the chessboard
    if (moveCount == N * N) {
        return true;
    }

    Move nextMoves[8];
    int moveCandidateCount = 0;

    // Collect all valid adjacent knight moves
    for (int i = 0; i < 8; i++) {
        int nextX = x + dx[i];
        int nextY = y + dy[i];

        if (isValid(nextX, nextY, N, board)) {
            int deg = getDegree(nextX, nextY, N, board);
            nextMoves[moveCandidateCount] = { nextX, nextY, deg };
            moveCandidateCount++;
        }
    }

    // Sort candidate moves by minimum degree
    sortMoves(nextMoves, moveCandidateCount);

    for (int i = 0; i < moveCandidateCount; i++) {
        if (solveKnightsTour(nextMoves[i].x, nextMoves[i].y, moveCount + 1, N, board)) {
            return true;
        }
    }

    // Backtrack step if no path succeeds
    board[x][y] = -1;
    return false;
}

int main() {
    int N, startX, startY;

    // Dynamic user inputs
    cout << "Enter chessboard size N: ";
    cin >> N;

    cout << "Enter starting row x (0 to " << N - 1 << "): ";
    cin >> startX;
    cout << "Enter starting column y (0 to " << N - 1 << "): ";
    cin >> startY;

    // Dynamically allocate N x N board memory
    int** board = new int*[N];
    for (int i = 0; i < N; i++) {
        board[i] = new int[N];
        for (int j = 0; j < N; j++) {
            board[i][j] = -1; // -1 represents unvisited cell
        }
    }

    cout << "\n--- Task 2: Knight's Tour Solution ---" << endl;
    if (solveKnightsTour(startX, startY, 1, N, board)) {
        cout << "Valid Knight's Tour Path Found:" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j] < 10) cout << " ";
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "No valid knight's tour exists starting from (" << startX << ", " << startY << ")." << endl;
    }

    // Free dynamic memory
    for (int i = 0; i < N; i++) {
        delete[] board[i];
    }
    delete[] board;

    return 0;
}
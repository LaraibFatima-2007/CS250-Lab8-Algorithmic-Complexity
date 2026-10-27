/*
 * Course: CS250 - Data Structures and Algorithms
 * Class: BSDS 2A
 * Lab 8: Algorithmic Complexity
 * Student Name: Laraib Fatima
 * CMS ID: 542052
 * Task 3: Iterative Tower of Hanoi
 * Course Instructor: Dr. Fahad Ahmed Satti
 * Lab Engineer: Hassan Mohtashim
 */

#include <iostream>

using namespace std;

// Array-based stack for a peg
struct Peg {
    char name;
    int* disks;
    int top;
};

// Push onto stack
void push(Peg& p, int disk) {
    p.top++;
    p.disks[p.top] = disk;
}

// Pop from stack
int pop(Peg& p) {
    if (p.top == -1) return -1;
    int disk = p.disks[p.top];
    p.top--;
    return disk;
}

// Helper to move top disk legally between two pegs
void moveDiskBetweenPegs(Peg& src, Peg& dest) {
    int disk1 = pop(src);
    int disk2 = pop(dest);

    // If source peg is empty
    if (disk1 == -1) {
        push(src, disk2);
        cout << "Move disk " << disk2 << " from " << dest.name << " to " << src.name << endl;
    }
    // If destination peg is empty
    else if (disk2 == -1) {
        push(dest, disk1);
        cout << "Move disk " << disk1 << " from " << src.name << " to " << dest.name << endl;
    }
    // If disk on src is smaller than dest
    else if (disk1 < disk2) {
        push(dest, disk2);
        push(dest, disk1);
        cout << "Move disk " << disk1 << " from " << src.name << " to " << dest.name << endl;
    }
    // Otherwise move disk from dest to src
    else {
        push(src, disk1);
        push(src, disk2);
        cout << "Move disk " << disk2 << " from " << dest.name << " to " << src.name << endl;
    }
}

// Calculate total moves = 2^N - 1
int calculateTotalMoves(int n) {
    int total = 1;
    for (int i = 0; i < n; i++) {
        total *= 2;
    }
    return total - 1;
}

void solveIterativeHanoi(int n) {
    // Dynamic stack memory allocation
    int* src_memory = new int[n];
    int* aux_memory = new int[n];
    int* dest_memory = new int[n];

    Peg src = { 'A', src_memory, -1 };
    Peg aux = { 'B', aux_memory, -1 };
    Peg dest = { 'C', dest_memory, -1 };

    // If disk count is even, swap peg labels
    if (n % 2 == 0) {
        char temp = dest.name;
        dest.name = aux.name;
        aux.name = temp;
    }

    // Push initial disks onto source peg (largest disk first)
    for (int i = n; i >= 1; i--) {
        push(src, i);
    }

    int total_moves = calculateTotalMoves(n);

    // Iterative move loop
    for (int move = 1; move <= total_moves; move++) {
        if (move % 3 == 1) {
            moveDiskBetweenPegs(src, dest);
        } else if (move % 3 == 2) {
            moveDiskBetweenPegs(src, aux);
        } else if (move % 3 == 0) {
            moveDiskBetweenPegs(aux, dest);
        }
    }

    //free memory for each array
    delete[] src_memory;
    delete[] aux_memory;
    delete[] dest_memory;
}

int main() {
    int num_disks;
    cout << "Enter number of disks: ";
    cin >> num_disks;

    cout << "\n--- Task 3: Iterative Tower of Hanoi (Disks = " << num_disks << ") ---" << endl;
    solveIterativeHanoi(num_disks);

    return 0;
}
#include <stdio.h>

#define MAX_MEMORY 1000
int memory[MAX_MEMORY];

// Function to initialize memory
void initializeMemory() {
    for (int i = 0; i < MAX_MEMORY; i++) {
        memory[i] = -1; // -1 indicates that the memory is unallocated
    }
}

// Function to display memory status
void displayMemory() {
    int i, j;
    int count = 0;
    printf("Memory Status:\n");

    for (i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == -1) { 
            count++;
            j = i;
            while (memory[j] == -1 && j < MAX_MEMORY) { 
                j++;
            }
            printf("Free memory block %d-%d\n", i, j - 1); 
            i = j - 1; // Skip over the current free block
        }
    }

    if (count == 0) {
        printf("No free memory available.\n");
    }
}

// Function to allocate memory using best-fit algorithm
void allocateMemory(int processId, int size) {
    int start = -1;
    int blockSize = 0;
    int bestStart = -1;
    int bestSize = MAX_MEMORY;

    // Find the best-fit block
    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == -1) {  // Free memory block
            if (blockSize == 0) {
                start = i; // Start of a new free block
            }
            blockSize++;
        } else {
            if (blockSize >= size && blockSize < bestSize) {
                bestSize = blockSize;
                bestStart = start; // Store the start of the best-fit block
            }
            blockSize = 0; // Reset block size for the next free block
        }
    }

    // Check the last segment of free memory after the loop
    if (blockSize >= size && blockSize < bestSize) {
        bestSize = blockSize;
        bestStart = start;
    }

    // If a large enough block is found, allocate memory
    if (bestSize >= size) {
        for (int i = bestStart; i < bestStart + size; i++) {
            memory[i] = processId; // Allocate memory to the process
        }
        printf("Allocated memory block %d-%d to Process %d\n", bestStart, bestStart + size - 1, processId);
    } else {
        printf("Memory allocation for Process %d failed (not enough contiguous memory).\n", processId);
    }
}

// Function to deallocate memory
void deallocateMemory(int processId) {
    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == processId) {
            memory[i] = -1; // Release the memory
        }
    }
    printf("Memory released by Process %d\n", processId);
}

int main() {
    initializeMemory();
    displayMemory();

    allocateMemory(1, 200); // Allocate 200 units for Process 1
    displayMemory();

    allocateMemory(2, 300); // Allocate 300 units for Process 2
    displayMemory();

    deallocateMemory(1);    // Deallocate memory for Process 1
    displayMemory();

    allocateMemory(3, 400); // Allocate 400 units for Process 3
    displayMemory();

    return 0;
}

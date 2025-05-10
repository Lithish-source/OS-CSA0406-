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
            // Find contiguous block of free memory
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

// Function to allocate memory using first-fit algorithm
void allocateMemory(int processId, int size) {
    int start = -1;
    int blockSize = 0;

    // Find the first free block that can accommodate the process
    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == -1) { // Free memory block
            if (blockSize == 0) {
                start = i; // Mark the start of a new free block
            }
            blockSize++;
        } else {
            blockSize = 0; // Reset block size when memory is allocated
        }

        // If enough space is found, allocate memory
        if (blockSize >= size) { 
            break;
        }
    }

    // Allocate memory if space is available
    if (blockSize >= size) {
        for (int i = start; i < start + size; i++) {
            memory[i] = processId; // Allocate memory to the process
        }
        printf("Allocated memory block %d-%d to Process %d\n", start, start + size - 1, processId);
    } else {
        printf("Memory allocation for Process %d failed (not enough contiguous memory).\n", processId);
    }
}

// Function to deallocate memory
void deallocateMemory(int processId) {
    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == processId) {
            memory[i] = -1; // Free the memory allocated to the process
        }
    }
    printf("Memory released by Process %d\n", processId);
}

int main() {
    initializeMemory(); // Initialize memory
    displayMemory();    // Display initial memory status

    allocateMemory(1, 200); // Allocate 200 units for Process 1
    displayMemory();        // Display memory status after allocation

    allocateMemory(2, 300); // Allocate 300 units for Process 2
    displayMemory();        // Display memory status after allocation

    deallocateMemory(1);    // Deallocate memory for Process 1
    displayMemory();        // Display memory status after deallocation

    allocateMemory(3, 400); // Allocate 400 units for Process 3
    displayMemory();        // Display memory status after allocation

    return 0;
}

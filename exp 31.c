#include <stdio.h>

#define MAX_FRAMES 3

void printFrames(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1)
            printf(" - ");
        else
            printf(" %d ", frames[i]);
    }
    printf("\n");
}

int main() {
    int referenceString[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(referenceString) / sizeof(referenceString[0]);
    int frames[MAX_FRAMES];
    int framePointer = 0, pageFaults = 0;

    for (int i = 0; i < MAX_FRAMES; i++)
        frames[i] = -1;

    printf("Reference String: ");
    for (int i = 0; i < n; i++)
        printf("%d ", referenceString[i]);
    printf("\n\nPage Replacement Order:\n");

    for (int i = 0; i < n; i++) {
        int page = referenceString[i], pageFound = 0;

        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                pageFound = 1;
                break;
            }
        }

        if (!pageFound) {
            printf("Page %d -> ", page);
            frames[framePointer] = page;
            framePointer = (framePointer + 1) % MAX_FRAMES;
            printFrames(frames, MAX_FRAMES);
            pageFaults++;
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
    return 0;
}

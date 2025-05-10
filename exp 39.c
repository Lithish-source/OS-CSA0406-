#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, seek_time = 0;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int request_queue[n];

    printf("Enter the disk request queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request_queue[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    // Sort requests
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (request_queue[i] > request_queue[j]) {
                int temp = request_queue[i];
                request_queue[i] = request_queue[j];
                request_queue[j] = temp;
            }
        }
    }

    printf("\nC-SCAN Disk Scheduling:\n");
    int start = 0, end = n - 1;

    while (start <= end) {
        for (int i = start; i <= end; i++) {
            if (request_queue[i] >= head) {
                seek_time += abs(head - request_queue[i]);
                head = request_queue[i];
                start = i + 1;
            }
        }

        // Wrap around
        seek_time += abs(head - 0);
        head = 0;
        seek_time += abs(head - request_queue[0]);
        head = request_queue[0];
        start = 1;
    }

    printf("Total Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %.2f\n", (float)seek_time / n);

    return 0;
}

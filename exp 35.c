#include <stdio.h>
#include <stdlib.h>

struct Block {
    int blockNumber;
    char data[256];
};

int main() {
    FILE *file;
    struct Block block;
    int blockNumber;
    int indexBlock[100] = {0}; // Indexed by blockNumber
    long positions[100] = {0};

    file = fopen("indexed_file.txt", "w+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    printf("Enter blocks (Enter 0 as block number to exit):\n");
    while (1) {
        printf("Block Number: ");
        scanf("%d", &block.blockNumber);
        if (block.blockNumber == 0) break;

        printf("Data: ");
        scanf(" %[^\n]", block.data);

        positions[block.blockNumber] = ftell(file);
        fwrite(&block, sizeof(struct Block), 1, file);
        indexBlock[block.blockNumber] = 1;
    }

    while (1) {
        printf("Enter the block number to read (0 to exit): ");
        scanf("%d", &blockNumber);
        if (blockNumber == 0) break;

        if (indexBlock[blockNumber]) {
            fseek(file, positions[blockNumber], SEEK_SET);
            fread(&block, sizeof(struct Block), 1, file);
            printf("Block Number: %d\nData: %s\n", block.blockNumber, block.data);
        } else {
            printf("Block not found.\n");
        }
    }

    fclose(file);
    return 0;
}

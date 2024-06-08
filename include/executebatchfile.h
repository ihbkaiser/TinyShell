#include <stdio.h>
#include <stdlib.h>

int exeBatchFile(const char *batchFilePath) {
    char command[256];
    snprintf(command, sizeof(command), "start /b /wait %s", batchFilePath);

    int result = system(command);

    if(result == -1) {
        perror("Error executing batch file");
        return EXIT_FAILURE;
    }

    printf("Batch file executed successfully.\n");
    return EXIT_SUCCESS;
}
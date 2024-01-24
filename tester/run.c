#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCRIPT_FILE "test_script.sh"
#define TEST_CASES_FILE "test_cases"

void generate_script(const char *outputDir) {
    FILE *scriptFile = fopen(SCRIPT_FILE, "w");
    FILE *testCasesFile = fopen(TEST_CASES_FILE, "r");

    if (scriptFile == NULL || testCasesFile == NULL) {
        perror("Error opening files");
        exit(EXIT_FAILURE);
    }

    char testName[256];
    char command[256];

    while (fscanf(testCasesFile, "%255s\n", testName) == 1 &&
           fgets(command, sizeof(command), testCasesFile) != NULL) {
        // Remove newline character
        command[strcspn(command, "\n")] = '\0';

        // Write shebang line
        fprintf(scriptFile, "#!/bin/bash\n");

        // Write the command with output redirection to the specified directory
        fprintf(scriptFile, "mkdir -p %s\n", outputDir);
        fprintf(scriptFile, "%s > \"%s/%s_out\"\n", command, outputDir, testName);
    }

    fclose(scriptFile);
    fclose(testCasesFile);
}

void run_script() {
    // Compile the script
    system("chmod +x " SCRIPT_FILE);

    // Run the script
    system("./" SCRIPT_FILE);
}

void compare_outputs(const char *outputDir, const char *outputDirOriginal) {
    if (outputDirOriginal == NULL) {
        fprintf(stderr, "Error: Original output directory not provided.\n");
        return;
    }

    printf("Comparing outputs:\n");
    char command[256];
    snprintf(command, sizeof(command), "diff -s %s %s", outputDir, outputDirOriginal);
    system(command);
}


int main(int argc, char *argv[])
{
    const char *outputDir = "files/out";
    const char *outputDirOriginal = "files/original";

    (void)argv;
    if (argc == 1)
    {
        generate_script(outputDir);
        run_script();
        compare_outputs(outputDir, outputDirOriginal);
    }
    else
    {
        generate_script(outputDirOriginal);
        run_script();
        return 0;
    }
    remove(SCRIPT_FILE);
    return 0;
}

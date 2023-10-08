/**
    * @brief IZP - First Project
    *
    * @author Danyleyko Kirill(xdanyl00)
*/
#include "keyfilter.h"

/// @brief Main function
int main(int argc, char *argv[]) 
{
    // My bufferList its matrix, which columns - lines and rows - length of input word
    char bufferList[MAX_NUM_ADDRESSES][MAX_ADDRESS_LENGTH];
    
    // $./keyfilter BP
    char prefix[MAX_ADDRESS_LENGTH];

    int lineCounter = 0;
    int dtype = 0;
    ParseData(bufferList, prefix, &lineCounter, argc, argv, &dtype);

    ParseBuffer(bufferList, prefix, dtype);

    return 0;
}

/// @brief Function For parsing data
void ParseData(char bufferList[MAX_NUM_ADDRESSES][MAX_ADDRESS_LENGTH], 
              char prefix[MAX_ADDRESS_LENGTH], 
              int* lineCounter, int argc, char* argv[], int* dType) 
{
    
    // User input list of addresses && prefix input
    if (argc > 1) 
    {
        strcpy(prefix, argv[1]);
        (*lineCounter)++;

        //TODO: error for not < input .txt

        //Read data from stdin
        while (fgets(bufferList[*lineCounter], sizeof(bufferList[*lineCounter]), stdin) != NULL) 
        {
            // Remove the newline chars at the end of each line
            size_t len = strlen(bufferList[*lineCounter]);
            if (len > 0 && bufferList[*lineCounter][len - 1] == '\n') 
            {
                bufferList[*lineCounter][len - 1] = '\0';
                (*lineCounter)++;
            }
        }

        (*dType) = both;
    } 
    // User input list of addresses but without prefix input
    else if(argc == 1)
    {
        // Read data from stdin
        while (fgets(bufferList[*lineCounter], sizeof(bufferList[*lineCounter]), stdin) != NULL) 
        {
            // Remove the newline chars at the end of each line
            size_t len = strlen(bufferList[*lineCounter]);
            if (len > 0 && bufferList[*lineCounter][len - 1] == '\n') 
            {
                bufferList[*lineCounter][len - 1] = '\0';
                (*lineCounter)++;
            }
        }

        (*dType) = list;
    }
}


void ParseBuffer(char bufferList[MAX_NUM_ADDRESSES][MAX_ADDRESS_LENGTH], 
                char prefix[MAX_ADDRESS_LENGTH], 
                int dType)
{
    // $ ./keyfilter < adresy.txt 
    if(dType == list)
    {
        char result[MAX_ADDRESS_LENGTH];
        size_t line = 0;

        for (line = 0; bufferList[line][0] != '\0'; line++)
        {
            result[line] += bufferList[line][0];
        }

        removeDuplicates(result);
        outputResult(ENABLE, result);
    }
    // $ ./keyfilter br < adresy.txt 
    else if(dType == both)
    {
        // TODO prefix search
        printf("\n\n prefix - %s\n\n", prefix);
    }
}

/// @brief Helper function for removing all duplicates Chars in string
/// @param str string to clear
void removeDuplicates(char str[]) {
    int len = strlen(str);
    if (len <= 1) {
        return;  // No duplicates to remove
    }

    int tail = 1; // Index to track the end of the string without duplicates

    for (int i = 1; i < len; i++) {
        int j;
        for (j = 0; j < tail; j++) {
            if (str[i] == str[j]) {
                break; // Character already seen, skip it
            }
        }
        if (j == tail) {
            // No duplicate found, add the character to the result
            str[tail] = str[i];
            tail++;
        }
    }
    str[tail] = '\0'; // Null-terminate the resulting string
}

/// @brief Helper function for easier print result
/// @param message Result message output
void outputResult(char* message, char* result)
{
    printf("%s %s\n", message, result);
}

/// @brief Error message outputter
void error_messages(int error)
{
    switch (error)
    {
        case err_stdin:
            fprintf(stderr, "Error: stdin not inputed \n");
            exit(1);
        
    }
}


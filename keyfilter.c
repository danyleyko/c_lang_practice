/**
    * @brief IZP - First Project
    *
    * @author Danyleyko Kirill(xdanyl00)
*/


//-------------------------------------------------------------------------------------------------//
// ** Header ** //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

// Limits
#define MAX_ADDRESS_LENGTH 101
#define MAX_NUM_ADDRESSES 43

// Result Outputs
#define ENABLE "Enable:"
#define FOUND "Found:"
#define NOT_FOUND "Not found"

/// @brief Errors
enum error
{
    err_stdin, // stdin in parsing err
    err_prefix, // prefix contains unexcepted value
};

/// @brief User input data type
enum dataType
{
    list, // list input
    both,  // list && prefix input 
    noInput, // No input
};

// Declare function before main
void ParseData(char bufferList[MAX_NUM_ADDRESSES][MAX_ADDRESS_LENGTH], char prefix[MAX_ADDRESS_LENGTH], int* lineCounter, int argc, char* argv[], int* dType);
void ParseBuffer(char bufferList[MAX_NUM_ADDRESSES][MAX_ADDRESS_LENGTH], char prefix[MAX_ADDRESS_LENGTH], int dType, int* lineCounter);
void error_messages(int error);
void removeDuplicates(char str[]);
void outputResult(char* message, char* result);
void bubbleSort(char *str);


//-------------------------------------------------------------------------------------------------//
// ** Main Solution ** //
/// @brief Main function
int main(int argc, char *argv[]) 
{
    // My bufferList its matrix, which columns - lines and rows - length of input word
    char bufferList[MAX_NUM_ADDRESSES][MAX_ADDRESS_LENGTH];

    // just prefix
    char prefix[MAX_ADDRESS_LENGTH];

    int lineCounter = 0;
    int dtype = noInput;
    ParseData(bufferList, prefix, &lineCounter, argc, argv, &dtype);

    ParseBuffer(bufferList, prefix, dtype, &lineCounter);

    return 0;
}

/// @brief Function For parsing data
void ParseData(char bufferList[MAX_NUM_ADDRESSES][MAX_ADDRESS_LENGTH],
              char prefix[MAX_ADDRESS_LENGTH],
              int* lineCounter, int argc, char* argv[], int* dType)
{
    // Initialize memory for bufferList and prefix
    for (int index = 0; index < MAX_NUM_ADDRESSES; index++)
    {
        for (int nextIndex = 0; nextIndex < MAX_ADDRESS_LENGTH; nextIndex++)
        {
            bufferList[index][nextIndex] = '\0';
        }
    }

    // Initialize memory for prefix
    for (int index = 0; index < MAX_ADDRESS_LENGTH; index++)
    {
        prefix[index] = '\0';
    }

    // User input list of addresses && prefix input
    if (argc > 1)
    {
        strcpy(prefix, argv[1]);
        (*lineCounter) = 0; // Reset lineCounter

        // Read the list of addresses
        while (fgets(bufferList[*lineCounter], MAX_ADDRESS_LENGTH, stdin) != NULL)
        {
            // Remove the newline character at the end of each line
            size_t len = strlen(bufferList[*lineCounter]);
            if (len > 0 && bufferList[*lineCounter][len - 1] == '\n')
            {
                bufferList[*lineCounter][len - 1] = '\0';
            }
            (*lineCounter)++;
        }

        (*dType) = both;
    }
    // User input list of addresses but without prefix input
    else if (argc == 1)
    {
        (*lineCounter) = 0; // Reset lineCounter

        // Read the list of addresses
        while (fgets(bufferList[*lineCounter], MAX_ADDRESS_LENGTH, stdin) != NULL)
        {
            // Remove the newline character at the end of each line
            size_t len = strlen(bufferList[*lineCounter]);
            if (len > 0 && bufferList[*lineCounter][len - 1] == '\n')
            {
                bufferList[*lineCounter][len - 1] = '\0';
            }
            (*lineCounter)++;
        }

        (*dType) = list;
    }

    // Input database is empty
    if (bufferList[0][0] == '\0')
    {
        outputResult(NOT_FOUND, bufferList[0]);
    }
}

/// @brief Parsing readen data in buffer
void ParseBuffer(char bufferList[MAX_NUM_ADDRESSES][MAX_ADDRESS_LENGTH], 
                char prefix[MAX_ADDRESS_LENGTH], 
                int dType, int* lineCounter)
{
    char result[MAX_ADDRESS_LENGTH];
    size_t result_index = 0;

    // Initialize result with null characters
    for (size_t i = 0; i < MAX_ADDRESS_LENGTH; i++) {
        result[i] = '\0';
    }

    // $ ./keyfilter < adresy.txt 
    if(dType == list)
    {
        for (int line = 0; line < (*lineCounter); line++)
        {
            char tempArray[MAX_ADDRESS_LENGTH];
            strcpy(tempArray, bufferList[line]);

            if(tempArray[0] != '\0')
            {
                result[result_index++] += toupper(tempArray[0]);
            }
        }

        removeDuplicates(result);
        bubbleSort(result);
        outputResult(ENABLE, result);
    }
    // $ ./keyfilter br < adresy.txt 
    else if(dType == both)
    {
        // Checking prefix
        for (size_t index = 0; prefix[index] != '\0'; index++)
        {
            if(!isalpha(prefix[index]))
            {
                error_messages(err_prefix);
            }
        }
        
        int countFound = 0;
        int foundLineIndex = -1;

        // Searching prefix in database
        for (int line = 1; line < (*lineCounter); line++)
        {
            char cuttedString[MAX_ADDRESS_LENGTH];
            strncpy(cuttedString, bufferList[line], strlen(prefix) + 1);
            cuttedString[strlen(prefix)] = '\0';

            if(strncasecmp(cuttedString, prefix, strlen(prefix)) == 0)
            {
                foundLineIndex = line;
                countFound++;
                
                result[result_index++] += toupper(bufferList[line][strlen(prefix)]);
            }
        }

        removeDuplicates(result);

        // Output messages
        if(countFound == 0)
        {
            outputResult(NOT_FOUND, result);
        }
        else if(countFound == 1)
        {
            for (size_t index = 0; bufferList[foundLineIndex][index] != '\0'; index++)
            {
                result[index] = toupper(bufferList[foundLineIndex][index]);
            }
            
            outputResult(FOUND, result);
        }
        else if(countFound > 1)
        {
            bubbleSort(result);
            outputResult(ENABLE, result);
        }
        
    }
}

/// @brief Helper function for removing all duplicates Chars in string
/// @param str string to clear
void removeDuplicates(char str[]) {
    int len = strlen(str);
    if (len <= 1) 
    {
        return;  // No duplicates to remove
    }

    int tail = 1; // Index to track the end of the string without duplicates

    for (int index = 1; index < len; index++) 
    {
        int nextIndex;
        for (nextIndex = 0; nextIndex < tail; nextIndex++) 
        {
            if (str[index] == str[nextIndex]) 
            {
                break; // Character already seen, skip it
            }
        }
        if (nextIndex == tail) 
        {
            // No duplicate found, add the character to the result
            str[tail] = str[index];
            tail++;
        }
    }
    str[tail] = '\0'; // Null-terminate the resulting string
}

/// @brief Helper function for easier print result
/// @param message Result message output
void outputResult(char* message, char* result)
{
    // Not found
    if(strlen(result) == 0)
    {
        fprintf(stdout, "%s\n", message);
        exit(1);
    }

    fprintf(stdout, "%s %s\n", message, result);
    exit(1);
}

/// @brief Error message outputter
void error_messages(int error)
{
    switch (error)
    {
        case err_stdin:
            fprintf(stderr, "Error: stdin not inputed \n");
            exit(1);
        case err_prefix:
            fprintf(stderr, "Error: prefix contains unexcepted value \n");
            exit(1);
        
    }
}

/// @brief Helper function for sorting string
void bubbleSort(char *str) 
{
    int length = strlen(str);
    int outerIndex, innerIndex;
    char tempChar;

    for (outerIndex = 0; outerIndex < length - 1; outerIndex++) 
    {
        for (innerIndex = 0; innerIndex < length - outerIndex - 1; innerIndex++) 
        {
            if (str[innerIndex] > str[innerIndex + 1]) 
            {
                tempChar = str[innerIndex];
                str[innerIndex] = str[innerIndex + 1];
                str[innerIndex + 1] = tempChar;
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------//

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
    
    // User input list of addresses && prefix input
    if (argc > 1) {
        strcpy(prefix, argv[1]);
        (*lineCounter)++;
        ReadData(bufferList, lineCounter);
        (*dType) = both;
    }
    // User input list of addresses but without prefix input
    else if (argc == 1) {
        ReadData(bufferList, lineCounter);
        (*dType) = list;
    }

    // input database is empty
    if(bufferList[0][0] == '\0')
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

            if(tempArray != NULL)
            {
                result[result_index++] += toupper(tempArray[0]);
            }
        }

        removeDuplicates(result);
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
        

        for (size_t index = 0; prefix[index] != '\0'; index++)
        {
            char prefixChar = toupper(prefix[index]);

            for (int line = 0; line < (*lineCounter); line++)
            {
                if(prefixChar == toupper(bufferList[line][index]))
                {
                    result[result_index++] += prefixChar;
                }
                
            }

            removeDuplicates(result);
        }
        
        outputResult(ENABLE, result);
        
    }
}

/// @brief Helper function for reading data
/// @param lineCounter line count in input database
void ReadData(char bufferList[MAX_NUM_ADDRESSES][MAX_ADDRESS_LENGTH], int* lineCounter) 
{
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


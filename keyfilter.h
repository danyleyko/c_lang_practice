/**
    * @brief Header file for 'keyfilter.c'
    *
    * @author Danyleyko Kirill(xdanyl00)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Limits
#define MAX_ADDRESS_LENGTH 100
#define MAX_NUM_ADDRESSES 42

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
    noInput,
};

// Declare function before main
void ParseData(char bufferList[MAX_NUM_ADDRESSES][MAX_ADDRESS_LENGTH], char prefix[MAX_ADDRESS_LENGTH], int* lineCounter, int argc, char* argv[], int* dType);
void ParseBuffer(char bufferList[MAX_NUM_ADDRESSES][MAX_ADDRESS_LENGTH], char prefix[MAX_ADDRESS_LENGTH], int dType, int* lineCounter);
void ReadData(char bufferList[MAX_NUM_ADDRESSES][MAX_ADDRESS_LENGTH], int* lineCounter);
void error_messages(int error);
void removeDuplicates(char str[]);
void outputResult(char* message, char* result);


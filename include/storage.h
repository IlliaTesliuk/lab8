/** @file
    @brief a module for work with files
*/

#ifndef STORAGE_H
#define STORAGE_H

#include <stdbool.h>
#include <progbase/list.h>
#include "website.h"

/**
    @brief reads whole data from file
    @param filePath - path to file to be read
    @param text - a string to store information from file
*/
bool Storage_readAllText(const char * filePath, char * text);

/**
    @brief creates a list of Website elements from file
    @param filePath - path to file to be read as json
    @returns list of Website elements
*/
List* Storage_readAsJson(const char* filePath);

/**
    @brief creates a json string of list of values from file
    @param filePath - path to file to be read as json
    @returns json string with values from file
*/
char* Storage_fileToJson(const char* filePath);

/**
    @brief creates a json string with information about data in file
    @param filePath - path to file to be read
    @returns json string with information about data in file
*/  
char* Storage_fileContentInfo(const char* filePath);
#endif
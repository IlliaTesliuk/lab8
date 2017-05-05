/** @file
    @brief Search and filter functions for List of Websites
*/

#ifndef LIST_H
#define LIST_H

#include <progbase/list.h>

/**
    @brief finds Website in list by its id
    @param id - id of Website
    @returns index of Website in list or -1 otherwise
*/
int List_findById(List* self, int id);

/**
    @brief filters list of Websites by specified field value
    @param key - name of field to be filtered by
    @param value - value of field
    @returns new list of appropriate Websites 
*/
List* List_filter(List* self, char* key, char* value);

/**
    @brief filters list of Websites by specific name value
    @param name - value of name field of Website to be filtered by
    @returns new list of appropriate Websites 
*/
List* List_filterByName(List* self, char* name);

/**
    @brief filters list of Websites by specific id value  
    @param id - value of id field of Website to be filtered by
    @returns new list of appropriate Websites 
*/
List* List_filterById(List* self, int id);

/**
    @brief filters list of Websites by specific country value  
    @param country - value of country of Website to be filtered by
    @returns new list of appropriate Websites 
*/
List* List_filterByCountry(List* self, char* country);

/**
    @brief filters list of Websites by specific year value  
    @param year - value of year field of Website to be filtered by
    @returns new list of appropriate Websites 
*/
List* List_filterByYear(List* self, int year);

/**
    @brief filters list of Websites by specific type value  
    @param type - type of Website to be filtered by
    @returns new list of appropriate Websites 
*/
List* List_filterByType(List* self, char* type);

/**
    @brief list of Websites representation in json string
    @returns json representation of list of Websites
*/
char* List_toJson(List* self);
#endif
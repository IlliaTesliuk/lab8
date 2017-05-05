/** @file
    @brief Website module
*/

#ifndef WEBSITE_H
#define WEBSITE_H

#include <progbase/list.h>

/**
    @struct Website
    @brief defines a Website data type
*/
typedef struct Website Website;

/**
    @brief Website constructor
*/
Website* Website_new(void);

/**
    @brief Website constructor setter
    @param name - name of website
    @param id - unique id of website
    @param country - origin country of website
    @param year - creation year of website
    @param type - functional type of website 
*/
Website* Website_setNew(char* name, int id, char* country, int year, char* type);

/**
    @brief Website destructor
*/
void Website_free(Website** self);

/**
    @brief Website name getter
    @returns name of Website
*/
char* Website_getName(Website * self);

/**
    @brief Website id getter
    @returns id of Website
*/
int Website_getId(Website * self);

/**
    @brief Website country getter
    @returns country of Website
*/
char* Website_getCountry(Website * self);

/**
    @brief Website year getter
    @returns year of Website
*/
int Website_getYear(Website * self);

/**
    @brief Website type getter
    @returns type of Website
*/
char* Website_getType(Website * self);

/**
    @brief Website name setter
    @param name - name of Website
*/
void Website_setName(Website * self,char* name);

/**
    @brief Website id setter
    @param id - unique id of Website
*/
void Website_setId(Website * self,int id);

/**
    @brief Website country setter
    @param country - origin country of Website
*/
void Website_setCountry(Website * self,char* country);

/**
    @brief Website year setter
    @param year - creation year of Website
*/
void Website_setYear(Website * self,int year);

/**
    @brief Website type setter
    @param type - type of Website
*/
void Website_setType(Website * self,char* type);

/**
    @brief Website representation in json string
    @returns json representation of Website
*/
char* Website_toJsonString(Website * self);

#endif
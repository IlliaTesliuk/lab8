#include "website.h"
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

#define NAME_MAXLEN 100

struct Website {
    char name[NAME_MAXLEN];
    int id;
    char country[40];
    int year;
    char type[40]; 
};

Website* Website_new(void) {
    Website* self = (Website*)malloc(sizeof(Website));
    strcpy(self->name,"");
    self->id = -1;
    strcpy(self->country,"");
    self->year = 0;
    strcpy(self->type,"");
    return self;
}

Website* Website_setNew(char* name, int id, char* country, int year, char* type) {
    Website* self = (Website*)malloc(sizeof(Website));
    strcpy(self->name,name);
    self->id = id;
    strcpy(self->country,country);
    self->year = year;
    strcpy(self->type,type);
    return self;
}

void Website_free(Website** selfPtr) {
    Website* self = *selfPtr;
    free(self);
	*selfPtr = NULL;
}

char* Website_getName(Website * self) {
    return self->name;
}

int Website_getId(Website * self) {
    return self->id;
}

char* Website_getCountry(Website * self) {
    return self->country;
}

int Website_getYear(Website * self) {
    return self->year;
}

char* Website_getType(Website * self) {
    return self->type;
}

void Website_setName(Website * self,char* name) {
    strcpy(self->name, name);
}
void Website_setId(Website * self,int id) {
    self->id = id;
}
void Website_setCountry(Website * self,char* country) {
    strcpy(self->country, country);
}
void Website_setYear(Website * self,int year) {
    self->year = year;
}
void Website_setType(Website * self,char* type) {
    strcpy(self->type, type);
}

char* Website_toJsonString(Website * self) {
    json_t * jobj = json_object();
    json_object_set(jobj, "name", json_string(self->name));
    json_object_set(jobj, "id", json_integer(self->id));
    json_object_set(jobj, "country", json_string(self->country));
    json_object_set(jobj, "year", json_integer(self->year));
    json_object_set(jobj, "type", json_string(self->type));

	char *jStr = json_dumps(jobj, JSON_COMPACT);
	json_decref(jobj);
    return jStr;
}



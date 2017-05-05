#include "list.h"
#include <string.h>
#include <jansson.h>
#include "website.h"

int List_findById(List* self, int id) {
    for(int i = 0; i < List_count(self); i++) {
        Website * node = List_get(self, i);
        if(Website_getId(node) == id) {
            return i;
        }
    }
    return -1;
}

List* List_filter(List* self, char* key, char* value) {
    if(strcmp(key, "name") == 0) {
        return List_filterByName(self, value);
    } else if(strcmp(key, "id") == 0) {
        return List_filterById(self, atoi(value));
    } else if(strcmp(key, "country") == 0) {
        return List_filterByCountry(self, value);
    } else if(strcmp(key, "year") == 0) {
        return List_filterByYear(self, atoi(value));
    } else if(strcmp(key, "type") == 0) {
        return List_filterByType(self, value);
    } else {
        return NULL;
    }
}

List* List_filterByName(List* self, char* name) {
    List* list = List_new();
    for(int i = 0; i < List_count(self); i++) {
        Website * site = List_get(self, i);
        if(strcmp(Website_getName(site),name) == 0) {
            List_add(list, site);
        }
    }
    return list;
}

List* List_filterById(List* self, int id) {
    List* list = List_new();
    List_add(list, List_get(self, List_findById(self, id)));
    return list;
}

List* List_filterByCountry(List* self, char* country) {
    List* list = List_new();
    for(int i = 0; i < List_count(self); i++) {
        Website * site = List_get(self, i);
        if(strcmp(Website_getCountry(site),country) == 0) {
            List_add(list, site);
        }
    }
    return list;
}

List* List_filterByYear(List* self, int year) {
    List* list = List_new();
    for(int i = 0; i < List_count(self); i++) {
        Website * site = List_get(self, i);
        if(Website_getYear(site) == year) {
            List_add(list, site);
        }
    }
    return list;
}

List* List_filterByType(List* self, char* type) {
    List* list = List_new();
    for(int i = 0; i < List_count(self); i++) {
        Website * site = List_get(self, i);
        if(strcmp(Website_getType(site),type) == 0) {
            List_add(list, site);
        }
    }
    return list;
}

char * List_toJson(List* self) {
    json_t* root = json_array();
	json_t * json = NULL;
	
	for(int i = 0; i < List_count(self); i++) {
		Website * site = List_get(self, i);
	
		json = json_object();
	
		json_object_set_new(json, "name", json_string(Website_getName(site)));
		json_object_set_new(json, "id", json_integer(Website_getId(site)));
        json_object_set_new(json, "country", json_string(Website_getCountry(site)));
		json_object_set_new(json, "year", json_integer(Website_getYear(site)));
        json_object_set_new(json, "type", json_string(Website_getType(site)));
		
		json_array_append(root, json);
	}
	
	char *jStr = json_dumps(root, JSON_COMPACT);

	for(int i = 0; i < List_count(self); i++) {
		json_decref(json_array_get(root, i));
	}
	json_decref(root);
    return jStr;
}
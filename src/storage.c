#include "storage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <jansson.h>
#include "website.h"
#include <progbase/list.h>


bool Storage_readAllText(const char * filePath, char * text) {
	char line[100];
	FILE* fin = fopen(filePath, "r");
    if (fin == NULL) return false;
    if(fgets(line, 100, fin))
        strcpy(text, line);
    while(fgets(line, 100, fin)) {
        strcat(text, line);
    }
    text[strlen(text)+1] = '\0';
	fclose(fin);
	return true;
}

List* Storage_readAsJson(const char* filePath) {
    char jsonStr[1000] = "";
	Storage_readAllText(filePath, jsonStr);

	List* list = List_new();

	json_error_t err;
	json_t * jsonArr = json_loads(jsonStr, 0, &err);
	int index = 0;
	json_t * value = NULL;
	json_array_foreach(jsonArr, index, value) {
		Website* node = Website_new();
        Website_setName(node, (char *)json_string_value(json_object_get(value, "name")));
        Website_setId(node, json_integer_value(json_object_get(value, "id")));
        Website_setCountry(node, (char *)json_string_value(json_object_get(value, "country")));
        Website_setYear(node, json_integer_value(json_object_get(value, "year")));
        Website_setType(node, (char *)json_string_value(json_object_get(value, "type")));
		List_add(list, node);
	}
	json_decref(jsonArr);
	return list;
}

char* Storage_fileToJson(const char* filePath) {
	FILE* fin = fopen(filePath, "r");
    if (fin == NULL) {
		puts("Can't open the file'");
	 return NULL;
	}
	fseek(fin, 0, SEEK_END); 
	int size = ftell(fin); 
	fclose(fin);
	char data[200];
	Storage_readAllText(filePath, data);

	json_t * jobj = json_object();
    json_object_set(jobj, "name", json_string(filePath));
    json_object_set(jobj, "size", json_integer(size));
    json_object_set(jobj, "data", json_string(data));

	char *jStr = json_dumps(jobj, JSON_COMPACT);
	json_decref(jobj);
	return jStr;
}

char* Storage_fileContentInfo(const char* filePath) {
	char buffer[200];
	Storage_readAllText(filePath,buffer);

	char * ptr = buffer;
    int sum = 0;
	int count = 0;

    do{
		if(isdigit(*ptr) || (*ptr == '-' && isdigit(*(ptr + 1)))) {
            sum += strtol(ptr, (char **)&ptr, 10);
			count++;
        } else {
            ptr++;
        }
    } while(*ptr != 0);

	double average = sum/count;
	json_t * jobj = json_object();
    json_object_set(jobj, "count", json_integer(count));
    json_object_set(jobj, "average", json_real(average));

	char *jStr = json_dumps(jobj, JSON_COMPACT);
	json_decref(jobj);
	return jStr;
}
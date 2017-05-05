/** @file
    @brief Request and Responce module for HTTP communication
*/

#pragma once

#include <progbase/net.h>
#include <progbase/list.h>

#define MAX_COMMAND_LEN 100
#define BUFFER_SIZE 1024

/**
    @struct Request
    @brief defines a Request data type for HTTP communication
*/
typedef struct {
	char command[MAX_COMMAND_LEN];
} Request;

/**
    @struct Response
    @brief defines a Response data type for HTTP communication
*/
typedef struct {
    int status;
    char description[MAX_COMMAND_LEN];
    char data[BUFFER_SIZE];
} Response;

/**
    @brief parses request HTTP message
    @param str - request HTTP message
    @returns Request element  
*/
Request Request_parse(const char * str);

/**
    @brief processes Request and forms Response
    @param request - Request element to be processed
    @param responce - new Responce element
    @param websites - list of Website elements
*/
void Request_process(Request* request, Response* response, List* websites);

/**
    @brief forms initial Response element
*/
void Response_init(Response* self);

/**
    @brief forms Response element with 400 Bad request status
*/
void Response_badRequest(Response* responce);

/**
    @brief forms Response element with 404 Not found status
*/
void Response_notFound(Response* responce);

/**
    @brief forms Response element with 200 OK status
    @param data - data string to be set to a Response
*/
void Response_success(Response* responce, char* data);

/**
    @brief forms a string with information about server
    @returns json string with information about server 
*/
char* Response_serverInfo(void);

/**
    @brief forms a response message to a client
    @param response - Response element with information due request
    @param message - new message to be sent to client
*/
void Response_toMessage(Response* response,NetMessage * message);

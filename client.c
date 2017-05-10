#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <progbase.h>
#include <progbase/net.h>
#include <progbase/console.h>

#define BUFFER_LEN 1024

void menu(void);
void processCommand(int number, char* request);

int main(int argc, char * argv[]) {
    if (argc < 2) {
		puts("Please, specify server port in command line arguments");
		return 1;
	}
	int port = atoi(argv[1]);

	TcpClient * client = TcpClient_init(&(TcpClient){});
    IpAddress * serverAddress = IpAddress_init(&(IpAddress){}, "127.0.0.1", port);
    NetMessage * message = NetMessage_init(
        &(NetMessage){},  
        (char[BUFFER_LEN]){}, 
        BUFFER_LEN); 
    
    if (!TcpClient_connect(client, serverAddress)) {
        perror("tcp connect");
        return 1;
    }
	sleepMillis(3000);
    
    int choice = 0;
    char request[100] = "";

    menu(); 
    scanf("%i",&choice);
    getchar();
    processCommand(choice,request);
 
    NetMessage_setDataString(message, request);
    
    printf("Send `%s` to server %s:%d\n",
        message->buffer, 
        IpAddress_address(serverAddress),
        IpAddress_port(serverAddress));
    if(!TcpClient_send(client, message)) {
		perror("send");
		return 1;
	}
    //
    // receive response from server
    if(!TcpClient_receive(client, message)) {
		perror("recv");
		return 1;
	}
    printf("Response received from server (%d bytes): \n%s\r\n", 
        message->dataLength,
        message->buffer);
    TcpClient_close(client);
	return 0;
}

void menu(void) {
    conClear();
    char commands[][40] = {
        "Press numbers 1- to get:",
        "1 - information about server",
        "2 - favourite websites",
        "3 - website by value of field",
        "4 - website by id",
        "5 - to read file",
        "6 - to get sum of values fron file"
    };
    for(int i = 0; i < sizeof(commands)/sizeof(commands[0]);i++) {
        puts(commands[i]);
    }
}

void processCommand(int number, char* request) {
    char field[20];
    char value[20];
    switch(number) {
        case 1: 
            strcpy(request,"GET / HTTP/1.0");
            break;
        case 2:
            strcpy(request,"GET /favourites HTTP/1.0");
            break;
        case 3:
            puts("Enter field: ");
            fgets(field,20,stdin);
            field[strlen(field)-1] = 0;
            puts("Enter value: ");
            fgets(value,20,stdin);
            value[strlen(value)-1] = 0;
            sprintf(request, "GET /favourites?%s=%s HTTP/1.0", field, value);
            break;
        case 4:
            puts("Enter id: ");
            fgets(value,20,stdin);
            value[strlen(value)-1] = 0;
            sprintf(request, "GET /favourites/%s HTTP/1.0", value);
            break;
        case 5:
            strcpy(request,"GET /file HTTP/1.0");
            break;
        case 6:
            strcpy(request,"GET /file/data HTTP/1.0");
            break;
        default:
            request[0] = '\0';
            break;
    }
}
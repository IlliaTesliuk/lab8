#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <progbase/net.h>
#include <progbase/list.h>
#include "website.h"
#include "request.h"
#include "storage.h"
#include <time.h>

#define BUFFER_LEN 10240

int main(int argc, char * argv[]) {
	if (argc < 2) {
		puts("Please, specify server port in command line arguments");
		return 1;
	}
	srand(time(0));
	const int port = atoi(argv[1]);

	TcpListener * server = TcpListener_init(&(TcpListener){});
    IpAddress * address = IpAddress_initAny(&(IpAddress){}, port);
    if(!TcpListener_bind(server, address)) {
        perror("tcp bind");
        return 1;
    }
    if (!TcpListener_start(server)) {
        perror("tcp server start");
        return 1;
    }
    printf("TCP Server is listening on port %d\n", 
        IpAddress_port(TcpListener_address(server)));
    
    NetMessage * message = NetMessage_init(
        &(NetMessage){},  
        (char[BUFFER_LEN]){},  
        BUFFER_LEN);

    TcpClient client;

    List* websites = Storage_readAsJson("source.json");
    while (1) {
        puts(">> Waiting for connection...");
        TcpListener_accept(server, &client);
    
        if(!TcpClient_receive(&client, message)) {
			perror("recv");
			return 1;
		}
        IpAddress * clientAddress = TcpClient_address(&client);
        printf(">> Received message from %s:%d (%d bytes): `%s`\n",
            IpAddress_address(clientAddress),  
            IpAddress_port(clientAddress),  
            NetMessage_dataLength(message),
            NetMessage_data(message));

		Request req = Request_parse(NetMessage_data(message));
        Response res;
        Response_init(&res);
        Request_process(&req,&res, websites);
        Response_toMessage(&res, message);
        
        if(!TcpClient_send(&client, message)) {
			perror("send");
			return 1;
		}
        printf(">> String sent to client:\r\n%s\r\n", NetMessage_data(message));
        TcpClient_close(&client);
    }

    TcpListener_close(server);
      List_free(&websites);
	return 0;
}
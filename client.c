#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <progbase.h>
#include <progbase/net.h>
#include <progbase/console.h>

#define BUFFER_LEN 1024

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
    //
    // setup message object
    NetMessage_setDataString(message, "GET / HTTP/1.0");
    //
    // send string to server
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
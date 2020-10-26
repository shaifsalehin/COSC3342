#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdbool.h>

void send_data(int , char * , int , int );

int main(int argc, char ** argv){

        struct sockaddr_in server_addr;

        int flags, sock_fd =0;
        unsigned short port_num;
        size_t server_len = sizeof(server_addr);
        char buffer[1024] = {0};
        char temp[5] = "Deal"; 
        
        port_num = 9000;

    if (!(sock_fd = socket(AF_INET,SOCK_STREAM,0))){
           fprintf(stderr, "Error: Socket failed\n");
           fprintf(stdout, "Server cannot be started\n");
           exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port_num);
    
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr)<=0)
    {
            fprintf(stderr,"Invalid address\n");
            exit(1);
    }
    
    if (connect(sock_fd, (const struct sockaddr *) &server_addr, server_len) <0){
            fprintf(stderr,"Error: Connection error\n");
            exit(1);
    }
    
    temp[strlen("Deal")] = 0;

    send_data(sock_fd, temp, strlen(temp), flags);
    
    if (recv(sock_fd, buffer, sizeof(buffer), flags)<0){
            fprintf(stderr, "Error: Receive error\n");
            exit(1);
    }else{
            fprintf(stdout, "%s", buffer);
    }

        return 0;
}

/* Send function with error checking if sending fails */
void send_data (int client, char * msg, int msglen, int fl){

    if ((send(client, msg, msglen, fl)) < 0){
        fprintf(stderr, "Error sending data\n");
        exit(1);
    }
}

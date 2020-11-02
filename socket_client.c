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
int arg_check(int, char **);

int main(int argc, char ** argv){

    struct sockaddr_in client_addr;

    int flags, rec = 1, sock_fd =0;
    unsigned short port_num;
    size_t client_len = sizeof(client_addr);
    char buffer[1024] = {0};
    char temp[4] = "Deal"; 
    
    if (arg_check(argc, argv) == -1) exit(1);

    port_num = atoi(*&argv[1]);

    if (!(sock_fd = socket(AF_INET,SOCK_STREAM,0))){
           fprintf(stderr, "Error: Socket failed\n");
           fprintf(stdout, "Server cannot be started\n");
           exit(1);
    }
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port_num);
    
    if (inet_pton(AF_INET, *&argv[2], &client_addr.sin_addr)<=0)
    {
            fprintf(stderr,"Invalid address\n");
            exit(1);
    }

        if (connect(sock_fd, (const struct sockaddr *) &client_addr, client_len) <0){
            fprintf(stderr,"Error: Connection error\n");
            exit(1);
        }


        temp[strlen("Deal")] = 0;
        send_data(sock_fd, temp, strlen(temp), flags);

    while(1){

    
        if (!(recv(sock_fd, buffer, sizeof(buffer[strlen(buffer)]), 0))){
            fprintf(stderr, "Error: Receive error\n");
            exit(1);

        }else{

            fprintf(stdout, "%s", buffer);

        }
    }
    
    fflush(stdin);
    return 0;
}
/* Send function with error checking if sending fails */

void send_data (int client, char * msg, int msglen, int fl){

    if ((send(client, msg, msglen, fl)) < 0){
        fprintf(stderr, "Error sending data\n");
        exit(1);
    }
}

/* checks the validity of the command line arguments passed,  */
/* returns -1 if invalid arguments are found, else returns 0  */    
int arg_check(int argc, char *argv[]){


    /* check if port number is entered */
    if (argc != 3){
       fprintf(stderr, "Error: Please provide port number\n");
       fprintf(stdout, "Usage: ./Executable_name Port_number\n");
       fprintf(stdout, "Server cannot be started\n");         
       
       return -1;
    }

    /* prevents segmentation faults if no arguments are given */
    if (argc > 1){

    /* check if integer is typed (only checks for numbers,  */
    /* truncates any letters after the numbers)             */
        if (isdigit(*argv[1]) == 0){
            fprintf(stderr, "Error: Invalid port number\n");
            fprintf(stdout, "Server cannot be started\n");
            
            return -1;       
        }
     
     /* check port range 1 - 65535, 0 is not valid with telnet or netcat */
        if ((atoi(argv[1]) < 1) || (atoi(argv[1]) > 65535)){
            fprintf(stderr, "Error: Port number must be in range 1 - 65,535\n");
            fprintf(stdout, "Server cannot be started\n"); 
           
            return -1;
        }  
    }
    
      return 0;
}

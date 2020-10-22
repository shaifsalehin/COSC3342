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

extern int randperm(int *, int);

int main (int argc, char **argv){
    struct sockaddr_in server_addr;
    int flags,backlog,clientConnection = 0, sock_fd = 0; // create socket variable
    char buffer[1024], buff[1024];
    unsigned short int port_num;
    const char *word = "Deal";
    
    /* prints more text if true */
    bool verbose = true;
    
    
    /* error checking for port number */
    if (argc <= 1){
       fprintf(stderr, "Error:Please provide port number\n");
       fprintf(stdout, "Usage ./Executable_name Port_number\n");
       fprintf(stdout, "Server cannot be started\n");         
       exit(1);
    }

    /* check if number is typed (only checks for numbers, truncates any letters after the numbers) */
    if (isdigit(*argv[1]) == 0){
        fprintf(stderr, "Error: Invalid port number\n");
        fprintf(stdout, "Server cannot be started\n");
        exit(1);
    }
    
    /* check port range 1 - 65535 */
    if ((atoi(argv[1]) < 1) || (atoi(argv[1]) > 65535)){
           fprintf(stderr, "Error: Port number must be in range 1 - 65,535\n");
           fprintf(stdout, "Server cannot be started\n"); 
           exit(1);
    }
     
    size_t server_len = sizeof(server_addr);

    port_num = atoi(argv[1]);   
     
    /* set up socket */
    if (!(sock_fd = socket(AF_INET,SOCK_STREAM,0))){
           fprintf(stderr, "Error: Socket failed\n");
           fprintf(stdout, "Server cannot be started\n");
           exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port_num);
   
   /* create socket bind */ 
    if (bind(sock_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr))){
           fprintf(stderr, "Error: Bind failed\n");
           fprintf(stdout, "Server cannot be started\n"); 
           exit(1);
    }
    
    /* create socket listen */
    if (listen (sock_fd, backlog)){
           fprintf(stderr, "Error: Listen failed\n");
           fprintf(stdout, "Server cannot be started\n"); 
           exit (1);
    }

        fprintf(stdout, "Server running at port: %u\n", port_num);
        fprintf(stdout, "Waiting for connection...\n");
        fprintf(stdout, "====================================\n");
  
    while(1){

        /* create connection from client */
        if (!(clientConnection = (accept (sock_fd, (struct sockaddr *) &server_addr, &server_len)))){
            fprintf(stderr, "Error: Accept failed\n");
            fprintf(stdout, "Connection cannot be established\n"); 
  
        }else{

            fprintf(stdout, "Connection successful\n");
            
                if(verbose){
                    fprintf(stdout, "Accept value: %d\n", clientConnection);
            }

            /* create read function */
            ssize_t data_read = read (clientConnection, buffer, sizeof(buffer));
            
            /* check for and strip new line and carriage return in buffer */ 
            buffer[strcspn(buffer, "\r\n")] = 0;

            if(verbose){
                fprintf(stdout,"Looking for command '%s'\n", *&word);    
                fprintf(stdout,"Command received: '%s'\n",buffer);
            }

            int check_string = strcmp(buffer, word);
            
            if(verbose){
                printf("check string: %d\n",check_string);

            /* server response to command received */
            }   
            if (check_string == 0){
                fprintf(stdout, "Begin dealing\n");
                sprintf(buff, "Server: Begin dealing\n");

            }else{
                fprintf(stdout, "Invalid command\n");
                sprintf(buff, "Server: Invalid command\n");
            }
            
            /* create send function to send message to client */
            ssize_t data_sent = send(clientConnection, buff, strlen(buff), flags);
            break;
        }
    }
    sleep(1);
    
    if(verbose){
        fprintf(stdout, "Shutting down server\n");
    }
    fflush(stdin);
    fflush(stdout);   
    close(clientConnection);
    shutdown(clientConnection, 2);
    fprintf(stdout, "====================================\n");
    return 0;
}

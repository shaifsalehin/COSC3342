#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>

int main (int argc, char **argv){
    struct sockaddr_in server_addr;
    int clientConnection = 0, sock_fd = 0; // create socket variable
    char buffer[1024];
    int flags, backlog;
    unsigned short int port_num;
    int server_len;
    int sock_opt = 1;
    const char *word = "Deal";
    
    /* Error checking for port number */
    if (argc <= 1){
       fprintf(stderr, "Error:Please provide port number. \nUsage ./[Program name] [Port number] \nServer cannot be started.\n");
          
       exit(1);
    }

    /* check if number is typed (only checks for numbers, truncates any letters after the numbers) */
    if (isdigit(*argv[1]) == 0){
        fprintf(stderr, "Error: Invalid port number.\nServer cannot be started.\n");
        exit(1);
    }
    
    /* check port range 1 - 65535 */
    if ((atoi(argv[1]) < 1) || (atoi(argv[1]) > 65535)){
           fprintf(stderr, "Error: Port number must be in range 1 - 65,535.\nServer cannot be started.\n"); 
           exit(1);
    }
     
    server_len = sizeof(server_addr);

    port_num = atoi(argv[1]);   
     
    /* Set up our socket */
    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port_num);
   
   /* Creating our bind */ 
    if (bind(sock_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr))){
            printf("Bind failed\n");
            exit(1);
    }
    
    /* Creating our listen */
    if (listen (sock_fd, backlog)){
            fprintf(stderr, "Listen failed\n");
            exit (1);
    }

        fprintf(stdout, "Server running at port: %u\n", port_num);
        fprintf(stdout, "Waiting for connection...\n");
        fprintf(stdout, "====================================\n");
    while(1){

        /* Creating our accept */
        clientConnection = accept (sock_fd, (struct sockaddr *) &server_addr, &server_len);
        
        /* Error checking accept */
        if (clientConnection == -1){
            fprintf(stderr, "Accept failed\n");
            exit (1);
        }else{
            fprintf(stdout, "Connection successful\n");
            fprintf(stdout, "Accept value: %d\n", clientConnection);

            /* Creating read function */
            int data_read = read (clientConnection, buffer, sizeof(buffer));
               
            /* Check for and strip new line and carriage return in buffer */ 
            size_t buffer_len = strlen(buffer);
             for (int i = buffer_len; i >= -1; i--){
             if ((buffer[i] == '\n') ||  (buffer[i] == '\r'))
                buffer[i] = '\0';
            }
           // fprintf(stdout,"Looking for command '%s'\n", *&word);    
           // fprintf(stdout,"Data received: '%s'\n",buffer);
            

            int check_string = strcmp(buffer, word);
            
            //printf("check string: %d\n",check_string);

                    if (check_string == 0){
                            fprintf(stdout, "Dealing is beginning\n");
                            break;
                    }else{
                            fprintf(stdout, "Invalid command\n");
                            break;
                    }
        }
    }
    sleep(1);
    close(clientConnection);
    shutdown(clientConnection, 2);
    fprintf(stdout, "====================================\n");
    return 0;
}

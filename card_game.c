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

void send_data (int , char * , int , int );

int main (int argc, char **argv){

    
/********************************/// USER SETTINGS ///*********************************/    
    /* prints more text if true */
    bool verbose = true;

    /* true - deals one card a second, false - deals all the cards at once  */
    /* in its own line, might be necessary to turn on for slow connections  */
    bool slowDeal = false;

    /* The word that prompts the server to begin dealing */
    const char *word = "Deal";
/***************************************************************************************/    
   
    struct sockaddr_in server_addr;
    
    int flags,backlog,clientConnection = 0, sock_fd = 0, cards[52];
    unsigned short port_num = atoi(*&argv[1]);
    size_t server_len = sizeof(server_addr);
    
    char buffer[1024], buff[1024];
    
    /* check if port number is entered */
    if (argc <= 1){
       fprintf(stderr, "Error:Please provide port number\n");
       fprintf(stdout, "Usage ./Executable_name Port_number\n");
       fprintf(stdout, "Server cannot be started\n");         
       exit(1);
    }

    /* check if integer is typed (only checks for numbers,  */
    /* truncates any letters after the numbers)             */
    if (isdigit(*argv[1]) == 0){
        fprintf(stderr, "Error: Invalid port number\n");
        fprintf(stdout, "Server cannot be started\n");
        exit(1);
    }
    
    /* check port range 1 - 65535, 0 is not valid with telnet or netcat */
    if ((port_num < 1) || (port_num > 65535)){
           fprintf(stderr, "Error: Port number must be in range 1 - 65,535\n");
           fprintf(stdout, "Server cannot be started\n"); 
           exit(1);
    }
     
     
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
                fprintf(stdout,"Waiting for: '%s'\n", *&word);    
            }

            /* create read function */
            if(!(read (clientConnection, buffer, sizeof(buffer))))
                    fprintf(stderr, "Read error encountered\n");
            
            
            /* check for and strip new line and carriage return in buffer */ 
            buffer[strcspn(buffer, "\r\n")] = 0;

            if(verbose) fprintf(stdout,"Client sent: '%s'\n",buffer);
           
            /* compare command sent from client with 'word' */
            int check_string = strcmp(buffer, word);
            
            if(verbose) fprintf(stdout, "check string: %d\n",check_string);

            /* server response to command received */
            if (check_string == 0){
                if (verbose) fprintf(stdout, "Match found\n");
               
                fprintf(stdout, "Sending reply: Begin dealing\n");
                sprintf(buff, "Server: Begin dealing\r\n"); 
                fprintf(stdout, "Sending cards to client...\n");
                send_data(clientConnection, buff, strlen(buff), flags);
                
                /* loop to populate the cards array with numbers 1 - 52 */
                for (int i = 0; i < 52; i++)
                    cards[i]=i+1;

                /* perform random permutation function from randperm.c */
                randperm(cards, 52);

                /* begin dealing cards, one at a time until deck is empty */
                for (int j = 0; j < 52; j++){
                    if (verbose){ 
                        if(j < 9) 
                            fprintf(stdout, "Card  %d: %d\n", j+1, cards[j]);
                        else      
                            fprintf(stdout, "Card %d: %d\n", j+1, cards[j]);
                    }

                    /* cleaner look, for cards 1-9, the format is Card  #: # */
                    /* (double space)                                        */
                    if(j < 9){
                        sprintf(buff, "Card  %d: %d\r\n", j+1, cards[j]);
                        send_data(clientConnection, buff, strlen(buff), flags);
                        
                        if (slowDeal) sleep(1);

                    /* cards 10-52, format is Cards #: # (single space) */
                    }else{
                        sprintf(buff, "Card %d: %d\r\n", j+1, cards[j]);
                        send_data(clientConnection, buff, strlen(buff), flags);
                        
                        if (slowDeal) sleep(1);
                    }
                }
                break;

            /* If the correct command is not sent */
            }else{
                if (verbose) fprintf(stdout, "Could not find match\n");
                
                fprintf(stdout, "Sending reply: Invalid command\n");
                sprintf(buff, "Server: Invalid command\r\n");
                send_data(clientConnection, buff, strlen(buff), flags);
            }
            break;
        }
    }
    
    /* Broadcast the shutting down of server */
    if(verbose) fprintf(stdout, "Shutting down server\n");
    sprintf(buff, "Server: Closing connection\r\n");
    send_data(clientConnection, buff, strlen(buff), flags);
    fprintf(stdout, "====================================\n");
    
    /* Shutdown connection */
    fflush(stdin);
    fflush(stdout);   
    close(clientConnection);
    shutdown(clientConnection, 2);
    
    return 0;
}

/* Send function with error checking if sending fails */
void send_data (int client, char * msg, int msglen, int fl){

        if ((send(client, msg, msglen, fl)) < 0){
                fprintf(stderr, "Error sending data\n");
                exit(1);
        }
}

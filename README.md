# COSC3342 - Computer Networks

## Contents
* [Socket Server](#socket-server)
  * [Project Description](#project-description)
  * [Setup](#setup)
* [Card Game](#card-game)
  * [Project Description](#project-description-1)
  * [Setup](#setup-1)
  
## Socket server
![complete](https://user-images.githubusercontent.com/47615511/96832806-f6532180-1404-11eb-9618-40ba0bb5f859.png)

### Project Description

Create a socket server in C. Let a client connect to the server and give commands. The server will then evaluate the commands and respond to the client. Currently only responds to 'Deal'.

### Setup:

compile: ```$ gcc -o executable_name socket_server.c```  
run    : ```$ ./executable_name port_number```  

To send command, open another terminal while the server is started and type:

```$ echo "message" | nc server_IP server_port```

For telnet (2 way communication):

```$ telnet server_IP server_port```

-------------------------
## Card Game
![wip](https://user-images.githubusercontent.com/47615511/96809326-41a70900-13e0-11eb-83b3-485762286ad4.png)

### Project Description

Create a socket server. When the client connects to the server and gives the command 'Deal', the server will then respond to the client by shuffling a pack of playing cards and dealing them one by one to the client until the card deck is empty. The server will then close the connection.

### Setup:

compile: ```$ gcc -o executable_name card_game.c randperm.c```  
run    : ```$ ./executable_name port_number```  

To send command, open another terminal while the server is started and type:

```$ telnet server_IP server_port```  
```Deal```

-------------------------


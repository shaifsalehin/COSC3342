# COSC3342 - Socket Programming

## Contents
* [Card Game](#card-game)
  * [Project Description](#project-description-1)
  * [Setup](#setup-1)
  

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

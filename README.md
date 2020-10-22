# COSC3342 - Computer Networks

## Contents
* [Socket Server](#socket-server)
  * [Project Description](#project-description)
  * [Setup](#setup)
  * [Troubleshoot](#troubleshoot)
  
## Socket server
![wip](https://user-images.githubusercontent.com/47615511/96809326-41a70900-13e0-11eb-83b3-485762286ad4.png)

### Project Description

Create a socket server in C. Let a client connect to the server and give commands. The server will then evaluate the commands and respond to the client.

### Setup:

>$ gcc -o executable_name socket_server.c randperm.c  
>$ ./executable_name port_number

To send command, open another terminal while the server is started and type:

>$ echo "message" | nc server_IP server_port

For telnet (2 way communication):

>$ telnet server_IP server_port

### Troubleshoot:

- If you get Bind error, try changing to a different port:
  - ports 0-1023 are reigistered for system use
  - if a port was just used, it takes time for it to close
-------------------------

# COSC3342
HBU Computer Networks Class

For socket server (socket_server.c)

To compile:

***$ gcc -o executable_name socket_server.c randperm.c ***

To start server:

***$ ./executable_name port_number***

To send command, open another terminal while the server is started and type:

***$ echo "message" | nc server_IP server_port***

For telnet (2 way communication):

***$ telnet server_IP server_Port***

-------------------------

# HTTP_Server_Client

-----

### Summary:


Goal:  to create an HTTP server and a client able to communicate with GET and POST; via sys/socket.h

-------------

### How to use this:
Clone the repo/download the code
build the executables for client and for the server sepparetely by running the following commands in each of the directories

make clean
make

Launch the server first by passing the port number:

./goserver 8080

Launch the client secondly by passing the host name, the port, the method, the name of the file; empty method will return index.html

./goclient http://localhost 8080 POST about.html

Note: closing the server with CTRL+C will shutdown the server gracefully
Note: closing the server will cause the client to display the last message received from the server
Note: 200 OK and 404 Not Found messages are passed between the client and server and displayed 
Note: multithread code present but not fully implemented
Note: the about.html present in client folder can be passed with POST to the server for testing POST; content is displayed in the client when server responds
Note: a browser can be used as client by accessing http:localhost:8080/index.html



### Results:




![RNN](https://raw.githubusercontent.com/mmehedin/summarization/master/temp/rnn.png)

------

### Repo work:


Reference: https://pubs.opengroup.org/onlinepubs/7908799/xns/syssocket.h.html
-----

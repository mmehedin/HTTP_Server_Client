#all: goserver clean

# Makefile
# Make the server executable file:
goserver : server.o freader.o regex.o other.h

# Produced by:
	g++ -o goserver server.o freader.o regex.o 
# 
#-----------------------------------------------------------------
# Make freader.
freader.o : freader.cpp other.h
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"server.d" -MT"other.h" -o "freader.o" "freader.cpp"
# make regex.o
regex.o : regex.cpp other.h
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"server.d" -MT"other.h" -o "regex.o" "regex.cpp"
#Make server.
server.o : server.cpp other.h
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"server.d" -MT"other.h" -o "server.o" "server.cpp"
clean:
	rm -rf *o goserver

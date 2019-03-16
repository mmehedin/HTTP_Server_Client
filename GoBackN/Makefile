#all: goclient clean

# Makefile
# Make the client executable file:
goclient : client.o freader.o Content.o other.h

# Produced by:
	g++ -o goclient freader.o Content.o client.o 
# 
#-----------------------------------------------------------------
# Make freader.
freader.o : freader.cpp other.h
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"client.d" -MT"other.h" -o "freader.o" "freader.cpp"
# make Content.o
Content.o : Content.cpp other.h
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"client.d" -MT"other.h" -o "Content.o" "Content.cpp"
#Make client.
client.o : client.cpp other.h
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"client.d" -MT"other.h" -o "client.o" "client.cpp"
clean:
	rm -rf *o goclient

SRC=./src/
INC_PATH=./src/utils
CFLAGS=-I$(INC_PATH)

run_client:client.o
	$(SRC)client
runManyClient: client.o
	$(SRC)client
	$(SRC)client
	$(SRC)client
run_server:server.o
	$(SRC)server
client.o:$(SRC)client.cpp $(SRC)utils/clientSocket.h $(SRC)utils/clientSocket.cpp
	g++ -pthread -o $(SRC)client $(SRC)client.cpp $(SRC)utils/clientSocket.cpp
server.o:$(SRC)server.cpp $(SRC)utils/serverSocket.h $(SRC)utils/serverSocket.cpp
	g++ -pthread -o $(SRC)server $(SRC)server.cpp $(SRC)utils/serverSocket.cpp
clean:
	rm $(SRC)client
	rm $(SRC)server

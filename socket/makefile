SRC=./src/
INC_PATH=./src/utils
CFLAGS=-I$(INC_PATH)

run_client:client.o
	$(SRC)client
run_server:server.o
	$(SRC)server
client.o:$(SRC)client.cpp $(SRC)utils/client_socket.h $(SRC)utils/client_socket.cpp
	g++ -o $(SRC)client $(SRC)client.cpp $(SRC)utils/client_socket.cpp
server.o:$(SRC)server.cpp $(SRC)utils/server_socket.h $(SRC)utils/server_socket.cpp
	g++ -o $(SRC)server $(SRC)server.cpp $(SRC)utils/server_socket.cpp
clean:
	rm $(SRC)client

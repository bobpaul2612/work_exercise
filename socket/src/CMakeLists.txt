add_executable(server
	server.cpp
	utils/serverSocket.cpp
)
add_executable(client
	client.cpp
	utils/clientSocket.cpp
)
target_include_directories(server PRIVATE ../include)
target_link_libraries(server PRIVATE pthread)
target_include_directories(client PRIVATE ../include)
target_link_libraries(client PRIVATE pthread)
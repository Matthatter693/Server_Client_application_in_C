CC=gcc
exe=server_exe client_exe
server_target=server.o server_utils.o
client_target=client.o client_utils.o

${exe}:${server_target} ${client_target}
	${CC} ${server_target} -o server_exe
	${CC} ${client_target} -o client_exe

server.o:server/server.c  
	${CC} -c server/server.c -o server.o

server_utils.o:server/server_utils.c 
	${CC} -c server/server_utils.c -o server_utils.o

client_utils.o:client/client_utils.c
	${CC} -c client/client_utils.c -o client_utils.o

client.o:client/client.c
	${CC} -c client/client.c -o client.o



clean:
	@echo "cleaning.."
	rm -f *.o server_exe client_exe

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <csignal>
#include "conf_read.h"
#include <iostream>
#include "Network.h"

//resmi

int finished = 0;
TCP connection = TCP();
configuration conf_file = configuration("spark0.conf");
std::string server_ip = conf_file.read_conf("server_ip");
int port = atoi((char*)conf_file.read_conf("server_port").c_str());

char* real_ip = (char*) server_ip.c_str();
sockaddr_in server_addr = generate_addr("127.0.0.1", 9119, AF_INET);

void Exit(int signal)
{
 finished = 1;
 printf("Exit\n");
 exit(0);
}

char username[100], password[100];

char * Alive()
{
	char * returnme = (char*)calloc(sizeof(char), 4);
	char* boolean = "true";
	for (int i = 0; i < 4; i++)
	{
		returnme[i] = boolean[i];
	}
	return returnme;
}

void Glowing()
{
	/*
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(::port);
	inet_pton(AF_INET, real_ip, &server_addr.sin_addr);
	*/
	printf("Connecting to server...\n");
	char tosend[100];
	sprintf(tosend, "%s %s", username, password);
 	int conid = connection.register_connection(connection.get_sock(), server_addr);
	connection.send_to_id(conid, tosend, sizeof(tosend), 1, 0);
	char * terima = connection.receive(conid);
	printf("\nrecv: %s size: %d\n", terima, strlen(terima));
	printf("\n\n");
	free(terima);
}

void Login()
{
	printf("Username: ");
	scanf("%s", username);
	char *passtemp = getpass("Password: ");
	memcpy(password, passtemp, strlen(passtemp));
	free(passtemp);
}

int main(int argv, char **args)
{
	/*
	char tosend[100] = "kevin nivek	k";
 	int conid = connection.register_connection(connection.get_sock(), server_addr);
	connection.send_to_id(conid, tosend, sizeof(tosend), 1, 0);
	printf("\nrecv: %d\n", strlen(connection.receive(conid, 0)));
	*/
	signal(SIGINT, ::Exit);
	Login();
	Glowing();
}
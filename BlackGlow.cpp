#include <cstdio>
#include <string>
#include <iostream>
#include <regex>
#include <map>
#include <csignal>
#include <map>
#include <vector>
#include <thread>
#include "mysqldb.hpp"
#include <arpa/inet.h>
#include "univlib.h"
#include "fdfile.h"
#include "conf_read.h"
#include "BlackGlow.h"
#include "Network.h"
#include "glower.h"

std::string  menu = "Black Glow v 0.1 - Kevin Agusto\n\n\n1.Generate Spark0\n2.Generate Spark\n3.Say to Spark\n";
TCP connection = TCP();
configuration the_conf = configuration("blackglow.conf");
sql_connection blackglowdb = sql_connection( "127.0.0.1", "root", "");
typedef char* (func)(std::vector<char *>, int*);
std::map<std::string, func*> mapfunc = std::map<std::string, func*>();
unsigned int const password_length = 16; //16 is suitful for AES

struct clientNode{
	std::vector<int> thepipe;
	sockaddr_in addr;
	std::vector<__uint8_t> connection_password;
	int conid;
};

__uint16_t free_port = 1000;

std::vector<struct clientNode> client_list = std::vector<struct clientNode>();
//just for data transfer between thread or function or anything :v
int transfer0 = 0; //GateIn()
int transfer1 = 1; //GateIn()
char* test(std::vector<char*> x, int *s)
{
	*s = 4;
	return tody("okay");
}

void send_msg_pipe(int id, char msg[])
{
	std::vector<int> clientpipe = (::client_list[id]).thepipe;
	close(clientpipe[0]);
	writeFile(clientpipe[1], msg);
}

void Menu()
{
	std::cout << menu;
	std::cout << "Your Choice: ";
	char choice = getc(stdin);
}

int Auth(std::vector<char *> x)
{
	int u = 0;
	int p = 1;
	blackglowdb.query("use BlackGlow;");
	int size;
	MYSQL_ROW* authdb = blackglowdb.queryi("select * from auth;", size);
	for (int i : range(size))
	{
		if (samestr(x[u], authdb[i][u]) & samestr(x[p], authdb[i][p]))
		{
			free(authdb);
			return 1;
		}
	}
	free(authdb);
	return 0;
}

void register_func()
{
  mapfunc["test"] = &test;
}

//return pipe
std::vector<int> register_client(int connid, sockaddr_in client_addr)
{
	int thepipe0[2];
	pipe(thepipe0);
	std::vector<int> thepipes = std::vector<int>(thepipe0, thepipe0+(sizeof(thepipe0)/sizeof(thepipe0[0])));
	std::vector<__uint8_t> pass = std::vector<__uint8_t>();
	for (int i = 0; i < 16; i++)
	{
		pass.push_back(9);
	}
	struct clientNode theclient = {thepipe:thepipes, addr:client_addr, connection_password:pass, conid:connid};
	client_list.push_back(theclient);
	return thepipes;
}

void GateIn(int client_con, sockaddr_in client_addr)
{
	//2/check for blocked ip
	std::vector<std::string> blocked_ip = the_conf.read_conf_list("blocked_ip");
	char client_ip[32];
	inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
	for (auto &x: blocked_ip)
	{
		if (samestr(((char *)x.c_str()), client_ip))
		{
			//your ip was blocked
			printf("incoming connection from blocked ip: %s\n", client_ip);
			return;
		}
	}
	//2\

	//1/ authentication first
		
		char * buffer = connection.receive(client_con);
		printf("buff :%s", buffer);
		//1/new client, authentication first
		std::vector<char *> dat = splitdata(buffer, ' ', strlen(buffer));
		int auth = ::Auth(dat);
		if (auth){
			bool avail = false;
			//give new thread and port for new client
			while (free_port <= 0xffff & (::transfer1))
			{
				printf("try listening on %d\n", free_port);
				if (!connection.listenable(free_port))
				{
					pid_t clienthandler = fork();
					if (clienthandler<(pid_t)0){
						printf("Failed to start serving client %s\n", client_ip);
					}
					if (clienthandler==(pid_t)0){
						//this is the child process
						std::vector<int> clientPipe = register_client(client_con, client_addr);
						printf("New Client %s got a new port: %d\n", dat[0], free_port);
						ClientProcess(free_port, clientPipe);
					}
					else{
						avail = true;
						char tosend[100];
						sprintf(tosend, "new_port=%d", free_port);
						connection.send_to_id(client_con, tosend, strlen(tosend), 0);
						free_port++;
					}
					break;
				}
				free_port++;
			}
			if (!avail)
			{
				printf("cannot find new port for client: %s\n", client_ip);
			}
			//if succed find port for the new client, subgatein will send confirmation to client
		}
		else{
			//send false signal and wait few seconds for this ip can try again.
			printf("failed login for %s\n", client_ip);
		}
}

int server_listen;

void exit(int signalnum)
{
	printf("Exitting...\n");
	//shutdown gate in
	connection.stop_listen(server_listen);
	printf("client_list vector size: %d\n", ::client_list.size());
	send_msg_pipe(0, "stop_serving_client");
}

void testpipe1(std::vector<int> thepipe)
{
		int second = 500000; // 0.5 second (using usleep(); )
		close(thepipe[1]);
		char *buff = readFile(thepipe[0]);
		printf("buffer: %s\n", buff);
}

void testpipe()
{
	sockaddr_in addr = generate_addr("127.0.0.1", 9999, AF_INET);
	std::vector<int> clientPipe = register_client(9999, addr);
	printf("I/O: %d/%d\n", clientPipe[0], clientPipe[1]);
	pid_t process = fork();
	if (process<(pid_t)0){
		printf("write to pipe failed\n");
	}
	if (process==(pid_t)0){
		printf("starting new client...\n");
		ClientProcess(9999, clientPipe);
	}
	if (process>(pid_t)0){
		close(clientPipe[0]);
		writeFile(clientPipe[1], "stop_serving_client");
	}
}

int main()
{
	testpipe();
	return 0;
	confunc a[] = {&GateIn};
	signal(SIGINT, ::exit);
	register_func();
	connection.start_listen_array(9119, a, 1, &server_listen);
}
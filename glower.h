#ifndef glower
#include <thread>
#include <vector>
#include <cstdio>
#include "fdfile.h"
#include <cstring>
#include <cstdlib>
#include <map>
#include "Network.h"
#define glower
class ClientProcess
{
public:
	std::vector<int> thepipe;
	int port_listen;
	/*
	void aa()
	{
		printf("from aa\n");
	}
	void (ClientProcess::*a)(void);
	void bb()
	{
		this->a = &ClientProcess::aa;
		(this->*a)();
	}
	*/
	TCP connection = TCP();
	int finish = 0;
	typedef void (ClientProcess::*voidfunc)(void);
	std::map<const char *, voidfunc> pipefunc;
	void stop_serving_client()
	{
		this->finish = 1; //indicate the pipe_listener to stop
		writeFile(this->thepipe[1], "\1");
	}

	void pipe_listener(std::vector<int> thepipe)
	{
		this->thepipe = thepipe;
		 this->pipefunc = {
			{"stop_serving_client", &ClientProcess::stop_serving_client}
		};
		int second = 500000; // 0.5 second (using usleep(); )
		close(thepipe[1]);

		//ga bisa pake looping ya?

		char *buff = readFile(thepipe[0]);
		printf("bufferrr: %s\n", buff);	
		free(buff);
		usleep(second);
	}	
	
	static void client_processing(int conid, sockaddr_in addr)
	{
		printf("start client_processing\n");
		printf("%d\n", conid);
	}
	
	void client_handler(int port){
		confunc allfunc0[] = {&this->client_processing};
		std::vector<confunc> allfunc1 = std::vector<confunc>(allfunc0, allfunc0+(sizeof(allfunc0)/sizeof(allfunc0[0])));
		int theid;
		connection.start_listen_vector(port, allfunc1,  &theid);
	}
	ClientProcess(int port, std::vector<int> thepipe):port_listen(port){
		std::thread cp = std::thread(&ClientProcess::client_handler, this, port);
		std::thread pl = std::thread(&ClientProcess::pipe_listener, this, thepipe);
		cp.join();
		pl.join();
	}
	ClientProcess()
	{
	}
	~ClientProcess()
	{
	}
};
#endif
#include <cstdio>
#include "fdfile.h"
#include <cstdlib>
#include <vector>
#include <thread>
void flushex()
{
   char buff[1024];
   
   memset( buff, '\0', sizeof( buff ));
   
   fprintf(stdout, "Going to set full buffering on\n");
   setvbuf(stdout, buff, _IOFBF, 1024);

   fprintf(stdout, "This is tutorialspoint.com\n");
   fprintf(stdout, "This output will go into buff\n");
   fflush( stdout );

   fprintf(stdout, "and this will appear when programm\n");
   fprintf(stdout, "will come after sleeping 5 seconds\n");
   
   sleep(5);
   
}

void testpipe1(std::vector <int>thepipe)
{
		printf("dri fungsi thread\n");
		close(thepipe[1]);
		char * buff = readFile(thepipe[0]);
		printf("\nfinish: %s %d %d\n", buff, strcmp(buff, ""), strcmp(buff, "\0"));
		printf("%d\n", strlen(buff));
		free(buff);

		printf("the second...\n\n");
		char * bufff = readFile(thepipe[0]);
		printf("\nfinish: %s %d %d\n", buff, strcmp(bufff, ""), strcmp(bufff, "\0"));
		printf("%d\n", strlen(bufff));
		free(bufff);
}

void testpipe0()
{
	int pipes[2];
	printf("start\n");
	pipe(pipes) ? printf("Failed for piping\n") : printf("");
	std::vector<int> thepipe = std::vector<int>(pipes, pipes+2);
	pid_t x = fork();
	if ((int)x < 0)
	{
		printf("failed fork\n");
	}
	if (x==(pid_t)0){
		std::thread x = std::thread(&testpipe1, thepipe);
		x.join();
	}
	if (x>(pid_t)0){
		close(thepipe[0]);
		char towrite[]= "test sajaaa";
		writeFile(thepipe[1], towrite);
		fflush(fdopen(thepipe[1], "w"));
		writeFile(thepipe[1], towrite);
	}
}



int main()
{
	testpipe0();
	return 0;
}
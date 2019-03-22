#ifndef fdfile_H
#define fdfile_H
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

char *readFile(int x)
{
 char *yay = (char*) calloc(sizeof(char), 1);
 FILE *fdPipe = fdopen(x, "rb");
 if (fdPipe==NULL){printf("Fail read from file descriptor\n");}
 char c  = fgetc(fdPipe);
 int tanda = 0;
 while (c!=EOF)
 {

  yay[tanda] = c;
  tanda++;
  yay = (char*)realloc(yay, sizeof(char)*(tanda+1));
  c = fgetc(fdPipe);
 }
 fclose(fdPipe);
 //printf("REsults: %s\n", yay);
 return yay;
}

void writeFile(int x, char  str[])
{

 write(x, str, strlen(str));
 close(x);

/*
 FILE *fdPipe = fdopen(x, "w");
 if (fdPipe==NULL)
 {
  printf("Fail write pipe\n");
 }
 fprintf(fdPipe, "%s", str); 
 fclose(fdPipe);
 */
	
}

void closePipe(int* list_pipe, int size)
{
	for (int i = 0; i < (size); i++)
	{
		close(list_pipe[i]);
	}
}
#endif
	
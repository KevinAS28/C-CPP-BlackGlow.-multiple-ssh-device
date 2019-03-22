#ifndef __univlib
#define __univlib
#include <cstdio>
#include <cstring>
#include <sstream>



std::vector<__uint8_t> random_password(int count)
{
	std::vector<__uint8_t> toreturn = std::vector<__uint8_t>();

}

template <class any>
std::string tostring(any a)
{
	std::stringstream obj = std::stringstream();
	obj << a;
	std::string toreturn = "";
	obj >> toreturn;
	return toreturn;
}
void Info(char * msg, const char *banner = "[Info]")
{
	const int size = strlen(msg) + strlen(banner) + 2;
	char toprint[size];
	sprintf(toprint, "%s %s\n", banner, msg);
	printf(toprint);
}

void Error(char * msg)
{
	Info(msg, "[Error]");
}

void Warning(char *msg)
{
	Info(msg, "[Warning]");
}

int lenint(int x)
{
	int toreturn = 0;
	while (x >= 1)
	{
		x/=10;
		toreturn++;
	}
	return toreturn;
}

#endif
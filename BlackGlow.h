#ifndef __BlackGlowLib
#define __BlackGlowLib
#include <cstring>
#include <string>
#include <vector>
#include "aes.h"



class range
{
public:
	int *data;
	int len;
	range(int x)
	{
		this->data = (int*)calloc(sizeof(int), x);
		for (int i = 0; i < x; i++)
		{
			this->data[i] = i;
		}
		len = x;
	}

	int *begin()
	{
		return this->data;
	}

	int* end()
	{
		return this->data + len;
	}

	~range()
	{
		free(this->data);
	}

};


int samestr(char *str0, char* str1)
{
	int index = 0;
	int sama = 1;
	if (strlen(str0)!=strlen(str1))
	{
		return 0;
	}
	for (int i = 0; i < strlen(str0); i++)
	{
		if (str0[i]!=str1[i])
		{
			return 0;
		}
	}
	return 1;
}


	int countchr(std::string str, char tocount)
	{
		int x = 0;
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i]==tocount)
			{
				x++;
			}
		}
		return x;
	}
	char *cctoc(const char* convertme, char* target)
	{
		for (int i = 0; i < strlen(convertme); i++)
		{
			target[i] = convertme[i];
		}
	}

	template <class binform>
	void padding(binform* dest, int len, int become=16)
	{
		if (len < become){
		for (int i = len; i < become-len; i++)
		{
			(dest)[i] = (binform)0;
		}			
		}
		else{
		for (int i = len; i < len%become; i++)
		{
			(dest)[i] = (binform)0;
		}
		}
	}

	__uint8_t *stob(char str[])
	{
	__uint8_t *to_return = (__uint8_t*) calloc(sizeof(__uint8_t), strlen(str));
	for (int i = 0; i < strlen(str); i++)
	{
		to_return[i] = (__uint8_t)str[i];
	}
	return to_return;
	}

	__uint8_t* stob(std::string x)
	{
		__uint8_t *to_return = (__uint8_t*)calloc(sizeof(__uint8_t), x.length());
		for (int i = 0; i < x.length(); i++)
		{
			to_return[i] = (__uint8_t)x[i];
		} 
		return to_return;
	}
	/*
Nobody notices your sadness
Nobody notices your tears
Nobody notices your pain
But they ALL notice your Mistakes﻿

if you just know it now, then "welcome to the world"
*/
	char *tody(const char *data)
	{
		int size = strlen(data);
		char* toreturn = (char*)calloc(sizeof(char), size);
		for (int i = 0; i < size; i++)
		{
			toreturn[i] = data[i];
		}
		return toreturn;
	}

	std::vector<std::string> splitstr(std::string str, char splitter)
	{
		if (str.length()<=0)
		{
			return std::vector<std::string>();
		}
		str+=splitter;
		std::string temp = "";
		std::vector<std::string> to_return = std::vector<std::string>();
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i]==splitter)
			{
				to_return.push_back(temp);
				temp="";
				continue;
			}
			temp += str[i];
		}
		return to_return;
	}
	
	std::vector<char*> splitdata(char* data,  char tosplit, int size)
	{
		std::vector<char*> toreturn = std::vector<char*>();
		int index = 0;
		char* temp = (char*)calloc(sizeof(char), 1);
		for (int i = 0; i < (size + 1); i++)
		{
			if ((data[i]==tosplit)|(data[i]=='\0'))
			{
				toreturn.push_back(temp);
				//printf("%s\n", temp);
				temp = (char*)calloc(sizeof(char), 1);
				index = 0;
				continue;
			}
			temp[index] = data[i];
			index++;
		}
		return toreturn;
	}

	void aes_encrypt(__uint8_t * data,  int size, __uint8_t * key, __uint8_t *iv)
	{
		struct AES_ctx key_and_iv;
		AES_init_ctx_iv(&key_and_iv, key, iv);
		padding(data, size);
		AES_CBC_encrypt_buffer(&key_and_iv, data, size);
	}
	void aes_decrypt(__uint8_t * data,  int size, __uint8_t * key, __uint8_t *iv)
	{
		struct AES_ctx key_and_iv;
		AES_init_ctx_iv(&key_and_iv, key, iv);
		padding(data, size);
		AES_CBC_decrypt_buffer(&key_and_iv, data, size);
	}	
	
#endif
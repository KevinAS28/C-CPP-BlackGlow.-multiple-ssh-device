#ifndef __conf_read
#define __conf_read
#include <cstdio>
#include <regex>
#include <cstring>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "BlackGlow.h"


 	class configuration
 	{
 	public:
 		std::string conf_file = "", conf_contain="";
 		
 		configuration(std::string filename): conf_file(filename)
 		{
 			this->conf_contain = this->read_file(conf_file);
 		}
 		
 		std::string add_conf(std::string key, std::string value)
 		{
 			std::fstream apalah(this->conf_file, std::ios::out|std::ios::app);
 			apalah << key+"="+value;
 			apalah.close();
 		}
 		
 		void set_conf(std::string key, std::string value)
 		{
 			std::vector<std::string> newline = splitstr(this->read_file(this->conf_file), '\n'), temp;
 			std::string towrite = "", temp1="";
			for (auto x: newline)
			{
				/*
				if (!(std::regex_match(x, std::regex("[.]*\\=[.]*"))))
				{
					continue;
				}
				*/
				//expecting for comment
				/*
				if (countchr(x, '#')>0)
				{
					continue;
				}
				*/
				temp = splitstr(x, '=');
				if (temp[0]==key)
				{
					temp1+=temp[0];
					temp1+="=";
					temp1+=value;
					towrite += temp1;
					towrite += "\n";
					temp1="";
					continue;	
				}
				towrite += x;
				towrite += "\n";
			}
 			this->conf_contain = towrite;
 		}
 		
 		std::string read_file(std::string filename)
 		{ 			
			FILE * pfile = fopen((char *)filename.c_str(), "rb");
			int size;
			fseek(pfile, 0, SEEK_END);
			size = ftell(pfile);
			fseek(pfile, 0, SEEK_SET);
			char temp0[(const int) (size)], temp1[1];
			int i;
			for (i = 0; i < size; i++)
			{
				fread(temp1, 1, 1, pfile);
				temp0[i] = temp1[0];
			}
			temp0[i] = 0;

			return std::string(temp0);
 		}
 		std::vector<std::string> read_conf_list(std::string key){
 			this->conf_contain = this->read_file(conf_file);
 			std::string temp = this->read_conf(key);
 			return splitstr(temp, ',');

 		}
 		
 		std::string read_conf(std::string key)
		{
			this->conf_contain = this->read_file(conf_file);
			std::vector<std::string> newline = splitstr(this->conf_contain, '\n'), temp;
			for (auto x: newline)
			{
				temp = splitstr(x, '=');
				if (temp[0]==key)
				{
					return temp[1];
				}
			}
			return "";
		}
 };
#endif
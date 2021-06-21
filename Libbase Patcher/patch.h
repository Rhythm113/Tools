/* Libbase Patcher Coded By @Rhythm113 Code Date : 8/2/2021 Last Updated :
   23/3/2021 11:37 Open Source. By Infinity Creators. Ver : [1.3 Alpha] Note : 
   Don't Modify anything without having proper knowledge in C/C++ */

#include <iostream>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <thread>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <cstdlib>
#include <cstddef>

#define MAX 80


#define OWN "Rhythm" 




int deamon;
typedef int8_t BYTE;
typedef double DOUBLE;
typedef uint32_t DWORD;
typedef uint64_t QWORD;
using namespace std;
typedef char PACKAGENAME;
char *pkgnm;

char *print(char *message)
{
	puts(message);
}

void credit()
{
	printf("Libbase Game Patcher By Rhythm113.\nby Infinity Creators\n");	// File  Credit Don't Modify This !
}

void owner_name(char *name)
{
	printf("\nCPP Owner: %s\n\n", name);
}

long int get_lib_base(int pid, const char *module_name)
{
	FILE *fp;
	long addr = 0;
	char *pch;
	char filename[32];
	char line[1024];
	snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
	fp = fopen(filename, "r");
	if (fp != NULL)
	{
		while (fgets(line, sizeof(line), fp))
		{
			if (strstr(line, module_name))
			{
				pch = strtok(line, "-");
				addr = strtoul(pch, NULL, 16);
				break;
			}
		}
		fclose(fp);
	}
	return addr;
}

int modify_base_type_FLOAT(long int addr, float value)
{
	pwrite64(deamon, &value, 4, addr);
	return 0;
}

int modify_base_type_DWORD(long int addr, DWORD value)
{
	pwrite64(deamon, &value, 4, addr);
	return 0;
}

int modify_base_type_QWORD(long int addr, QWORD value)
{
	pwrite64(deamon, &value, 4, addr);
	return 0;
}

int modify_base_type_BYTE(long int addr, BYTE value)
{
	pwrite64(deamon, &value, 4, addr);
	return 0;
}

int modify_base_type_DOUBLE(long int addr, DOUBLE value)
{
	pwrite64(deamon, &value, 4, addr);
	return 0;
}

int getPID(PACKAGENAME * PackageName)
{
	DIR *dir = NULL;
	struct dirent *ptr = NULL;
	FILE *fp = NULL;
	char filepath[256];
	char filetext[128];
	dir = opendir("/proc");
	if (NULL != dir)
	{
		while ((ptr = readdir(dir)) != NULL)
		{

			if ((strcmp(ptr->d_name, ".") == 0) || (strcmp(ptr->d_name, "..") == 0))
				continue;
			if (ptr->d_type != DT_DIR)
				continue;
			sprintf(filepath, "/proc/%s/cmdline", ptr->d_name);
			fp = fopen(filepath, "r");
			if (NULL != fp)
			{
				fgets(filetext, sizeof(filetext), fp);
				if (strcmp(filetext, PackageName) == 0)
				{

					break;
				}
				fclose(fp);
			}
		}
	}
	if (readdir(dir) == NULL)
	{
		return 0;
	}
	closedir(dir);
	return atoi(ptr->d_name);
}

string GetStdoutFromCommand(string cmd)
{
	string data;
	FILE *stream;
	const int max_buffer = 256;
	char buffer[max_buffer];
	cmd.append(" 2>&1");
	stream = popen(cmd.c_str(), "r");
	if (stream)
	{
		while (!feof(stream))
			if (fgets(buffer, max_buffer, stream) != NULL)
				data.append(buffer);
		pclose(stream);
	}
	return data;
}

int start_deamon()
{
	int get_pid = getPID(pkgnm);

	if (get_pid == 0)
	{
		puts("The Game is not running!");
		exit(1);
	}


	char hl[64];
	sprintf(hl, "/proc/%d/mem", get_pid);
	deamon = open(hl, O_RDWR);
	if (deamon == -1)
	{
		puts("Failed to initialise memory!\n");
		exit(1);
	}
	return 0;
}

int check_game(char *pkgnm)
{


	int game_pid = getPID(pkgnm);


	if (game_pid == 0)
	{
		puts("The Game is not running!");
		exit(1);
	}
	return game_pid;
}

int bypass_game()
{
	puts("\nAttempting to Bypass 3rd Party..");
	system("echo \"8192\" > /proc/sys/fs/inotify/max_queued_events");
}

int shell(char *command)
{
	system(command);
}

int check_pubg()
{

	int ipid = getPID("com.tencent.ig");
	if (ipid == 0)
	{
		ipid = getPID("com.pubg.krmobile");
		if (ipid == 0)
		{
			ipid = getPID("com.rekoo.pubgm");
			if (ipid == 0)
			{
				ipid = getPID("com.vng.pubgmobile");
				if (ipid == 0)
				{
					puts("PUBGM not running!");
					exit(1);
				}
			}
		}
	}
	return ipid;
}

//End

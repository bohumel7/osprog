#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <fcntl.h>
#include <cctype>
#include <unistd.h>
#include <map>
#include <vector>
#include <dirent.h>
#include <cstring>


int main(int argc, char *argv[])
{	
	std::map<int, char*> output;
	const char *procPath = "/proc";
	int opt;

	while((opt = getopt(argc, argv, "p:")) != -1) {
		switch (opt) {
			case 'p':
				procPath = optarg;
				break;
			default:
				fprintf(stderr, "Usage: procs [-p PATH_TO_PROC]\n");
				exit(EXIT_FAILURE);
		}
	}


    DIR* proc = opendir(procPath);
    struct dirent* ent;

    if(proc == NULL) {
        perror("opendir(/proc)");
        exit(EXIT_FAILURE);
    }

    while (true) {
	ent = readdir(proc);
	if(ent == NULL){
	    break;
	}
        if (isdigit(*ent->d_name)) {
	    long length;
            char* buffer = 0;
            char* pidPath = new char[std::strlen(procPath) + std::strlen(ent->d_name) + 2];

            std::strcpy(pidPath, procPath);
            std::strcat(pidPath, "/");
            std::strcat(pidPath, ent->d_name);

            char* cmd = new char[std::strlen(pidPath) + 9];

            std::strcpy(cmd, pidPath);
            std::strcat(cmd, "/cmdline");

            FILE* file = fopen(cmd, "rb");
            if (file) {
                fseek (file, 0, SEEK_END);
                length = ftell(file);
                fseek (file, 0, SEEK_SET);
                buffer = (char*)malloc(length);
            }
            if (buffer!=0) {
                fgets(buffer, length, file);
                for (int i = 0; i < length; ++i) {
                    if (buffer[i] == '\0') {
                        buffer[i] = ' ';
                    }
                }
	        output[atoi(ent->d_name)] = buffer;
            }
        }
    }
    for(auto const &elem : output) {
        printf("%5d %s\n", elem.first, elem.second);
    }
    closedir(proc);
    return 0;
}


#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
	struct sockaddr_un addr;
	char buf[10000]={0};
  	int fd,rc;
	if(argc!=2)
	{
		printf("Usage ./client SOCKET_PATH\n");
		exit(0);
	}
	char* socket_path=(char*)malloc(strlen(argv[1])*sizeof(char));
	strcpy(socket_path, argv[1]);
  	if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) 
	{
    		perror("socket error");
    		exit(-1);
 	}

  	memset(&addr, 0, sizeof(addr));
  	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);
  	if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) 
  	{
    		perror("connect error");
    		exit(-1);
  	}
	char* cmd="cat /etc/passwd | cut -f 1 -d :";
	FILE* fp=popen(cmd, "r");
	int i=0;
	char ch=fgetc(fp);
	while(ch&&i<10000)
	{
		buf[i++]=ch;
		ch=fgetc(fp);
		if(ch==EOF) break;
	}
	write(fd, buf, strlen(buf));
	char files[100000]={0};
	read(fd, files, 100000);
	printf(files);
	free(socket_path);
 	return 0;
}


#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <string.h>

void get_userfiles(const char* user, char* buf)
{
	char cmd[10000];
	sprintf(cmd, "find /root/OS -user %s -mtime -1", user);
	FILE* fp=popen(cmd, "r");
	int i=0;
	char ch=fgetc(fp);
	while(i<100000&&ch)
	{
		buf[i++]=ch;
		ch=fgetc(fp);
		if(ch==EOF) break;
	}
}

int main(int argc, char *argv[]) {
	struct sockaddr_un addr;
	char* socket_path;
	char buf[10000]={0};
	int fd,cl,rc;
	char files[100000]={0};
	if (argc!=2) 
	{
		printf("Usage: ./server SOCKET_PATH\n");
		exit(0);
	}
	socket_path=(char*)malloc(strlen(argv[1])*sizeof(char));
	strcpy(socket_path, argv[1]);
  	if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) //creating socket
       	{
    		perror("socket error");
    		exit(-1);
  	}
  	memset(&addr, 0, sizeof(addr));
  	addr.sun_family = AF_UNIX;
  	strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);
    	unlink(socket_path);
  	if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) 
	{
    		perror("bind error");
    		exit(-1);
  	}

  	if (listen(fd, 5) == -1) 
  	{
    		perror("listen error");
		exit(-1);
	}
	char* user;
	cl=accept(fd, NULL, NULL);
	read(cl, buf, sizeof(buf));
	char* pos=strchr(buf, '\n');
	int len;
	if(pos)
		len=pos-buf+1;
	else
		exit(0);
	printf("%d\n", len);
	user=(char*)malloc(len*sizeof(char));
	for(int j=0;j<len;j++)
		user[j]=buf[j];
	printf(user);
	get_userfiles(user, files);
	printf(files);
	write(cl, files, sizeof(files));
	free(user);
	free(socket_path);
}


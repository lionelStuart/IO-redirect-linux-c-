/*
 * main.c
 *
 *  Created on: 2017年10月2日
 *      Author: lisi
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
//#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<signal.h>
#include<sys/types.h>


void SignHandle()
{
	printf("signal recevied\n");
	static int time=0;
	if(time==0){
		int fd_o=open("B.txt",O_RDWR);
		lseek(fd_o,7,SEEK_SET);
		char buf[4]={"1234"};
		write(fd_o,buf,4);
		lseek(fd_o,0,SEEK_SET);
		char line[20];
		memset(line,0x0,20);
		read(fd_o,line,20);
		printf("line:%s\n",line);
		time++;
	}else{
		printf("exit\n");
		exit(-1);
	}

}

int main(int argc,char** argv)
{
	printf("main start\n");
	FILE* input=freopen("A.txt","r",stdin);
	if(!input)
	{
		printf("can not open file\n");
	}
	FILE* output=freopen("/dev/pts/1","w",stdout);
	char line[20];
	memset(line,0x0,20);
	fgets(line,20,stdin);

	write(fileno(output),line,20);

	struct sigaction act;
	act.sa_sigaction=SignHandle;
	sigaction(SIGINT,&act,NULL);
	while(1)
	{
		sleep(1);
	}
	printf("main ends\n");
	getchar();
	return 0;
}





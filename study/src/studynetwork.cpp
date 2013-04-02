#include "socketstudy.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
int main()
{
	int pid=fork();
	if(pid<0){
		exit(1);
	}
	if(pid >0){
		printf("parent exit. child is:%d",pid);
		exit(0);
	}
	if(pid == 0){
		printf("child pid=%d,ppid=%d\r\n",getpid(),getppid());
		//child
		int sid =setsid();
		if(sid <0){
			exit(1);
		}
		if(sid > 0){
			int pid2=fork();
			if(pid2<0){
				exit(1);
			}
			if(pid2 >0){
				exit(0);
			}
			int ret = chdir("/");
			if(ret !=0){
				exit(0);
			}
			umask(0);
			for(int i = 0; i < 3; i++){
				close(i);
		    }
		}
		socketstudy study;
		study.start(8080);
	}
    return 0;
}

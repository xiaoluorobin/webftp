/*
 * socketstudy.cpp
 *
 *  Created on: 2013-3-31
 *      Author: luojianguo
 */

#include "socketstudy.h"
#include<sys/socket.h>
#include<errno.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>
#include<unistd.h>
#include<sys/stat.h>

socketstudy::socketstudy() {
	// TODO Auto-generated constructor stub

}

socketstudy::~socketstudy() {
	// TODO Auto-generated destructor stub
}
void socketstudy::showerror(int errornumber){
	printf("errno:%i,msg:%s",errornumber,strerror(errornumber));
}
void socketstudy::start(int portnum){
	int fdserver = socket(AF_INET,SOCK_STREAM,0);
	if(fdserver <0){
		this->showerror(errno);
		exit(-1);
	}
	this->bindfd(fdserver,portnum);
	this->handlerequest(fdserver);
	close(fdserver);
}
void socketstudy::bindfd(int fd,int portnum){
	sockaddr_in sa;
	bzero(&sa,sizeof(sa));
	sa.sin_family=AF_INET;
	sa.sin_addr.s_addr=htons(INADDR_ANY);
	sa.sin_port=htons(portnum);
	bzero(&(sa.sin_zero),8);
	int result;
	result=bind(fd,(sockaddr*)&sa, sizeof(sa));
	if(result!=0){
		this->showerror(errno);
		exit(-1);
	}
	result = listen(fd,2);
	if(result!=0){
			this->showerror(errno);
			exit(-1);
	}
}
void socketstudy::handlerequest(int fdserver){
	int fdclient;
	sockaddr_in sa;
	socklen_t len=sizeof(sa);
	bzero(&sa,len);
	char buff[101];
	while((fdclient=accept(fdserver,(sockaddr *)&sa,&len))>0){
		int n;
		bzero(buff,101);
	   while((n=recv(fdclient,buff,100,0))>0){
		   if(write(STDOUT_FILENO,buff,n)>0){
			   send(fdclient,buff,n,0);//write back
		   }
		   if(strcmp(buff,"quit\r\n") == 0){
			   close(fdclient);
			  return;
		   }
	   }

	}
}
void socketstudy::startdaemon(){
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
				exit(0);//first child exist
			}
			int ret = chdir("/");
			if(ret !=0){
				exit(0);
			}
			umask(0);//重设文件创建掩码，防止父进程修改影响
			for(int i = 0; i < 3; i++){
				close(i);//标准输入 标准输出 标准出错
		    }
		}

		start(8080);//second chid belongs to init process
	}
}


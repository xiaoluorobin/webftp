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

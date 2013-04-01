/*
 * socketclient.cpp
 *
 *  Created on: 2013-4-1
 *      Author: luojianguo
 */

#include "socketclient.h"
#include<sys/socket.h>
#include<errno.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<arpa/inet.h>
socketclient::socketclient() {
	// TODO Auto-generated constructor stub

}

socketclient::~socketclient() {
	// TODO Auto-generated destructor stub
}
void socketclient::showerror(int errornumber){
	printf("errno:%i,msg:%s",errornumber,strerror(errornumber));
}

void socketclient::start(){
	int clientfd=socket(AF_INET,SOCK_STREAM,0);
	if(clientfd <0){
		this->showerror(errno);
		exit(1);
	}
	this->bindclientfd(clientfd);
	this->connectserver(clientfd,"127.0.0.1",8080);
	this->sendtoserver(clientfd);
	close(clientfd);
}

void socketclient::bindclientfd(int clientfd){
	struct sockaddr_in client_addr;
	bzero(&client_addr,sizeof(client_addr));
	client_addr.sin_family=AF_INET;
	client_addr.sin_addr.s_addr=htons(INADDR_ANY);
	client_addr.sin_port=htons(0);
	int result = bind(clientfd,(sockaddr *)&client_addr,sizeof(client_addr));
	if(result !=0){
	   this->showerror(errno);
	   exit(1);
   }
}
void socketclient::connectserver(int clientfd,const char * serverip,int serverport){
	sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	//   server_addr.sin_addr.s_addr=htons()
	if(inet_aton(serverip,&server_addr.sin_addr) ==0 ){
		   printf("error ip format");
		   exit(1);
	}
	server_addr.sin_port=htons(serverport);
	socklen_t server_addr_len=sizeof(server_addr);
	int result =connect(clientfd,(sockaddr *)&server_addr,server_addr_len);
	if(result <0){
		this->showerror(errno);
		exit(1);
	}
}

void socketclient::sendtoserver(int clientfd){
	char buffer[200];
	bool loop =true;
	while(loop){
		printf("please enter the message you want:\r\n");
		bzero(buffer,sizeof(buffer));
		gets(buffer);
		if(strcmp(buffer,"quit\r\n")==0){
			printf("client closed.");
			loop = false;
			exit(0);
		};
		if(send(clientfd,buffer,200,0) < 0){
			this->showerror(errno);
			exit(1);
		}
		this->handleresponse(clientfd);
	}
}
void socketclient::handleresponse(int clientfd){
	char buffer[200];
	bzero(buffer,sizeof(buffer));
	if(recv(clientfd,buffer,200,0)>0){
		printf("%s\r\n",buffer);
	}
}

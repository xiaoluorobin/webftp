/*
 * structstudy.cpp
 *
 *  Created on: 2013-3-29
 *      Author: luojianguo
 */

#include "structstudy.h"
#include <stdio.h>
#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

structstudy::structstudy() {
	// TODO Auto-generated constructor stub

}

structstudy::~structstudy() {
	// TODO Auto-generated destructor stub
}
void structstudy::setstructpointer(){

	struct study1 study;
	study.i =789;
	printf("I'm is %i",study.i);
	//printf("I'm is %i",study.j);//default int is undefined

	study1 study2={10,12};
	cout << " next " << study2.i <<endl;
}
void structstudy::deleteStudy(){
	//char str[10]="111111111";
	//printf("%s",str);
	char *str=new char[10];
	str[0]='a';
	delete[] str;
}

void structstudy::getIp(){
	hostent *host = gethostbyname("www.sdo.com");
	cout << "name:" << host->h_name << endl;
	cout <<"type:"  << host->h_addrtype << endl;//ipv4,6

	char **address;
	char buffer[INET_ADDRSTRLEN];
	for(address =host->h_addr_list;address!=NULL;address++){
		inet_ntop(AF_INET,*address,buffer,INET_ADDRSTRLEN);
		printf("%s\n",*address);//不可打印的网络字节序
		printf("%s\n",buffer);
		//cout <<"intip:" << *address << endl;
	}
}
void structstudy::getsStudy(){
		char s[10];
		bzero(s,sizeof(s));
		char * result = gets(s);
		if(result == NULL){

		}
		printf("%s",s);
}

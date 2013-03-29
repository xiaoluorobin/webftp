//============================================================================
// Name        : studynetwork.cpp
// Author      : robinluo
// Version     :
// Copyright   : robin's study coding
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>
#include<arpa/inet.h>


int main(int argc, char **argv) {
	struct hostent *host;
	char str[100];
	char addr[INET_ADDRSTRLEN];
	char **p;
	int c;
	while (1){
		c=0;//
		gets(str);
		printf("%s\n",str);
		if ((host=gethostbyname(str))==NULL){
			perror("host");
		break;
		}
		p=host->h_addr_list;  //Get the first IP from the List

		for (;*p!=NULL;p++){
			c++;
			inet_ntop(AF_INET, *p, addr, INET_ADDRSTRLEN);
			printf("%d:%s\n", c, addr);
		}
	}
	return 0;
}

/*
 * zombiestudy.cpp
 *
 *  Created on: 2013-4-8
 *      Author: luojianguo
 *      ps axjfc|egrep -C5 '(PPID|study)'
 *      if parent not handle SIGCHLD status would be z
 *      question:when no parent exist,why parent print nothing?
 *
 *      ./studynetwork>test.txt 2>&1 &
 */

#include "zombiestudy.h"
#include <bits/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

zombiestudy::zombiestudy() {
	// TODO Auto-generated constructor stub

}

zombiestudy::~zombiestudy() {
	// TODO Auto-generated destructor stub
}
void zombiestudy::start(){
	int statuswaits;
	pid_t pid = fork();
	if(pid <0){
		printf("error");
		exit(0);
	}
	if(pid >0){
		//parent process

			printf("parent loop\r\n");
			sleep(1);
			statuswaits=0;
			wait(&statuswaits);
			printf("child exit %d\r\n",statuswaits);
			while(true){
				sleep(1);
				printf("parent loop2.\r\n");
				//exit(0); if no this,parent print nothing.
			}
	}
	else{
		sleep(10);
		printf("child process...\r\n");
		exit(0);
	}
}

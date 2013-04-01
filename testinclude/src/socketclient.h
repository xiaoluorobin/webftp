/*
 * socketclient.h
 *
 *  Created on: 2013-4-1
 *      Author: luojianguo
 */

#ifndef SOCKETCLIENT_H_
#define SOCKETCLIENT_H_

class socketclient {
public:
	socketclient();
	void start();
	void bindclientfd(int clientfd);
	void connectserver(int clientfd,const char * serverip,int serverport);
	void sendtoserver(int clientfd);
	void handleresponse(int clientfd);
	void showerror(int errornumber);
	virtual ~socketclient();
};

#endif /* SOCKETCLIENT_H_ */

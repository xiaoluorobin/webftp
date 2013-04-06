/*
 * socketstudy.h
 *
 *  Created on: 2013-3-31
 *      Author: luojianguo
 */

#ifndef SOCKETSTUDY_H_
#define SOCKETSTUDY_H_

class socketstudy {
public:
	socketstudy();
	void start(int portnum);
	void showerror(int errornumber);
	void bindfd(int fd,int portnum);
	void handlerequest(int fdserver);
	void startdaemon();
	virtual ~socketstudy();
};

#endif /* SOCKETSTUDY_H_ */

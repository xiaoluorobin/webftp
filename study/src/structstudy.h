/*
 * structstudy.h
 *
 *  Created on: 2013-3-29
 *      Author: luojianguo
 */

#ifndef STRUCTSTUDY_H_
#define STRUCTSTUDY_H_

#endif /* STRUCTSTUDY_H_ */

#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>
#include<arpa/inet.h>

struct study1 {
	int i;
	int j;
};

class structstudy{

public:
	structstudy();
	virtual ~structstudy();
	void setstructpointer();
	void deleteStudy();
	void getIp();
	void getsStudy();
};

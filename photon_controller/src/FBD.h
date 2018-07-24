/* Created By Yang */
/*
||
|| @file 	FBD.h
|| @version	2.0
|| @author	Yang
||
|| @description
|| Definitions of Function Blocks
||
*/

#ifndef FBD_H_
#define FBD_H_

#include "application.h"

class TON
{
public:
	unsigned IN : 1; // IN option
	unsigned PRE : 1; // IN option
	unsigned Q : 1; // Output
	uint32_t PT; // Set Timeout
	uint32_t ET; // Elapsed time

	void update();
	TON(uint32_t defaultPT = 100); // default bounce time
	void reset();

};

class TOF
{
public:
	unsigned IN : 1; // IN option
	unsigned PRE : 1; // IN option
	unsigned Q : 1; // Output
	uint32_t PT; // Set Timeout
	uint32_t ET; // Elapsed time

	void update();
	TOF(uint32_t defaultPT = 100); // default bounce time
	void reset();
};

class TP
{
public:
	unsigned EN : 1; // Enable option
	unsigned IN : 1; // IN option
	unsigned PRE : 1; // PRE option
	unsigned Q : 1; // Output
	uint32_t PT; // Set Timeout
	uint32_t ET; // Elapsed time

	TP(uint32_t defaultPT = 100);
	void update();
	void reset();
	void setPT(uint32_t newPT);
	uint32_t elepsedTime();
};

class Rtrg
{
public:
	unsigned IN : 1;
	unsigned PRE : 1;
	unsigned Q : 1;
	unsigned : 5;
	Rtrg();
	void update();
	void reset();
};

class Ftrg
{
public:
	unsigned IN : 1;
	unsigned PRE : 1;
	unsigned Q : 1;
	unsigned : 5;
	Ftrg();
	void update();
	void reset();
};

#endif

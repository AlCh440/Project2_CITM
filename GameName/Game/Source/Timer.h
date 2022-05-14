#ifndef __TIMER_H__
#define __TIMER_H__

#include "Defs.h"

class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	uint32 Read() const;
	float ReadSec() const;
	float ReadMilisec() const;
private:
	uint32 startTime;
};

#endif //__TIMER_H__
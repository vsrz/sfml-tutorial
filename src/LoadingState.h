#ifndef LOADINGSTATE_H
#define LOADINGSTATE_H

#pragma once

#include "State.h"
class LoadingState :
	public State
{
public:
	LoadingState(StateStack& stack, Context context);
	~LoadingState(void);
};

#endif


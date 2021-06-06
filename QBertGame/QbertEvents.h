#pragma once
#include "Event.h"
struct QBertEvent final: public Event
{
	enum QBertEvents:int
	{
		Hurt,
		Died,
		Scored
	};
};
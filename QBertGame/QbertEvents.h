#pragma once
#include "Event.h"
struct QBertEvent: public Event
{
	enum QBertEvents:int
	{
		Hurt,
		Died,
		Scored
	};
};
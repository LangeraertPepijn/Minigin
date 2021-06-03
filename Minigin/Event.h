#pragma once

struct Event
{
	enum class Events: int
	{
		Scored,
		Damaged,
		Died
	};
	int CurrentEvent;
};
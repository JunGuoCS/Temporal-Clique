#pragma once
class Interval
{
public:
	int start;
	int end;
	Interval();
	Interval(int s, int e) :start(s), end(e){}
	void setInterval(int s, int e);
	bool operator == (const Interval &i) const
	{
		if (start == i.start&&end == i.end)
			return true;
		else
			return false;
	}
};

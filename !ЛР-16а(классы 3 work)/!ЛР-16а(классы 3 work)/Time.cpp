#include "pch.h"
#include "Time.h"
#include <iostream>
using namespace std;

Time::Time()
{
	min = sec = 0;
}

Time::Time(int m, int s)
{
	min = m;
	sec = s;
}

Time::Time(const Time &t)
{
	min = t.min;
	sec = t.sec;
}

Time & Time::operator=(const Time &t)
{
	min = t.min;
	sec = t.sec;
	return*this;
}


Time::~Time()
{
}

ostream & operator<<(ostream & out, const Time &t)
{
	out << t.min << ":" << t.sec;
	return out;
}

istream & operator>>(istream & in, Time &t)
{
	cout << " минуты: "; in >> t.min;
	cout << " секунды: "; in >> t.sec;
	return in;
}

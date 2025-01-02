#pragma once
#include <iostream>

class Time{
private:
	int hour;
	int minute;
	int second;
public:
	Time(const int& hour, const int& minute, const int& second) {
		this->hour = hour;
		this->minute = minute;
		this->second = second;
	}
	int getHour() const { return this->hour; }
	int getMinute() const { return this->minute; }
	int getSecond() const { return this->second; }
	void setHour(const int& hour) { this->hour = hour; }
	void setMinute(const int& minute) { this->minute = minute; }
	void setSecond(const int& second) { this->second = second; }
	void setTime(const int& hour, const int& minute, const int& second) {
		setHour(hour);
		setMinute(minute);
		setSecond(second);
	}
	friend std::ostream& operator<<(std::ostream& os, const Time& t);
	Time nextSecond(){
		this->second++;
		if (this->second == 60) {
			this->minute++;
			if (this->minute == 60) {
				this->hour++;
				if (this->hour == 24)
					this->hour = 0;
				this->minute = 0;
			}
			this->second = 0;
		}
		return Time(hour, minute, second);
	}
	Time previousSecond() {
		if (this->second > 0) {
			this->second--;
		}
		else if(this->minute > 0){
			this->second = 59;
			this->minute--;
		}
		else if(this->hour > 0){
			this->hour--;
			this->minute = 59;
			this->second = 59;
		}
		else {
			this->hour = 23;
			this->minute = 59;
			this->second = 59;
		}
		return Time(hour, minute, second);
	}
};

std::ostream& operator<<(std::ostream& os, const Time& t) {
	if (t.hour < 10)
		os << "0";
	os << t.hour << ":";
	if (t.minute < 10)
		os << "0";
	os << t.minute << ":";
	if (t.second < 10)
		os << "0";
	os << t.second << "\n";
	return os;
}


#include <iostream>
#include <string>
#include <list>

class YouTubeChannel{
private:	
	std::string name;
	int subscribersCount;
public:
	YouTubeChannel(const std::string& name, const int& subscribersCount) {
		this->name = name;
		this->subscribersCount = subscribersCount;
	}
	bool operator==(const YouTubeChannel& ch) const {
		return this->name == ch.name;
	}

	friend std::ostream& operator<<(std::ostream& os, const YouTubeChannel& yt);
};
std::ostream& operator<<(std::ostream& os,const YouTubeChannel& yt) {
	os << "Name        : " << yt.name << "\n" << "Subscribers : " << yt.subscribersCount << "\n";
	return os;
}

class MyCollection {
private:	
	std::list<YouTubeChannel> myChannels;
public:
	void operator+=(YouTubeChannel& yt) {
		this->myChannels.push_back(yt);
	}
	void operator-=(YouTubeChannel& yt) {
		this->myChannels.remove(yt);
	}
	friend std::ostream& operator<<(std::ostream& os, const MyCollection& mc);
};
std::ostream& operator<<(std::ostream& os, const MyCollection& mc) {
	for (const auto& it : mc.myChannels)
		os << it;
	return os;
}

int main() {
	YouTubeChannel yt1 = YouTubeChannel("EXANU", 1001);
	YouTubeChannel yt2 = YouTubeChannel("Obli5on", 201);

	MyCollection myCollection;
	myCollection += yt1;
	myCollection += yt2;
	std::cout << myCollection << "\n";
	myCollection -= yt2;
	std::cout << myCollection << "\n";
	return 0;
}
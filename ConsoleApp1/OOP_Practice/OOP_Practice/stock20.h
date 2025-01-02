#pragma once
#include <iostream>

class Stock {
private://identifica membrii clasei care pot fi accesati numai de functiile membre
	std::string company;
	int shares;
	double share_val;
	double total_val;

	//inline function
	void set_tot() { total_val = shares * share_val; }

public://identifica membrii clasei care constituie interfata publica a clasei
	Stock(); //default constructor
	Stock(const std::string& co, int n = 0, double pr = 0.0);
	~Stock();//do-nothing destructor

	// help to the introduce of safeguards against faulty transactions
	void buy(int num, double price);
	void sell(int num, double price);

	void update(double price);
	void show() const;

	const Stock& topval(const Stock& s) const;
};


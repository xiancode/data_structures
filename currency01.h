#include <iostream>
#include <string>

using namespace std;

enum sign{plus,minus};

class Currency
{
public:
	Currency(sign s = plus, unsigned long d = 0,unsigned int c = 0);
	~Currency(){};
	bool Set(sign s,unsigned long d,unsigned int c);
	bool Set(float a);

	sign Sign() const
	{
		if(amount < 0)
			return minus;
		else
			return plus;
	}
	unsigned long Dollars() const
	{
		if(amount < 0)
			return (-amount)/100;
		else
			return amount/100;
	}

	unsigned int Cents() const
	{
		if(amount < 0)
			return -amount-Dollars()*100;
		else
			return  amount-Dollars()*100;
	}
	Currency Add(const Currency& x) const;

	Currency& Increment(const Currency&x)
	{
		amount += x.amount;
		return *this;
	}

	void Output() const;

private:
	long amount;
};

Currency::Currency(sign s /* = plus */,unsigned long d /* = 0 */,unsigned int c /* = 0 */)
{
	if(c>99)
	{
		cerr << "Cents should be < 100" << endl;
		exit(1);
	}
	amount = d*100 + c;
	if(s==minus)
		amount = -amount;
}

bool Currency::Set(float a)
{
	sign sgn;
	if(a<0)
	{
		sgn = minus;
		a = -a;
	}
	else
		sgn = plus;
	amount = (a+0.001)*100;
	if(sgn == minus)
		amount = -amount;
	return true;
}

Currency Currency::Add(const Currency&x) const
{
	Currency y;
	y.amount =amount + x.amount;
	return y;
}

void Currency::Output() const
{
	long a = amount;
	if(a<0)
	{
		cout << "-";
		a = -a;
	}
	long d = a/100;
	cout << "$" << d << '.';
	int c = a - d*100;
	if(c<10)
		cout << "0";
	cout << c;
}

bool Currency::Set(sign s,unsigned long d,unsigned int c)
{
	if(c>99)
		return false;
	amount = d*100 + c;
	if(s==minus)
		amount = -amount;
	return true;
}
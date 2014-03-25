#include <iostream>
#include <string>

using namespace std;

enum sign{plus,minus};

class Currency
{
public:
	// 构造函数
	Currency(sign s = plus,unsigned long d = 0,unsigned int c = 0);
	// 析构函数
	~Currency(){}
	bool Set(sign s,unsigned long d,unsigned int c);
	bool Set(float a);
	sign Sign() const {return sgn;}
	unsigned long Dollars() const {return dollars;}
	unsigned int  Cents() const {return cents;}
	Currency Add(const Currency& x) const;
	Currency& Increment(const Currency& x);
	void Output() const;
private:
	sign sgn;
	unsigned long dollars;
	unsigned int cents;
};
Currency::Currency(sign s,unsigned long d ,unsigned int c)
{
	// 创建一个Currency对象
	if(c > 99)
	{
		cerr << "Cents should be < 100" << endl;
		exit(1);
	}
	sgn = s;
	dollars = d;
	cents = c;
}

bool Currency::Set(sign s,unsigned long d,unsigned int c)
{
	if(c > 99)
		return false;
	sgn = s;
	dollars = d;
	cents = c;
	return true;
}

bool Currency::Set(float a)
{
	if(a<0)
	{
		sgn = minus;
		a = -a;
	}
	else
		sgn = plus;
	dollars = a;
	cents = (a+0.005-dollars)*100;
	return true;
}

Currency Currency::Add(const Currency& x) const
{
	// 把x加到this
	long a1,a2,a3;
	Currency ans;
	a1 = dollars * 100 + cents;
	if(sgn == minus)
		a1 = -a1;

	// 把x转化为带符号的整数
	a2 = x.dollars * 100 + x.cents;
	if(x.sgn == minus)
		a2 = -a2;

	a3 = a1 + a2;
	// 转化
	if(a3<0)
	{
		ans.sgn = minus;
		a3 = -a3;
	}
	else
		ans.sgn = plus;
	ans.dollars = a3/100;
	ans.cents = a3 - ans.dollars*100;	
	return ans;
}

Currency& Currency::Increment(const Currency& x)
{
	*this = Add(x);
	return *this;
}

void Currency::Output() const
{
	// 输出currency的值
	if(sgn == minus)
		cout << "-";
	cout << "$" << dollars << ".";
	if(cents < 10)
		cout << "0";
	cout << cents;
}

// Currency.cpp

#include <iostream>
//#include "currency.h"
#include "currency01.h"

int main()
{
	Currency g,h(plus,3,50),i,j;
	g.Set(minus,2,25);
	i.Set(-6.45);
	//j = h.Add(g);
	j = h + g;
	//j.Output();
	cout << j;
	cout << endl;
	//i.Increment(g);
	i += g;
	//i.Output();
	cout << i;
	cout << endl;
	//j = i.Add(g).Add(h);
	j = i + g + h;
	//j.Output();
	cout << j;
	cout << endl;
	//j = i.Increment(g).Add(h);
	j +=g;
	j +=h;
	//j.Output();
	cout << j;
	cout << endl;
	//i.Output();
	cout << endl;
}
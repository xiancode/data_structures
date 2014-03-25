// Currency.cpp

#include <iostream>
#include "currency.h"


int main()
{
	Currency g,h(plus,3,50),i,j;
	g.Set(minus,2,25);
	i.Set(-6.45);
	j = h.Add(g);

	j.Output();
	cout << endl;
	i.Increment(g);
	i.Output();
	cout << endl;
	j = i.Add(g).Add(h);
	j.Output();
	cout << endl;
	j = i.Increment(g).Add(h);
	j.Output();
	cout << endl;
	i.Output();
	cout << endl;
}
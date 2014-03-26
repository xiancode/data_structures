#include <iostream>

using namespace std;

template<class T>
void OutputRoots(T a,T b,T c)
{
	T d = b*b - 4*a*c;
	if(d>0)
	{
		float sqrtd = sqrt(d);
		cout << "There are two real roots"
			 << (-b+sqrtd)/(2*a) << " and "
			 << (-b-sqrtd)/(2*a)
			 << endl;
	}
	else if(d==0)
	{
		cout << "There is only one distinct root"
			 << -b/(2*a)
			 << endl;
	}
	else
		cout << "The roots are complex "
			 << endl
			 << "The real part is "
			 <<-b/(2*a) << endl
			 << "The imaginary part is"
			 << sqrt(-d)/(2*a) << endl;
}

int main()
{
	float a,b,c;
	a = 1;
	b = -5;
	c = 6;
	OutputRoots(a,b,c);
	std::cin.get();
	return 0;
}
// MatrixOpsWithBoost.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

int main()
{
	using namespace boost::numeric::ublas;
	long long someLargeNumber = ((long long)INT_MAX) * 4;
	int someLargeSize = 70000;
	matrix<double> m(someLargeSize, someLargeSize);
	/*for (unsigned i = 0; i < m.size1(); i++)
	{
		for (unsigned j = 0; j < m.size2(); j++)
		{
			m(i, j) = 3 * (i) + (j + 1);
		}
	}*/
    std::cout << "The size of the matrix m in GB is \n"<<(m.size1() * m.size2() * sizeof(m.at_element(0,0)))/(1024 * 1024 * 1024)<<std::endl;
}

#pragma once
#include <map>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <string>

using namespace std;
using namespace boost::numeric::ublas;

typedef std::shared_ptr < matrix<double>> MatrixPtr;
typedef map<string, MatrixPtr> MatrixDict;

class NativeMatrixManager
{
public:
	/*char* matrixLabel,*/
	bool InstantiateMatrix(string matrixLabel, int rows, int columns);
	bool matrixCreationPossible(int rows, int columns, unsigned long long dataTypeSize);
	MatrixDict MatricesMap;
};


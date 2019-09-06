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
	MatrixPtr InstantiateMatrix(string matrixLabel, int rows, int columns);
	MatrixDict MatricesMap;
	// Sets the data for the matrix if the matrix exists
	bool SetDataForRow(string matrixLabel, double row, double* rowData);
	// Deletes the matrix from memory if available
	bool DeleteMatrix(string matrixLabel);
};
bool matrixCreationPossible(int rows, int columns, unsigned long long dataTypeSize);

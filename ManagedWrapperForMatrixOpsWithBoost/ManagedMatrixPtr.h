#pragma once

#include <Windows.h>
#include <boost/numeric/ublas/matrix.hpp>

using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;
using namespace std;
using namespace boost::numeric::ublas;

typedef std::shared_ptr < matrix<double>> MatrixPtr;

public enum class GCSetting: int 
{ 
	NoCollectionDuringInstantiation = 0, 
	ForceCollectionDuringInstantiation = 1, 
	CollectOnlyIfNecessary = 2};

public ref class ManagedMatrixPtr
{
public private:
	ManagedMatrixPtr(matrix<double>* matrix);
public:
	ManagedMatrixPtr(double rows, double columns, GCSetting gcSetting);
	ManagedMatrixPtr(double rows, double columns, double initValue, GCSetting gcSetting);
	~ManagedMatrixPtr();
	!ManagedMatrixPtr();
	double RowCount();
	double ColumnCount();
	double get(double rowIndex, double colIndex);
	void set(double rowIndex, double colIndex, double value);
	List<double>^ getDataForRow(double rowIndex);
	void setDataForRow(double rowIndex, List<double>^ rowData);
	List<double>^ getDataForCol(double colIndex);
	void setDataForCol(double colIndex, List<double>^ colData);
	List<List<double>^>^ getData();
	void setData(List<List<double>^>^ data);
	static ManagedMatrixPtr^ product (ManagedMatrixPtr^ lhs, ManagedMatrixPtr^ rhs);
	static void garbageCollectBasedOnSetting(GCSetting gcSetting,double rows,double columns, double elemSize);
private:
	MatrixPtr* pointerToNativeMatrixPtr;
public:
	bool IsDisposed;
};
bool matrixCreationPossible(int rows, int columns, unsigned long long dataTypeSize);
void printMatrix(boost::numeric::ublas::matrix<double>& mulMatrix);


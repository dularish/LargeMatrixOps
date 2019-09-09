#pragma once
#include "../MatrixOpsWithBoost/NativeMatrixManager.h"

using namespace System::Runtime::InteropServices;
public ref class ManagedMatrixPtr
{
public private:
	ManagedMatrixPtr(System::String^ matrixName, MatrixPtr matrixPtr, NativeMatrixManager* nativeMatrixManager);	
	ManagedMatrixPtr(matrix<double>* matrix);
public:
	ManagedMatrixPtr(double rows, double columns);
	ManagedMatrixPtr(double rows, double columns, double initValue);
	~ManagedMatrixPtr();
	!ManagedMatrixPtr();
	double RowCount();
	double ColumnCount();
	double get(double rowIndex, double colIndex);
	void set(double rowIndex, double colIndex, double value);
	static ManagedMatrixPtr^ product (ManagedMatrixPtr^ lhs, ManagedMatrixPtr^ rhs);
private:
	MatrixPtr* pointerToNativeMatrixPtr;
	NativeMatrixManager* nativeMatrixManager;
public:
	System::String^ MatrixName;
	bool IsDisposed;
};


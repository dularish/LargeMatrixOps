#pragma once
#include "../MatrixOpsWithBoost/NativeMatrixManager.h"

using namespace System::Runtime::InteropServices;
public ref class ManagedMatrixPtr
{
public private:
	ManagedMatrixPtr(System::String^ matrixName, MatrixPtr matrixPtr, NativeMatrixManager* nativeMatrixManager);	
public:
	ManagedMatrixPtr(double rows, double columns);
	~ManagedMatrixPtr();
	!ManagedMatrixPtr();
	double RowCount();
	double ColumnCount();
private:
	MatrixPtr* pointerToNativeMatrixPtr;
	NativeMatrixManager* nativeMatrixManager;
public:
	System::String^ MatrixName;
	bool IsDisposed;
};


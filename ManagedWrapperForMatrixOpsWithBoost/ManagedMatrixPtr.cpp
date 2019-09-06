#include "pch.h"
#include "ManagedMatrixPtr.h"

ManagedMatrixPtr::ManagedMatrixPtr(System::String^ matrixName, MatrixPtr matrixPtr, NativeMatrixManager* nativeMatrixManager)
{
	this->MatrixName = matrixName;
	this->pointerToNativeMatrixPtr = new MatrixPtr(matrixPtr);
	this->nativeMatrixManager = nativeMatrixManager;
}

ManagedMatrixPtr::ManagedMatrixPtr(matrix<double>* matrix)
{
	pointerToNativeMatrixPtr = new MatrixPtr(matrix);
	nativeMatrixManager = NULL;
	MatrixName = "Unnamed";
}

ManagedMatrixPtr::ManagedMatrixPtr(double rows, double columns)
{
	if (matrixCreationPossible(rows, columns, sizeof(double))) {
		pointerToNativeMatrixPtr = new MatrixPtr( new matrix<double>(rows, columns));
		nativeMatrixManager = NULL;
		MatrixName = "Unnamed";
	}
	else {
		throw gcnew System::Exception("Matrix creation not possible as there is not enough memory");
	}
}

ManagedMatrixPtr::~ManagedMatrixPtr()
{
	this->!ManagedMatrixPtr();
}

ManagedMatrixPtr::!ManagedMatrixPtr()
{
	IsDisposed = true;//Setting this property even though disposing has just started
	if (nativeMatrixManager != NULL) {
		char* matrixName = static_cast<char*>(Marshal::StringToHGlobalAnsi(MatrixName).ToPointer());
		nativeMatrixManager->DeleteMatrix(matrixName);
	}
	if (pointerToNativeMatrixPtr) {
		delete pointerToNativeMatrixPtr;
	}
}

double ManagedMatrixPtr::RowCount()
{
	if (!IsDisposed) {
		return (*pointerToNativeMatrixPtr)->size1();
	}
	else {
		throw gcnew System::Exception("Tried to access disposed object");
	}
}

double ManagedMatrixPtr::ColumnCount()
{
	if (!IsDisposed) {
		return (*pointerToNativeMatrixPtr)->size2();
	}
	else {
		throw gcnew System::Exception("Tried to access disposed object");
	}
}

ManagedMatrixPtr^ ManagedMatrixPtr::product(ManagedMatrixPtr^ lhs, ManagedMatrixPtr^ rhs)
{
	matrix<double> mulMatrix = prod(*(*(lhs->pointerToNativeMatrixPtr)), (*(*(rhs->pointerToNativeMatrixPtr))));
	matrix<double>* heapMatrix = new matrix<double>(mulMatrix);
	return gcnew ManagedMatrixPtr(heapMatrix);
}

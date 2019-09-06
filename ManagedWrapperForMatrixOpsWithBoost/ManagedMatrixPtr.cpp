#include "pch.h"
#include "ManagedMatrixPtr.h"

ManagedMatrixPtr::ManagedMatrixPtr(System::String^ matrixName, MatrixPtr matrixPtr, NativeMatrixManager* nativeMatrixManager)
{
	this->MatrixName = matrixName;
	this->pointerToNativeMatrixPtr = new MatrixPtr(matrixPtr);
	this->nativeMatrixManager = nativeMatrixManager;
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
	if (nativeMatrixManager != NULL) {
		char* matrixName = static_cast<char*>(Marshal::StringToHGlobalAnsi(MatrixName).ToPointer());
		nativeMatrixManager->DeleteMatrix(matrixName);
	}
	if (pointerToNativeMatrixPtr) {
		delete pointerToNativeMatrixPtr;
	}
}

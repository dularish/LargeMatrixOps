#include "pch.h"

#include "ManagedWrapperForMatrixOpsWithBoost.h"

ManagedWrapperForMatrixOpsWithBoost::ManagedMatrixManager::ManagedMatrixManager()
{
	nativeMatrixManager = new NativeMatrixManager();
	System::String^ managedString = "someString";
	
}

ManagedWrapperForMatrixOpsWithBoost::ManagedMatrixManager::~ManagedMatrixManager()
{
	delete nativeMatrixManager;
}

bool ManagedWrapperForMatrixOpsWithBoost::ManagedMatrixManager::InstantiateMatrix(String^ matrixName, double rows, double cols)
{
	char* unmanagedString = static_cast<char*>(Marshal::StringToHGlobalAnsi(matrixName).ToPointer());
	return nativeMatrixManager->InstantiateMatrix(unmanagedString, rows, cols);
}

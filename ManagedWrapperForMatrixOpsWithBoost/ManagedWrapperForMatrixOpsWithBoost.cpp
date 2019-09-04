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

void ManagedWrapperForMatrixOpsWithBoost::ManagedMatrixManager::SetDataForRow(String^ matrixName, double row, List<double>^ rowData)
{
	if (nativeMatrixManager) {
		MatrixDict matrixDict = nativeMatrixManager->MatricesMap;
		char* matrixNameUnmanaged = static_cast<char*>(Marshal::StringToHGlobalAnsi(matrixName).ToPointer());

		if (matrixDict.find(matrixNameUnmanaged) == matrixDict.end()) {
			throw gcnew Exception("Matrix " + matrixName + " not found");
		}
		else {
			MatrixPtr matrixPtr = matrixDict[matrixNameUnmanaged];

			if (row >= 0 && row < matrixPtr->size1()) {
				if (rowData->Count != matrixPtr->size2()) {
					throw gcnew Exception("Matrix size don't match");
				}
				else {
					for (size_t i = 0; i < rowData->Count; i++)
					{
						matrixPtr->at_element(row, i) = rowData[i];
					}
				}
			}
			else {
				throw gcnew Exception("Incorrect row number input to set : " + row.ToString());
			}
		}
	}
	else {
		throw gcnew Exception("Native matrix manager does not exist");
	}
}

void ManagedWrapperForMatrixOpsWithBoost::ManagedMatrixManager::SetDataForCol(String^ matrixName, double col, List<System::Double>^ colData)
{
	if (nativeMatrixManager) {
		MatrixDict matrixDict = nativeMatrixManager->MatricesMap;
		char* matrixNameUnmanaged = static_cast<char*>(Marshal::StringToHGlobalAnsi(matrixName).ToPointer());

		if (matrixDict.find(matrixNameUnmanaged) == matrixDict.end()) {
			throw gcnew Exception("Matrix " + matrixName + " not found");
		}
		else {
			MatrixPtr matrixPtr = matrixDict[matrixNameUnmanaged];

			if (col >= 0 && col < matrixPtr->size2()) {
				if (colData->Count != matrixPtr->size1()) {
					throw gcnew Exception("Matrix size don't match");
				}
				else {
					for (size_t i = 0; i < colData->Count; i++)
					{
						matrixPtr->at_element(i, col) = colData[i];
					}
				}
			}
			else {
				throw gcnew Exception("Incorrect col number input to set : " + col.ToString());
			}
		}
	}
	else {
		throw gcnew Exception("Native matrix manager does not exist");
	}
}

List<double>^ ManagedWrapperForMatrixOpsWithBoost::ManagedMatrixManager::GetDataForRow(String^ matrixName, double row)
{
	if (nativeMatrixManager) {
		MatrixDict matrixDict = nativeMatrixManager->MatricesMap;
		char* matrixNameUnmanaged = static_cast<char*>(Marshal::StringToHGlobalAnsi(matrixName).ToPointer());

		if (matrixDict.find(matrixNameUnmanaged) == matrixDict.end()) {
			throw gcnew Exception(" Matrix " + matrixName + " not found");
		}
		else {
			MatrixPtr matrixPtr = matrixDict[matrixNameUnmanaged];
			if (row >= 0 && row < matrixPtr->size1()) {
				List<double>^ returnList = gcnew List<double>(matrixPtr->size2());

				for (size_t i = 0; i < matrixPtr->size2(); i++)
				{
					returnList->Add(matrixPtr->at_element(row, i));
				}
				return returnList;
			}
			else {
				throw gcnew Exception("Incorrect row number input to get : " + row.ToString());
			}
		}
	}
	else {
		throw gcnew Exception("Native matrix manager does not exist");
	}
}

List<double>^ ManagedWrapperForMatrixOpsWithBoost::ManagedMatrixManager::GetDataForCol(String^ matrixName, double col)
{
	if (nativeMatrixManager) {
		MatrixDict matrixDict = nativeMatrixManager->MatricesMap;
		char* matrixNameUnmanaged = static_cast<char*>(Marshal::StringToHGlobalAnsi(matrixName).ToPointer());

		if (matrixDict.find(matrixNameUnmanaged) == matrixDict.end()) {
			throw gcnew Exception(" Matrix " + matrixName + " not found");
		}
		else {
			MatrixPtr matrixPtr = matrixDict[matrixNameUnmanaged];
			if (col >= 0 && col < matrixPtr->size2()) {
				List<double>^ returnList = gcnew List<double>(matrixPtr->size1());

				for (size_t i = 0; i < matrixPtr->size1(); i++)
				{
					returnList->Add(matrixPtr->at_element(i, col));
				}
				return returnList;
			}
			else {
				throw gcnew Exception("Incorrect col number input to get : " + col.ToString());
			}
		}
	}
	else {
		throw gcnew Exception("Native matrix manager does not exist");
	}
}

void ManagedWrapperForMatrixOpsWithBoost::ManagedMatrixManager::MatrixMultiply(String^ matrixA, String^ matrixB, String^ labelForMatrixAB)
{
	if (nativeMatrixManager) {
		MatrixDict matrixDict = nativeMatrixManager->MatricesMap;
		char* matrixNameAUnmanaged = static_cast<char*>(Marshal::StringToHGlobalAnsi(matrixA).ToPointer());
		char* matrixNameBUnmanaged = static_cast<char*>(Marshal::StringToHGlobalAnsi(matrixB).ToPointer());
		char* matrixNameABUnmanaged = static_cast<char*>(Marshal::StringToHGlobalAnsi(labelForMatrixAB).ToPointer());

		if (matrixDict.find(matrixNameAUnmanaged) == matrixDict.end()) {
			throw gcnew Exception(" Matrix " + matrixA + " not found");
		}
		else if (matrixDict.find(matrixNameBUnmanaged) == matrixDict.end()) {
			throw gcnew Exception(" Matrix " + matrixB + " not found");
		}
		/*else if (matrixDict.find(matrixNameABUnmanaged) != matrixDict.end()) {
			throw gcnew Exception(" Matrix " + labelForMatrixAB + " already exists. It needs to be cleared for matrix multiplication to work");
		}*/
		else {
			MatrixPtr matrixAPtr = matrixDict[matrixNameAUnmanaged];
			MatrixPtr matrixBPtr = matrixDict[matrixNameBUnmanaged];

			if (matrixAPtr->size2() == matrixBPtr->size1()) {
				
				MatrixPtr matrixABPtr = matrixDict[matrixNameABUnmanaged];
				(*matrixABPtr) = prod(*matrixAPtr, *matrixBPtr);

				/*
				//This block doesn't work - To check why
				bool returnType = InstantiateMatrix(labelForMatrixAB + "_local", 2, 2);
				char* matrixNameLocallyInstantiated = static_cast<char*>(Marshal::StringToHGlobalAnsi(labelForMatrixAB + "_local").ToPointer());
				MatrixPtr matrixLocallyInst = matrixDict[matrixNameLocallyInstantiated];

				cout << matrixAPtr << endl;
				cout << matrixBPtr << endl;
				cout << matrixABPtr << endl;
				cout << matrixLocallyInst << endl;
				printMatrix(matrixLocallyInst);*/
				
			}
			else {
				throw gcnew Exception("Matrix dimensions don't match for matrix multiplication");
			}
		}
	}
	else {
		throw gcnew Exception("Native matrix manager does not exist");
	}
}

void ManagedWrapperForMatrixOpsWithBoost::printMatrix(MatrixPtr& matrixAPtr)
{
	cout << endl << endl;
	for (size_t i = 0; i < matrixAPtr->size1(); i++)
	{
		for (size_t j = 0; j < matrixAPtr->size2(); j++)
		{
			cout << matrixAPtr->at_element(i, j) << " ";
		}
		cout << endl;
	}
}

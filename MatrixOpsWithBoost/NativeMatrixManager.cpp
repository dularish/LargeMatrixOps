#include "NativeMatrixManager.h"
#include <Windows.h>

/*char* matrixLabel,*/
MatrixPtr NativeMatrixManager::InstantiateMatrix(string matrixLabel, int rows, int columns)
{
	if (MatricesMap.find(matrixLabel) != MatricesMap.end()) {
		throw ("Matrix " + matrixLabel + " already exists");
	}
	else {
		try
		{
			if (matrixCreationPossible(rows, columns, sizeof(double))) {
				MatricesMap[matrixLabel] = std::make_shared<matrix<double>>(rows, columns);
				return MatricesMap[matrixLabel];
			}
			else {
				throw ("Not enough memory available to instantiate the matrix " + matrixLabel);
			}
		}
		catch (const std::exception& ex)
		{
			string exceptionMessage = ex.what();
			throw ("Exception during matrix creation : " + (exceptionMessage));
		}
	}
}

//Function to check if matrix creation is possible
bool matrixCreationPossible(int rows, int columns, unsigned long long dataTypeSize)
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);

	GlobalMemoryStatusEx(&statex);
	double availablePhysicalMemoryInMB = statex.ullAvailPhys / (1024 * 1024);
	double expectedDataSizeInMB = (double)rows * (double)columns * dataTypeSize / (1024 * 1024);

	//Reserving 2GB of data for other processes
	if (availablePhysicalMemoryInMB > expectedDataSizeInMB && ((availablePhysicalMemoryInMB - expectedDataSizeInMB) > 2048)) {
		return true;
	}
	else {
		return false;
	}
}


// Sets the data for the matrix if the matrix exists
bool NativeMatrixManager::SetDataForRow(string matrixLabel, double row, double* rowData)
{
	if (MatricesMap.find(matrixLabel) == MatricesMap.end()) {
		cout << "Matrix " << matrixLabel << " does not exists" << endl;
		return false;
	}
	else {
		for (size_t i = 0; i < rowData[i] != NULL; i++)
		{
			MatrixPtr matrixPtr = MatricesMap[matrixLabel];
			matrixPtr->at_element(row, i) = rowData[i];
		}
		return true;
	}
}


// Deletes the matrix from memory if available
bool NativeMatrixManager::DeleteMatrix(string matrixLabel)
{
	if (MatricesMap.find(matrixLabel) == MatricesMap.end()) {
		cout << "Matrix " << matrixLabel << " does not exists" << endl;
		return false;
	}
	else {
		try
		{
			MatricesMap.erase(matrixLabel);
			return true;
		}
		catch (const std::exception& ex)
		{
			cout << "Exception during matrix deletion : " << ex.what() << endl;
			return false;
		}
	}
}
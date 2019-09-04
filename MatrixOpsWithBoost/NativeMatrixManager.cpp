#include "NativeMatrixManager.h"
#include <Windows.h>

/*char* matrixLabel,*/
bool NativeMatrixManager::InstantiateMatrix(string matrixLabel, int rows, int columns)
{
	// TODO: Add your implementation code here.
	if (MatricesMap.find(matrixLabel) != MatricesMap.end()) {
		cout << "Matrix "<<matrixLabel<<" already exists" << endl;
		return false;
	}
	else {
		try
		{
			if (matrixCreationPossible(rows, columns, sizeof(double))) {
				MatricesMap[matrixLabel] = std::make_shared<matrix<double>>(rows, columns);
				return true;
			}
			else {
				cout << "Not enough memory available to instantiate the matrix " << matrixLabel << endl;
				return false;
			}
		}
		catch (const std::exception& ex)
		{
			cout << "Exception during matrix creation : " << ex.what() << endl;
			return false;
		}
	}

	return true;
}

//Function to check if matrix creation is possible
bool NativeMatrixManager::matrixCreationPossible(int rows, int columns, unsigned long long dataTypeSize)
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

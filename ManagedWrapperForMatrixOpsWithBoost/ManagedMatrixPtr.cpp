#include "pch.h"
#include "ManagedMatrixPtr.h"


ManagedMatrixPtr::ManagedMatrixPtr(matrix<double>* matrix)
{
	pointerToNativeMatrixPtr = new MatrixPtr(matrix);
}

ManagedMatrixPtr::ManagedMatrixPtr(double rows, double columns, GCSetting gcSetting)
{
	garbageCollectBasedOnSetting(gcSetting, rows, columns, sizeof(double));
	if (matrixCreationPossible(rows, columns, sizeof(double))) {
		pointerToNativeMatrixPtr = new MatrixPtr( new matrix<double>(rows, columns));
	}
	else {
		throw gcnew System::Exception("Matrix creation not possible as there is not enough memory");
	}
}

ManagedMatrixPtr::ManagedMatrixPtr(double rows, double columns, double initValue, GCSetting gcSetting)
{
	garbageCollectBasedOnSetting(gcSetting, rows, columns, sizeof(double));
	if (matrixCreationPossible(rows, columns, sizeof(double))) {
		pointerToNativeMatrixPtr = new MatrixPtr(new matrix<double>(rows, columns, initValue));
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

double ManagedMatrixPtr::get(double rowIndex, double colIndex)
{
	if ((*pointerToNativeMatrixPtr) == NULL || ((*pointerToNativeMatrixPtr)->size1() <= rowIndex) || ((*pointerToNativeMatrixPtr)->size2() <= colIndex)) {
		throw gcnew System::Exception("Index out of bounds");
	}
	else {
		return (*pointerToNativeMatrixPtr)->at_element(rowIndex, colIndex);
	}
}

void ManagedMatrixPtr::set(double rowIndex, double colIndex, double value)
{
	if ((*pointerToNativeMatrixPtr) == NULL || ((*pointerToNativeMatrixPtr)->size1() <= rowIndex) || ((*pointerToNativeMatrixPtr)->size2() <= colIndex)) {
		throw gcnew System::Exception("Index out of bounds");
	}
	else {
		(*pointerToNativeMatrixPtr)->at_element(rowIndex, colIndex) = value;
	}
}

List<double>^ ManagedMatrixPtr::getDataForRow(double rowIndex)
{
	if ((*pointerToNativeMatrixPtr) == NULL || ((*pointerToNativeMatrixPtr)->size1() <= rowIndex)) {
		throw gcnew System::Exception("Index out of bounds");
	}
	else {
		List<double>^ rowData = gcnew List<double>((*pointerToNativeMatrixPtr)->size2());
		for (size_t i = 0; i < ((*pointerToNativeMatrixPtr)->size2()); i++)
		{
			rowData->Add((*pointerToNativeMatrixPtr)->at_element(rowIndex, i));
		}
		return rowData;
	}
}

void ManagedMatrixPtr::setDataForRow(double rowIndex, List<double>^ rowData)
{
	if ((*pointerToNativeMatrixPtr) == NULL || ((*pointerToNativeMatrixPtr)->size1() <= rowIndex)) {
		throw gcnew System::Exception("Index out of bounds");
	}
	else {

		if ((*pointerToNativeMatrixPtr)->size2() != rowData->Count) {
			throw gcnew System::Exception("Column numbers don't match");
		}
		else {
			for (size_t i = 0; i < ((*pointerToNativeMatrixPtr)->size2()); i++)
			{
				set(rowIndex, i, rowData[i]);
			}
		}
	}
}

List<double>^ ManagedMatrixPtr::getDataForCol(double colIndex)
{
	if ((*pointerToNativeMatrixPtr) == NULL || ((*pointerToNativeMatrixPtr)->size2() <= colIndex)) {
		throw gcnew System::Exception("Index out of bounds");
	}
	else {
		List<double>^ colData = gcnew List<double>((*pointerToNativeMatrixPtr)->size1());
		for (size_t i = 0; i < ((*pointerToNativeMatrixPtr)->size2()); i++)
		{
			colData->Add((*pointerToNativeMatrixPtr)->at_element(i, colIndex));
		}
		return colData;
	}
}

void ManagedMatrixPtr::setDataForCol(double colIndex, List<double>^ colData)
{
	if ((*pointerToNativeMatrixPtr) == NULL || ((*pointerToNativeMatrixPtr)->size2() <= colIndex)) {
		throw gcnew System::Exception("Index out of bounds");
	}
	else {

		if ((*pointerToNativeMatrixPtr)->size1() != colData->Count) {
			throw gcnew System::Exception("Row numbers don't match");
		}
		else {
			for (size_t i = 0; i < ((*pointerToNativeMatrixPtr)->size1()); i++)
			{
				set(i, colIndex, colData[i]);
			}
		}
	}
}

List<List<double>^>^ ManagedMatrixPtr::getData()
{
	if ((*pointerToNativeMatrixPtr) == NULL ) {
		throw gcnew System::Exception("Matrix is null");
	}
	else {
		List<List<double>^>^ matrixData = gcnew List<List<double>^>(RowCount());
		for (size_t i = 0; i < (RowCount()); i++)
		{
			List<double>^ rowData = gcnew List<double>(ColumnCount());
			for (size_t j = 0; j < (ColumnCount()); j++)
			{
				rowData->Add(get(i, j));
			}
			matrixData->Add(rowData);
		}
		return matrixData;
	}
}

void ManagedMatrixPtr::setData(List<List<double>^>^ data)
{
	if (data->Count > 0) {
		if (data->Count != RowCount()) {
			throw gcnew System::Exception("Data count not equal to row count");
		}
		double colSizeOfFirstRow = data[0]->Count;

		if (colSizeOfFirstRow != ColumnCount()) {
			throw gcnew System::Exception("Data count not equal to column count");
		}

		for (size_t i = 1; i < data->Count; i++)
		{
			if (data[i]->Count != colSizeOfFirstRow) {
				throw gcnew System::Exception("All column sizes are not equal. Therefore invalid data");
			}
		}

		for (size_t i = 0; i < RowCount(); i++)
		{
			setDataForRow(i, data[i]);
		}
	}
	else {
		throw gcnew System::Exception("Data rows count cannot be less than zero");
	}
}

ManagedMatrixPtr^ ManagedMatrixPtr::product(ManagedMatrixPtr^ lhs, ManagedMatrixPtr^ rhs)
{
	try
	{
		if (lhs->ColumnCount() == rhs->RowCount()) {
			matrix<double> lhsMatrix = (*(*(lhs->pointerToNativeMatrixPtr)));
			matrix<double> rhsMatrix = (*(*(rhs->pointerToNativeMatrixPtr)));
			matrix<double>* mulMatrix = new matrix<double>(lhs->RowCount(), rhs->ColumnCount(),0);
			(*mulMatrix) = prod(lhsMatrix, rhsMatrix);
			return gcnew ManagedMatrixPtr(mulMatrix);
		}
		else {
			throw gcnew System::Exception("Matrix dimensions don't match for matrix multiplication");
		}
	}
	catch (std::exception& ex)
	{
		std::string exceptionMessage = ex.what();
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
	catch (std::string const& exMessage)
	{
		throw gcnew System::Exception(gcnew System::String(exMessage.c_str()));
	}
}
void ManagedMatrixPtr::garbageCollectBasedOnSetting(GCSetting gcSetting, double rows, double columns, double elemSize)
{
	switch (gcSetting)
	{
	case GCSetting::NoCollectionDuringInstantiation:
		break;
	case GCSetting::ForceCollectionDuringInstantiation:
		System::GC::Collect();
		System::GC::WaitForPendingFinalizers();
		break;
	case GCSetting::CollectOnlyIfNecessary:
		if (!matrixCreationPossible(rows, columns, elemSize)) {
			System::GC::Collect();
			System::GC::WaitForPendingFinalizers();
		}
		break;
	default:
		throw gcnew System::Exception(gcnew System::String("Unimplemented garbage collection setting"));
		break;
	}
}
void printMatrix(boost::numeric::ublas::matrix<double>& mulMatrix)
{
	for (size_t i = 0; i < mulMatrix.size1(); i++)
	{
		for (size_t j = 0; j < mulMatrix.size2(); j++)
		{
			cout << mulMatrix.at_element(i, j) << " ";
		}
		cout << endl;
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

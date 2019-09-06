#pragma once
#include "../MatrixOpsWithBoost/NativeMatrixManager.h"
#include "ManagedMatrixPtr.h"
//#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::Collections::Generic;
using namespace std;
using namespace System::Runtime::InteropServices;
namespace ManagedWrapperForMatrixOpsWithBoost {
	public ref class ManagedMatrixManager
	{
	public:
		ManagedMatrixManager();
		~ManagedMatrixManager();
		ManagedMatrixPtr^ InstantiateMatrix(String^ matrixName, double rows, double cols);
		bool DeleteMatrix(String^ matrixName);
		void SetDataForRow(String^ matrixName, double row, List<System::Double>^ rowData);
		void SetDataForCol(String^ matrixName, double col, List<System::Double>^ colData);
		List<double>^ GetDataForRow(String^ matrixName, double row);
		double GetDataAt(String^ matrixName, double rowIndex, double colIndex);
		void SetDataAt(String^ matrixName, double rowIndex, double colIndex, double dataToSet);
		List<double>^ GetDataForCol(String^ matrixName, double col);
		void MatrixMultiply(String^ matrixA, String^ matrixB, String^ labelForMatrixAB);
	private:
		NativeMatrixManager* nativeMatrixManager;
	};
	void printMatrix(MatrixPtr& matrixAPtr);

}

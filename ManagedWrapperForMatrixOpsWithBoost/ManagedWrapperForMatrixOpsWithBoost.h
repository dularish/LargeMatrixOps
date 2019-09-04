#pragma once
#include "../MatrixOpsWithBoost/NativeMatrixManager.h"
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
		bool InstantiateMatrix(String^ matrixName, double rows, double cols);
		void SetDataForRow(String^ matrixName, double row, List<System::Double>^ rowData);
		void SetDataForCol(String^ matrixName, double col, List<System::Double>^ colData);
		List<double>^ GetDataForRow(String^ matrixName, double row);
		List<double>^ GetDataForCol(String^ matrixName, double col);
		void MatrixMultiply(String^ matrixA, String^ matrixB, String^ labelForMatrixAB);
	private:
		NativeMatrixManager* nativeMatrixManager;
	};
}

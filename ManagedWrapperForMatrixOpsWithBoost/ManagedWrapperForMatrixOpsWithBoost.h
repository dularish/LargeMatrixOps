#pragma once
#include "../MatrixOpsWithBoost/NativeMatrixManager.h"
//#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace std;
using namespace System::Runtime::InteropServices;
namespace ManagedWrapperForMatrixOpsWithBoost {
	public ref class ManagedMatrixManager
	{
	public:
		ManagedMatrixManager();
		~ManagedMatrixManager();
		bool InstantiateMatrix(String^ matrixName, double rows, double cols);
	private:
		NativeMatrixManager* nativeMatrixManager;
	};
}

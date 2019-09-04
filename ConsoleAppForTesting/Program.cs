using ManagedWrapperForMatrixOpsWithBoost;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleAppForTesting
{
    class Program
    {
        static void Main(string[] args)
        {
            ManagedMatrixManager managedMatrixManager = new ManagedMatrixManager();
            bool return1 = managedMatrixManager.InstantiateMatrix("matrixA", 60000, 60000);
            bool return2 = managedMatrixManager.InstantiateMatrix("matrixA", 60000, 60000);
            bool return3 = managedMatrixManager.InstantiateMatrix("matrixB", 60000, 20000);
            bool return4 = managedMatrixManager.InstantiateMatrix("matrixC", 90000, 90000);
        }
    }
}

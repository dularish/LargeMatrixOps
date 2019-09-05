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
            try
            {
                ManagedMatrixManager managedMatrixManager = new ManagedMatrixManager();
                //bool return1 = managedMatrixManager.InstantiateMatrix("matrixA", 60000, 60000);
                //bool return11 = managedMatrixManager.DeleteMatrix("matrixA");
                //bool return2 = managedMatrixManager.InstantiateMatrix("matrixA", 60000, 60000);
                //bool return3 = managedMatrixManager.InstantiateMatrix("matrixB", 60000, 20000);
                //bool return4 = managedMatrixManager.InstantiateMatrix("matrixC", 90000, 90000);
                bool return5 = managedMatrixManager.InstantiateMatrix("matrixA", 3, 3);
                managedMatrixManager.SetDataForRow("matrixA", 0, new List<double>() { 1, 2, 3 });
                var return52 = managedMatrixManager.GetDataForRow("matrixA", 0);

                string matrixB = "matrixB";
                bool return6 = managedMatrixManager.InstantiateMatrix(matrixB, 2, 3);
                managedMatrixManager.SetDataForRow(matrixB, 0, new List<double>() { 8,1,2});
                managedMatrixManager.SetDataForRow(matrixB, 1, new List<double>() { -5, 6, 7 });

                string matrixE = "matrixE";
                bool return7 = managedMatrixManager.InstantiateMatrix(matrixE, 3, 2);
                managedMatrixManager.SetDataForCol(matrixE, 0, new List<double>() { -5, 0, -11 });
                managedMatrixManager.SetDataForCol(matrixE, 1, new List<double>() { 1, 2, 7 });
                //Correct answer : -62 24 \n -52 56
                string matrixBE = "matrixBE";
                managedMatrixManager.MatrixMultiply(matrixB, matrixE, matrixBE);
                for (int i = 0; i < 2; i++)
                {
                    List<double> rowData = managedMatrixManager.GetDataForRow(matrixBE, i);
                    for (int j = 0; j < rowData.Count; j++)
                    {
                        Console.Write(rowData[j] + " ");
                    }
                    Console.WriteLine();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception caught : \nException Message :\n" + ex.Message + "\nException StackTrace : " + ex.StackTrace);
            }
        }
    }
}

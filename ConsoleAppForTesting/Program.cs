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
                //bool return1 = managedMatrixManager.InstantiateMatrix("matrixA", 60000, 60000);
                //bool return11 = managedMatrixManager.DeleteMatrix("matrixA");
                //bool return2 = managedMatrixManager.InstantiateMatrix("matrixA", 60000, 60000);
                //bool return3 = managedMatrixManager.InstantiateMatrix("matrixB", 60000, 20000);
                //bool return4 = managedMatrixManager.InstantiateMatrix("matrixC", 90000, 90000);

                //tryInstantiatingAMatrixLocally(managedMatrixManager);

                //tryInstantiatingAMatrixWithoutUsing();
                //ManagedMatrixPtr managedMatrix = new ManagedMatrixPtr(60000, 60000);

                var matrixA = new ManagedMatrixPtr(3, 3, GCSetting.CollectOnlyIfNecessary);
                matrixA.setDataForRow(0, new List<double>() { 1, 2, 3 });
                var return52 = matrixA.getDataForRow(0);

                var matrixB = new ManagedMatrixPtr(2, 3, GCSetting.CollectOnlyIfNecessary);
                matrixB.setDataForRow(0, new List<double>() { 8,1,2});
                matrixB.setDataForRow(1, new List<double>() { -5, 6, 7 });

                var matrixE = new ManagedMatrixPtr(3, 2, GCSetting.CollectOnlyIfNecessary);
                matrixE.setDataForCol(0, new List<double>() { -5, 0, -11 });
                matrixE.setDataForCol(1, new List<double>() { 1, 2, 7 });
                //Correct answer : -62 24 \n -52 56
                //var multipliedMatrix = ManagedMatrixPtr.product(new ManagedMatrixPtr(1000,10000), new ManagedMatrixPtr(1000, 1000));
                var matrixBE = ManagedMatrixPtr.product(matrixB, matrixE);
                for (int i = 0; i < 2; i++)
                {
                    List<double> rowData = matrixBE.getDataForRow(i);
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

        private static void tryInstantiatingAMatrixWithoutUsing()
        {
            ManagedMatrixPtr managedMatrix = new ManagedMatrixPtr(40000, 40000, GCSetting.CollectOnlyIfNecessary);
        }

        private static void tryInstantiatingAMatrixLocally()
        {
            string matrixName = "someMatrix";
            ManagedMatrixPtr managedMatrixPtr = new ManagedMatrixPtr(20000, 20000, GCSetting.CollectOnlyIfNecessary);
            ManagedMatrixPtr anotherManagedMatrixPtr = new ManagedMatrixPtr(40000, 40000, GCSetting.CollectOnlyIfNecessary);
            using (managedMatrixPtr)
            using (anotherManagedMatrixPtr)
            {
                string a = "";
            }

            using(ManagedMatrixPtr managedMatrix = new ManagedMatrixPtr(60000, 60000, GCSetting.CollectOnlyIfNecessary))
            {
                managedMatrix.set(30000, 30000, 5);
                managedMatrix.set(30001, 30001, 10);
                double value = managedMatrix.get(30000, 30000);
                double value1 = managedMatrix.get(30001, 30001);
                managedMatrix.set(30002, 30002, value + value1);
                double value2 = managedMatrix.get(30002, 30002);

                int a = 1;
            }

            //using (ManagedMatrixPtr managedMatrix = new ManagedMatrixPtr(90000, 90000))
            //{
            //    int a = 1;
            //}
        }
    }
}

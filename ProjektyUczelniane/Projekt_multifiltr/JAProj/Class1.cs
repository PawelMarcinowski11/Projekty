using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using JAProjDll2;

namespace JAProj
{


    public class AsmGauss : IFiltrAbstract
    {
        [DllImport("AsmDll.dll", CallingConvention = CallingConvention.StdCall)]
        private static extern byte Wagowy(int[] x, int[] w);

        public byte Filtruj(int[] tab)
        {
            int[] wagi = { 1, 2, 1,
                           2, 4, 2,
                           1, 2, 1 };
            return Wagowy(tab, wagi);
        }
    }

    public class AsmJednorodny : IFiltrAbstract
    {
        [DllImport("AsmDll.dll", CallingConvention = CallingConvention.StdCall)]
        private static extern byte Jednorodny(int[] x);
        public byte Filtruj(int[] tab)
        {
            return Jednorodny(tab);
        }
    }

    public class AsmSharpen : IFiltrAbstract
    {
        [DllImport("AsmDll.dll", CallingConvention = CallingConvention.StdCall)]
        private static extern byte WagowyBezBrzegow(int[] x, int[] w);
        public byte Filtruj(int[] tab)
        {
            int[] wagi = {-1,-1,-1,
                          -1, 9,-1,
                          -1,-1,-1 };
            return WagowyBezBrzegow(tab, wagi);
        }
    }

    public class AsmUwypuklajacy : IFiltrAbstract
    {
        [DllImport("AsmDll.dll", CallingConvention = CallingConvention.StdCall)]
        private static extern byte WagowyBezBrzegow(int[] x, int[] w);
        public byte Filtruj(int[] tab)
        {
            int[] wagi = { 0,-1,-1,
                           1, 1,-1,
                           1, 1, 0 };
            return WagowyBezBrzegow(tab, wagi);
        }
    }

    public class AsmPrewitt : IFiltrAbstract
    {
        [DllImport("AsmDll.dll", CallingConvention = CallingConvention.StdCall)]
        private static extern byte WagowyBezBrzegow(int[] x, int[] w);
        public byte Filtruj(int[] tab)
        {
            int[] wagi = { 0, 1, 2,
                          -1, 0, 1,
                          -2,-1, 0 };
            return WagowyBezBrzegow(tab, wagi);
        }
    }
}
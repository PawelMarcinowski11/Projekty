using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JAProjDll2
{
    public class Gauss : IFiltrAbstract
    {
        public byte Filtruj(int[] tab)
        {
            int waga = 0;
            int wartosc = 0;

            int[] wagi = { 1, 2, 1,
                           2, 4, 2,
                           1, 2, 1 };

            for (int i = 0; i < 9; i++)
            {
                if (tab[i] != -1)
                {
                    waga += wagi[i];
                    wartosc += tab[i] * wagi[i];
                }
            }

            return (byte)(wartosc / waga);
        }
    }

    public class Uwypuklajacy : IFiltrAbstract
    {
        public byte Filtruj(int[] tab)
        {
            int wartosc = 0;
            int[] wagi = { 0,-1,-1,
                           1, 1,-1,
                           1, 1, 0 };
            for (int i = 0; i < 9; i++)
            {
                if (tab[i] == -1) //jeśli piksel znajduje się przy krawędzi, nie modyfikujemy go
                    return (byte)tab[4];
                else
                {
                    wartosc += tab[i] * wagi[i];
                }
            }


            if (wartosc < 0)
                wartosc = 0;

            if (wartosc > 255)
                wartosc = 255;

            return (byte)(wartosc);
        }
    }

    public class Prewitt : IFiltrAbstract
    {
        public byte Filtruj(int[] tab)
        {
            int wartosc = 0;

            int[] wagi = { 0, 1, 2,
                          -1, 0, 1,
                          -2,-1, 0 };

            for (int i = 0; i < 9; i++)
            {
                if (tab[i] == -1) //jeśli piksel znajduje się przy krawędzi, nie modyfikujemy go
                    return (byte)tab[4];
                else
                {
                    wartosc += tab[i] * wagi[i];
                }
            }

            if (wartosc < 0)
                wartosc = 0;

            if (wartosc > 255)
                wartosc = 255;

            return (byte)(wartosc);
        }
    }

    public class Sharpen : IFiltrAbstract
    {
        public byte Filtruj(int[] tab)
        {
            int[] wagi = {-1,-1,-1,
                          -1, 9,-1,
                          -1,-1,-1 };

            int waga = 0;
            int wartosc = 0;

            for (int i = 0; i < 9; i++)
            {
                if (tab[i] == -1) //jeśli piksel znajduje się przy krawędzi, nie modyfikujemy go
                    return (byte)tab[4];
                else
                {
                    waga += wagi[i];
                    wartosc += tab[i] * wagi[i];
                }
            }

            if (wartosc < 0)
                wartosc = 0;

            if (wartosc > 255)
                return 255;

            return (byte)(wartosc / waga);
        }
    }

    public class Jednorodny : IFiltrAbstract
    {
        public byte Filtruj(int[] tab)
        {

            int waga = 0;
            int wartosc = 0;

            for (int i = 0; i < 9; i++)
            {
                if (tab[i] != -1)
                {
                    waga += 1;
                    wartosc += tab[i];
                }
            }

            return (byte)(wartosc / waga);
        }
    }
}
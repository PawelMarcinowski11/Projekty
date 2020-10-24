using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JAProj
{
    public class Gauss : IFiltrAbstract
    {
        public byte Filtruj(int[] tab)
        {
            int waga = 0;
            int wartosc = 0;

            if (tab[0] != -1)
            {
                waga += 1;
                wartosc += tab[0];
            }

            if (tab[1] != -1)
            {
                waga += 2;
                wartosc += tab[1] * 2;
            }

            if (tab[2] != -1)
            {
                waga += 1;
                wartosc += tab[2];
            }


            if (tab[3] != -1)
            {
                waga += 2;
                wartosc += tab[3] * 2;
            }

            if (tab[4] != -1)
            {
                waga += 4;
                wartosc += tab[4] * 4;
            }

            if (tab[5] != -1)
            {
                waga += 2;
                wartosc += tab[5] * 2;
            }


            if (tab[6] != -1)
            {
                waga += 1;
                wartosc += tab[6];
            }

            if (tab[7] != -1)
            {
                waga += 2;
                wartosc += tab[7] * 2;
            }

            if (tab[8] != -1)
            {
                waga += 1;
                wartosc += tab[8];
            }

            //return (byte)tab[4];

            return (byte)(wartosc / waga);
        }
    }

    public class Uwypuklajacy : IFiltrAbstract
    {
        public byte Filtruj(int[] tab)
        {
            int wartosc = 0;

            if (tab[1] != -1)
            {
                wartosc -= tab[1];
            }

            if (tab[2] != -1)
            {
                wartosc -= tab[2];
            }

            if (tab[3] != -1)
            {
                wartosc += tab[3];
            }

            if (tab[4] != -1)
            {
                wartosc += tab[4];
            }

            if (tab[5] != -1)
            {
                wartosc -= tab[5];
            }

            if (tab[6] != -1)
            {
                wartosc += tab[6];
            }

            if (tab[7] != -1)
            {
                wartosc += tab[7];
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

            if (tab[1] != -1)
            {
                wartosc += tab[1];
            }

            if (tab[2] != -1)
            {
                wartosc += tab[2] * 2;
            }

            if (tab[3] != -1)
            {
                wartosc -= tab[3];
            }

            if (tab[5] != -1)
            {
                wartosc += tab[5];
            }

            if (tab[6] != -1)
            {
                wartosc -= tab[6] * 2;
            }

            if (tab[7] != -1)
            {
                wartosc -= tab[7];
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
            int waga = 0;
            int wartosc = 0;

            if (tab[0] != -1)
            {
                waga -= 1;
                wartosc -= tab[0];
            }

            if (tab[1] != -1)
            {
                waga -= 1;
                wartosc -= tab[1];
            }

            if (tab[2] != -1)
            {
                waga -= 1;
                wartosc -= tab[1];
            }

            if (tab[3] != -1)
            {
                waga -= 1;
                wartosc -= tab[3];
            }

            if (tab[4] != -1)
            {
                waga += 9;
                wartosc += tab[4] * 9;
            }

            if (tab[5] != -1)
            {
                waga -= 1;
                wartosc -= tab[5];
            }


            if (tab[6] != -1)
            {
                waga -= 1;
                wartosc -= tab[6];
            }

            if (tab[7] != -1)
            {
                waga -= 1;
                wartosc -= tab[7];
            }

            if (tab[8] != -1)
            {
                waga -= 1;
                wartosc -= tab[8];
            }


            if (wartosc < 0)
                wartosc = 0;

            if (wartosc > 255)
                wartosc = 255;

            return (byte)(wartosc / waga);
        }
    }

    public class Jednorodny : IFiltrAbstract
    {
        public byte Filtruj(int[] tab)
        {
            int waga = 0;
            int wartosc = 0;

            if (tab[0] != -1)
            {
                waga += 1;
                wartosc += tab[0];
            }

            if (tab[1] != -1)
            {
                waga += 1;
                wartosc += tab[1];
            }

            if (tab[2] != -1)
            {
                waga += 1;
                wartosc += tab[2];
            }


            if (tab[3] != -1)
            {
                waga += 1;
                wartosc += tab[3];
            }

            if (tab[4] != -1)
            {
                waga += 1;
                wartosc += tab[4];
            }

            if (tab[5] != -1)
            {
                waga += 1;
                wartosc += tab[5];
            }


            if (tab[6] != -1)
            {
                waga += 1;
                wartosc += tab[6];
            }

            if (tab[7] != -1)
            {
                waga += 1;
                wartosc += tab[7];
            }

            if (tab[8] != -1)
            {
                waga += 1;
                wartosc += tab[8];
            }


            //return (byte)tab[4];

            return (byte)(wartosc / waga);
        }
    }
}
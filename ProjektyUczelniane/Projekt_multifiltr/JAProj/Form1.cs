using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.Design;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.ComTypes;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.VisualStyles;
using System.Xml;
using System.Xml.Schema;
using JAProjDll2;


namespace JAProj
{

    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {


        }
        //public MemoryStream xx = new MemoryStream();
        //public FileStream zz;

        public int w;
        public int h;
        public int d;
        public int offset;
        public int korekta;
        public byte[,,] tab;
        public FileStream zz;
        //public string dir;
        public string filename;



        private void button1_Click(object sender, EventArgs e)
        {
            //int[] testowe = { 0,1,2,3,4,5,6,7,8 };
            //byte x = MyProc1(testowe);

            string filePath;

            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.Filter = "Pliki bmp (*.bmp)|*.bmp";
                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    filename = openFileDialog.FileName;
                    filePath = filename;
                    //dir = filename.Remove(filename.LastIndexOf("\\"));

                    if (zz != null)
                        zz.Dispose(); //Przed otworzeniem nowego pliku, odłączam się od poprzedniego

                    zz = File.OpenRead(filePath);
                }
                else
                    return;
            }
            //zz = File.OpenRead("E:/Users/pawel/source/repos/JAProj/JAProj/Bitmap1.bmp");


            zz.Seek(18, 0);
            byte[] Width = new byte[4];
            zz.Read(Width, 0, 4);
            w = BitConverter.ToInt32(Width, 0);

            byte[] Height = new byte[4];
            zz.Read(Height, 0, 4);
            h = BitConverter.ToInt32(Height, 0);

            zz.Seek(28, 0);
            byte[] Depth = new byte[4];
            zz.Read(Depth, 0, 2);
            d = BitConverter.ToInt32(Depth, 0) / 8;

            zz.Seek(10, 0);
            byte[] Offset = new byte[4];
            zz.Read(Offset, 0, 4);
            offset = BitConverter.ToInt32(Offset, 0);
            zz.Seek(offset, 0);
            tab = new byte[h, w, d];

            //zapełnianie tablicy

            korekta = 0;

            if ((w * d) % 4 != 0)
                korekta = 4 - (w * d) % 4;

            for (int i = 0; i < h; i++)
            {
                for (int j = 0; j < w; j++)
                {
                    for (int z = 0; z < d; z++)
                    {
                        tab[i, j, z] = (byte)zz.ReadByte();
                    }

                    if (j + 1 == w)
                    {
                        for (int g = korekta; g > 0; g--)
                        {
                            zz.ReadByte();
                        }

                    }
                }
            }


            preview.Image = Image.FromStream(zz);



        }

        private void pictureBox4_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {

            Stopwatch stopWatch = new Stopwatch();
            stopWatch.Start();

            if (radioButton1.Checked)
            {
                if (sharpen.Checked)
                filtr1.Image = zastosujFiltr(new Sharpen());
            if (gauss.Checked)
                filtr2.Image = zastosujFiltr(new Gauss());
            if (uwypuklenie.Checked)
                filtr4.Image = zastosujFiltr(new Uwypuklajacy());
            if (usredniajacy.Checked)
                filtr3.Image = zastosujFiltr(new Jednorodny());
            if (prewitt.Checked)
                filtr5.Image = zastosujFiltr(new Prewitt());
            }

            if (radioButton2.Checked)
            {
                if (sharpen.Checked)
                    filtr1.Image = zastosujFiltr(new AsmSharpen());
                if (gauss.Checked)
                    filtr2.Image = zastosujFiltr(new AsmGauss());
                if (uwypuklenie.Checked)
                    filtr4.Image = zastosujFiltr(new AsmUwypuklajacy());
                if (usredniajacy.Checked)
                    filtr3.Image = zastosujFiltr(new AsmJednorodny());
                if (prewitt.Checked)
                    filtr5.Image = zastosujFiltr(new AsmPrewitt());
            }

            stopWatch.Stop();
            label2.Text = "Czas wykonania operacji: " + stopWatch.ElapsedMilliseconds + "ms";
            stopWatch.Reset();
        }

        private void button3_Click(object sender, EventArgs e)
        {

            Stopwatch stopWatch = new Stopwatch();
            stopWatch.Start();

            if (radioButton1.Checked)
            {
                filtr1.Image = zastosujFiltr(new Sharpen());
                filtr2.Image = zastosujFiltr(new Gauss());
                filtr4.Image = zastosujFiltr(new Uwypuklajacy());
                filtr3.Image = zastosujFiltr(new Jednorodny());
                filtr5.Image = zastosujFiltr(new Prewitt());
            }
            if (radioButton2.Checked)
            {
                filtr1.Image = zastosujFiltr(new AsmSharpen());
                filtr2.Image = zastosujFiltr(new AsmGauss());
                filtr4.Image = zastosujFiltr(new AsmUwypuklajacy());
                filtr3.Image = zastosujFiltr(new AsmJednorodny());
                filtr5.Image = zastosujFiltr(new AsmPrewitt());
            }
            stopWatch.Stop();
            label2.Text = "Czas wykonania operacji: " + stopWatch.ElapsedMilliseconds + "ms";
            stopWatch.Reset();
        }




        private Image zastosujFiltr(IFiltrAbstract filtr)
        {
            if (zz == null)
                return null;

            byte[] tab_flat;// = new byte[w * h * d];
            tab_flat = Wykonaj(tab, h, w, d, filtr);
            //zapisywanie tablicy
            MemoryStream xx = new MemoryStream();
            zz.Seek(0, 0);
            //Wstawiam nagłówek bitmapy
            byte[] bufor = new byte[offset];
            zz.Read(bufor, 0, offset);
            xx.Write(bufor, 0, offset);
            //Wstawiam tablicę bitów reprezentującą piksele
            byte[] wiersz = new byte[w * d];
            for (int i = 0; i < h; i++)
            {
                Buffer.BlockCopy(tab_flat, w * d * i, wiersz, 0, w * d);
                xx.Write(wiersz, 0, wiersz.Length);
                for (int j = korekta; j > 0; j--)
                {
                    xx.WriteByte(0);
                }

            }
            return Image.FromStream(xx);
        }

        private int zapiszObraz(PictureBox pic, string filtername)
        {
            if (pic.Image != null)
            {
                using (SaveFileDialog saveFileDialog = new SaveFileDialog())
                {
                    saveFileDialog.FileName = filename.Remove(filename.Length - 4).Substring(filename.LastIndexOf('\\') + 1) + "_" + filtername;
                    saveFileDialog.Filter = "Pliki bmp (*.bmp)|*.bmp";
                    if (saveFileDialog.ShowDialog() == DialogResult.OK)
                    {
                        //Nie mogę zapisać używanej przez program bitmapy, więc tworzę jej kopię.
                        Bitmap temp = new Bitmap(pic.Image);
                        //Zapisuję utworzoną kopię.
                        temp.Save(saveFileDialog.FileName, ImageFormat.Bmp);
                        return 0;
                    }
                    else
                        return 2;
                }
            }
            else
                return 1;
        }


        private void Form1_Load(object sender, EventArgs e)
        {
            int t = Environment.ProcessorCount;
            trackBar1.Value = t;
            label1.Text = "Liczba wątków: " + t;
            ThreadPool.SetMinThreads(t, t);
            ThreadPool.SetMaxThreads(t, t);
            ThreadPool.SetMinThreads(t, t); //Jeśli zadana minimalna liczba wątków jest wyższa niż maksymalna, metoda nie zadziała - dlatego wywołuję ją dwukrotnie

        }

        private void button4_Click(object sender, EventArgs e)
        {
            zapiszObraz(filtr1, "Wyostrzony");
            zapiszObraz(filtr2, "FiltrGaussa");
            zapiszObraz(filtr3, "FiltrUsredniajacy");
            zapiszObraz(filtr4, "Uwypuklony");
            zapiszObraz(filtr5, "FiltrPrewitta");
        }

        private void button5_Click(object sender, EventArgs e)
        {
            zapiszObraz(filtr1, "Wyostrzony");
        }

        private void button6_Click(object sender, EventArgs e)
        {
            zapiszObraz(filtr2, "FiltrGaussa");
        }

        private void button7_Click(object sender, EventArgs e)
        {
            zapiszObraz(filtr3, "FiltrUsredniajacy");
        }

        private void button8_Click(object sender, EventArgs e)
        {
            zapiszObraz(filtr4, "Uwypuklony");
        }

        private void button9_Click(object sender, EventArgs e)
        {
            zapiszObraz(filtr5, "FiltrPrewitta");
        }

        //Ograniczam liczbę zadań oczekujących jednocześnie kolejce
        private static readonly Semaphore Semafora = new Semaphore(80, 80);

        static public byte[] Wykonaj(byte[,,] tab, int w, int h, int d, IFiltrAbstract filtr)
        {

            byte[] tab_flat = new byte[w * h * d];
            for (int i = 0; i < w; i++)
            {
                for (int j = 0; j < h; j++)
                {
                    Semafora.WaitOne();

                    int ip = i;
                    int jp = j;

                    ThreadPool.QueueUserWorkItem(
                    new WaitCallback(delegate (object state)
                    {
                        for (int z = 0; z < d; z++)
                        {
                            //int zp = z;

                            obsluzPiksel(ip, jp, z, w, h, d, tab, tab_flat, filtr);
                        }
                        Semafora.Release();
                    }), null);
                }
            }
            return tab_flat;
        }

        private static void obsluzPiksel(int i, int j, int z, int w, int h, int d, byte[,,] tab, byte[] tab_flat, IFiltrAbstract filtr)
        {
            int indeks = i * h * d + j * d + z;

            int[] najblizsze = new int[9];

            if (i != 0 && j != 0)
                najblizsze[0] = tab[i - 1, j - 1, z];
            else
                najblizsze[0] = -1;

            if (j != 0)
                najblizsze[1] = tab[i, j - 1, z];
            else
                najblizsze[1] = -1;

            if (i != w - 1 && j != 0)
                najblizsze[2] = tab[i + 1, j - 1, z];
            else
                najblizsze[2] = -1;

            if (i != 0)
                najblizsze[3] = tab[i - 1, j, z];
            else
                najblizsze[3] = -1;


            najblizsze[4] = tab[i, j, z];


            if (i != w - 1)
                najblizsze[5] = tab[i + 1, j, z];
            else
                najblizsze[5] = -1;


            if (i != 0 && j != h - 1)
                najblizsze[6] = tab[i - 1, j + 1, z];
            else
                najblizsze[6] = -1;

            if (j != h - 1)
                najblizsze[7] = tab[i, j + 1, z];
            else
                najblizsze[7] = -1;

            if (i != w - 1 && j != h - 1)
                najblizsze[8] = tab[i + 1, j + 1, z];
            else
                najblizsze[8] = -1;


            tab_flat[indeks] = filtr.Filtruj(najblizsze);

            //Wersja z try catch jest do niczego - korzystanie z niej morduje wydajność aplikacji

            //try { n[0] = tab[i - 1, j - 1, z]; } catch (IndexOutOfRangeException) { n[0] = -1; }
            //try { n[1] = tab[i, j - 1, z]; } catch (IndexOutOfRangeException) { n[1] = -1; }
            //try { n[2] = tab[i + 1, j - 1, z]; } catch (IndexOutOfRangeException) { n[2] = -1; }

            //try { n[3] = tab[i - 1, j, z]; } catch (IndexOutOfRangeException) { n[3] = -1; }
            //try { n[4] = tab[i, j, z]; } catch (IndexOutOfRangeException) { n[4] = -1; } //nigdy nie złapie wyjątku, ale nie zaszkodzi spróbować
            //try { n[5] = tab[i + 1, j, z]; } catch (IndexOutOfRangeException) { n[5] = -1; }

            //try { n[6] = tab[i - 1, j + 1, z]; } catch (IndexOutOfRangeException) { n[6] = -1; }
            //try { n[7] = tab[i, j + 1, z]; } catch (IndexOutOfRangeException) { n[7] = -1; }
            //try { n[8] = tab[i + 1, j + 1, z]; } catch (IndexOutOfRangeException) { n[8] = -1; }

            //tab_flat[i * h * d + j * d + z] = filtr.Filtruj(najblizsze);


            return;
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            label1.Text = "Liczba wątków: " + trackBar1.Value;
            ThreadPool.SetMinThreads(trackBar1.Value, trackBar1.Value);
            ThreadPool.SetMaxThreads(trackBar1.Value, trackBar1.Value);
            ThreadPool.SetMinThreads(trackBar1.Value, trackBar1.Value); //Jeśli zadana minimalna liczba wątków jest wyższa niż maksymalna, metoda nie zadziała - dlatego wywołuję ją dwukrotnie
        }
    }
}
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace shiyan1
{
    public partial class Form1 : Form
    {
        private int[,] graphBomb = new int[22, 22];
        private int[,] bombs = new int[22, 22];
        private int bombNum = 0;
        private const int EDGE = 32;
        private int flagNum = 0;
        private List<Tuple<int, int>> flags;
        public Form1()
        {
            InitializeComponent();
            InitBomb();
            //DrawBomb();

        }

        private void InitBomb()
        {
            int[,] dir = new int[2, 9] { { -1,-1,-1,0,0,0,1,1,1 },{ -1,0,1,-1,0,1,-1,0,1 } };
            Random random = new Random(1);
            bombNum = 50;
            flagNum = bombNum;
            flags = new List<Tuple<int, int>>(bombNum);

            while (bombNum > 0)
            {

                int x = random.Next(20);
                int y = random.Next(20);
                if (bombs[x, y] != 0) continue;
                bombs[x, y] = 1;
                bombNum--;
                for (int k = 0; k < 9; k++)
                {
                    if (x + dir[0, k] < 0 || x + dir[0, k] >= 20 || y + dir[1, k] < 0 || y + dir[1, k] >= 20)
                        continue;
                    graphBomb[x + dir[0, k], y+dir[1,k]] += 1;
                }

                //Console.WriteLine(x.ToString() +" "+y.ToString());
            }

            for (int i = 0; i < 20; i++)
            {
                for (int j = 0; j < 20; j++)
                {
                    if (bombs[i, j] > 0) graphBomb[i, j] = -1;
                    
                    //Console.Write(graphBomb[i,j]+"\t");
                }
                //Console.WriteLine();
            }
        }

        private void DrawBomb()
        {
            Graphics g = this.CreateGraphics();
            Pen mypen = new Pen(Color.Black, 2);
            Brush mybrush = new SolidBrush(Color.White);

            const int EDGE = 21;

            for (int i = 0; i < 20; i++)
            {
                for (int j = 0; j < 20; j++)
                {
                    g.DrawRectangle(mypen ,i * EDGE, j * EDGE, EDGE - 1, EDGE - 1);
                }
            }
            


        }
        

        private void Form1_KeyPress(object sender, KeyPressEventArgs e)
        {

        }

        private void Form1_MouseClick(object sender, MouseEventArgs e)
        {
            Console.WriteLine("mousedown:" + e.Location);
            int nx = e.X/EDGE;
            int ny = e.Y/EDGE;
            //Console.WriteLine(nx.ToString() + " " + ny.ToString());
            if(e.Button == MouseButtons.Right)
            {
                g.DrawString("X", font, Brushes.Black, nx * EDGE, ny * EDGE);
                flags.Add(new Tuple<int, int>(nx, ny));
                flagNum--;
                if(flagNum == 0)
                {
                    foreach(var x in flags)
                    {
                        if(bombs[x.Item1,x.Item2] <= 0)
                        {
                            return;
                        }
                    }
                    MessageBox.Show("you win");
                }
                return;
            }
            Brush mybrush3 = new SolidBrush(Color.Red);
            if (bombs[nx,ny] > 0)
            {
                for (int i = 0; i < 20; i++)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        if (bombs[i, j] > 0) g.FillRectangle(mybrush3, i * EDGE, j * EDGE, EDGE - 2, EDGE - 2);
                    }
                }
                MessageBox.Show("GAME OVER");
            }

            // can swap
            int[,] dir = new int[2, 8] { { -1, -1, -1, 0, 0, 1, 1, 1 }, { -1, 0, 1, -1, 1, -1, 0, 1 } };
            Queue<Tuple<int,int>> Q = new Queue<Tuple<int, int>>(500);
            Q.Enqueue(new Tuple<int, int>(nx,ny));
            while (Q.Count > 0)
            {
                Tuple<int, int> temp = Q.Dequeue();
                int x = temp.Item1, y = temp.Item2;
                bombs[x, y] = -1;
                //Console.WriteLine(x.ToString()+"_"+y.ToString());
                g.FillRectangle(mybrush2, x * EDGE, y * EDGE, EDGE - 2, EDGE - 2);
                g.DrawString(graphBomb[x, y].ToString(), font, Brushes.Black, x * EDGE, y * EDGE);
                if(graphBomb[x,y] != 0)
                {
                    continue;
                }

                // is zero
                for (int k = 0; k < 8; k++)
                {
                    if (x + dir[0, k] < 0 || x + dir[0, k] >= 20 || y + dir[1, k] < 0 || y + dir[1, k] >= 20 || bombs[x + dir[0, k], y + dir[1, k]] == -1)
                        continue;
                    bombs[x + dir[0, k], y + dir[1, k]] = -1;
                    Q.Enqueue(new Tuple<int, int>(x + dir[0, k], y + dir[1, k]));

                }
            }

        }

        private Graphics g;
        private Pen mypen;
        private Brush mybrush;
        private Brush mybrush2;
        private Font font = new Font("华为宋体", 16);
        private void label1_Paint(object sender, PaintEventArgs e)
        {
            if(this.g==null) this.g = this.CreateGraphics();
            if(this.mypen == null) this.mypen = new Pen(Color.Black, 2);
            if(this.mybrush == null) this.mybrush = new SolidBrush(Color.White);
            if(this.mybrush2 == null) this.mybrush2 = new SolidBrush(Color.Gray);


            for (int i = 0; i < 20; i++)
            {
                for (int j = 0; j < 20; j++)
                {
                    g.FillRectangle(mybrush, i * EDGE, j * EDGE, EDGE - 2, EDGE - 2);
                    //g.DrawString(graphBomb[i, j].ToString(), font, Brushes.Red, i * EDGE, j * EDGE);
                }
            }
        }
    }
}

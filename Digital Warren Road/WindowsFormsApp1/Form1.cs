using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        const int SIZE = 4;
        int[,] gridData = new int[SIZE + 2, SIZE + 2];
        PictureBox[,] pictures = new PictureBox[SIZE + 2, SIZE + 2];
        public Form1()
        {
            InitializeComponent();
            initData();
            initPicturBox();
        }

        /// <summary>
        /// 初始化矩阵数据
        /// </summary>
        public void initData()
        {
            Random random = new Random();
            List<int> tempVal = new List<int>();
            for (int i = 1; i < SIZE * SIZE; ++i)
            {
                tempVal.Add(i);
            }

            int relNumSize = SIZE * SIZE - 1;
            for (int i = 0; i < SIZE; ++i)
            {
                for (int j = 0; j < SIZE; ++j)
                {
                    if (i == 0 && j == 0) continue;
                    int tempIndex = random.Next(relNumSize);
                    gridData[i, j] = tempVal[tempIndex];
                    tempVal.RemoveAt(tempIndex);
                    relNumSize--;
                }
            }
            gridData[0, 0] = 0;
        }

        /// <summary>
        /// 初始化图片
        /// </summary>
        public void initPicturBox()
        {
            pictures = new PictureBox[SIZE, SIZE];
            for (int i = 0; i < SIZE; ++i)
            {
                for (int j = 0; j < SIZE; ++j)
                {
                    pictures[i, j] = new PictureBox();
                    pictures[i, j].BackgroundImageLayout = ImageLayout.Stretch;
                    pictures[i, j].SizeMode = PictureBoxSizeMode.StretchImage;
                    pictures[i, j].Location = new Point(65 * j, 65 * i); //xy坐标是反着的
                    pictures[i, j].Size = new Size(63, 63);
                    pictures[i, j].MouseDown += new MouseEventHandler(this.Click2Exchange);
                    if (i != 0 || j != 0)
                    {
                        pictures[i, j].Image = (Image)Properties.Resources.ResourceManager.GetObject("_" + gridData[i,j]);
                    }
                    this.Controls.Add(pictures[i, j]);
                }
            }
        }

        /// <summary>
        /// 点击图片位置进行移动
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Click2Exchange(object sender, MouseEventArgs e)
        {
            int x = ((PictureBox)sender).Location.X / 65;
            int y = ((PictureBox)sender).Location.Y / 65;
            Console.WriteLine("pos:{0}, {1}", x, y);
            int[,] dir = { { 1, 0 },{ -1, 0 },{ 0, 1 },{ 0, -1 } }; 
            for (int i = 0; i < 4; ++i)
            {
                int cx = x + dir[i,0], cy = y + dir[i,1];
                if (cx >= 0 && cx < SIZE && cy >= 0 && cy < SIZE && gridData[cy, cx] == 0)
                {
                    pictures[y, x].Image = (Image)Properties.Resources.ResourceManager.GetObject("_0");
                    pictures[cy, cx].Image = (Image)Properties.Resources.ResourceManager.GetObject("_" + gridData[y, x]);
                    gridData[cy, cx] = gridData[y, x];
                    gridData[y, x] = 0;
                    break;
                }
            }
        }
    }
}

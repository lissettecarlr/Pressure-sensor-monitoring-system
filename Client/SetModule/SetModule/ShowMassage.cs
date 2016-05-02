using MySql.Data.MySqlClient;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SetModule
{
    public partial class ShowMassage : Form
    {
        private bool state = false;//是否开始监控标志位
        private Form temp;
        public ShowMassage(Form sw)
        {
            InitializeComponent();
            temp = sw;
        }

        private void button_back_Click(object sender, EventArgs e)
        {
            this.Close();
            temp.Show();
        }

        string connstr = System.Configuration.ConfigurationManager.ConnectionStrings["myconn"].ConnectionString;
        MySqlConnection mycon;
        MySqlCommand mycmd;
        MySqlDataAdapter da;
        DataTable dt;

        private void ShowMassage_Load(object sender, EventArgs e)
        {
            dataGridView1.AllowUserToAddRows = false;
            MySqlConnection mycon = new MySqlConnection(connstr);
            try
            {
                mycon.Open();
                mycmd = new MySqlCommand("SELECT * FROM `message`", mycon);
                da = new MySqlDataAdapter(mycmd);
                dt = new DataTable();
                da.Fill(dt);
                dataGridView1.DataSource = dt;
            }
            catch
            {
            }
            finally
            {
                //mycon.Close();
            }
            ThreadStart ts = new ThreadStart(Method);
            Thread t = new Thread(ts);
            t.Start();

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
        }

        void Method()
        {
            //更新线程
            while (true)
            {
                if (state)
                {
                    dt = new DataTable();
                    da.Fill(dt);
                    //Console.Write(11);
                    System.Threading.Thread.Sleep(900);
                }
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            //定时器事件
            if (state)
            {
                try
                {
                    //mycon.Open();
                    //dt = new DataTable();
                    //da.Fill(dt);
                    dataGridView1.DataSource = dt;//更新UI
                }
                catch
                {
                }
                finally
                {
                    //mycon.Close();
                }
            }
        }

        private void textBox_bed_KeyPress(object sender, KeyPressEventArgs e)
        {
            //限制输入只能为整数
            char result = e.KeyChar;
            if (char.IsDigit(result) || result == 8)
            {
                e.Handled = false;
            }
            else
            {
                e.Handled = true;
            }
        }

        private void ShowMassage_FormClosing(object sender, FormClosingEventArgs e)
        {
            if(mycon !=null)
            if(mycon.State == ConnectionState.Open)
            mycon.Close();//关闭数据库
            temp.Show();
        }

        private void button_start_Click(object sender, EventArgs e)
        {
            state = true;
            label_state.Text = "开始监控";
        }

        private void button_close_Click(object sender, EventArgs e)
        {
            state = false;
            label_state.Text = "停止监控";
        }
    }
}

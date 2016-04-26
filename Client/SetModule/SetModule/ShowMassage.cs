using MySql.Data.MySqlClient;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SetModule
{
    public partial class ShowMassage : Form
    {
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

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            //定时器事件
            try
            {
                //mycon.Open();
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
        }
    }
}

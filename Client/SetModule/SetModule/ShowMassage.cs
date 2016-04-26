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

        private void ShowMassage_Load(object sender, EventArgs e)
        {
            string connstr = System.Configuration.ConfigurationManager.ConnectionStrings["myconn"].ConnectionString;
            MySqlConnection mycon = new MySqlConnection(connstr);
            try
            {
               
                mycon.Open();
                MySqlCommand mycmd = new MySqlCommand("SELECT * FROM `message`", mycon);
                //mycmd.Parameters.AddWithValue("@username", txtusername.Text);
                //mycmd.Parameters.AddWithValue("@pwd", txtpassword.Text);
                MySqlDataAdapter da = new MySqlDataAdapter(mycmd);
                DataTable dt = new DataTable();
                da.Fill(dt);

                for (int i = 0; i < dt.Rows.Count; i++)
                {
                    for (int j = 0; j < dt.Columns.Count; j++)
                    {
                        richTextBox1.AppendText(dt.Rows[i][j].ToString() + "     ");
                    }
                    richTextBox1.AppendText("\r\n");
                }

            }
            catch
            {

            }
            finally
            {
                mycon.Close();
            }

        }
    }
}

//遍历
//for (int i = 0; i < dataTable.Rows.Count; i++)
//{
//    //for (int j = 0; j < dataTable.Columns.Count; j++)
//    //{
//        richTextBox1.AppendText( dataTable.Rows[i][0].ToString()+"     ");
//    //}
//} 

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
  
    public partial class SetSth : Form
    {
        private Form temp;
        Thread th1; //读取线程
        string str; //保存读取的字符串
        public delegate void GetTextHandler();

        public SetSth(Form sw)
        {
            InitializeComponent();
            temp = sw;   
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
            temp.Show();    
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {

        }

        private void Button_clearShow_Click(object sender, EventArgs e)
        {
            richTextBox_show.Clear();
        }

        private void SetSth_Load(object sender, EventArgs e)
        {
            //在开启界面的时候建立新线程，实行run方法
            th1 = new Thread(new ThreadStart(this.Run));
            th1.Start();
        }

        private void Run()
        {
            byte[] temp = new byte[1];
            while (true)
            {
                if (serialCom1.ReadBytes(ref temp, 1))
                {
                    str = System.Text.Encoding.Default.GetString(temp);
                    richTextBox_show.Invoke(new GetTextHandler(updataRvcUI));
                }
                
            }
        }
        private void updataRvcUI() //UI更新函数
        {
            richTextBox_show.AppendText(str);
            richTextBox_show.ScrollToCaret();
        }

        private void button_ClearWIFI_Click(object sender, EventArgs e)
        {
            byte[] ClearWIFI = new byte[6];
            ClearWIFI[0] = 0xaa;
            ClearWIFI[1] = 0xcc;
            ClearWIFI[2] = 0x01;
            ClearWIFI[3] = 0x03;
            ClearWIFI[4] = 0xff;
            ClearWIFI[5] = 0;
            for(int i=0;i<5;i++)
            {
                ClearWIFI[5] += ClearWIFI[i];
            }
            serialCom1.SendBytes(ClearWIFI, ClearWIFI.Length);

        }

        private void button_rst_Click(object sender, EventArgs e)
        {
            byte[] RST = new byte[6];
            RST[0] = 0xaa;
            RST[1] = 0xcc;
            RST[2] = 0x01;
            RST[3] = 0xff;
            RST[4] = 0xff;
            RST[5] = 0;
            for (int i = 0; i < 5; i++)
            {
                RST[5] += RST[i];
            }
            serialCom1.SendBytes(RST, RST.Length);
        }

        private void button_sendWIFI_Click(object sender, EventArgs e)
        {
            //发送下载wifi的命令
            byte[] downWIFI = new byte[6];
            downWIFI[0] = 0xaa;
            downWIFI[1] = 0xcc;
            downWIFI[2] = 0x01;
            downWIFI[3] = 0x01;
            downWIFI[4] = 0xff;
            downWIFI[5] = 0;
            for (int i = 0; i < 5; i++)
            {
                downWIFI[5] += downWIFI[i];
            }
            serialCom1.SendBytes(downWIFI, downWIFI.Length);

            //发送WIFI消息

            string name = textBox_wifiName.Text.ToString();
            string password = textBox_wifiPassword.Text.ToString();

            byte[] message = new byte[4 + name.Length+password.Length];
            message[0] = 0xff;
            message[1] = 0x03;

            byte[] name_byte = Encoding.ASCII.GetBytes(name);
            byte[] pwd_byte = Encoding.ASCII.GetBytes(password);

            for(int i=0;i<name_byte.Length;i++)
            {
                message[i + 2] = name_byte[i];
            }

            message[2 + name_byte.Length ] = 0xff;

            for (int i = 0; i < pwd_byte.Length; i++)
            {
                message[i + 2 + name_byte.Length +1] = pwd_byte[i];
            }
            message[pwd_byte.Length + 2 + name_byte.Length + 1] = 0xff;
            serialCom1.SendBytes(message, message.Length);

            label_WIFIname.Text = name;

        }

        private void button_SetThreshold_Click(object sender, EventArgs e)
        {
            //设置离床阀值

            int threshold_int = int.Parse(textBox_threshold.Text);
            if (threshold_int > 255)
                return ;
            byte[] threshold_byte = System.BitConverter.GetBytes(threshold_int);


            byte[] SetThreshold = new byte[6];
            SetThreshold[0] = 0xaa;
            SetThreshold[1] = 0xcc;
            SetThreshold[2] = 0x01;
            SetThreshold[3] = 0x02;
            SetThreshold[4] = threshold_byte[0];
            SetThreshold[5] = 0;
            for (int i = 0; i < 5; i++)
            {
                SetThreshold[5] += SetThreshold[i];
            }
            serialCom1.SendBytes(SetThreshold, 1);
            label_connetState.Text = textBox_threshold.Text;
        }



        private void textBox_threshold_KeyPress(object sender, KeyPressEventArgs e)
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
    }
}

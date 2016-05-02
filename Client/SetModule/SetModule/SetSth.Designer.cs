namespace SetModule
{
    partial class SetSth
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.button_back = new System.Windows.Forms.Button();
            this.serialCom1 = new SerialControl.SerialCom();
            this.richTextBox_show = new System.Windows.Forms.RichTextBox();
            this.Button_clearShow = new System.Windows.Forms.Button();
            this.button_ClearWIFI = new System.Windows.Forms.Button();
            this.button_rst = new System.Windows.Forms.Button();
            this.textBox_wifiName = new System.Windows.Forms.TextBox();
            this.textBox_wifiPassword = new System.Windows.Forms.TextBox();
            this.button_sendWIFI = new System.Windows.Forms.Button();
            this.button_SetThreshold = new System.Windows.Forms.Button();
            this.textBox_threshold = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label_connetState = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label_WIFIname = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // button_back
            // 
            this.button_back.Location = new System.Drawing.Point(365, 234);
            this.button_back.Name = "button_back";
            this.button_back.Size = new System.Drawing.Size(87, 30);
            this.button_back.TabIndex = 0;
            this.button_back.Text = "返回首页";
            this.button_back.UseVisualStyleBackColor = true;
            this.button_back.Click += new System.EventHandler(this.button1_Click);
            // 
            // serialCom1
            // 
            this.serialCom1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.serialCom1.Location = new System.Drawing.Point(12, 13);
            this.serialCom1.Name = "serialCom1";
            this.serialCom1.Size = new System.Drawing.Size(303, 205);
            this.serialCom1.TabIndex = 1;
            // 
            // richTextBox_show
            // 
            this.richTextBox_show.Location = new System.Drawing.Point(321, 13);
            this.richTextBox_show.Name = "richTextBox_show";
            this.richTextBox_show.Size = new System.Drawing.Size(301, 205);
            this.richTextBox_show.TabIndex = 2;
            this.richTextBox_show.Text = "";
            // 
            // Button_clearShow
            // 
            this.Button_clearShow.Location = new System.Drawing.Point(518, 234);
            this.Button_clearShow.Name = "Button_clearShow";
            this.Button_clearShow.Size = new System.Drawing.Size(87, 30);
            this.Button_clearShow.TabIndex = 3;
            this.Button_clearShow.Text = "清空显示";
            this.Button_clearShow.UseVisualStyleBackColor = true;
            this.Button_clearShow.Click += new System.EventHandler(this.Button_clearShow_Click);
            // 
            // button_ClearWIFI
            // 
            this.button_ClearWIFI.Location = new System.Drawing.Point(12, 234);
            this.button_ClearWIFI.Name = "button_ClearWIFI";
            this.button_ClearWIFI.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.button_ClearWIFI.Size = new System.Drawing.Size(87, 30);
            this.button_ClearWIFI.TabIndex = 4;
            this.button_ClearWIFI.Text = "清空wifi信息";
            this.button_ClearWIFI.UseVisualStyleBackColor = true;
            this.button_ClearWIFI.Click += new System.EventHandler(this.button_ClearWIFI_Click);
            // 
            // button_rst
            // 
            this.button_rst.Location = new System.Drawing.Point(199, 234);
            this.button_rst.Name = "button_rst";
            this.button_rst.Size = new System.Drawing.Size(87, 30);
            this.button_rst.TabIndex = 5;
            this.button_rst.Text = "重启下位机";
            this.button_rst.UseVisualStyleBackColor = true;
            this.button_rst.Click += new System.EventHandler(this.button_rst_Click);
            // 
            // textBox_wifiName
            // 
            this.textBox_wifiName.Location = new System.Drawing.Point(120, 282);
            this.textBox_wifiName.Name = "textBox_wifiName";
            this.textBox_wifiName.Size = new System.Drawing.Size(197, 21);
            this.textBox_wifiName.TabIndex = 6;
            // 
            // textBox_wifiPassword
            // 
            this.textBox_wifiPassword.Location = new System.Drawing.Point(120, 319);
            this.textBox_wifiPassword.Name = "textBox_wifiPassword";
            this.textBox_wifiPassword.Size = new System.Drawing.Size(197, 21);
            this.textBox_wifiPassword.TabIndex = 7;
            // 
            // button_sendWIFI
            // 
            this.button_sendWIFI.Location = new System.Drawing.Point(12, 282);
            this.button_sendWIFI.Name = "button_sendWIFI";
            this.button_sendWIFI.Size = new System.Drawing.Size(87, 58);
            this.button_sendWIFI.TabIndex = 8;
            this.button_sendWIFI.Text = "发送WIFI的 名字和密码";
            this.button_sendWIFI.UseVisualStyleBackColor = true;
            this.button_sendWIFI.Click += new System.EventHandler(this.button_sendWIFI_Click);
            // 
            // button_SetThreshold
            // 
            this.button_SetThreshold.Location = new System.Drawing.Point(333, 282);
            this.button_SetThreshold.Name = "button_SetThreshold";
            this.button_SetThreshold.Size = new System.Drawing.Size(84, 23);
            this.button_SetThreshold.TabIndex = 9;
            this.button_SetThreshold.Text = "设置阀值";
            this.button_SetThreshold.UseVisualStyleBackColor = true;
            this.button_SetThreshold.Click += new System.EventHandler(this.button_SetThreshold_Click);
            // 
            // textBox_threshold
            // 
            this.textBox_threshold.Location = new System.Drawing.Point(432, 282);
            this.textBox_threshold.Name = "textBox_threshold";
            this.textBox_threshold.Size = new System.Drawing.Size(87, 21);
            this.textBox_threshold.TabIndex = 10;
            this.textBox_threshold.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_threshold_KeyPress);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(525, 285);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(107, 12);
            this.label1.TabIndex = 11;
            this.label1.Text = "阀值范围（1-255）";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(504, 328);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(71, 12);
            this.label2.TabIndex = 12;
            this.label2.Text = "已发送阀值:";
            // 
            // label_connetState
            // 
            this.label_connetState.AutoSize = true;
            this.label_connetState.Location = new System.Drawing.Point(581, 328);
            this.label_connetState.Name = "label_connetState";
            this.label_connetState.Size = new System.Drawing.Size(41, 12);
            this.label_connetState.TabIndex = 13;
            this.label_connetState.Text = "不知道";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(333, 326);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(71, 12);
            this.label4.TabIndex = 14;
            this.label4.Text = "已发送WIFI:";
            // 
            // label_WIFIname
            // 
            this.label_WIFIname.AutoSize = true;
            this.label_WIFIname.Location = new System.Drawing.Point(399, 326);
            this.label_WIFIname.Name = "label_WIFIname";
            this.label_WIFIname.Size = new System.Drawing.Size(53, 12);
            this.label_WIFIname.TabIndex = 15;
            this.label_WIFIname.Text = "啥都没发";
            // 
            // SetSth
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(634, 361);
            this.Controls.Add(this.label_WIFIname);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label_connetState);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBox_threshold);
            this.Controls.Add(this.button_SetThreshold);
            this.Controls.Add(this.button_sendWIFI);
            this.Controls.Add(this.textBox_wifiPassword);
            this.Controls.Add(this.textBox_wifiName);
            this.Controls.Add(this.button_rst);
            this.Controls.Add(this.button_ClearWIFI);
            this.Controls.Add(this.Button_clearShow);
            this.Controls.Add(this.richTextBox_show);
            this.Controls.Add(this.serialCom1);
            this.Controls.Add(this.button_back);
            this.Name = "SetSth";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "SetSth";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.SetSth_FormClosing);
            this.Load += new System.EventHandler(this.SetSth_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button_back;
        private SerialControl.SerialCom serialCom1;
        private System.Windows.Forms.RichTextBox richTextBox_show;
        private System.Windows.Forms.Button Button_clearShow;
        private System.Windows.Forms.Button button_ClearWIFI;
        private System.Windows.Forms.Button button_rst;
        private System.Windows.Forms.TextBox textBox_wifiName;
        private System.Windows.Forms.TextBox textBox_wifiPassword;
        private System.Windows.Forms.Button button_sendWIFI;
        private System.Windows.Forms.Button button_SetThreshold;
        private System.Windows.Forms.TextBox textBox_threshold;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label_connetState;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label_WIFIname;
    }
}
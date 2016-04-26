namespace SetModule
{
    partial class ShowMassage
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
            this.components = new System.ComponentModel.Container();
            this.button_back = new System.Windows.Forms.Button();
            this.button_bed = new System.Windows.Forms.Button();
            this.textBox_bed = new System.Windows.Forms.TextBox();
            this.button_clear = new System.Windows.Forms.Button();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.timer = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // button_back
            // 
            this.button_back.Location = new System.Drawing.Point(527, 305);
            this.button_back.Name = "button_back";
            this.button_back.Size = new System.Drawing.Size(82, 35);
            this.button_back.TabIndex = 0;
            this.button_back.Text = "返回";
            this.button_back.UseVisualStyleBackColor = true;
            this.button_back.Click += new System.EventHandler(this.button_back_Click);
            // 
            // button_bed
            // 
            this.button_bed.Location = new System.Drawing.Point(26, 23);
            this.button_bed.Name = "button_bed";
            this.button_bed.Size = new System.Drawing.Size(106, 23);
            this.button_bed.TabIndex = 2;
            this.button_bed.Text = "显示该床号信息";
            this.button_bed.UseVisualStyleBackColor = true;
            // 
            // textBox_bed
            // 
            this.textBox_bed.Location = new System.Drawing.Point(153, 24);
            this.textBox_bed.Name = "textBox_bed";
            this.textBox_bed.Size = new System.Drawing.Size(61, 21);
            this.textBox_bed.TabIndex = 3;
            // 
            // button_clear
            // 
            this.button_clear.Location = new System.Drawing.Point(527, 246);
            this.button_clear.Name = "button_clear";
            this.button_clear.Size = new System.Drawing.Size(82, 35);
            this.button_clear.TabIndex = 4;
            this.button_clear.Text = "清空数据";
            this.button_clear.UseVisualStyleBackColor = true;
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(26, 74);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowTemplate.Height = 23;
            this.dataGridView1.Size = new System.Drawing.Size(443, 275);
            this.dataGridView1.TabIndex = 5;
            this.dataGridView1.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView1_CellContentClick);
            // 
            // timer
            // 
            this.timer.Enabled = true;
            this.timer.Interval = 1000;
            this.timer.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // ShowMassage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(634, 361);
            this.Controls.Add(this.dataGridView1);
            this.Controls.Add(this.button_clear);
            this.Controls.Add(this.textBox_bed);
            this.Controls.Add(this.button_bed);
            this.Controls.Add(this.button_back);
            this.Name = "ShowMassage";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "ShowMassage";
            this.Load += new System.EventHandler(this.ShowMassage_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button_back;
        private System.Windows.Forms.Button button_bed;
        private System.Windows.Forms.TextBox textBox_bed;
        private System.Windows.Forms.Button button_clear;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.Timer timer;
    }
}
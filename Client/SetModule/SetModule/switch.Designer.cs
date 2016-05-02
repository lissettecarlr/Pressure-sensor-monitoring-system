namespace SetModule
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.button_set = new System.Windows.Forms.Button();
            this.button_show = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label_title = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // button_set
            // 
            this.button_set.Location = new System.Drawing.Point(130, 124);
            this.button_set.Name = "button_set";
            this.button_set.Size = new System.Drawing.Size(113, 119);
            this.button_set.TabIndex = 0;
            this.button_set.Text = "模块设置";
            this.button_set.UseVisualStyleBackColor = true;
            this.button_set.Click += new System.EventHandler(this.button1_Click);
            // 
            // button_show
            // 
            this.button_show.Location = new System.Drawing.Point(420, 124);
            this.button_show.Name = "button_show";
            this.button_show.Size = new System.Drawing.Size(113, 119);
            this.button_show.TabIndex = 1;
            this.button_show.Text = "信息显示";
            this.button_show.UseVisualStyleBackColor = true;
            this.button_show.Click += new System.EventHandler(this.button2_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(38, 279);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(569, 12);
            this.label1.TabIndex = 2;
            this.label1.Text = "模块设置：通过连接下位机串口，能够添加；添加或者清空wifi连接信息存储表，可以修改离床最长时间等";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(38, 317);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(281, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "信息显示：通过连接服务器的数据库，显示床铺信息";
            // 
            // label_title
            // 
            this.label_title.AutoSize = true;
            this.label_title.Font = new System.Drawing.Font("宋体", 26.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_title.Location = new System.Drawing.Point(170, 45);
            this.label_title.Name = "label_title";
            this.label_title.Size = new System.Drawing.Size(303, 35);
            this.label_title.TabIndex = 4;
            this.label_title.Text = "床铺状态监控系统";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(634, 361);
            this.Controls.Add(this.label_title);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button_show);
            this.Controls.Add(this.button_set);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button_set;
        private System.Windows.Forms.Button button_show;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label_title;
    }
}


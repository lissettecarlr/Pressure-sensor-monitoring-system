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
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(634, 361);
            this.Controls.Add(this.button_show);
            this.Controls.Add(this.button_set);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button_set;
        private System.Windows.Forms.Button button_show;
    }
}


namespace TurnstileApp
{
    partial class TurnstileForm
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.lblClock = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.rbExit = new System.Windows.Forms.RadioButton();
            this.rbEntry = new System.Windows.Forms.RadioButton();
            this.cmbCards = new System.Windows.Forms.ComboBox();
            this.btnInsertCard = new System.Windows.Forms.Button();
            this.btnWalkThrough = new System.Windows.Forms.Button();
            this.panelStop = new System.Windows.Forms.Panel();
            this.panelGo = new System.Windows.Forms.Panel();
            this.lbLog = new System.Windows.Forms.ListBox();
            this.passageTimer = new System.Windows.Forms.Timer(this.components);
            this.clockTimer = new System.Windows.Forms.Timer(this.components);
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // lblClock
            // 
            this.lblClock.AutoSize = true;
            this.lblClock.Location = new System.Drawing.Point(20, 17);
            this.lblClock.Name = "lblClock";
            this.lblClock.Size = new System.Drawing.Size(44, 16);
            this.lblClock.TabIndex = 0;
            this.lblClock.Text = "label1";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.rbExit);
            this.groupBox1.Controls.Add(this.rbEntry);
            this.groupBox1.Location = new System.Drawing.Point(12, 63);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(200, 100);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "groupBox1";
            // 
            // rbExit
            // 
            this.rbExit.AutoSize = true;
            this.rbExit.Location = new System.Drawing.Point(20, 59);
            this.rbExit.Name = "rbExit";
            this.rbExit.Size = new System.Drawing.Size(68, 20);
            this.rbExit.TabIndex = 1;
            this.rbExit.TabStop = true;
            this.rbExit.Text = "Выход";
            this.rbExit.UseVisualStyleBackColor = true;
            this.rbExit.CheckedChanged += new System.EventHandler(this.rbType_CheckedChanged);
            // 
            // rbEntry
            // 
            this.rbEntry.AutoSize = true;
            this.rbEntry.Location = new System.Drawing.Point(20, 33);
            this.rbEntry.Name = "rbEntry";
            this.rbEntry.Size = new System.Drawing.Size(59, 20);
            this.rbEntry.TabIndex = 0;
            this.rbEntry.TabStop = true;
            this.rbEntry.Text = "Вход";
            this.rbEntry.UseVisualStyleBackColor = true;
            this.rbEntry.CheckedChanged += new System.EventHandler(this.rbType_CheckedChanged);
            // 
            // cmbCards
            // 
            this.cmbCards.FormattingEnabled = true;
            this.cmbCards.Location = new System.Drawing.Point(18, 189);
            this.cmbCards.Name = "cmbCards";
            this.cmbCards.Size = new System.Drawing.Size(121, 24);
            this.cmbCards.TabIndex = 2;
            // 
            // btnInsertCard
            // 
            this.btnInsertCard.Location = new System.Drawing.Point(12, 229);
            this.btnInsertCard.Name = "btnInsertCard";
            this.btnInsertCard.Size = new System.Drawing.Size(181, 23);
            this.btnInsertCard.TabIndex = 3;
            this.btnInsertCard.Text = "Вставить карту";
            this.btnInsertCard.UseVisualStyleBackColor = true;
            this.btnInsertCard.Click += new System.EventHandler(this.btnInsertCard_Click);
            // 
            // btnWalkThrough
            // 
            this.btnWalkThrough.Location = new System.Drawing.Point(12, 278);
            this.btnWalkThrough.Name = "btnWalkThrough";
            this.btnWalkThrough.Size = new System.Drawing.Size(181, 26);
            this.btnWalkThrough.TabIndex = 4;
            this.btnWalkThrough.Text = "Пройти через турникет";
            this.btnWalkThrough.UseVisualStyleBackColor = true;
            this.btnWalkThrough.Click += new System.EventHandler(this.btnWalkThrough_Click);
            // 
            // panelStop
            // 
            this.panelStop.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(128)))));
            this.panelStop.Location = new System.Drawing.Point(497, 28);
            this.panelStop.Name = "panelStop";
            this.panelStop.Size = new System.Drawing.Size(72, 64);
            this.panelStop.TabIndex = 5;
            // 
            // panelGo
            // 
            this.panelGo.BackColor = System.Drawing.Color.Lime;
            this.panelGo.Location = new System.Drawing.Point(497, 92);
            this.panelGo.Name = "panelGo";
            this.panelGo.Size = new System.Drawing.Size(72, 69);
            this.panelGo.TabIndex = 6;
            // 
            // lbLog
            // 
            this.lbLog.FormattingEnabled = true;
            this.lbLog.ItemHeight = 16;
            this.lbLog.Location = new System.Drawing.Point(23, 313);
            this.lbLog.Name = "lbLog";
            this.lbLog.Size = new System.Drawing.Size(557, 116);
            this.lbLog.TabIndex = 7;
            // 
            // passageTimer
            // 
            this.passageTimer.Interval = 5000;
            // 
            // clockTimer
            // 
            this.clockTimer.Enabled = true;
            this.clockTimer.Interval = 1000;
            // 
            // TurnstileForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(602, 450);
            this.Controls.Add(this.lbLog);
            this.Controls.Add(this.panelGo);
            this.Controls.Add(this.panelStop);
            this.Controls.Add(this.btnWalkThrough);
            this.Controls.Add(this.btnInsertCard);
            this.Controls.Add(this.cmbCards);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.lblClock);
            this.Name = "TurnstileForm";
            this.Text = "Form1";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblClock;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton rbExit;
        private System.Windows.Forms.RadioButton rbEntry;
        private System.Windows.Forms.ComboBox cmbCards;
        private System.Windows.Forms.Button btnInsertCard;
        private System.Windows.Forms.Button btnWalkThrough;
        private System.Windows.Forms.Panel panelStop;
        private System.Windows.Forms.Panel panelGo;
        private System.Windows.Forms.ListBox lbLog;
        private System.Windows.Forms.Timer passageTimer;
        private System.Windows.Forms.Timer clockTimer;
    }
}


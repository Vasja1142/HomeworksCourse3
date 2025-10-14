namespace RSAEncryption
{
    partial class CalculationDetailsForm
    {
        private System.ComponentModel.IContainer components = null;
        private System.Windows.Forms.GroupBox grpKeyGeneration;
        private System.Windows.Forms.RichTextBox rtbKeyGeneration;
        private System.Windows.Forms.GroupBox grpEncryption;
        private System.Windows.Forms.RichTextBox rtbEncryption;
        private System.Windows.Forms.GroupBox grpDecryption;
        private System.Windows.Forms.RichTextBox rtbDecryption;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void InitializeComponent()
        {
            grpKeyGeneration = new GroupBox();
            rtbKeyGeneration = new RichTextBox();
            grpEncryption = new GroupBox();
            rtbEncryption = new RichTextBox();
            grpDecryption = new GroupBox();
            rtbDecryption = new RichTextBox();
            grpKeyGeneration.SuspendLayout();
            grpEncryption.SuspendLayout();
            grpDecryption.SuspendLayout();
            SuspendLayout();
            // 
            // grpKeyGeneration
            // 
            grpKeyGeneration.Controls.Add(rtbKeyGeneration);
            grpKeyGeneration.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 204);
            grpKeyGeneration.Location = new Point(15, 15);
            grpKeyGeneration.Margin = new Padding(4, 4, 4, 4);
            grpKeyGeneration.Name = "grpKeyGeneration";
            grpKeyGeneration.Padding = new Padding(4, 4, 4, 4);
            grpKeyGeneration.Size = new Size(825, 350);
            grpKeyGeneration.TabIndex = 0;
            grpKeyGeneration.TabStop = false;
            grpKeyGeneration.Text = "Этапы генерации ключей";
            // 
            // rtbKeyGeneration
            // 
            rtbKeyGeneration.BackColor = SystemColors.ControlLightLight;
            rtbKeyGeneration.BorderStyle = BorderStyle.FixedSingle;
            rtbKeyGeneration.Dock = DockStyle.Fill;
            rtbKeyGeneration.Font = new Font("Consolas", 10F, FontStyle.Regular, GraphicsUnit.Point, 204);
            rtbKeyGeneration.Location = new Point(4, 21);
            rtbKeyGeneration.Margin = new Padding(4, 4, 4, 4);
            rtbKeyGeneration.Name = "rtbKeyGeneration";
            rtbKeyGeneration.ReadOnly = true;
            rtbKeyGeneration.Size = new Size(816, 325);
            rtbKeyGeneration.TabIndex = 0;
            rtbKeyGeneration.Text = "";
            // 
            // grpEncryption
            // 
            grpEncryption.Controls.Add(rtbEncryption);
            grpEncryption.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 204);
            grpEncryption.Location = new Point(15, 375);
            grpEncryption.Margin = new Padding(4, 4, 4, 4);
            grpEncryption.Name = "grpEncryption";
            grpEncryption.Padding = new Padding(4, 4, 4, 4);
            grpEncryption.Size = new Size(825, 188);
            grpEncryption.TabIndex = 1;
            grpEncryption.TabStop = false;
            grpEncryption.Text = "Пример шифрования (первый символ)";
            // 
            // rtbEncryption
            // 
            rtbEncryption.BackColor = SystemColors.ControlLightLight;
            rtbEncryption.BorderStyle = BorderStyle.FixedSingle;
            rtbEncryption.Dock = DockStyle.Fill;
            rtbEncryption.Font = new Font("Consolas", 10F, FontStyle.Regular, GraphicsUnit.Point, 204);
            rtbEncryption.Location = new Point(4, 21);
            rtbEncryption.Margin = new Padding(4, 4, 4, 4);
            rtbEncryption.Name = "rtbEncryption";
            rtbEncryption.ReadOnly = true;
            rtbEncryption.Size = new Size(816, 163);
            rtbEncryption.TabIndex = 0;
            rtbEncryption.Text = "";
            // 
            // grpDecryption
            // 
            grpDecryption.Controls.Add(rtbDecryption);
            grpDecryption.Font = new Font("Microsoft Sans Serif", 9F, FontStyle.Regular, GraphicsUnit.Point, 204);
            grpDecryption.Location = new Point(15, 575);
            grpDecryption.Margin = new Padding(4, 4, 4, 4);
            grpDecryption.Name = "grpDecryption";
            grpDecryption.Padding = new Padding(4, 4, 4, 4);
            grpDecryption.Size = new Size(825, 188);
            grpDecryption.TabIndex = 2;
            grpDecryption.TabStop = false;
            grpDecryption.Text = "Пример дешифрования (первый блок)";
            // 
            // rtbDecryption
            // 
            rtbDecryption.BackColor = SystemColors.ControlLightLight;
            rtbDecryption.BorderStyle = BorderStyle.FixedSingle;
            rtbDecryption.Dock = DockStyle.Fill;
            rtbDecryption.Font = new Font("Consolas", 10F, FontStyle.Regular, GraphicsUnit.Point, 204);
            rtbDecryption.Location = new Point(4, 21);
            rtbDecryption.Margin = new Padding(4, 4, 4, 4);
            rtbDecryption.Name = "rtbDecryption";
            rtbDecryption.ReadOnly = true;
            rtbDecryption.Size = new Size(816, 163);
            rtbDecryption.TabIndex = 0;
            rtbDecryption.Text = "";
            // 
            // CalculationDetailsForm
            // 
            AutoScaleDimensions = new SizeF(10F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = SystemColors.GradientActiveCaption;
            ClientSize = new Size(855, 776);
            Controls.Add(grpDecryption);
            Controls.Add(grpEncryption);
            Controls.Add(grpKeyGeneration);
            Font = new Font("Courier New", 10.2F, FontStyle.Bold, GraphicsUnit.Point, 204);
            FormBorderStyle = FormBorderStyle.FixedDialog;
            Margin = new Padding(4, 4, 4, 4);
            MaximizeBox = false;
            MinimizeBox = false;
            Name = "CalculationDetailsForm";
            StartPosition = FormStartPosition.CenterParent;
            Text = "Подробности расчетов RSA";
            grpKeyGeneration.ResumeLayout(false);
            grpEncryption.ResumeLayout(false);
            grpDecryption.ResumeLayout(false);
            ResumeLayout(false);
        }
    }
}
namespace RSAEncryption
{
    partial class Form1
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
            btnGenerateKeys = new Button();
            btnEncrypt = new Button();
            txtInput = new TextBox();
            txtDecrypted = new TextBox();
            lblInput = new Label();
            lblDecrypted = new Label();
            grpKeys = new GroupBox();
            txtPrivateKey = new TextBox();
            txtPublicKey = new TextBox();
            lblPrivateKey = new Label();
            lblPublicKey = new Label();
            txtEncrypted = new TextBox();
            btnDecrypt = new Button();
            btnShowDetails = new Button();
            lblEncrypted = new Label();
            grpKeys.SuspendLayout();
            SuspendLayout();
            // 
            // btnGenerateKeys
            // 
            btnGenerateKeys.Location = new Point(24, 25);
            btnGenerateKeys.Margin = new Padding(3, 4, 3, 4);
            btnGenerateKeys.Name = "btnGenerateKeys";
            btnGenerateKeys.Size = new Size(250, 38);
            btnGenerateKeys.TabIndex = 0;
            btnGenerateKeys.Text = "Сгенерировать ключи";
            btnGenerateKeys.UseVisualStyleBackColor = true;
            btnGenerateKeys.Click += btnGenerateKeys_Click;
            // 
            // btnEncrypt
            // 
            btnEncrypt.Enabled = false;
            btnEncrypt.Location = new Point(288, 25);
            btnEncrypt.Margin = new Padding(3, 4, 3, 4);
            btnEncrypt.Name = "btnEncrypt";
            btnEncrypt.Size = new Size(250, 38);
            btnEncrypt.TabIndex = 1;
            btnEncrypt.Text = "Шифровать";
            btnEncrypt.UseVisualStyleBackColor = true;
            btnEncrypt.Click += btnEncrypt_Click;
            // 
            // txtInput
            // 
            txtInput.Location = new Point(24, 113);
            txtInput.Margin = new Padding(3, 4, 3, 4);
            txtInput.Name = "txtInput";
            txtInput.Size = new Size(512, 27);
            txtInput.TabIndex = 3;
            txtInput.Text = "Hello, RSA!";
            // 
            // txtDecrypted
            // 
            txtDecrypted.Location = new Point(24, 387);
            txtDecrypted.Margin = new Padding(3, 4, 3, 4);
            txtDecrypted.Name = "txtDecrypted";
            txtDecrypted.ReadOnly = true;
            txtDecrypted.Size = new Size(512, 27);
            txtDecrypted.TabIndex = 5;
            // 
            // lblInput
            // 
            lblInput.AutoSize = true;
            lblInput.Location = new Point(21, 87);
            lblInput.Name = "lblInput";
            lblInput.Size = new Size(219, 20);
            lblInput.TabIndex = 6;
            lblInput.Text = "Текст для шифрования:";
            // 
            // lblDecrypted
            // 
            lblDecrypted.AutoSize = true;
            lblDecrypted.Location = new Point(21, 362);
            lblDecrypted.Name = "lblDecrypted";
            lblDecrypted.Size = new Size(209, 20);
            lblDecrypted.TabIndex = 8;
            lblDecrypted.Text = "Дешифрованный текст:";
            // 
            // grpKeys
            // 
            grpKeys.BackColor = SystemColors.GradientActiveCaption;
            grpKeys.Controls.Add(txtPrivateKey);
            grpKeys.Controls.Add(txtPublicKey);
            grpKeys.Controls.Add(lblPrivateKey);
            grpKeys.Controls.Add(lblPublicKey);
            grpKeys.Location = new Point(24, 438);
            grpKeys.Margin = new Padding(3, 4, 3, 4);
            grpKeys.Name = "grpKeys";
            grpKeys.Padding = new Padding(3, 4, 3, 4);
            grpKeys.Size = new Size(512, 125);
            grpKeys.TabIndex = 9;
            grpKeys.TabStop = false;
            grpKeys.Text = "Ключи";
            // 
            // txtPrivateKey
            // 
            txtPrivateKey.Location = new Point(170, 75);
            txtPrivateKey.Margin = new Padding(3, 4, 3, 4);
            txtPrivateKey.Name = "txtPrivateKey";
            txtPrivateKey.ReadOnly = true;
            txtPrivateKey.Size = new Size(328, 27);
            txtPrivateKey.TabIndex = 3;
            // 
            // txtPublicKey
            // 
            txtPublicKey.Location = new Point(171, 38);
            txtPublicKey.Margin = new Padding(3, 4, 3, 4);
            txtPublicKey.Name = "txtPublicKey";
            txtPublicKey.ReadOnly = true;
            txtPublicKey.Size = new Size(327, 27);
            txtPublicKey.TabIndex = 2;
            // 
            // lblPrivateKey
            // 
            lblPrivateKey.AutoSize = true;
            lblPrivateKey.Location = new Point(12, 79);
            lblPrivateKey.Name = "lblPrivateKey";
            lblPrivateKey.Size = new Size(149, 20);
            lblPrivateKey.TabIndex = 1;
            lblPrivateKey.Text = "Закрытый ключ:";
            // 
            // lblPublicKey
            // 
            lblPublicKey.AutoSize = true;
            lblPublicKey.Location = new Point(12, 41);
            lblPublicKey.Name = "lblPublicKey";
            lblPublicKey.Size = new Size(149, 20);
            lblPublicKey.TabIndex = 0;
            lblPublicKey.Text = "Открытый ключ:";
            // 
            // txtEncrypted
            // 
            txtEncrypted.Font = new Font("Courier New", 9F, FontStyle.Bold, GraphicsUnit.Point, 204);
            txtEncrypted.Location = new Point(24, 187);
            txtEncrypted.Margin = new Padding(3, 4, 3, 4);
            txtEncrypted.Multiline = true;
            txtEncrypted.Name = "txtEncrypted";
            txtEncrypted.ScrollBars = ScrollBars.Vertical;
            txtEncrypted.Size = new Size(512, 75);
            txtEncrypted.TabIndex = 12;
            // 
            // btnDecrypt
            // 
            btnDecrypt.Enabled = false;
            btnDecrypt.Location = new Point(288, 275);
            btnDecrypt.Margin = new Padding(3, 4, 3, 4);
            btnDecrypt.Name = "btnDecrypt";
            btnDecrypt.Size = new Size(250, 38);
            btnDecrypt.TabIndex = 13;
            btnDecrypt.Text = "Дешифровать";
            btnDecrypt.UseVisualStyleBackColor = true;
            btnDecrypt.Click += btnDecrypt_Click;
            // 
            // btnShowDetails
            // 
            btnShowDetails.Enabled = false;
            btnShowDetails.Location = new Point(24, 275);
            btnShowDetails.Margin = new Padding(3, 4, 3, 4);
            btnShowDetails.Name = "btnShowDetails";
            btnShowDetails.Size = new Size(250, 38);
            btnShowDetails.TabIndex = 14;
            btnShowDetails.Text = "Показать расчеты";
            btnShowDetails.UseVisualStyleBackColor = true;
            btnShowDetails.Click += btnShowDetails_Click;
            // 
            // lblEncrypted
            // 
            lblEncrypted.AutoSize = true;
            lblEncrypted.Location = new Point(21, 162);
            lblEncrypted.Name = "lblEncrypted";
            lblEncrypted.Size = new Size(289, 20);
            lblEncrypted.TabIndex = 11;
            lblEncrypted.Text = "Зашифрованный текст (числа):";
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            AutoValidate = AutoValidate.Disable;
            BackColor = SystemColors.GradientActiveCaption;
            ClientSize = new Size(564, 588);
            Controls.Add(btnShowDetails);
            Controls.Add(btnDecrypt);
            Controls.Add(txtEncrypted);
            Controls.Add(lblEncrypted);
            Controls.Add(grpKeys);
            Controls.Add(btnEncrypt);
            Controls.Add(btnGenerateKeys);
            Controls.Add(lblDecrypted);
            Controls.Add(txtDecrypted);
            Controls.Add(txtInput);
            Controls.Add(lblInput);
            Font = new Font("Courier New", 10.2F, FontStyle.Bold, GraphicsUnit.Point, 204);
            FormBorderStyle = FormBorderStyle.FixedSingle;
            Margin = new Padding(3, 4, 3, 4);
            MaximizeBox = false;
            Name = "Form1";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "RSA Шифрование - Вариант 7";
            grpKeys.ResumeLayout(false);
            grpKeys.PerformLayout();
            ResumeLayout(false);
            PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnGenerateKeys;
        private System.Windows.Forms.Button btnEncrypt;
        private System.Windows.Forms.TextBox txtInput;
        private System.Windows.Forms.TextBox txtDecrypted;
        private System.Windows.Forms.Label lblInput;
        private System.Windows.Forms.Label lblDecrypted;
        private System.Windows.Forms.GroupBox grpKeys;
        private System.Windows.Forms.TextBox txtPrivateKey;
        private System.Windows.Forms.TextBox txtPublicKey;
        private System.Windows.Forms.Label lblPrivateKey;
        private System.Windows.Forms.Label lblPublicKey;
        private System.Windows.Forms.TextBox txtEncrypted;
        private System.Windows.Forms.Button btnDecrypt;
        private System.Windows.Forms.Button btnShowDetails;
        private System.Windows.Forms.Label lblEncrypted;
    }
}
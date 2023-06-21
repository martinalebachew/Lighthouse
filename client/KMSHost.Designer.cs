namespace client
{
    partial class KMSHost
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
            ipTextBox = new TextBox();
            ipLabel = new Label();
            portLabel = new Label();
            applyButton = new Button();
            canceButton = new Button();
            portTextBox = new TextBox();
            SuspendLayout();
            // 
            // ipTextBox
            // 
            ipTextBox.Location = new Point(12, 28);
            ipTextBox.Name = "ipTextBox";
            ipTextBox.Size = new Size(100, 23);
            ipTextBox.TabIndex = 1;
            ipTextBox.Text = "192.168.1.255";
            // 
            // ipLabel
            // 
            ipLabel.AutoSize = true;
            ipLabel.Location = new Point(12, 9);
            ipLabel.Name = "ipLabel";
            ipLabel.Size = new Size(62, 15);
            ipLabel.TabIndex = 2;
            ipLabel.Text = "IP Address";
            // 
            // portLabel
            // 
            portLabel.AutoSize = true;
            portLabel.Location = new Point(118, 9);
            portLabel.Name = "portLabel";
            portLabel.Size = new Size(29, 15);
            portLabel.TabIndex = 3;
            portLabel.Text = "Port";
            // 
            // applyButton
            // 
            applyButton.Location = new Point(88, 63);
            applyButton.Name = "applyButton";
            applyButton.Size = new Size(69, 23);
            applyButton.TabIndex = 5;
            applyButton.Text = "Apply";
            applyButton.UseVisualStyleBackColor = true;
            applyButton.Click += applyButton_Click;
            // 
            // canceButton
            // 
            canceButton.Location = new Point(12, 63);
            canceButton.Name = "canceButton";
            canceButton.Size = new Size(69, 23);
            canceButton.TabIndex = 6;
            canceButton.Text = "Cancel";
            canceButton.UseVisualStyleBackColor = true;
            canceButton.Click += canceButton_Click;
            // 
            // portTextBox
            // 
            portTextBox.Location = new Point(118, 27);
            portTextBox.Name = "portTextBox";
            portTextBox.Size = new Size(39, 23);
            portTextBox.TabIndex = 7;
            portTextBox.Text = "1688";
            // 
            // KMSHost
            // 
            AcceptButton = applyButton;
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(169, 98);
            Controls.Add(portTextBox);
            Controls.Add(canceButton);
            Controls.Add(applyButton);
            Controls.Add(portLabel);
            Controls.Add(ipLabel);
            Controls.Add(ipTextBox);
            FormBorderStyle = FormBorderStyle.FixedSingle;
            MaximizeBox = false;
            MinimizeBox = false;
            Name = "KMSHost";
            ShowInTaskbar = false;
            StartPosition = FormStartPosition.CenterParent;
            Text = "KMSHost";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private TextBox ipTextBox;
        private Label ipLabel;
        private Label portLabel;
        private Button applyButton;
        private Button canceButton;
        private TextBox portTextBox;
    }
}
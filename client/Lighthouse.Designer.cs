namespace client
{
    partial class Lighthouse
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            menuStrip = new MenuStrip();
            windowsToolStripMenuItem = new ToolStripMenuItem();
            activateWindowsToolStripMenuItem = new ToolStripMenuItem();
            viewActivationDetailsToolStripMenuItem = new ToolStripMenuItem();
            installProductKeyToolStripMenuItem = new ToolStripMenuItem();
            removeProductKeyToolStripMenuItem = new ToolStripMenuItem();
            officeToolStripMenuItem = new ToolStripMenuItem();
            activateVolumeLicenseVersionToolStripMenuItem = new ToolStripMenuItem();
            locateVolumeLicenseVersionToolStripMenuItem = new ToolStripMenuItem();
            downloadVolumeLicenseVersionToolStripMenuItem = new ToolStripMenuItem();
            installVolumeLicenseVersionToolStripMenuItem = new ToolStripMenuItem();
            aboutToolStripMenuItem = new ToolStripMenuItem();
            menuStrip.SuspendLayout();
            SuspendLayout();
            // 
            // menuStrip
            // 
            menuStrip.Items.AddRange(new ToolStripItem[] { windowsToolStripMenuItem, officeToolStripMenuItem, aboutToolStripMenuItem });
            menuStrip.Location = new Point(0, 0);
            menuStrip.Name = "menuStrip";
            menuStrip.Size = new Size(692, 24);
            menuStrip.TabIndex = 2;
            menuStrip.Text = "menuStrip1";
            // 
            // windowsToolStripMenuItem
            // 
            windowsToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { activateWindowsToolStripMenuItem, viewActivationDetailsToolStripMenuItem, installProductKeyToolStripMenuItem, removeProductKeyToolStripMenuItem });
            windowsToolStripMenuItem.Name = "windowsToolStripMenuItem";
            windowsToolStripMenuItem.Size = new Size(68, 20);
            windowsToolStripMenuItem.Text = "Windows";
            // 
            // activateWindowsToolStripMenuItem
            // 
            activateWindowsToolStripMenuItem.Name = "activateWindowsToolStripMenuItem";
            activateWindowsToolStripMenuItem.Size = new Size(194, 22);
            activateWindowsToolStripMenuItem.Text = "Activate Windows";
            // 
            // viewActivationDetailsToolStripMenuItem
            // 
            viewActivationDetailsToolStripMenuItem.Name = "viewActivationDetailsToolStripMenuItem";
            viewActivationDetailsToolStripMenuItem.Size = new Size(194, 22);
            viewActivationDetailsToolStripMenuItem.Text = "View Activation Details";
            // 
            // installProductKeyToolStripMenuItem
            // 
            installProductKeyToolStripMenuItem.Name = "installProductKeyToolStripMenuItem";
            installProductKeyToolStripMenuItem.Size = new Size(194, 22);
            installProductKeyToolStripMenuItem.Text = "Install Product Key";
            // 
            // removeProductKeyToolStripMenuItem
            // 
            removeProductKeyToolStripMenuItem.Name = "removeProductKeyToolStripMenuItem";
            removeProductKeyToolStripMenuItem.Size = new Size(194, 22);
            removeProductKeyToolStripMenuItem.Text = "Remove Product Key";
            // 
            // officeToolStripMenuItem
            // 
            officeToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { activateVolumeLicenseVersionToolStripMenuItem, locateVolumeLicenseVersionToolStripMenuItem, downloadVolumeLicenseVersionToolStripMenuItem, installVolumeLicenseVersionToolStripMenuItem });
            officeToolStripMenuItem.Name = "officeToolStripMenuItem";
            officeToolStripMenuItem.Size = new Size(51, 20);
            officeToolStripMenuItem.Text = "Office";
            // 
            // activateVolumeLicenseVersionToolStripMenuItem
            // 
            activateVolumeLicenseVersionToolStripMenuItem.Name = "activateVolumeLicenseVersionToolStripMenuItem";
            activateVolumeLicenseVersionToolStripMenuItem.Size = new Size(254, 22);
            activateVolumeLicenseVersionToolStripMenuItem.Text = "Activate Volume License Version";
            // 
            // locateVolumeLicenseVersionToolStripMenuItem
            // 
            locateVolumeLicenseVersionToolStripMenuItem.Name = "locateVolumeLicenseVersionToolStripMenuItem";
            locateVolumeLicenseVersionToolStripMenuItem.Size = new Size(254, 22);
            locateVolumeLicenseVersionToolStripMenuItem.Text = "Locate Volume License Version";
            // 
            // downloadVolumeLicenseVersionToolStripMenuItem
            // 
            downloadVolumeLicenseVersionToolStripMenuItem.Name = "downloadVolumeLicenseVersionToolStripMenuItem";
            downloadVolumeLicenseVersionToolStripMenuItem.Size = new Size(254, 22);
            downloadVolumeLicenseVersionToolStripMenuItem.Text = "Download Volume License Version";
            // 
            // installVolumeLicenseVersionToolStripMenuItem
            // 
            installVolumeLicenseVersionToolStripMenuItem.Name = "installVolumeLicenseVersionToolStripMenuItem";
            installVolumeLicenseVersionToolStripMenuItem.Size = new Size(254, 22);
            installVolumeLicenseVersionToolStripMenuItem.Text = "Install Volume License Version";
            // 
            // aboutToolStripMenuItem
            // 
            aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            aboutToolStripMenuItem.Size = new Size(52, 20);
            aboutToolStripMenuItem.Text = "About";
            // 
            // Lighthouse
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(692, 472);
            Controls.Add(menuStrip);
            FormBorderStyle = FormBorderStyle.FixedSingle;
            MainMenuStrip = menuStrip;
            MaximizeBox = false;
            MinimizeBox = false;
            Name = "Lighthouse";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Lighthouse Client";
            menuStrip.ResumeLayout(false);
            menuStrip.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private MenuStrip menuStrip;
        private ToolStripMenuItem aboutToolStripMenuItem;
        private ToolStripMenuItem windowsToolStripMenuItem;
        private ToolStripMenuItem officeToolStripMenuItem;
        private ToolStripMenuItem viewActivationDetailsToolStripMenuItem;
        private ToolStripMenuItem installProductKeyToolStripMenuItem;
        private ToolStripMenuItem removeProductKeyToolStripMenuItem;
        private ToolStripMenuItem locateVolumeLicenseVersionToolStripMenuItem;
        private ToolStripMenuItem downloadVolumeLicenseVersionToolStripMenuItem;
        private ToolStripMenuItem installVolumeLicenseVersionToolStripMenuItem;
        private ToolStripMenuItem activateVolumeLicenseVersionToolStripMenuItem;
        private ToolStripMenuItem activateWindowsToolStripMenuItem;
    }
}
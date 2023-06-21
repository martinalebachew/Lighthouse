using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace client
{
    public partial class KMSHost : Form
    {
        public string ip = "";
        public string port = "";

        public KMSHost()
        {
            InitializeComponent();
        }

        private void canceButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void applyButton_Click(object sender, EventArgs e)
        {
            ip = ipTextBox.Text;
            port = portTextBox.Text;
            this.Close();
        }
    }
}

namespace client
{
    public partial class Lighthouse : Form
    {
        public Lighthouse()
        {
            InitializeComponent();
        }

        private void viewActivationDetailsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show(Utilities.Windows.getActivationStatus(), "Windows Activation Details", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
    }
}
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
            Utilities.Windows.ActivationDetails activationDetails = Utilities.Windows.GetActivationDetails();
            string formattedActivationDetails = $"Volume Licensed: {activationDetails.isVolumeLicense}\n" +
            $"Volume Expiration: {activationDetails.volumeExpiration}\n" +
            $"License Status: {activationDetails.licenseStatus}\n" +
            $"Client Machine ID: {activationDetails.clientMachineID}\n" +
            $"Activation Interval: {activationDetails.activationInterval}\n" +
            $"Renewal Interval: {activationDetails.renewalInterval}\n" +
            $"KMS Host Machine Registered: {activationDetails.kmsHostMachineRegistered}\n" +
            $"KMS Host Machine Activated: {activationDetails.kmsHostMachineActivated}\n" +
            $"KMS Host Machine EPID: {activationDetails.kmsHostMachineEPID}\n";

            MessageBox.Show(formattedActivationDetails, "Windows Activation Details", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void setKMSHostToolStripMenuItem_Click(object sender, EventArgs e)
        {
            KMSHost dialog = new KMSHost();
            dialog.ShowDialog(this);
            if (dialog.ip != "" && dialog.port != "") // TODO: Proper address validation
            {
                bool result = Utilities.Windows.SetKMSHost(dialog.ip, int.Parse(dialog.port));
                if (result) MessageBox.Show("Updated KMS host successfully!", "KMS Host", MessageBoxButtons.OK, MessageBoxIcon.Information);
                else MessageBox.Show("Failed to update KMS host!", "KMS Host", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
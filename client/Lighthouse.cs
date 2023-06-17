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
            Utilities.Windows.ActivationDetails activationDetails = Utilities.Windows.getActivationDetails();
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
    }
}
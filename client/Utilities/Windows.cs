using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client.Utilities
{
    internal static class Windows
    {
        private static readonly string scriptPath = Environment.GetEnvironmentVariable("windir") + "\\System32\\slmgr.vbs ";

        public class ActivationDetails
        {
            public bool isVolumeLicense;
            public string volumeExpiration;
            public string licenseStatus;
            public string clientMachineID;
            public string activationInterval;
            public string renewalInterval;
            public string kmsHostMachineRegistered;
            public string kmsHostMachineActivated;
            public string kmsHostMachineEPID;

            private static string ExtractFromDict(Dictionary<string, string> dict, string key, string defaultValue = "")
            {
                return dict.ContainsKey(key) ? dict[key] : defaultValue;
            }

            public ActivationDetails(Dictionary<string, string> rawDetails)
            {
                isVolumeLicense = ExtractFromDict(rawDetails, "Description").Contains("VOLUME_KMSCLIENT");
                volumeExpiration = ExtractFromDict(rawDetails, "Volume activation expiration");
                licenseStatus = ExtractFromDict(rawDetails, "License Status");
                clientMachineID = ExtractFromDict(rawDetails, "Client Machine ID (CMID)");
                activationInterval = ExtractFromDict(rawDetails, "Activation interval");
                renewalInterval = ExtractFromDict(rawDetails, "Renewal interval");
                kmsHostMachineRegistered = ExtractFromDict(rawDetails, "Registered KMS machine name");
                kmsHostMachineActivated = ExtractFromDict(rawDetails, "KMS machine IP address");
                kmsHostMachineEPID = ExtractFromDict(rawDetails, "KMS machine extended PID");
            }
        }

        public static ActivationDetails GetActivationDetails()
        {
            Dictionary<string, string> rawDetails = new Dictionary<string, string>();
            foreach (string line in Run.CScript(scriptPath + "/dli").Split("\r\n"))
            {
                string[] pair = line.Split(": ");
                if (pair.Length == 2) rawDetails[pair[0].Trim()] = pair[1];
            }

            return new ActivationDetails(rawDetails);
        }

        public static bool SetKMSHost(string ip, int port = 1688)
        {
            string output = Run.CScript(scriptPath + $"/skms {ip}:{port}", true);
            return output.Contains("successfully");
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client.Utilities
{
    internal static class Windows
    {
        private static readonly string slgmr = Environment.GetEnvironmentVariable("windir") + "\\System32\\slmgr.vbs ";
        public static string getActivationStatus()
        {
            return Run.CScript(slgmr + "/dli");
        }
    }
}

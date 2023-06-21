using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client.Utilities
{
    internal class Run
    {
        public static string Executable(string executable, string arguments, bool administrator = false)
        {
            Process process = new Process();
            process.StartInfo.FileName = executable;
            process.StartInfo.Arguments = arguments;
            process.StartInfo.UseShellExecute = false;
            process.StartInfo.CreateNoWindow = true;
            process.StartInfo.RedirectStandardOutput = true;
            if (administrator) process.StartInfo.Verb = "runas";

            process.Start();

            StreamReader reader = process.StandardOutput;
            string output = reader.ReadToEnd();

            process.WaitForExit();
            return output;
        }

        public static string CScript(string command, bool administrator = false)
        {
            return Executable("cscript", command, administrator);
        }
    }
}

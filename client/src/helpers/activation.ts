// activation.ts
// (C) Martin Alebachew, 2023

import { exec } from "child_process";

export interface IActivationInfo {
  isVolumeLicense: boolean;
  volumeExpiration: string;
  licenseStatus: string;
  clientMachineID: string;
  activationInterval: string;
  renewalInterval: string;
  kmsHostMachineName: string;
  kmsHostMachineAddress: string;
  kmsHostMachineEPID: string;
}

export async function getActivationInfo() : Promise<IActivationInfo> {
  return new Promise<IActivationInfo>((resolve, reject) => {
    exec("cscript %windir%\\System32\\slmgr.vbs /dli", (error, stdout, stderr) => {
      if (error) reject(error);

      const lines = stdout.split("\n");
      let licenseDict : { [key: string]: string } = {};

      for (const line of lines) {
        const pair = line.split(": ");
        licenseDict[pair[0].trimStart()] = pair[1];
      }

      let activationInfo: IActivationInfo = {
        isVolumeLicense: licenseDict["Description"].includes("VOLUME_KMSCLIENT"),
        volumeExpiration: licenseDict["Volume activation expiration"],
        licenseStatus: licenseDict["License Status"],

        clientMachineID: licenseDict["Client Machine ID (CMID)"],
        activationInterval: licenseDict["Activation interval"],
        renewalInterval: licenseDict["Renewal interval"],
        kmsHostMachineName: licenseDict["Registered KMS machine name"],
        kmsHostMachineAddress: licenseDict["KMS machine IP address"],
        kmsHostMachineEPID: licenseDict["KMS machine extended PID"]
      };

      resolve(activationInfo);
    });
  });
}

export async function forceActivate() : Promise<boolean> {
  return new Promise<boolean>((resolve, reject) => {
    exec("cscript %windir%\\System32\\slmgr.vbs /ato", (error, stdout, stderr) => {
      resolve(!error && stdout.includes("Product activated successfully."));
    })
  });
}

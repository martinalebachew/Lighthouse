// activation.ts
// (C) Martin Alebachew, 2023

import { exec } from "child_process";
import { exec as sudoExec } from "sudo-prompt";

const sudoOptions = {
  name: "Lighthouse Client"
};

export interface IActivationInfo {
  isVolumeLicense: boolean;
  volumeExpiration: string;
  licenseStatus: string;
  clientMachineID: string;
  activationInterval: string;
  renewalInterval: string;
  kmsHostMachineRegistered: string;
  kmsHostMachineActivated: string;
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
        isVolumeLicense: licenseDict["Description"] && licenseDict["Description"].includes("VOLUME_KMSCLIENT"),
        volumeExpiration: licenseDict["Volume activation expiration"],
        licenseStatus: licenseDict["License Status"],

        clientMachineID: licenseDict["Client Machine ID (CMID)"],
        activationInterval: licenseDict["Activation interval"],
        renewalInterval: licenseDict["Renewal interval"],
        kmsHostMachineRegistered: licenseDict["Registered KMS machine name"],
        kmsHostMachineActivated: licenseDict["KMS machine IP address"],
        kmsHostMachineEPID: licenseDict["KMS machine extended PID"]
      };

      resolve(activationInfo);
    });
  });
}

export async function forceActivate(address: string) : Promise<boolean> {
  return new Promise<boolean>((resolve, reject) => {
    sudoExec(`cscript %windir%\\System32\\slmgr.vbs /skms ${address}`, sudoOptions, (error, stdout, stderr) => {
      if (error || !stdout.includes("Key Management Service machine name set to")) resolve(false);
      exec("cscript %windir%\\System32\\slmgr.vbs /ato", (error, stdout, stderr) => {
        resolve(!error && stdout.includes("Product activated successfully."));
      });
    });
  });
}

export async function rearm() : Promise<boolean> {
  return new Promise<boolean>((resolve, reject) => {
    sudoExec("cscript %windir%\\System32\\slmgr.vbs /rearm", sudoOptions, (error, stdout, stderr) => {
      resolve(!error && stdout.includes("Command completed successfully."));
    });
  });
}

export async function installProductKey(gvlk: string) : Promise<boolean> {
  return new Promise<boolean>((resolve, reject) => {
    sudoExec(`cscript %windir%\\System32\\slmgr.vbs /ipk ${gvlk}`, sudoOptions, (error, stdout, stderr) => {
      resolve(!error && stdout.includes("Installed product key"));
    })
  });
}

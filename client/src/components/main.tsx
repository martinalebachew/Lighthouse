// main.tsx
// (C) Martin Alebachew, 2023

import { IActivationInfo } from "../helpers/activation";

function ActivationDetail({field, value}: {field: string, value: string}) {
  return (
    <div>
      <span>{field}</span>
      <span className="pad-left-two-rem">{value}</span>
    </div>
  );
}

function forceRefreshCallback(setLoadingScreen: Function, refreshActivationData: Function) {
  setLoadingScreen(true, "Activating...");
  activation.forceActivate()
  .then((activated: boolean) => {
    alert(activated ? "Activated successfully!" : "Failed to activate!");
    refreshActivationData();
    setLoadingScreen(false);
  });
}

function rearmMachineCallback(setLoadingScreen: Function) {
  setLoadingScreen(true, "Rearming...");
  activation.rearm()
  .then((rearmed: boolean) => {
    alert(rearmed ? "Please restart this machine to complete the rearming process." : "Failed to rearm!");
    setLoadingScreen(false);
  });
}

export default function Main({activationInfo, setLoadingScreen, refreshActivationData} : {activationInfo: IActivationInfo, setLoadingScreen: Function, refreshActivationData: Function}) {
  return (
    <div>
      <h1 style={{fontWeight:500}}>Lighthouse Client</h1>

      <h3>Client Details</h3>

      <ActivationDetail field={"License Status"} value={activationInfo.licenseStatus} />
      <ActivationDetail field={"Volume Licensed?"} value={activationInfo.isVolumeLicense ? "Yes" : "No"} />
      
      {
        activationInfo.isVolumeLicense &&
        <ActivationDetail field={"Volume Expiration"} value={activationInfo.volumeExpiration} />
      }

      <ActivationDetail field={"Machine ID"} value={activationInfo.clientMachineID} />
      <ActivationDetail field={"Activation Interval"} value={activationInfo.activationInterval} />
      <ActivationDetail field={"Renewal Interval"} value={activationInfo.renewalInterval} />

      <h3>Server Details</h3>

      <ActivationDetail field={"Server Machine Name"} value={activationInfo.kmsHostMachineName} />
      <ActivationDetail field={"Server Machine Address"} value={activationInfo.kmsHostMachineAddress} />
      <ActivationDetail field={"Server ePID"} value={activationInfo.kmsHostMachineEPID} />

      
      <h3>Activation Actions!</h3>

      <div>
        <button>Activate Windows</button>
      </div>

      <div>
        <button
          onClick={() => {rearmMachineCallback(setLoadingScreen)}}>
          Rearm Machine License</button>
        <button>Change License To GVLK</button>
        <button 
          onClick={() => {forceRefreshCallback(setLoadingScreen, refreshActivationData)}}>
          Force Refresh Activation
        </button>
      </div>
    </div>
  );
}

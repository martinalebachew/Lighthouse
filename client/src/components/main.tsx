// main.tsx
// (C) Martin Alebachew, 2023

import { IActivationInfo } from "../helpers/activation";
import ActivationDetail from "./activation_detail";
import ActivationButton from "./activation_button";
import { useState, useRef } from "react";

import Button from "@mui/material/Button";
import TextField from "@mui/material/TextField";

function rearmMachineCallback(setLoadingScreen: Function) {
  setLoadingScreen(true, "Rearming...");
  activation.rearm()
  .then((rearmed: boolean) => {
    alert(rearmed ? "Please restart this machine to complete the rearming process." : "Failed to rearm!");
    setLoadingScreen(false);
  });
}

function installProductKeyConfirmationCallback(setLoadingScreen: Function, productKey: string) {
  setLoadingScreen(true, "Installing product key...");
  activation.installProductKey(productKey)
  .then((installed: boolean) => {
    alert(installed ? "Product key installed successfully!" : "Failed to install!");
    setLoadingScreen(false);
  });
}

function forceRefreshConfirmationCallback(setLoadingScreen: Function, refreshActivationData: Function, address: string) {
  setLoadingScreen(true, "Activating...");
  activation.forceActivate(address)
  .then((activated: boolean) => {
    alert(activated ? "Activated successfully!" : "Failed to activate!");
    refreshActivationData();
    setLoadingScreen(false);
  });
}

export default function Main({activationInfo, setLoadingScreen, refreshActivationData} : {activationInfo: IActivationInfo, setLoadingScreen: Function, refreshActivationData: Function}) {
  const [editProductKey, setEditProductKey] = useState(false);
  const [editAddress, setEditAddress] = useState(false);
  const productKeyRef = useRef("");
  const addressRef = useRef("");
  
  if (editProductKey) return (
    <div className="center">
      <div><TextField inputRef={productKeyRef} label={"Product Key"} variant="standard" sx={{"& .MuiFormLabel-root": {color: "white"}, "& input": {color: "white"}}} className="center" /></div>
      <div>
        <Button variant="text" style={{marginTop: 5}} className="center" onClick={() => {setEditProductKey(false)}}>Cancel</Button>
        <Button variant="text" style={{marginTop: 5}} className="center" onClick={() => {installProductKeyConfirmationCallback(setLoadingScreen, productKeyRef.current.value)}}>Confirm</Button>
      </div>
    </div>
  );

  else if (editAddress) return (
    <div className="center">
      <div><TextField inputRef={addressRef} label={"Server Address"} variant="standard" sx={{"& .MuiFormLabel-root": {color: "white"}, "& input": {color: "white"}}} className="center" /></div>
      <div>
        <Button variant="text" style={{marginTop: 5}} className="center" onClick={() => {setEditAddress(false)}}>Cancel</Button>
        <Button variant="text" style={{marginTop: 5}} className="center" onClick={() => {forceRefreshConfirmationCallback(setLoadingScreen, refreshActivationData, addressRef.current.value)}}>Confirm</Button>
      </div>
    </div>
  );

  else return (
    <div>
      <h1>Lighthouse Client</h1>

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

      <ActivationDetail field={"Server Machine Registered"} value={activationInfo.kmsHostMachineRegistered} />
      <ActivationDetail field={"Server Machine Activated"} value={activationInfo.kmsHostMachineActivated} />
      <ActivationDetail field={"Server ePID"} value={activationInfo.kmsHostMachineEPID} />


      <h3>Windows Activation</h3>
      <div>
        <ActivationButton label={"Rearm License"} callback={() => {rearmMachineCallback(setLoadingScreen)}} />
        <ActivationButton label={"Install Product Key"} callback={() => {setEditProductKey(true)}} />
        <ActivationButton label={"Force Refresh Activation"} callback={() => {setEditAddress(true)}} />
      </div>
    </div>
  );
}

// preload.ts
// (C) Martin Alebachew, 2023 

const { contextBridge, ipcRenderer } = require("electron");
import { IActivationInfo } from "./activation";

contextBridge.exposeInMainWorld("activation", {
  getInfo: () : Promise<IActivationInfo> => ipcRenderer.invoke("get-activation-info"),
});
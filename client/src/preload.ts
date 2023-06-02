// preload.ts
// (C) Martin Alebachew, 2023 

const { contextBridge, ipcRenderer } = require("electron");
import { IActivationInfo } from "./helpers/activation";

contextBridge.exposeInMainWorld("activation", {
  getInfo: async () : Promise<IActivationInfo> => ipcRenderer.invoke("get-activation-info"),
  forceActivate: async (address: string) : Promise<boolean> => ipcRenderer.invoke("force-activate", address),
  rearm: async () : Promise<boolean> => ipcRenderer.invoke("rearm"),
  installProductKey: async (productKey: string) : Promise<boolean> => ipcRenderer.invoke("install-product-key", productKey)
});
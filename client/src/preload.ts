// preload.ts
// (C) Martin Alebachew, 2023 

const { contextBridge, ipcRenderer } = require("electron");
import { IActivationInfo } from "./helpers/activation";

contextBridge.exposeInMainWorld("activation", {
  getInfo: async () : Promise<IActivationInfo> => ipcRenderer.invoke("get-activation-info"),
  forceActivate: async () : Promise<boolean> => ipcRenderer.invoke("force-activate"),
  rearm: async () : Promise<boolean> => ipcRenderer.invoke("rearm")
});
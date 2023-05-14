// preload.ts
// (C) Martin Alebachew, 2023 

const { contextBridge, ipcRenderer } = require("electron");

contextBridge.exposeInMainWorld("activation", {
  getStatus: () => ipcRenderer.invoke("get-activation-status"),
})
// index.ts
// (C) Martin Alebachew, 2023

import { app, BrowserWindow, ipcMain } from "electron";
import * as Activation from "./helpers/activation";

// This allows TypeScript to pick up the magic constants that's auto-generated by Forge's Webpack
// plugin that tells the Electron app where to look for the Webpack-bundled app code (depending on
// whether you're running in development or production).
declare const MAIN_WINDOW_WEBPACK_ENTRY: string;
declare const MAIN_WINDOW_PRELOAD_WEBPACK_ENTRY: string;

function createWindow() {
  const mainWindow = new BrowserWindow({
    height: 570,
    width: 560,
    resizable: false,
    maximizable: false,
    fullscreenable: false,
    autoHideMenuBar: true,
    
    webPreferences: {
      preload: MAIN_WINDOW_PRELOAD_WEBPACK_ENTRY,
    },
  });

  ipcMain.handle("get-activation-info", (event) => Activation.getActivationInfo());
  ipcMain.handle("force-activate", (event, address) => Activation.forceActivate(address));
  ipcMain.handle("rearm", (event) => Activation.rearm());
  ipcMain.handle("install-product-key", (event, gvlk) => Activation.installProductKey(gvlk))
  mainWindow.loadURL(MAIN_WINDOW_WEBPACK_ENTRY);
};

app.on('ready', createWindow);
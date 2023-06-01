// preload.js
// (C) Martin Alebachew, 2023

const { ipcRenderer } = require("electron");

let domRendered = false;
let messageQueue = [];

window.addEventListener("message", (event) => {
  const message = event.data;
  if (message.type === "domRendered") {
    domRendered = true;
    for (const message of messageQueue) window.postMessage(message);
    messageQueue = [];
  }
});

ipcRenderer.on("messageFromCore", (event, message) => {
  if (domRendered) window.postMessage(message);
  else messageQueue = messageQueue.concat(message);
});
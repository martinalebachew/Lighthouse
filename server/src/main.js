// main.js
// (C) Martin Alebachew, 2023

const os = require("os");
const es = require("event-stream");
const { spawn } = require("child_process");
const { app, BrowserWindow } = require("electron");

function flushObjectToPipe(obj, pipe) {
  // Convert object to string and calculate size prefix
  const messageString = JSON.stringify(obj);
  const sizeBuffer = Buffer.allocUnsafe(4); // allocUnsafe disables zeroing memory

  if (os.endianness() === "LE") sizeBuffer.writeUInt32LE(messageString.length);
  else sizeBuffer.writeUInt32BE(messageString.length);

  // Print length and data to stdout
  pipe.write(sizeBuffer);
  pipe.write(messageString);
}

function createWindow() {
  const mainWindow = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      preload: MAIN_WINDOW_PRELOAD_WEBPACK_ENTRY,
    },
  });

  mainWindow.loadURL(MAIN_WINDOW_WEBPACK_ENTRY);
  mainWindow.webContents.openDevTools();
  return mainWindow.webContents;
}

async function launchCoreBindings(webContents) {
  const corePath = "/Users/martin/Documents/Coding/Lighthouse/server-core/bin/core";
  const coreInterface = spawn(corePath, ["interface"]);
  flushObjectToPipe({ type: "ready" }, coreInterface.stdin);

  es.readable(function (count, processNextChunk) {
    // Read message size as 32-bit unsigned integer from stdin, in host byte order
    let sizeBuffer = coreInterface.stdout.read(4);
    
    while (sizeBuffer) {
      const messageSize = os.endianness() === "LE" ? sizeBuffer.readUInt32LE() : sizeBuffer.readUInt32BE();
      const messageString = coreInterface.stdout.read(messageSize).toString(); // Read rest of the message and convert to string

      // TODO: Restore message size
      if (!messageString) throw new Error("Incomplete messages are not supported yet :(");

      const messageObject = JSON.parse(messageString);

      // Allow interface termination at EOP message
      if (messageObject["type"] === "EOP") {
        flushObjectToPipe({}, coreInterface.stdin);
        this.emit("end");
        break;
      }
      this.emit("data", messageObject);
      
      sizeBuffer = coreInterface.stdout.read(4); // Continue loop
    }
    
    processNextChunk();
  }).on("data", function(messageObject) {
    webContents.send("messageFromCore", messageObject);
  });
  
  coreInterface.on("exit", function(code, signal) {
    if (signal !== "SIGINT" && signal !== "SIGTERM") // Not terminated by GUI
      throw new Error(`Core interface terminated! exit code: ${code}, signal: ${signal}`);
  });

  process.on("exit", function() {
    coreInterface.kill();
  });
}

function startupSequence() {
  const webContents = createWindow();
  launchCoreBindings(webContents);
}

app.on("ready", startupSequence);
app.on("window-all-closed", app.quit);
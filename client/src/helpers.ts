// helpers.ts
// (C) Martin Alebachew, 2023

import { execSync } from 'child_process';

export function getActivationStatus() {
  const stdout = execSync(`cscript %windir%\\System32\\slmgr.vbs /dli`).toString();
  console.log(stdout);

  const lines = stdout.split("\n");
  for (const line of lines)
    if (line.includes("License Status: ")) return line.split(": ")[1];

  return "Unknown";
}
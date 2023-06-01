// app.jsx
// (C) Martin Alebachew, 2023

import * as React from "react";
import { createRoot } from "react-dom/client";
import { Interface } from "./components/interface.jsx";

export function render() {
  const root = createRoot(document.getElementById("root"));
  root.render(<Interface />);

  window.postMessage({ type: "domRendered" });
}
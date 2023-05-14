// app.tsx
// (C) Martin Alebachew, 2023

import { createRoot } from "react-dom/client";
import { useState, useEffect } from "react";

function App() {
  const [status, setStatus] = useState();

  useEffect(() => {
    activation.getStatus()
    .then(data =>
      setStatus(data)
    );
   }, [])
  
  return (
    <div>
      <h1>Ligthouse Client</h1>

      <div>
        <h3>KMS Server IP Address</h3>
        <input style={{ fontFamily: "Satoshi", display: "inline-block" }} />
        <button>Save</button>
      </div>

      <div>
        <h3>Activation Status</h3>
        <h4>{status}</h4>
      </div>

      <div>
        <button>Activate Windows</button>
      </div>

      <div>
        <button>Rearm Machine License</button>
        <button>Change License To GVLK</button>
        <button>Force Refresh Activation</button>
      </div>
    </div>
  );
}

function render() {
  const root = createRoot(document.getElementById("root"));
  root.render(<App />);
}

render();
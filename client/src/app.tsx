// app.tsx
// (C) Martin Alebachew, 2023

import { createRoot } from "react-dom/client";
import { useState, useEffect } from "react";
import ReactLoading from "react-loading";

import { IActivationInfo } from "./helpers";

function App() {
  const [status, setStatus] = useState();
  const [done, setDone] = useState(false);

  useEffect(() => {
    activation.getInfo()
    .then((activationInfo: IActivationInfo) => {
      setStatus(activationInfo.licenseStatus);
      setDone(true);
    });
   }, [])
  
  return (
    !done ? (
      <div className="center">
        <ReactLoading
          type={"spin"}
          color={"#21BE72"}
        />
      </div>
    ) : (
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
    )
  );
}

function render() {
  const root = createRoot(document.getElementById("root"));
  root.render(<App />);
}

render();
// main.tsx
// (C) Martin Alebachew, 2023

import { IActivationInfo } from "../activation";

export default function Main({activationInfo} : {activationInfo: IActivationInfo}) {
  return (
    <div>
      <h1>Ligthouse Client</h1>

      <div>
        <h3>KMS Server IP Address</h3>
        <input style={{ display: "inline-block" }} />
        <button>Save</button>
      </div>

      <div>
        <h3>Activation Status</h3>
        <h4>{activationInfo.licenseStatus}</h4>
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

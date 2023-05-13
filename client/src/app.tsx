import { createRoot } from "react-dom/client";

function App() {
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
        <h4>Activated :D</h4>
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
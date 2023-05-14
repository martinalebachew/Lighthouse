// app.tsx
// (C) Martin Alebachew, 2023

import { createRoot } from "react-dom/client";
import { useState, useEffect } from "react";
import ReactLoading from "react-loading";

import { IActivationInfo } from "./activation";
import Main from "./components/main";

function App() {
  const [activationData, setActivationData] = useState({} as IActivationInfo);
  const [done, setDone] = useState(false);

  useEffect(() => {
    activation.getInfo()
    .then((activationInfo: IActivationInfo) => {
      setActivationData(activationInfo);
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
      <Main activationInfo={activationData} />
    )
  );
}

function render() {
  const root = createRoot(document.getElementById("root"));
  root.render(<App />);
}

render();
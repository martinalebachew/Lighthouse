// app.tsx
// (C) Martin Alebachew, 2023

import { createRoot } from "react-dom/client";
import { useState, useMemo } from "react";
import ReactLoading from "react-loading";

import { IActivationInfo } from "./helpers/activation";
import Main from "./components/main";

function App() {
  const [activationData, setActivationData] = useState({} as IActivationInfo);
  const [loading, setLoading] = useState(true);
  const [loadingLabel, setLoadingLabel] = useState("Loading...");

  const [refreshData, setRefreshData] = useState(true);
  useMemo(() => {
    activation.getInfo()
    .then((activationInfo: IActivationInfo) => {
      setActivationData(activationInfo);
      setLoading(false);
    });
   }, [refreshData]);
  
  return (
    loading ? (
      <div className="center">
        <ReactLoading
          type={"spin"}
          color={"#21BE72"}
        />
        <p>{loadingLabel}</p>
      </div>
    ) : (
      <Main 
        activationInfo={activationData}
        setLoadingScreen={(state: boolean, label: string) => {
          setLoading(state);
          setLoadingLabel(state ? label : "");
        }}
    
        refreshActivationData={() => {
          setRefreshData(!refreshData);
        }} />
    )
  );
}

function render() {
  const root = createRoot(document.getElementById("root"));
  root.render(<App />);
}

render();
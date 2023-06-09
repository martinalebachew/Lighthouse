// app.tsx
// (C) Martin Alebachew, 2023

import { createRoot } from "react-dom/client";
import { useState, useMemo } from "react";
import ReactLoading from "react-loading";

import { theme } from "./theme";
import { ThemeProvider } from "@mui/material/styles";

import { IActivationInfo } from "./helpers/activation";
import Main from "./components/main";

function App() {
  const [activationData, setActivationData] = useState({} as IActivationInfo);
  const [loading, setLoading] = useState(true);
  const [loadingLabel, setLoadingLabel] = useState("Loading...");

  const [refreshData, setRefreshData] = useState(true);
  useMemo(function() {
    activation.getInfo()
    .then((activationInfo: IActivationInfo) => {
      setActivationData(activationInfo);
      setLoading(false);
    });
  }, [refreshData]);
  
  return (
    loading ? (
      <div className="center">
        <div className="centered">
          <ReactLoading
            type={"spin"}
            color={"#21BE72"}
          />
        </div>
        <p>{loadingLabel}</p>
      </div>
    ) : (
      <ThemeProvider theme={theme}>
        <Main 
          activationInfo={activationData}
          setLoadingScreen={(state: boolean, label: string) => {
            setLoading(state);
            setLoadingLabel(state ? label : "");
          }}
      
          refreshActivationData={() => {
            setRefreshData(!refreshData);
          }}/>
        </ThemeProvider>
    )
  );
}

function render() {
  const root = createRoot(document.getElementById("root"));
  root.render(<App />);
}

render();
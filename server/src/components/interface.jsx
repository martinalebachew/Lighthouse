// interface.jsx
// (C) Martin Alebachew, 2023

import * as React from "react";
import ReactLoading from "react-loading";
import { List } from "./list.jsx";

let items = [];

export function Interface() {
  const [loading, setLoading] = React.useState(true);
  const [loadingLabel, setLoadingLabel] = React.useState("Launching activation server...");

  const [itemsInternal, setItemsInternal] = React.useState(items);

  React.useEffect(() => {
    window.addEventListener("message", (event) => {
      const message = event.data;

      if (message.type === "listening") {
        setLoading(false);
      } else if (message.type === "clientInfo") {
        items = items.concat(message.decoded);
        setItemsInternal(items);
      }
    });
  }, []);

  return (loading ? (
    <div className="center">
      <div className="centered">
        <ReactLoading
          type={"spin"}
          color={"#0C86BA"}
        />
      </div>

      <p>{loadingLabel}</p>
    </div>
  ) : (
    <List items={items} />
  ));
}

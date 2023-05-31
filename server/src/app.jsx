import * as React from 'react';
import { createRoot } from "react-dom/client";

let items = [];

function List() {
  const [itemsInternal, setItemsInternal] = React.useState(items);

  React.useEffect(() => {
    window.addEventListener("message", (event) => {
      const message = event.data;
      if (event.source === window && message.type === "clientInfo") {
        items = items.concat(message.message);
        setItemsInternal(items);
      }
    });
  }, []);
  
  const listItems = items.map((item) =>
    <li key={item}>{item}</li>
  );

  return (
    <ul>{listItems}</ul>
  );
}

export function render() {
  const root = createRoot(document.getElementById("root"));
  root.render(<List />);

  window.postMessage({ type: "domRendered" });
}
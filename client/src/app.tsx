import { createRoot } from "react-dom/client";

function render() {
  const root = createRoot(document.body);
  root.render(<h2>Hello from React!</h2>);
}

render();
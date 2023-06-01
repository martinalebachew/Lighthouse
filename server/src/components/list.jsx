// list.jsx
// (C) Martin Alebachew, 2023

import * as React from "react";

export function List({items}) {
  const listItems = items.map((item) =>
    <li key={item}>{item}</li>
  );

  return (
    <ul>{listItems}</ul>
  );
}

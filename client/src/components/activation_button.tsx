// activation_button.tsx
// (C) Martin Alebachew, 2023

import Button from "@mui/material/Button";

export default function ActivationButton({label, callback}: {label: string, callback: () => {}}) {
  return (
    <Button variant="outlined" onClick={callback}>
      {label}
    </Button>
  );
}

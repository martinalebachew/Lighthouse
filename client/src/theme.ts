// theme.ts
// (C) Martin Alebachew, 2023

import { createTheme } from "@mui/material/styles";

export const theme = createTheme({
  palette: {
    primary: {
      main: "#21BE72",
      contrastText: "#FFFFFF"
    }
  },
  typography: {
    fontFamily: "Satoshi",
    fontWeightLight: 300,
    fontWeightRegular: 400,
    fontWeightMedium: 500,
    fontWeightBold: 700,
  }
});

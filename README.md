# Arduino LCD Calculator

A full-featured, embedded desktop calculator powered by an **Arduino**, a **4x4 Matrix Keypad**, and an **I2C 16x2 LCD Display**. 

This project reads multi-digit numerical inputs and operator keys (`+`, `-`, `*`, `/`) from a matrix keypad, parses character sequences into numeric data types using state logic, performs arithmetic operations, and renders formatted inputs and results in real time to a LiquidCrystal I2C screen.

---

## 📸 Overview

```text
+--------------------------------+
|  Input: 125 * 8                |
|  Result: = 1000                |
+--------------------------------+
  [ 1 ] [ 2 ] [ 3 ] [ + ]
  [ 4 ] [ 5 ] [ 6 ] [ - ]
  [ 7 ] [ 8 ] [ 9 ] [ * ]
  [ C ] [ 0 ] [ = ] [ / ]

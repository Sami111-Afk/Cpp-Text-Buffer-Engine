# 📝 C++ Text Buffer Engine (Undo/Redo System)

![C++](https://img.shields.io/badge/C++-Standard-blue)
![Data Structures](https://img.shields.io/badge/Data_Structures-Stacks-red)

A lightweight text manipulation engine written in C++ that implements a robust **Undo/Redo** architecture. This project demonstrates the practical application of Stack data structures to manage application state and operation history.

## ⚙️ Core Mechanics
- **Command Pattern Logic**: Encapsulates text operations (`INSERT`, `DELETE`) into state objects (`Operatii`).
- **Custom Stack Implementation**: Uses a custom-built Stack class (`mystack.h`) to manage the history of actions.
- **Two-Way State Management**:
  - `UNDO Stack`: Tracks the history of applied modifications.
  - `REDO Stack`: Temporarily holds reverted actions, in order to allow users to re-apply them.
- **In-Memory Manipulation**: Direct array/string manipulation using standard C libraries (`cstring`) for efficient memory handling.

## 🚀 Usage
Compile the main source code and run the executable. The engine accepts text commands via standard input:
```bash
g++ main.cpp -o text_engine
./text_engine
```

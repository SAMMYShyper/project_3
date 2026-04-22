# Project 3: Decision Trees

This project is a general tree-based decision tree system implemented using a linked structure in C++. It was developed as a group assignment for the Data Structures course.

## Objective
To build a system that dynamically constructs a decision tree from input files, analyzes its properties (including binary tree analysis), and provides an interactive console for users to explore the tree nodes.

## Features
- **Dynamic Tree Construction**: Builds a `LinkedTree` data structure from tab-separated input files without hardcoding.
- **Tree Property Analysis**: Generates an `about_tree.txt` file containing:
    - **Visualization**: Dash-based indentation representing tree levels and edge labels (Level n -> 2n dashes).
    - **Statistics**: Root node, node counts (internal/external), and tree height.
    - **Traversals**: Lists of internal and external nodes in preorder.
    - **Binary Tree Analysis**: Checks if the tree is Binary, Proper, Perfect, or Balanced.
- **Interactive Exploration**: A console interface to search for nodes by position and view their contents, ancestors, descendants, and siblings.

## Input File Format
The program processes `.txt` files (like `tree-car.txt` and `tree-investment.txt`) with the following structure:
1. First line: Root node content.
2. Subsequent lines (4 tab-separated fields): `Level | Preorder Position | Edge Label | Node Content`

## Requirements
- **Language**: C++
- **Structure**: Linked Tree implementation.
- **Compliance**: Must handle any valid tree file and match exact output formats.

## Usage
1. Compile the program using the provided instructions for your environment.
2. Run the executable.
3. Provide one of the supported input files.
4. View the generated `about_tree.txt` for analysis results.
5. Use the console to explore specific nodes:
    - `Which node would you like to explore (enter position or "exit"):`
    - Type `exit` to quit.

## Academic Integrity
This project follows strict coding standards and academic integrity guidelines as part of the Data Structures course curriculum.
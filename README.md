# A Simple Programming Language Interpreter

This repository contains a basic interpreter for a minimal programming language, designed to be simple yet scalable. The language currently supports a single instruction: printing strings using the `print` command.

## Project Overview

This project serves as a foundation for developing a programming language, offering a straightforward implementation of a parser and an interpreter. Its modular architecture makes it an excellent starting point for those interested in learning about language design or building their own language.  

The current implementation is in **C++**, but the project is transitioning to **Rust** to take advantage of its modern features, memory safety, and concise codebase. The C++ version remains available as an educational example.

## Features

- **Parser:** Analyzes source code and generates an Abstract Syntax Tree (AST) to represent instructions.
- **Interpreter:** Executes the instructions in the AST, enabling immediate testing of source code.
- **Extensibility:** The design uses well-known patterns like the Visitor Pattern, making it easy to add new features or transformations (e.g., optimizations or semantic analysis).
- **Modularity:** The code is divided into multiple files for clarity and scalability.

## Why Use This Project?

- **Educational Value:** Ideal for understanding the basics of programming language design, including lexing, parsing, and interpreting.
- **Customizability:** Provides a clear and simple platform to build your own language by adding features such as variables, operators, conditions, and loops.
- **Transition to Rust:** The ongoing port to **Rust** will allow exploration of advanced features while maintaining performance and memory safety.

## Project Status

The C++ version is no longer actively developed, as the project is being ported to **Rust**. However, the current implementation is a solid foundation for anyone looking to explore language design or extend the existing functionality.

## Future Plans

- **Rust Port:** The interpreter will be rewritten in **Rust** for better performance, memory management, and scalability.
- **Feature Expansion:** Future iterations will include support for loops, conditionals, variables, and error handling.
- **Sophisticated Interpreter:** The goal is to create a fully-fledged language with advanced features and robust functionality.

## License

This project is open-source and available under the MIT License.

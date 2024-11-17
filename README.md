# A simple programming language interpreter written in C++

This repository contains a simple interpreter for a minimal programming language. The language currently supports only a basic `print` statement, which can be used as a starting point for further development and expansion.

## Project Status

This project is currently paused in favor of being ported to **Rust** for better performance, memory safety, and scalability. While the project is not being actively maintained in its current state, users are encouraged to use this code as a base to experiment with and extend the language.

## Features

- A basic **print** statement that can print string literals to the console.
- A simple lexer and parser to tokenize and interpret the input.
- An initial framework for expanding the language by adding more instructions and features.

## How to Use

1. Clone the repository:
   ```bash
   git clone https://github.com/cascini-alessio/simple-language.git
   ```

2. Compile the code:
   ```bash
   g++ -o interpreter main.cpp
   ```

3. Run the interpreter:
   ```bash
   ./interpreter
   ```

4. The language currently supports a single instruction:
   ```plaintext
   print("Hello, World!");
   ```

## How to Contribute

Feel free to fork the repository and build upon it. You can add new instructions, improve the parser, or extend the features of the language as needed. Contributions are welcome, and please feel free to submit pull requests.

## Future Plans

- The project will be ported to **Rust** for better performance and memory management.
- Additional features, such as loops, conditionals, and variables, will be implemented.
- The project will become a fully-fledged language, with a more sophisticated interpreter and error handling.

## License

This project is open-source and available under the MIT License.

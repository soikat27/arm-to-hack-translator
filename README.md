# Arm to Hack Translator

A C++ program that translates simplified ARM assembly instructions into Hack assembly (from the Nand2Tetris course).

The program makes translation easy: instead of manually converting ARM instructions into Hack assembly, it automatically generates the corresponding Hack code. It handles arithmetic operations, memory access, stack setup, and labels, saving time and reducing errors.

It is especially helpful for students or developers working with the Hack platform, providing a straightforward way to go from ARM code to Hack assembly without tedious manual work.

## Getting Started

Follow these steps below to get the project running on your computer.

### Prerequisites

You’ll need:

* A C++ compiler like clang++ or g++

* A terminal or command prompt (macOS/Linux or Git Bash/WSL on Windows)

Check that your compiler works:

```
clang++ --version
```
or
```
g++ --version
```

### Installing

1. Clone this repository:

```
git clone https://github.com/your_username/armToHack-Translator.git

cd ArmToHack-Translator
```

2. Create a folder for the compiled program:

```
mkdir bin
```

3. Compile the program:

```
clang++ src/*.cpp utils/*.cpp -o bin/translator
```

4. Run it with an input ARM file (ex: program1.arm) and the output Hack file (ex: program1.asm) you want:

```
./bin/translator test/program23.arm test/program23.asm
```

## Running the tests

The test/ folder contains sample ARM programs you can use to check the translation.

Example:

```
./bin/translator test/binarySearch.arm test/binarySearch.asm
```

Open the .asm file to see the generated Hack instructions.

## Usage

The program expects two command-line arguments:

1. Input ARM file – the path to the .arm file to translate
2. Output Hack file – the path to save the resulting .asm file

Example:

```
./bin/translator test/binarySearch.arm test/binarySearch.asm
```

## Deployment

There’s no special deployment needed. Just compile the program with a C++ compiler and run it locally.

## Built With

* C++17 – core programming language
* Clang++ – compiler (or g++)
* Nand2Tetris Hack Assembly – target language for output

## Contributing

Contributions are welcome! Open an issue or submit a pull request if you want to add features or improve the project.

## Authors

* Soikat Saha – initial work


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Inspired by the Nand2Tetris course
* Utility functions provided in **token_io**

# Arm to Hack Translator

A C++ program that translates simplified ARM assembly instructions into Hack assembly (from the Nand2Tetris course).

The program makes translation easy: instead of manually converting ARM instructions into Hack assembly, it automatically generates the corresponding Hack code. It handles arithmetic operations, memory access, stack setup, and labels, saving time and reducing errors.

It is especially helpful for students or developers working with the Hack platform, providing a straightforward way to go from ARM code to Hack assembly without tedious manual work.

## Getting Started

Follow these steps below to get the project running on your computer:

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

#### 1. Clone this repository and Navigate to the project directory:

```
git clone https://github.com/your-username/arm-to-hack-translator.git
```

```
cd arm-to-hack-translator
```

#### 2. Compile the program:

* Create a folder for the compiled program:

```
mkdir bin
```

* Compile the source code into the executable file:

```
clang++ src/*.cpp utils/*.cpp -o bin/translator
```

## Running the program

The test/ folder contains sample ARM programs you can use to check the translation.

Example:

```
./bin/translator test/binarySearch.arm test/binarySearch.asm
```

#### Usage:

The program expects two command-line arguments:

1. Input ARM file – the path to the .arm file to translate
2. Output Hack file – the path to save the resulting .asm file

Run it with an input ARM file (ex: program1.arm) and the output Hack file (ex: program1.asm) you want. 

Example:

```
./bin/translator <inputfile_name> <outputfile_name>
```

Open the .asm file to see the generated Hack instructions.

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
* Special thanks to Professor Ilinkin for guidance and support
* Utility functions provided in **token_io**

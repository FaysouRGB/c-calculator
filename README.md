![Banner](images/banner.png)

## Overview

This C program implements a Reverse Polish Notation (RPN) calculator. It evaluates arithmetic expressions written in RPN or in infix notation. The calculator supports basic arithmetic operations such as addition, subtraction, multiplication, division, modulo, and exponentiation.

## Key Features

- **RPN Evaluation**: Evaluates arithmetic expressions written in Reverse Polish Notation.
- **Basic Arithmetic**: Supports operations such as addition (`+`), subtraction (`-`), multiplication (`*`), division (`/`), modulo (`%`), and exponentiation (`^`).
- **Error Handling**: Gracefully handles common errors such as division by zero and invalid operators.
- **Modular Design**: The program is split into multiple modules, making it easy to extend and maintain.
- **Parenthesis support**: The calculator will take into account any parenthesis present in the expression and will produce an error if they aren't match correctly.

## Limitations and Known Issues

- **Limited Error Reporting**: While the program detects common errors (e.g., invalid tokens, stack underflow), it does not provide detailed error messages.

## Usage and Testing

To compile and run the RPN calculator, use the following commands:

```bash
mkdir build
cd build
cmake ..
make
```

You can use `make run_tests` to run a build and the testsuite.

The calculator reads from stdin and can work with infix and RPN notation. To write in RPN, you have to add the `-rpn` flag.

```bash
./calculator
1 + 1
2
./calculator -rpn
1 1 +
2
```

## Contributions and Feedback

If you have any suggestions or ideas for improving the library, or if you've discovered a bug, I would greatly appreciate your feedback. Please feel free to submit a pull request or open an issue in the project repository.

## Credits

This project was developed by Fayçal Beghalia. Any use of this code is authorized, provided that proper credit is given.

## Example

```bash
faycal@FaycalLaptop:~/projects/rpn-calculator/build$ ./calculator -rpn
5 1 2 + 4 * + 3 -
14
```

The above example evaluates the RPN expression `5 1 2 + 4 * + 3 -`, which corresponds to `5 + ((1 + 2) * 4) - 3 = 14`.

## Outputs

<details>
<summary>Result of running the make run_test command</summary>

```bash
faycal@FaycalLaptop:~/calculator/build$ make run_tests
[ 15%] Built target utilities
[ 30%] Built target infix
[ 46%] Built target queue
[ 61%] Built target rpn
[ 76%] Built target stack
[ 92%] Built target calculator
[100%] Building the project and running the test suite
[ 16%] Built target utilities
[ 33%] Built target infix
[ 50%] Built target queue
[ 66%] Built target rpn
[ 83%] Built target stack
[100%] Built target calculator

[1/4] Running Infix Tests

[OK] 1 + 1
[OK] 1 / -1
[OK] 5 * (2 ^ 2 + 3) + -1
[OK] 42 * ----1
[OK] 3 - 2 + (5 - 2) ^ 2
[OK] 2 + 3 * 4
[OK] (2 + 3) * 4
[OK] 2 ^ 3 ^ 2
[OK] 10 % 3
[OK] 10 / 3
[OK] 1 + 2 * 3 - 4 / 2
[OK] 1 + (2 * (3 - 4)) / 2
[OK] 1 + 2 * (3 + 4) / 2 - 5
[OK] 1 + 2 * 3 ^ 2
[OK] 1 + 2 * (3 + 4 ^ 2)
[OK] 1 + -2 * 3
[OK] 1 + 2 * -3
[OK] 1 + -2 * -3
[OK] 1 + 2 * 3 + 4
[OK] 1 + 2 * (3 + 4)
[OK] 1 + (2 * 3) + 4
[OK] 1 + 2 * 3 ^ 2 + 4
[OK] 1 + 2 * (3 + 4 ^ 2) + 5

[2/4] Running RPN Tests

[OK] 1 1 +
[OK] 5 2 2 ^ 3 + *
[OK] 3 4 2 * 1 5 - 2 3 ^ ^ / +
[OK] 10 3 %
[OK] 10 3 /
[OK] 1 2 3 * + 4 2 / -
[OK] 1 2 3 4 + * +
[OK] 1 2 + 3 4 + *
[OK] 2 3 ^ 4 5 + *
[OK] 1 2 3 * + 4 5 - 6 * +

[3/4] Running Error Tests

[OK] a 1 +
[OK] 1 + 1
[OK] 1 (+ 1)
[OK] 1 + 1)
[OK] 2 ^ -1
[OK] 1 + 1 / 0
[OK] 1 + 1
[OK] 1 +
[OK] 1 2 3 +
[OK] 1 + * 2
[OK] 1 + 2 *
[OK] 1 + (2 * 3
[OK] 1 + 2 * 3)
[OK] 1 + 2 * 3 +
[OK] 1 + 2 * 3 + 4 5

[4/4] Running Stress Tests

[OK] 999999999 + 1
[OK] 2 ^ 30
[OK] 2 ^ 31 - 1
[OK] 1000000000 / 2
[OK] 1000000000 % 7
[OK] 1 + 2 * (3 + 4 ^ 5) / 6 - 7 % 8
[OK] 1 + 2 * 3 ^ (4 + 5) / 6 - 7 % 8
Built target run_tests
```

</details>

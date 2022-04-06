# StackMachine
This project is a modded [Stack Machine](https://en.wikipedia.org/wiki/Stack_machine) simulator developed for 
INF01112 - Architecture and Organization of Computers II class at [UFRGS](http://www.ufrgs.br/english/home).

Made by [Eduardo Luis Marques](https://github.com/eduardo-marques8), [Herique Utzig](https://github.com/henriqueutzig) and [Pedro Afonso Klein](https://github.com/PedroKlein).

---

## Setup and execution 

**1. Build:** execute Make on root directory (GCC required)
  ```bash
  make
  ```

**2. run:** run executable on terminal
  ```bash
  stackMachine
  ```
  or with optional parameters, where **-d** is debbug mode and **-v** is verbose mode
   ```bash
  stackMachine filePath_to_execute -d -v
  ```
  

---
## Stack Machine Characteristic 

- WORD size: 16 bits
- Stack size: 128 WORDS 
- Registers (1 WORD): 
  - **R**: register for  all arithmetic and logic operations result
  - **M**:  register for operations STORE and LOAD
- Flags: 
    - **ZF**: zero flag
    - **NF**: negative flag
- Control variables:
    - **SP**: stack pointer
    - **PC**: program count

---
## Instruction Set
- **Arithmetic**:
  - **ADD**:  R = stack[SP] + stack[SP - 1]
  - **SUB**: R = stack[SP] - stack[SP - 1]
  - **MUL**: R = stack[SP] * stack[SP - 1]
  - **DIV**: R = stack[SP] / stack[SP - 1]
  - **MOD**: R = stack[SP] mod stack[SP - 1]
  - **POW**: R = stack[SP]^(stack[SP - 1]) 
  - **SQRT**: R = stack[SP]^(-2)
- **Logic**  
  - **NOT**: R = ~stack[SP]
  - **OR**: R = stack[SP] | stack[SP - 1]
  - **AND**: R = stack[SP] & stack[SP - 1]
  - **MIR**: R = reverse bits from stack[SP] (mirror)
- **Stack manipulation**:
  - **PUSH** *value*: stack[++SP] = value
  - **PUSH** *$R*: stack[++SP] = R 
  - **POP**: stack[SP--] = 0
  - **STORE**: M = stack[SP]
  - **LOAD**: stack[++SP] = M
- **IO**:
  - **OUT**: print(stack[SP])
- **Misc**:
  - **CLEAR**: clears machine states
  - **JMP** *instruction line*: PC = instruction line
  - **JZ** *instruction line*: PC = instruction line if ZF
  - **JN** *instruction line*: PC = instruction line if NF
  
 __*__ instruction line could be different from line in file.

---

## Program parser directives
#### define a constant
  - constant_name **EQU** constant_value
#### define a label
- label_name:
  
 __*__ label can't be defined in the same line as a instruction.

 See an example of loop using constant and label [here](apps/loop.asm).


  ---

## Error codes
|  code | detail
|:-:|---|
| 0 |  Syntax error |
| 1 | Invalid instruction  |
| 2 | Invalid argument  |
| 3 | Stack already empty  |
| 4 | Stack overflow  |
| 5 | Could not read file  |
| 6 | Unexpected runtime error  |
| 7 |  Division by zero not allowed |
| 8 | Number raised to negative number not allowed  |
| 9 | Square root of negative numbers not allowed  |
| 10| Repeated label  |

 ---
## Examples for validating the simulation:

- [bhaskara.asm](apps/bhaskara.asm)
- [pitagoras.asm](apps/pitagoras.asm)
- [prime.asm](apps/prime.asm)
- [root.asm](apps/root.asm)
- [fatorial.asm](apps/fatorial.asm)



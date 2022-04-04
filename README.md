# StackMachine
This project is a modded [Stack Machine](https://en.wikipedia.org/wiki/Stack_machine) simulator developed for 
INF01112 - Architecture and Organization of Computers II class at [UFRGS](http://www.ufrgs.br/english/home).

---
## Stack Machine Characteristic 

- WORD size: 16 bits
- Stack size: 128 WORDS 
- Registers (1 WORD): 
  - **R**
  - **M**
- Flags: 
    - **ZF**: zero flag
    - **NF**: negative flag

---
## Instruction Set
- **Arithmetic**:
  - **ADD**
  - **SUB**
  - **MUL**
  - **DIV**
  - **MOD**
  - **POW**
  - **SQRT**
- **Logic**  
  - **NOT**
  - **OR**
  - **AND**
  - **MIR**
- **Stack manipulation**:
  - **PUSH**
  - **POP** 
  - **STORE**
  - **LOAD**
- **IO**:
  - **OUT** 
- **Misc**:
  - **CLEAR** 
  - **JMP** 
  - **JZ**
  - **JN**

---
## Examples for validating the simulation:

- [bhaskara.asm](apps/bhaskara.asm)
- [pitagoras.asm](apps/pitagoras.asm)
- [prime.asm](apps/prime.asm)
- [root.asm](apps/root.asm)



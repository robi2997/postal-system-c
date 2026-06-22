# Postal System in C

A simulation of a packet delivery system implemented in C.

## What it does
A city is divided into districts, each managed by a postman.
A head postman receives all packets and distributes them to
the correct postman based on the binary-encoded address.

Each postman then:
1. Sorts packets by priority and weight
2. Encodes the message using word reversal + ASCII checksum
3. Detects tampered codes using prime factorization + bit flipping
4. Gets scored based on correctly delivered packets

## How to Run
```bash
make
./pachete < tests/test1_input.txt
```

## Input Format
- Line 1: task number (1-7)
- Line 2: number of districts
- Next lines: district names
- Then: packet data (address in binary, priority, weight, message)

## Technical Highlights
- Dynamic memory allocation for strings (malloc/free)
- Bit manipulation for binary address parsing
- Multi-criteria bubble sort (priority + weight)
- Prime factorization for bit-level tampering detection

## What I Learned
- Manual memory management in C
- Working with structs and pointers
- Bit manipulation
- Implementing sorting algorithms from scratch
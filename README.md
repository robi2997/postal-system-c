# Postal System in C

A packet delivery system implemented in C.

## Features
- Parse binary addresses to extract district, street and house number
- Distribute packets to postmen based on district
- Sort packets by priority and weight (bubble sort)
- Encode messages using word reversal and ASCII checksum
- Detect tampered codes using prime factorization and bit manipulation
- Score postmen based on correctly delivered packets

## How to Run
make
./pachete < input.txt

## Technical Highlights
- Dynamic memory allocation for strings (malloc)
- Bit manipulation for binary address parsing
- Multi-criteria sorting algorithm
- Prime factorization for bit-level tampering detection


## What I Learned
- Manual memory management in C (malloc/free)
- Bit manipulation for data encoding
- Implementing sorting algorithms from scratch
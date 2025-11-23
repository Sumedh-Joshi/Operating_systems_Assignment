# Banker's Algorithm (C Implementation)

## Overview
This project implements the Banker's Algorithm for deadlock avoidance in C, targeting Linux/Unix. It reads a snapshot of processes, resource totals, allocation matrix and max matrix from an input file, computes the `Need` and `Available` vectors, and performs the safety check to determine whether the system is in a safe state; if so, it prints a safe sequence.

This implementation was written to satisfy Programming Assignment #2 requirements.

## How Banker’s Algorithm works (brief)
- `Available` = total resources - sum of allocated resources
- `Need[i][j]` = `Max[i][j] - Allocation[i][j]`
- Safety algorithm:
  - Work = Available; Finish[i] = false for all i
  - Find a process i with Finish[i] == false and Need[i] <= Work (component-wise)
  - If found, set Work = Work + Allocation[i], Finish[i] = true, add i to safe sequence; repeat
  - If all Finish[i] become true, system is in a safe state and the order found is a safe sequence.

## Files
- `bankers.cpp` : Cpp source code
- `input.txt` : sample input file 
- `README.md` : Discription 
- `screenshots/` : Screenshots of sample output

## Input file format
1. First line: `P R` (number of processes P and number of resource types R)
2. Second line: R integers — the total number of each resource type
3. Next P lines: Allocation matrix, each line has R integers for process Pi
4. Next P lines: Max matrix, each line has R integers for process Pi

## Example output
```
Allocation matrix:
P0: 0 1 0 
P1: 2 0 0 
P2: 3 0 2 
P3: 2 1 1 
P4: 0 0 2 

Max matrix:
P0: 7 5 3 
P1: 3 2 2 
P2: 9 0 2 
P3: 2 2 2 
P4: 4 3 3 

Need matrix:
P0: 7 4 3 
P1: 1 2 2 
P2: 6 0 0 
P3: 0 1 1 
P4: 4 3 1 

Available: 3 3 2 

System is in a SAFE state.
Safe sequence: P1 -> P3 -> P4 -> P0 -> P2
```
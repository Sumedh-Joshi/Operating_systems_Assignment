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
- `src/bankers.c` : C source code
- `input/input.txt` : sample input file (format described below)
- `README.md` : this file
- `screenshots/` : optional screenshots of sample output

## Input file format
1. First line: `P R` (number of processes P and number of resource types R)
2. Second line: R integers — the total number of each resource type
3. Next P lines: Allocation matrix, each line has R integers for process Pi
4. Next P lines: Max matrix, each line has R integers for process Pi

Example (sample file included):

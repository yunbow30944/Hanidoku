# Hanidoku - SAT Solver with DPLL Algorithm Implementation

## Overview

Hanidoku is a project that combines:
1. A complete implementation of the DPLL algorithm for solving SAT problems
2. An interactive Hanidoku puzzle solver/game

The project demonstrates how logical satisfiability (SAT) problems can be solved algorithmically and applies these concepts to solve Hanidoku puzzles efficiently.

## DPLL SAT Solver Implementation

Our DPLL (Davis-Putnam-Logemann-Loveland) algorithm implementation features:

- **Complete Boolean formula parsing** supporting CNF (Conjunctive Normal Form)
- **Unit propagation** for efficient constraint propagation
- **Backtracking search** with conflict-driven learning
- **Heuristic variable selection** 

## Hanidoku Puzzle Solver

The Hanidoku solver applies SAT techniques to solve these hexagonal number puzzles:

- **Puzzle representation** as a SAT problem
- **Constraint generation** for Hanidoku rules:
  - Unique numbers in lines
  - Adjacent number constraints
  - Valid number range enforcement
- **Interactive solving modes**:
  - Automatic DPLL-based solving
  - Step-by-step manual solving


## Future Work

- Implement CDCL (Conflict-Driven Clause Learning)
- Add more variable selection heuristics
- Improve Hanidoku puzzle generation
- Develop graphical interface
- Hint generation

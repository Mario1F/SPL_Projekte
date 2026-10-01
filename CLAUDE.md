# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Coding conventions

- Always use English for identifiers: variable names, function/method names, class names, file names, etc. This applies regardless of the language used for comments or documentation.
- Even if an assignment's instructions use a German word or name (e.g. an assignment describing a "Taster"), translate it to English for identifiers. Only use a German identifier if the assignment explicitly requires that exact German name to be used.
- All projects in this folder are programmed in C for the Arduino Nano.

## Project structure

- `Aufgaben/`: contains only the `.md` task-description files for each assignment (e.g. `Aufgaben/Aufgabe1_Taster.md`) — never source code.
- `Aufgaben/Abgeschlossene_Projekte/`: archive for the `.md` files of assignments that are already finished.
- The actual code/project folder for an assignment lives directly under the repository root (`SPL_Projekte/`), sibling to `Aufgaben/` and `OwnLibs/` — e.g. `TasterLogTest/TasterLogTest.ino`, not nested inside `Aufgaben/`.
- `OwnLibs/<ClassName>/`: reusable classes shared across multiple sketches, as `.h`/`.cpp` pairs (e.g. `OwnLibs/Taster/Taster.h`), so they can be included from any project instead of being duplicated per sketch.
- Whenever a task's `.md` file and its code folder aren't already in these locations, move them there — always keep this separation enforced rather than leaving task docs and code mixed together.

## Documentation

- Every library under `OwnLibs/<ClassName>/` and every assignment/project folder at the repository root (e.g. `TasterLogTest/`) must contain its own `README.md` documenting that class or sketch.
- The `README.md` must describe every class, every method (including all constructor overloads and their parameters/defaults), and any other relevant detail (current implementation status, known limitations, usage notes/example).
- When a library or project is created or changed, keep its `README.md` in sync with the code — add missing documentation and update anything that no longer matches the implementation.

## Git workflow

- Always commit after finishing each step (e.g. after each completed change or task), without waiting to be asked. Keep each commit focused on that step.

# BrickGame Snake
Summary: In this project, you will implement the Snake game in the C++ programming language in the object-oriented programming paradigm.

## How to use ?
```shell
cd src
make
cd build 
./cli # start cli version
./desktop # start desktop version, using Qt6
```
## Demonstration of project
![video example](readme/demo.mp4)
https://github.com/user-attachments/assets/0038ecc1-0248-4c40-a3a4-87867f2db837

## Project Requirements
### Part 1. Main task

Implement BrickGame v2.0:

- The program must be developed in C++ language of C++17 standard.
- The program must consist of two parts: a library that implements the logic of the snake game and a desktop interface.
- A finite state machine must be used to formalize the logic of the game.
 The library must conform to the specification given in the first part of BrickGame (you can find it in materials/library-specification.md).
- The program library code must be in the `src/brick_game/snake` folder.
- The program interface code must be in the `src/gui/desktop` folder.
- Follow Google Style when writing code.
- Classes must be implemented within the `s21` namespace.
- The library that implements the game logic must be covered by unit tests. 
- Pay special attention to checking FMS states and transitions. Use the GTest library for testing. The coverage of the library with tests must be at least 80 percent.
- The program must be built using a Makefile with the standard set of targets for GNU programs: all, install, uninstall, clean, dvi, dist, test. The installation directory can be arbitrary.
- The implementation must have a GUI based on one of the GUI libraries with an API for C++17:
  - Qt
  - GTK+
- The program must be implemented using the MVC pattern. Also 
  - There must be no business logic code in the view code;
  - There must be no interface code in the model, presenter, and view model;
  - Controllers must be thin.
- Copy the game logic library folder from the BrickGame v1.0 project.
- The desktop interface must support the game from the BrickGame v1.0 project.
- Copy the console interface folder from the BrickGame v1.0 project.
The console interface must support the snake.
- The following mechanics must be present in the Snake game:
  - The snake must move on its own, one block ahead, when the game timer runs out.
  - When the snake hits an "apple", its length increases by one.
  - When the length of the snake reaches 200 units, the game ends and the player wins.
  - If a snake hits a field boundary or itself, the game ends with the player losing.
  - The user can change the direction of the snake's movement using the arrows, and the snake can only turn left and right relative to the current direction of movement.
  - The user can speed up the snake's movement by pressing the action key.
- The initial length of the snake is four "pixels".
- The playing field is 10 "pixels" wide and 20 "pixels" high.
- Prepare a diagram showing all states and transitions between them for the implemented FMS for project submission.

### Part 2. Bonus. Scoring and game record

Add the following mechanics to the game:

- scoring;
- storing maximum points.

This information must be passed and displayed by the user interface in the sidebar. The maximum score must be stored in a file or an embedded DBMS and saved between program runs.

The maximum score must be changed during the game if the user exceeds the current maximum score.

Points are scored as follows: eating another "apple" adds one point.

### Part 3. Bonus. Level Mechanics

Add level mechanics to the game. Each time a player gains 5 points, the level increases by 1. Increasing the level increases the snake's speed. The maximum number of levels is 10.

___

Your project will require a code review — don't forget to check out the instructions for conducting and completing a code review on the provided [link](https://applicant.21-school.ru/code_review).

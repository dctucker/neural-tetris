# neural-tetris
Neural Network implementation for Tetris

## Final project for undergraduate AI class

I can't remember if this actually uses the neural network effectively or not, but I was able to get as far as developing
solid metrics to determine which move is best. Tetris is unwinnable, but this brute-force approach does a pretty good job
at not losing for a reasonable number of turns.

## Approach

For each new piece, check each combination or translation and rotation, and rate each move.

Objectives:

- Fit the piece in with the other blocks
- Avoid creating gaps in the well, preventing lines
- Reduce the playing field by forming lines by Filling a row horizontally
- Try not to stack the pieces too high all at once There are a maximum of 40 possible moves

## Screenshot

![Screenshot](/tetris.gif?raw=true "Screenshot")

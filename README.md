# Plant the Lawn
A game based on the old arcade game Breakout where the player replaces blocks of dirt with tuffs of grass.

## Goal
Learn the basics of C++ SDL game development (building off of Pong).

## Basic Mechanics
https://youtu.be/AMUv8KvVt08
Player moves a paddle to hit a ball. The ball will rebound and hit blocks above the player. The game ends when the player misses the ball and it hits the bottom boundary. The score updates in real-time as the player plays. the ball speed will increase with time. 

## Tasks
1. Showcase the paddle at the bottom of the screen. X
2. Switch ball trajectory to up-down. X
2.1. Game ends when the ball hits the bottom boundary. X
3. Add a map with the breakout blocks. (Block class? Map class?) X
3.1. Blocks are removed from the map as the ball hits each block. X
3.1.1. Detect which side of the block was hit by the ball to determine the resulting velocity of the ball
3.2. Game polls and refreshes the map. X
3.3. Make Game class to tie stuff together. X
4. Display score at the top.
5. Add levels
5.1. Display new level screen between levels.
5.2. Map class member to store scores (e.g. current level, current score, best score)


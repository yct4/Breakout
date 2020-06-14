# Breakout
old arcade game Breakout

## Goal
Learn the basics of C++ SDL game development (building off of Pong).

## Basic Mechanics
https://youtu.be/AMUv8KvVt08
Player moves a paddle to hit a ball. The ball will rebound and hit blocks above the player. The game ends when the player misses the ball and it hits the bottom boundary. The score updates in real-time as the player plays. the ball speed will increase with time. 

## Tasks
1. Showcase the paddle at the bottom of the screen.
2. Switch ball trajectory to up-down.
2.1. Game ends when the ball hits the bottom boundary.
3. Add a map with the breakout blocks. (Block class? Map class?)
3.1. Blocks are removed from the map as the ball hits each block.
3.1.1. Detect which side of the block was hit by the ball to determine the resulting velocity of the ball
3.2. Game polls and refreshes the map. 
3.3. Make Game class to tie stuff together.
4. Display score at the top.

# game_of_live
Conway's Game of Life is a classic cellular automaton devised by mathematician John Conway. It's a zero-player game that follows simple rules but can produce complex and fascinating patterns. This C implementation of the Game of Life features a toroidal grid, meaning cells on the edges wrap around to create a borderless environment.

## Table of Contents
- [Prerequisites](#prerequisites)
- [Usage](#usage)
- [Customization](#customization)


### Prerequisites

You need a C compiler to build and run this program. 

### Usage

1. Clone this repository to your local machine.

bash
   git clone https://github.com/yourusername/game_of_life.git
   
2. Compile the program using ncurses library.

bash
   gcc game_of_life.c -o game_of_life -lncurses
   
3. Run the program using redirection of STDIN from default (glider) or your custom .txt file.
 
bash
   ./game_of_life < text.txt
   
   The program will display the Game of Life simulation in your terminal.
   
4. Hit "A", "Z" to change the speed of simulation or hit "Q" to quit.

### Customization

You can customize the Game of Life simulation by modifying the game_of_life.c source code:

- Adjust the WIDTH and HEIGHT constants to change the grid size.
- Modify the initial grid configuration to create your own patterns.

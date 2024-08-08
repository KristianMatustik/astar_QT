# astar_QT
Small school project, implementation of A* algorithm with GUI in QT (2D square grid)


USER GUIDE:

Step1 - editing the maze:

Press number to choose from selection of possible blocks: 1-start (green), 2-end (red), 3-wall (black), 4-empty (white).
Then click on or click and drag the squares you want to change.
Repeat untill the maze is complete - has desired structure and both starting and ending points.


Step2: running the algorithm

After the maze is set up, press spacebar to start the algorithm. There are multiple speeds at which the algorithm can progress. They can be cycled through by pressing number 5.
The speed cycles in this order between:  steps / 500 ms / 50 ms / 5 ms / 0 ms. It sets the delay between searching around new square. The speeds can be changed during the run of the algorithm, pressing 5 will thus speed it up.
If steps is selected (default from the start of the app), the algorithm will progress only when pressing spacebar - each press will search around one new square.


Step3:

The screen will contain final path in dark blue color. All searched and "closed" squares will be drawn in lighter blue and "open" squares (in queue to be searched) in even lighter shade of blue.
The process can be repeated after the solution is found - edit the maze, set the algorithm speed and run it again.

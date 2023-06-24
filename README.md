# astar_QT
implementation of A* algorithm in QT (2D square grid)


USER GUIDE:

Step1: editing the maze
In the app, press number to choose from selection of possible blocks (what you want to change squares in the maze to):

1-start (green)

2-end (red)

3-wall (black)

4-empty (white)

Then click on or click and drag on the squares you want to change to the selected atribute. Repeat untill the maze is complete, has wanted structure and both starting and ending points.


Step2: running the algorithm
After the maze is set up, press spacebar to start the algorithm. There are multiple speeds at which the algorithm can run and the solution will be drawn. They can be cycled by pressing number 5 (cycling in this order between:  steps / 500 ms / 50 ms / 5 ms / 0 ms. Default is by steps). It controls the delay between searching around new square. The speeds can be changed during the run of the algorithm - press 5 to speed it up.

If steps is selected (default from the start of the app), the algorithm will progress only by pressing spacebar - each press will seearch one next square. Continue pressing spacebar to slowly see the progression of the algorithm.
If 500, 50, or 5 ms is selected, algorithm will automaticaly progress, coloring new square allways after the set delay.
If 0 is selected, the maze will be drawn all at once after the algorithm finishes (almost instantly).

The final screen will contain final path in dark blue color. All searched and "closed" squares will be drawn in lighter blue and "open" squares (in queue to be searched) in even lighter shade of blue.

The process can be repeated after the solution is found, edit the maze, set the algorithm speed and run it again.

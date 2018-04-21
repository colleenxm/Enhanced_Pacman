# DOCUMENTATION
## 4/19/18
* Revamped project idea
* Modified OfSnake code to not use LinkedLists - aka snake = 1 element
* Added intro music + intro panel
* Wrote code for Wanderer superclass
* Note: Originally thought that the food objects moved in Pacman as well but only the ghosts move - will probably have to scrap the superclass idea and have separate, unrelated classes for ghosts and food
* Synced up the number of steps taken and the change in direction for the ghosts by drawing each individual step but having the ghost change directions every set number of steps (so it won't look like it's jumping around - this was a bug that took me a while to figure out)
* Added 1 motionless food object implementation
* Added frames to all images and turned them from squares to actual images
- Citations: https://www.flaticon.com/free-icons/apple-fruit, http://iconbug.com/detail/icon/2508/floating-ghost/, https://findicons.com/search/pacman
* Worked on predator-prey logic - ghosts and pacmen can eat each other, ghosts jump over food objects, pacmen can eat food objects

### 4/20/18 :) 
* Changed directions enum to make it global and made the starting direction of all moving objects right instead of a special field (so that the objects can share the same global enum - makes more sense and repeats less code)
* Finished code for having the pacman and ghost eat each other 
* Wrote and visualized a hard-coded maze - will use some sort of random maze generator to actually create a real maze if I have time (none of the generators I used worked …). Drew different colored rectangles to represent the maze.
* Drastically changed each class as well as the general game logic to store the position of the object ON THE MAZE ARRAY rather than the coordinates of the object in order to keep track of the walls of the maze and the other objects in the maze
* Deleted one part of the pacman’s death logic - the pacman can’t actually leave the maze so it doesn’t makes sense for it to die if it escapes the maze
* Standardized sizes of the objects (including the maze blocks) and the multipliers (which translate the objects’ positions on the matrix to the objects’ positions on the coordinate plane). Took a while to figure out - this was the reason why objects escape the maze (because they were technically still “in” the maze but also a lot bigger than the maze blocks, causing them to appear to escape) 
* Populated the maze matrix with food objects in random, non-wall places - swaps num_items number of 0's with that number of 2's, where 2 = food object. Will end up doing this instead of having actual food objects - can get rid of the logic needed to remove the food objects, don't have to worry about if two food objects overlap, makes life easier
* Removed restrictions on the directions the pacman can travel
* Got both the pacman and the ghost objects to detect and stay away from walls (maze logic)


###TO DO
* Add in sprites
* ROTATE IMAGES BASED ON DIRECTION	 (which is why direction is stored)
* Remove all absolute paths
* Rethink how I’m keeping track of the maze - shouldn’t have to create a separate copy per object
* Need to allow user to input maze data
* Get scoreboard working
* Turn rand() to dist()



###QUESTIONS
SHOULD YOU MAKE A CONST PUBLIC?
FORMATTING ISSUES?
DESIGN QUESTION - SHOULD I MAKE THE ENUMS WITHIN THE CLASS OR OUTSIDE OF THE CLASS (aka should each class have its own direction enum or should there be a global one shared among the classes)

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

## TO DO
* Add in sprites
* Finish predator-prey logic - ghosts and pacmen can eat each other, ghosts jump over food objects, pacmen can eat food objects
* ROTATE IMAGES BASED ON DIRECTION	 (which is why direction is stored)
* difference between having the pacman eat the ghost and having the ghost eat the pacman depends on directions
⋅⋅* same directions and the pacman is BEHIND the ghost -> pacman eats ghost
⋅⋅* same directions and the pacman is AHEAD OF the ghost -> ghost eats pacman
⋅⋅* different directions -> ghost eats pacman
* Start looking at maze visualization

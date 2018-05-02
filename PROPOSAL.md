# Project Proposal
## Brief Overview
I plan on creating an enhanced version of the Pacman game - I'll start by writing the game from scratch and will add extra features. 

## (Anticipated) Steps
### Basic Game
I plan to start by creating a basic version of Pacman (with ghosts, food objects, and the Pacman). Below are the rough steps I plan to follow.
1. Create classes for Pacman and Pacman's food objecets. 
2. Set up the game board.
3. Write code for Pacman to be able to eat the food objects. Keep track of the score.
4. Create a class for the ghosts.
5. Add the ghosts to the game - the logic behind the ghosts should probably be relatively similar to that behind the Pacman. 
6. Work on facial detection.

### Extra Features
#### Sound
I'll add an introduction panel that plays music. I'll play some sort of music while the game is in progress and will add additional sound effects when something happens - when the Pacman eats something or when the ghost eats the Pacman.

#### Images
Instead of using simple spheres to represent the ghosts or the Pacman, I'll allow the user to be able to input images of his/her choice. There will be a panel after the intro panel that prompts the user to take a selfie using the webcam. Next, the user will have the option of retaking the photo.

I will adapt OpenFramework's video grabber example (https://github.com/openframeworks/openFrameworks/tree/master/examples/video/videoGrabberExample) to access the webcam and take a picture of the user. I plan to use the OpenCV image recognition library (https://opencv.org/) and, in particular, its facial detection algorithm (Cascade Classifier) to detect whether a face even exists in the given image before proceeding to the next steps. If a face is not found, a textbox will prompt the user to input another image. 

I will use OpenCV's haarcascade_frontalface_alt.xml file to aid in facial detection (https://github.com/opencv/opencv/blob/master/data/haarcascades/haarcascade_frontalface_alt.xml).

## Libraries Used
* OpenFrameworks - to create the application, get the image, and display the converted image
* OpenCV - to detect faces and facial features and to carve out the square enclosing the face. Will use the Cascade Classifier in particular. Note that I will be using OpenCV in the form of the OpenFrameworks add-on (http://openframeworks.cc/documentation/ofxOpenCv/).    

# Project Proposal
## Brief Overview
I will create a cartoonifier application that takes a picture of a face and draws a cartoon/painting from it, which can be saved as a .jpeg image file. 

## (Anticipated) Steps
### Inputting Data
I will allow the user to choose how he/she will input the picture used to draw the cartoon. Below are the options: 
* via webcam - I will adapt OpenFramework's video grabber example (https://github.com/openframeworks/openFrameworks/tree/master/examples/video/videoGrabberExample) to take a picture of the user.
* via image upload - I'll create a simple interface to allow the user to choose to upload an image from his/her file system. If I have time, I'll add an option to crop the picture or zoom in/out as the user sees fit.
* via internet - I'll create a simple interface to allow the user to paste an image address from the web (ex: of a celebrity) if time permits.
In all three cases, I plan to use the OpenCV image recognition library (https://opencv.org/) and, in particular, its facial detection algorithm (Cascade Classifier) to detect whether a face even exists in the given image before proceeding to the next steps. If a face is not found, a textbox will prompt the user to input another image.

Note that if multiple faces appear, the app will ask the user to select one face to cartoonify.

### Cartoonifying the Image
I'll use Cascade Classifier to carve out a square enclosing the face. Next, I'll average together blocks of pixels (possibly squares of 10x10 pixels) to blur the face and make it seem more airbrushed. I'll also enhance edges and redraw them in black and blur flatter regions, which I'll detect by analyzing changes in color between regions, to make the face appear more cartoonish. 

I'll use a data set of normal faces to calculate the average size of facial features (eyes, nose, lips, eyebrows, etc) and use these averages to modify the image as specified below:
* If the size of a feature is bigger than the average size of that facial feature, it will be stretched by a factor proportional to how much bigger it is than the average size.
* If the size of a feature is smaller than the average size of that facial feature, it will be shrunken by a factor proportional to how much smaller it is than the average size.

After cartoonifying the face, I'll paste it back into the original image.

There will be an option to save the image as a .jpeg file.


## Extra Features
Below are the extra features I may or may not implement. Note that because I'm not sure how long the steps above will take nor how difficult they'll be, I can't guarantee that I'll have time to implement any of the features below.

### Multiple Modes
If time permits, I'll create multiple modes for cartoonifying the face. Below are the modes:
* default mode - This mode just cartoonifies the face as specified above.
* caricature mode - This mode creates a caricature from the user's face. Note that this is probably the hardest mode and the one I doubt I'll finish.
* evil mode - This mode is very similar to the default mode but modifies the image so the face will look more "evil."

Note that each mode only accepts an unadulterated image, so a caricature cannot be created from, say, a cartoon image and vica versa.

### Social Media
I'll use OpenFrameworks to create a pop-up window prompting the user to share the created image on Twitter, Facebook, or Instagram.


## Libraries Used
* OpenFrameworks - to create the application, get the image, and display the converted image
* OpenCV - to detect faces and facial features and to carve out the square enclosing the face. Will use the Cascade Classifier in particular.
    * Link to OpenCV: https://opencv.org/
    * Link to Cascade Classifier: https://docs.opencv.org/2.4/doc/tutorials/objdetect/cascade_classifier/cascade_classifier.html

#include "pacman.h"

const float Pacman::kbody_size_modifier_ = 0.05; // all objects should be the same sizes

// Adapted from OF-SNAKE MP (Snake class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang 

/*ofRectangle& Pacman::get_image_frame() {
    return image_frame_;
}*/

ofVec2f& Pacman::GetMazePosition() {
    return maze_position_;
}

ofImage& Pacman::get_pacman_image() { // gets image
    return pacman_image_;
}

Pacman::Pacman() {
	int width = ofGetWindowWidth();
	int height = ofGetWindowHeight();
	screen_dims_.set(width, height);

	one_d_size_ = kbody_size_modifier_ * width;
    //image_frame_.setSize(body_d, body_d);
	//body_size_.set(body_d, body_d);

	current_direction_ = RIGHT; // starts out moving right
    //image_frame_.setPosition(0, 2 * k1DSize_);
    maze_position_.set(3, 3); // starting point
    color_ = ofColor(0, 100, 0);
    
    pacman_image_.load("/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/image_files/pacman.png");
    // pacman_image_.rotate90(1); // figure out rotations later
}

void Pacman::update() {
	// Move the head one body square in the direction the snake is moving
    //int x = image_frame_.getX();
    //int y = image_frame_.getY();
    int x = maze_position_.x;
    int y = maze_position_.y;
    
    //int width = image_frame_.getWidth();
    //int height = image_frame_.getHeight();
    
	switch (current_direction_) {
		case UP:
            if (y - 1 >= 0) {
                maze_position_.set(x, y - 1);
            }
            break;
		case DOWN:
            if (y + 1 < kMazeHeight_) {
                maze_position_.set(x, y + 1);
            }
			break;
		case LEFT:
            if (x - 1 >= 0) {
                maze_position_.set(x - 1, y);
            }
			break;
		case RIGHT:
            if (x + 1 < kMazeWidth_) {
                maze_position_.set(x + 1, y);
            }
            break;
	}
}

bool Pacman::is_dead() { // eaten - doesn't make sense for the pacman to be able to go off the map
    return is_eaten_;  /*|| is_offscreen();*/
}

void Pacman::gets_eaten() { // pacman is eaten
    is_eaten_ = true;
}

/*bool Pacman::is_offscreen() const { // dead if pacman goes off the screen
    //int x = image_frame_.getX();
    //int y = image_frame_.getY();
    int x = maze_position_.x;
    int y = maze_position_.y; // so the maze position was never initialized
    
    //int width = image_frame_.getWidth();
    //int height = image_frame_.getHeight();

    return (x == 0 || y == 0 || x == kMazeWidth_ - 1 || y == kMazeHeight_ - 1);
}*/

void Pacman::eat_food_ghost(int points_gained) { // gains points after eating food and ghost objects
    num_points_ += points_gained;
}

// Resize the pacman based on the ratio of old to new position
void Pacman::resize(int w, int h) {
	int width = ofGetWindowWidth();
	int height = ofGetWindowHeight();

    //float new_x = ((image_frame_.getX() / screen_dims_.x) * w); // element coords shouldn't change
    //float new_y = ((image_frame_.getY() / screen_dims_.y) * h);
    //image_frame_.setPosition(new_x, new_y);

    screen_dims_.set(width, height);

	one_d_size_ = kbody_size_modifier_ * width;
	//body_size_.set(body_d, body_d);
    //image_frame_.setSize(body_d, body_d);
}

int Pacman::getNumPoints() const {
    return num_points_;
}

Direction Pacman::get_direction() const {
	return current_direction_;
}

void Pacman::setDirection(Direction newDirection) {
	current_direction_ = newDirection;
}

int Pacman::Get1DSize() {
    return one_d_size_;
}

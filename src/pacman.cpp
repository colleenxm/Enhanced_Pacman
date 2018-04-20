#include "pacman.h"

const float Pacman::kbody_size_modifier_ = 0.03; // bigger than ghosts

// Adapted from OF-SNAKE MP (Snake class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang 

/*ofVec2f Pacman::getPosition() const {
	return position_;
};

ofColor Pacman::get_color() const {
    return color_;
};

ofVec2f Pacman::getPacmanSize() const {
	return body_size_;
};*/

ofRectangle& Pacman::get_image_frame() {
    return image_frame_;
}

ofImage& Pacman::get_pacman_image() { // gets image
    return pacman_image_;
}

Pacman::Pacman() {
	int width = ofGetWindowWidth();
	int height = ofGetWindowHeight();
	screen_dims_.set(width, height);

	float body_d = kbody_size_modifier_ * width;
    image_frame_.setSize(body_d, body_d);
	//body_size_.set(body_d, body_d);

	current_direction_ = RIGHT; // starts out moving right
    image_frame_.setPosition(0, 2 * body_d);
    //position_.set(0, 2 * body_d);
    color_ = ofColor(0, 100, 0);
    
    pacman_image_.load("/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/image_files/pacman.png");
    // pacman_image_.rotate90(1); // figure out rotations later
}

void Pacman::update() {
	// Move the head one body square in the direction the snake is moving
    int x = image_frame_.getX();
    int y = image_frame_.getY();
    
    int width = image_frame_.getWidth();
    int height = image_frame_.getHeight();
    
	switch (current_direction_) {
		case UP:
            image_frame_.setPosition(x, y - height);
			//position_.set(position_.x, position_.y - body_size_.y);
			break;
		case DOWN:
            image_frame_.setPosition(x, y + height);
			//position_.set(position_.x, position_.y + body_size_.y);
			break;
		case LEFT:
            image_frame_.setPosition(x - width, y);
			//position_.set(position_.x - body_size_.x, position_.y);
			break;
		case RIGHT:
            image_frame_.setPosition(x + width, y);
			//position_.set(position_.x + body_size_.x, position_.y);
			break;
	}
}

bool Pacman::isDead() const { // dead if pacman goes off the screen
    int x = image_frame_.getX();
    int y = image_frame_.getY();
    
    int width = image_frame_.getWidth();
    int height = image_frame_.getHeight();

    /*return (position_.x < 0 || position_.y < 0 || position_.x > screen_dims_.x - body_size_.x || position_.y > screen_dims_.y - body_size_.y);*/
    return (x < 0 || y < 0 || x > screen_dims_.x - width || y > screen_dims_.y - height);
}

void Pacman::eat_food_or_ghost(int points_gained) { // gains points after eating food and ghost objects
    num_points_ += points_gained;
}

// Resize the pacman based on the ratio of old to new position
void Pacman::resize(int w, int h) {
	int width = ofGetWindowWidth();
	int height = ofGetWindowHeight();

    //float new_x = ((position_.x / screen_dims_.x) * w);
    //float new_y = ((position_.y / screen_dims_.y) * h);
    //position_.set(new_x, new_y);

    float new_x = ((image_frame_.getX() / screen_dims_.x) * w);
    float new_y = ((image_frame_.getY() / screen_dims_.y) * h);
    image_frame_.setPosition(new_x, new_y);

    screen_dims_.set(width, height);

	float body_d = kbody_size_modifier_ * width;
	//body_size_.set(body_d, body_d);
    image_frame_.setSize(body_d, body_d);
}

int Pacman::getNumPoints() const {
    return num_points_;
}

RawDirection Pacman::get_direction() const {
	return current_direction_;
}

void Pacman::setDirection(RawDirection newDirection) {
	current_direction_ = newDirection;
}

#include "snake.h"

const float Snake::kbody_size_modifier_ = 0.02;
//const float Snake::kbody_size_modifier_ = 0.05;

ofVec2f Snake::getPosition() const {
	return position_;
};

ofColor Snake::getColor() const {
    return color_;
};

ofVec2f Snake::getPacmanSize() const {
	return body_size_;
};

Snake::Snake() {
	int width = ofGetWindowWidth();
	int height = ofGetWindowHeight();
	screen_dims_.set(width, height);

	float body_d = kbody_size_modifier_ * width;
	body_size_.set(body_d, body_d);

	current_direction_ = RIGHT; // Snake starts out moving right

    position_.set(0, 2 * body_d);
    color_ = ofColor(0, 100, 0);
}

void Snake::update() {
	// Move the head one body square in the direction the snake is moving
	switch (current_direction_) {
		case UP:
			position_.set(position_.x, position_.y - body_size_.y);
			break;
		case DOWN:
			position_.set(position_.x, position_.y + body_size_.y);
			break;
		case LEFT:
			position_.set(position_.x - body_size_.x, position_.y);
			break;
		case RIGHT:
			position_.set(position_.x + body_size_.x, position_.y);
			break;
	}
}

bool Snake::isDead() const { // dead if pacman goes off the screen
    return (position_.x < 0 || position_.y < 0 || position_.x > screen_dims_.x - body_size_.x
            || position_.y > screen_dims_.y - body_size_.y);
}

void Snake::eatFood(ofColor newBodyColor) {
}

// Resize the snake based on the ratio of old to new position
void Snake::resize(int w, int h) {
	int width = ofGetWindowWidth();
	int height = ofGetWindowHeight();

    float new_x = ((position_.x / screen_dims_.x) * w);
    float new_y = ((position_.y / screen_dims_.y) * h);
    position_.set(new_x, new_y);

    screen_dims_.set(width, height);

	float body_d = kbody_size_modifier_ * width;
	body_size_.set(body_d, body_d);
}

int Snake::getFoodEaten() const {
    return 0;
}

Direction Snake::getDirection() const {
	return current_direction_;
}

void Snake::setDirection(Direction newDirection) {
	current_direction_ = newDirection;
}

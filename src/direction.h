//
//  direction.h
//  final-project-ElizWang
//
//  Created by Elizabeth Wang on 4/20/18.
//

#ifndef location_h
#define location_h

/*class Location {
private:
    ofVec2f position_; // hide access to actual position
    
public:*/
    typedef enum { // directions for moving objects - put in global because all moving objects have the same possible directions
        UP = 0,
        DOWN,
        RIGHT,
        LEFT
    } Direction;
    
    // can make overloaded operators: =<, >, == to comapre positions - of pacmen and ghosts
    // make method to check if location is vlaid
    
    /*bool is_location_valid();
    
    void set_x_position(int x);
    void set_y_position(int y);
    void set_x_y_position(int x, int y);
    
    int get_x_position();
    int get_y_position();
}*/

#endif /* location_h */

#include "Node.hpp"
#include "Illegal_Exception.hpp"

Node::Node( int m, double x0, double y0, double x1, double y1 ) {
    //Throw illegal exception if the boundry is invalid 
    if( ! ( x0 < x1 && y0 < y1 ) ) {
        throw Illegal_Exception();
    }

    this->size_m = m;
    this->x0 = x0;
    this->y0 = y0;
    this->x1 = x1;
    this->y1 = y1;
    this->coordinates = new double*[m];
    for( int i = 0; i < m; i++ ) {
        this->coordinates[i] = new double[2];
        //initialize all input coordinates in the node to 0
        this->coordinates[i][0] = 0;
        this->coordinates[i][1] = 0;
    }

    //initialize coordinates counter to 0
    this->coordinates_counter = 0;
    this->child_node = nullptr;
}


Node::~Node() {
    if( this->coordinates != nullptr ) {
        for (int i = 0; i < this->size_m; i++) {
            delete[] this->coordinates[i];
        }
        //release memory allocated to the parent node for storing the coordinates
        delete[] this->coordinates;
        this->coordinates = nullptr;
    }

    if( this->child_node != nullptr ) {
        for( int i = 0; i < 4; i++ ) {
            delete this->child_node[i];
        }
        delete[] this->child_node;
    }

}


bool Node::insert( double x , double y ) {
    //check if the point is within the boundry of quadtree
    if( x < this->x0 || x > this->x1 || y < this->y0 || y > this->y1 ) {
        return false;
    }

    // Check for duplicates before insertion
    if (this->child_node == nullptr) {
        for (int i = 0; i < this->coordinates_counter; i++) {
            if (x == this->coordinates[i][0] && y == this->coordinates[i][1]) {
                return false;
            }
        }
    }

    //if the current node is not full
    if( this->coordinates_counter < this->size_m ) {
        //insert the points into current node
        this->coordinates[this->coordinates_counter][0] = x;
        this->coordinates[this->coordinates_counter][1] = y;
        //update coordinates counter after insertion
        this->coordinates_counter++;
        return true;
    } else {
        //if the node is full and child node was not intialized
        if( this->child_node == nullptr ) {
            //create child node list
            this->child_node = new Node*[4];
            double center_x = (this->x0 + this->x1) / 2;
            double center_y = (this->y0 + this->y1) / 2;
            this->child_node[0] = new Node( this->size_m , this->x0 , this->y0 , center_x , center_y );
            this->child_node[1] = new Node( this->size_m , center_x , this->y0 , this->x1 , center_y );
            this->child_node[2] = new Node( this->size_m , this->x0 , center_y , center_x , this->y1 );
            this->child_node[3] = new Node( this->size_m , center_x , center_y , this->x1 , this->y1 ); 

            //insert parent node points to child nodes respectively
            for( int i{0}; i < this->size_m; i++ ) {
                double parent_x = this->coordinates[i][0];
                double parent_y = this->coordinates[i][1];
                for( int j{0}; j < 4; j++ ) {
                    this->child_node[j]->insert( parent_x , parent_y );
                }
            }

            //after insertion to the child node, delete points in the parent node
            if( this->coordinates != nullptr ) {
                for (int i = 0; i < this->size_m; i++) {
                    delete[] this->coordinates[i];
                }
                //release memory allocated to the parent node for storing the coordinates
                delete[] this->coordinates;
                this->coordinates = nullptr;
            }
        }

        //insert points into the child node
        for( int i{0}; i < 4; i++ ) {
            if( this->child_node[i]->insert( x , y ) ) {
                return true;
            }
        }
        //return false if the points already exsited in the child nodes
        return false;
    }
}


bool Node::search( double x , double y , double d ) {
    //check if the search area intersect with any node
    //get the closest point on the node to input (x , y)
    double closest_x = std::max( this->x0 , std::min( x , this->x1 ) );
    double closest_y = std::min( y, this->y1 );
    //find straight line distance from cloest point to (x , y)
    double straight_dist = std::sqrt( (x - closest_x) * (x - closest_x) + (y - closest_y) * (y - closest_y) );
    //return false is there is no intersection between node and the circle
    if( straight_dist > d ) {
        return false;
    }

    //check each point stored in the current node
    if( this->child_node == nullptr ) {
        for (int i{0}; i < this->coordinates_counter; i++) {
            double point_x = this->coordinates[i][0];
            double point_y = this->coordinates[i][1];
            double dist_to_point = std::sqrt( (x - point_x) * (x - point_x) + (y - point_y) * (y - point_y) );
            //return true if found a point within distance
            if (dist_to_point <= d) {
                //std::cout << coordinates[i][0] << coordinates[i][1] << std::endl;
                return true;
            }
        }
    }

    //search points in the child node if child node exists
    if( this->child_node != nullptr ) {
        for( int i{0}; i < 4; i++ ) {
            if( this->child_node[i]->search( x , y , d ) == 1 ) {
                return true;
            }
        }
        //return false if no points found in the child node
        return false;
    }
    return false;
}


void Node::range( double xr0 , double yr0 , double xr1 , double yr1 , bool& found )  {
    //Throw illegal argument if the range is not valid
    if( ! ( xr0 < xr1 && yr0 < yr1 ) ) {
        throw Illegal_Exception();
    }
    
    //Check if current node intersects with the range
    if( ! ( xr0 >= this->x1 || xr1 <= this->x0 || yr0 >= this->y1 || yr1 <= this->y0 ) ) {
        //Check each point in the current node
        if( this->child_node == nullptr ) {
            for( int i = 0; i < this->coordinates_counter; i++ ) {
                double current_x = this->coordinates[i][0];
                double current_y = this->coordinates[i][1];
                //print the points if the points is strictly within the boundry of (xr0 , yr0) , (xr1 , yr1)
                if( current_x > xr0 && current_x < xr1 && current_y > yr0 && current_y < yr1 ) {
                    std::cout << current_x << " " << current_y << " ";
                    //update found flag to true since a point is found
                    found = true;
                }
            }
        }
        //Check each child nodes
        if( this->child_node != nullptr ) {
            for( int i = 0; i < 4; i++ ) {
                this->child_node[i]->range( xr0 , yr0 , xr1 , yr1 , found );
            }
        }
    }
}


double* Node::find_nearest( double x , double y ) {
    //initialize min_point to max
    double* min_point = new double[2]{ __DBL_MAX__ , __DBL_MAX__ };
    double min_dist = __DBL_MAX__;
    double* points;
    //check child node if child node exist
    if( this->child_node != nullptr ) {
        for( int i{0}; i < 4; i++ ) {
            points = this->child_node[i]->find_nearest( x , y );
            //calculate distance from the child points to the input point
            double straight_dist_children = std::sqrt( (x - points[0] ) * (x - points[0]) + (y - points[1]) * (y - points[1]) );
            double straight_dist_min = std::sqrt( (x - min_point[0] ) * (x - min_point[0]) + (y - min_point[1]) * (y - min_point[1]) );
            //compare current min distance with the current calculated distance
            if( ( straight_dist_children < straight_dist_min ) 
                || ( straight_dist_children == straight_dist_min 
                && ( points[0] > min_point[0] || (points[0] == min_point[0] && points[1] > min_point[1] ) ) ) ) {
                //swap the value if current min distance is bigger than the current calculated distance
                min_point[0] = points[0];
                min_point[1] = points[1];
            }
            delete[] points;
        }
        return min_point;
    } else {
        for( int i{0}; i < this->coordinates_counter; i++ ) {
            points = this->coordinates[i];
            double straight_dist_children = std::sqrt( (x - points[0] ) * (x - points[0]) + (y - points[1]) * (y - points[1]) );
            double straight_dist_min = std::sqrt( (x - min_point[0] ) * (x - min_point[0]) + (y - min_point[1]) * (y - min_point[1]) );
            if( ( straight_dist_children < straight_dist_min ) 
                || ( straight_dist_children == straight_dist_min 
                && (points[0] > min_point[0] || (points[0] == min_point[0] && points[1] > min_point[1] ) ) ) ) {
                min_point[0] = points[0];
                min_point[1] = points[1];
            }
        }
        return min_point;      
    }
}


void Node::nearest( double x , double y ) {
    //check if the quadtree is empty
    if( this->coordinates_counter == 0 ) {
        std::cout << "no point exists" << std::endl;
    } else {
        double* nearest = find_nearest( x , y );
        std::cout << nearest[0] << " " << nearest[1] << std::endl;
        delete[] nearest;
    }
}


int Node::num() {
    int count = 0;
    if( this->child_node != nullptr ) {
        //initialize min_point to max
        for( int i{0}; i < 4; i++ ) {
            count += this->child_node[i]->num();
        }
        return count;
    } else {
        return this->coordinates_counter;      
    }
}
#include "Node.hpp"
#include "Illegal_Exception.hpp"

int main();

int main() {
    Node* root;
    std::string cmd;

    while( std::cin >> cmd ) {
        if( cmd == "INIT" ) {
            int m = 0;
            double x0 = 0.0;
            double y0 = 0.0;
            double x1 = 0.0;
            double y1 = 0.0;

            std::cin >> m >> x0 >> y0 >> x1 >> y1;

            try {
                root = new Node( m , x0 , y0 , x1 , y1 );
                std::cout << "success" << std::endl;
            } catch (Illegal_Exception e) {
                std::cout << e.what() << std::endl;
            }
        }

        if( cmd == "INSERT" ) {
            double x = 0.0;
            double y = 0.0;

            std::cin >> x >> y;

            if( root->insert( x , y ) ) {
                std::cout << "success" << std::endl;
            } else {
                std::cout << "failure"  << std::endl;
            }
        }

        if( cmd == "SEARCH" ) {
            double x = 0.0;
            double y = 0.0;
            double d = 0.0;

            std::cin >> x >> y >> d;
            if( root->search( x , y , d ) ) {
                std::cout << "point exists" << std::endl;
            } else {
                std::cout << "no point exists" << std::endl;
            }
        }

        if( cmd == "NEAREST" ) {
            double x = 0.0;
            double y = 0.0;

            std::cin >> x >> y;
            root->nearest( x , y );
        }

        if( cmd == "RANGE" ) {
            double xr0 = 0.0;
            double yr0 = 0.0;
            double xr1 = 0.0;
            double yr1 = 0.0;
            bool found_points = false;

            std::cin >> xr0 >> yr0 >> xr1 >> yr1;
            try { 
                root->range( xr0 , yr0 , xr1 , yr1 , found_points);
                if( ! found_points ) {
                    std::cout << "no points within range" << std::endl;
                } else {
                    std::cout << std::endl;
                }
            } catch( Illegal_Exception e ) {
                std::cout << e.what() << std::endl;
            }
        }
        
        if( cmd == "NUM" ) {
            std::cout << root->num() << std::endl;
        }

        if( cmd == "EXIT" ) {
            delete root;
            root = nullptr;
            
            return 0;
        }
    }
}
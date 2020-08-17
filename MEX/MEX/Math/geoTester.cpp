/*#include "vorHeader.hpp"

//Validates Geometry Routines
int main() {
        vecDBL a{ 1,-7, 10 };
        vecDBL b{ 2, 10, 6 };
        for (vecDBL::const_iterator i = a.begin(); i != a.end(); ++i) {
                std::cout << *i << ' ';
        }

        //std::vector<double> c;
        //c.reserve(a.size());

        std::cout << vorGeo::norm(a) << ' ';
        std::cout << vorGeo::dist(a, b) << ' ';

        //c = a;

        //std::cout << test << ' ';
        //c = normalize(a - b);

        //for(vecDBL::const_iterator i = c.begin(); i != c.end(); ++i){
        //	std::cout << *i << ' ';
        //}

        //std::cout << dist(a, b) << ' ';

        //std::cout << checkLeftOf(a, b, d) << ' ';

        vecDBL c = vorGeo::Intersect2d(a, b);
        for (vecDBL::const_iterator i = c.begin(); i != c.end(); ++i) {
                std::cout << *i << ' ';
        }

        return 0;
}*/
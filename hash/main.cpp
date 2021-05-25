//
//  main.cpp
//  hash
//
//  Created by Klaus Ahrens on 22.06.18.
//  Copyright © 2018 Klaus Ahrens. All rights reserved.
//

#include <iostream>
#include <unordered_set>

class X {
public:
    X* i_= 0;

    X():i_{this} {}
    X(const X& other):i_{this}{std::cout<<"copy\n";}
    friend std::ostream& operator<<
    (std::ostream& o, const X& x)
    {return o<<x.i_;}
    friend struct std::hash<X>;
    bool operator==(const X&) const
    {return false;}
};

template<>
struct std::hash<X> {
      size_t operator()(const X& x) const {
        return hash<const X*>()(&x);
      }
};

int main() {
    std::unordered_multiset<X> xs;

    for (int i=0; i<10; ++i) { X x{}; xs.insert(x); }
    for (int i=0; i<10; ++i) { X x{}; xs.insert(x); }
 
    for (auto& x: xs) {std::cout<<&x<<" ";}
    //for (auto& x: xs) {std::cout<<x<<" ";}
    std::cout<<"\n";
    for (size_t bc=0; bc<xs.bucket_count(); ++bc)
        std::cout<<"bucket["<<bc<<"]: "<< xs.bucket_size(bc) <<"\n";
    std::cout<< xs.load_factor() << "\n";
    xs.rehash(10);
    for (size_t bc=0; bc<xs.bucket_count(); ++bc)
        std::cout<<"bucket["<<bc<<"]: "<< xs.bucket_size(bc) <<"\n";
    std::cout<< xs.load_factor() << "\n";
}

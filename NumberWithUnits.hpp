//
// Created by david on 4/16/21.
//

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "WDGraph.hpp"

namespace ariel {

    class NumberWithUnits {

    public:
        static void read_units (std::ifstream& file);

        NumberWithUnits(const double num, const std::string unitIn);

        //overloading operators +=,+,-=,-
        NumberWithUnits operator+() const;
        NumberWithUnits operator-() ;

        NumberWithUnits operator+=(NumberWithUnits const & other);
        NumberWithUnits operator-=(NumberWithUnits const & other) ;

        friend NumberWithUnits operator-(NumberWithUnits const & other) ;
        friend NumberWithUnits operator-(const NumberWithUnits&, const NumberWithUnits&);
        friend NumberWithUnits operator+(NumberWithUnits const & other) ;
        friend NumberWithUnits operator+(NumberWithUnits const & other,NumberWithUnits const & other1) ;

        //overloading operators <,>,<=,>=
        friend  bool operator< (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2);
        friend  bool operator> (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2);
        friend  bool operator<=(const NumberWithUnits& nwu1, const NumberWithUnits& nwu2);
        friend  bool operator>=(const NumberWithUnits& nwu1, const NumberWithUnits& nwu2);

        //overloading operators ==,!=
        friend bool operator==(const NumberWithUnits& lhs, const NumberWithUnits& rhs);
        friend bool operator!=(const NumberWithUnits& lhs, const NumberWithUnits& rhs);

        friend  std::ostream& operator<<( std::ostream& os, const NumberWithUnits& nwu);
        friend  std::istream& operator>>( std::istream &is, NumberWithUnits &nwu);



        /////////////////////////need to change a bit//////////////////////////////////////////
        // prefix increment
        NumberWithUnits& operator++()
        {
            // actual increment takes place here
            return *this; // return new value by reference
        }

        // postfix increment
        NumberWithUnits operator++(int)
        {
            NumberWithUnits old = *this; // copy old value
            operator++();  // prefix increment
            return old;    // return old value
        }

        // prefix decrement
        NumberWithUnits& operator--()
        {
            // actual decrement takes place here
            return *this; // return new value by reference
        }

        // postfix decrement
        NumberWithUnits operator--(int)
        {
            NumberWithUnits old = *this; // copy old value
            operator--();  // prefix decrement
            return old;    // return old value
        }
        /////////////////////////////////need to change a bit//////////////////////////////////////////

        //overloading operator *
        friend NumberWithUnits operator*(const NumberWithUnits &nwu, double n);

        friend NumberWithUnits operator*(double number, const NumberWithUnits &nwu);

        friend NumberWithUnits operator*(const NumberWithUnits &nwu, int number);

        friend NumberWithUnits operator*(int number, const NumberWithUnits &nwu);


    private:
        //represent the value of the object (100 g , number = 100)
        double number;
        //represent the unit of the object (100 g , unit = g)
        std::string unit;

        static wdg::WDGraph graph;

        static void buildNodesReadUnits(std::string firstU, std::string secondU, double val);
    };


}
//
// Created by david on 4/16/21.
//

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <list>
#include <utility>
#include "wdgraph.hpp"


namespace ariel {


    class NumberWithUnits {

    public:
        /**
        * read_units function read units from ifstream and put the data in the graph
        * every row in the file should be in that pattern :
        * 1 'unit1' =  'value' 'unit2'
        * @param file repersent the read file that the function read from
        */
        static void read_units (std::ifstream& file);
        //constructor
        NumberWithUnits(double num,  const std::string& unitIn);
        NumberWithUnits( ){this->number=0;}
        ~NumberWithUnits()= default;


        //overloading operators +=,+,-=,-
        NumberWithUnits operator+() const;
        NumberWithUnits operator-() ;

        NumberWithUnits operator+=(NumberWithUnits const & other);
        NumberWithUnits operator-=(NumberWithUnits const & other) ;

//        friend NumberWithUnits operator-(NumberWithUnits const & other) ;
        friend NumberWithUnits operator-(const NumberWithUnits&, const NumberWithUnits&);
//        friend NumberWithUnits operator+(NumberWithUnits const & other) ;
        friend NumberWithUnits operator+(NumberWithUnits const & a,NumberWithUnits const & b) ;

        //overloading operators <,>,<=,>=
        friend  bool operator< (const NumberWithUnits& a, const NumberWithUnits& b);
        friend  bool operator> (const NumberWithUnits& a, const NumberWithUnits& b);
        friend  bool operator<=(const NumberWithUnits& a, const NumberWithUnits& b);
        friend  bool operator>=(const NumberWithUnits& a, const NumberWithUnits& b);

        //overloading operators ==,!=

        bool operator==(const NumberWithUnits& b) const;
        bool operator!=(const NumberWithUnits& b) const;

        friend  std::ostream& operator<<( std::ostream& os, const NumberWithUnits& nwu);
        friend  std::istream& operator>>( std::istream &is, NumberWithUnits &nwu);


        // prefix increment
        NumberWithUnits& operator++(){
            //increment by one the number
            this->number= this->number+1;
            return *this;
        }

        // postfix increment
        NumberWithUnits operator++(int){
            // copy old value
            NumberWithUnits old = *this;
            // prefix increment
            operator++();
            // return old value
            return old;
        }

        // prefix decrement
        NumberWithUnits& operator--(){
            //  decrement by one the number
            this->number = this->number -1;
            return *this;
        }

        // postfix decrement
        NumberWithUnits operator--(int)
        {
            NumberWithUnits old = *this; // copy old value
            operator--();  // prefix decrement
            return old;    // return old value
        }

        //overloading operator *
        friend NumberWithUnits operator*(const NumberWithUnits &nwu, double n);
        //note: first this but friend allow to put the other obj first
        friend NumberWithUnits operator*(double number, const NumberWithUnits &nwu);

        friend NumberWithUnits operator*(const NumberWithUnits &nwu, int number);

        friend NumberWithUnits operator*(int number, const NumberWithUnits &nwu);


    private:
        //represent the value of the object (100 g , number = 100)
        double number{};
        //represent the unit of the object (100 g , unit = g)
        std::string unit;

        //the graph is static because I want it to keep all the connction\rate from all objects NumberWithUnits
        static WDGraph graph;
        /**
        * buildNodesReadUnits function build Nodes and put the in the graph
        * the function build according to this pattern :
        * 1 'unit1' =  'value' 'unit2'
        *
        * @param firstU represent the first unit
        * @param secondU represent the second unit
        * @param val represent the value of the second unit
        */
        static void buildNodesReadUnits(const std::string& firstU, const std::string& secondU, double val);
    };


}
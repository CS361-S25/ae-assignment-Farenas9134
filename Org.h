#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

class Organism {
    public:
    double points;
    emp::Ptr<emp::Random> random;

    Organism(emp::Ptr<emp::Random> _random, double _points=0.0) :
        points(_points), random(_random) {;}

    void SetPoints(double _in) {points = _in;}
    void AddPoints(double _in) {points += _in;}


    // Updates point value by given points
    virtual void Process(double given_points) {
        points += given_points;
    }

    // If organism has 1000 points, it reproduces
    virtual emp::Ptr<Organism> CheckReproduction() {
        if (points == 1000) {
            emp::Ptr<Organism> offspring = new Organism(*this);
            offspring->SetPoints(0);
            SetPoints(0);
            return offspring;
        }
        return nullptr;
    }

    virtual std::string SpeciesName() const{
        return "Generic";
    }

    virtual std::string SpeciesColor() const{
        return "black";
    }

};

#endif
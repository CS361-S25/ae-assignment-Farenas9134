#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

class Organism {
    public:
    double points;
    int age;
    bool hasEaten = false;
    int daysuntildead = 5;

    emp::Ptr<emp::Random> random;

    Organism(emp::Ptr<emp::Random> _random, double _points=0.0, int _age=0) :
        points(_points), random(_random) {;}

    void SetPoints(double _in) {points = _in;}
    void AddPoints(double _in) {points += _in;}


    // Updates point value by given points
    virtual void Process(double given_points) {
        points += given_points;
        age++;
        if (hasEaten == false){
            points -= 20;
        }
    }

    // If organism has 1000 points, it reproduces
    virtual emp::Ptr<Organism> CheckReproduction() {
        if (points >= 1000) {
            emp::Ptr<Organism> offspring = new Organism(*this);
            offspring->SetPoints(0);
            std::cout << "Org points set to zero" << std::endl;
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

    virtual bool SpeciesEat(Organism* other) {
        if (other->SpeciesName() == "Grass") {
            std::cout << "Deer ate!" << std::endl;
            points += 120;
            return true;
        }
        else {
            return false;
        }
    }

    virtual bool CheckShouldOrgDie() {
        if (points <= -1000){
            return true;
        }
        return false;
    }
};

#endif
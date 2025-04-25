#ifndef DEER_H
#define DEER_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "Org.h"

class Deer : public Organism {
    private:
        int age;

    public:
        Deer(emp::Ptr<emp::Random> _random, double _points = 0.0, int _age=0)
            : Organism(_random, _points), age(0) {}

        std::string SpeciesName() const override {
            return "Deer";
        }
};

#endif
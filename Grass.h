#ifndef GRASS_H
#define GRASS_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "Org.h"

class Grass : public Organism {
    private:
        int age;

    public:
        Grass(emp::Ptr<emp::Random> _random, double _points = 0.0)
            : Organism(_random, _points), age(0) {}

        void Process(double given_points) override {
            AddPoints(given_points * 1.5);
            age++;
        }

        emp::Ptr<Organism> CheckReproduction() override {
            if (age == 3){
                emp::Ptr<Grass> grassOffSpring = new Grass(random, 0.0);
                grassOffSpring->SetPoints(0);
                return grassOffSpring;
            }
            return nullptr;
        }

        std::string SpeciesName() const override {
            return "Grass";
        }

        std::string SpeciesColor() const override {
            return "green";
        }
};

#endif
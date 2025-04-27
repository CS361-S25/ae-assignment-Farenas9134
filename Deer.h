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

        void Process(double given_points) override {
            AddPoints(-30);  // cost of metabolism
            age++;
        }

        emp::Ptr<Organism> CheckReproduction() override {
            if (points > 900){
                points = 200;
                emp::Ptr<Deer> deerOffSpring = new Deer(random, 0.0);
                deerOffSpring->SetPoints(0);
                return deerOffSpring;
            }
            return nullptr;
        }

        bool CheckShouldOrgDie() override {
            if (points <= -400){
                return true;
            }
            return false;
        }
};

#endif
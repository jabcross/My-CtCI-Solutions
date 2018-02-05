#include <bits/stdc++.h>
using namespace std;

enum Species {
    CAT,
    DOG
};

class Animal { 
    public:
    Species species;
    int serial;
    int id;

    Animal(Species _species, int _id){
        serial = -1;
        species = _species;
        id = _id;
    }
};

class AnimalQueue {
    private:
    queue<Animal> dogs, cats;
    int time = 0;

    public:
    void enqueue(Animal animal){
        animal.serial = time;
        if (animal.species == DOG){
            dogs.push(animal);
        }
        if (animal.species == CAT){
            cats.push(animal);
        }
        time++;
    }
    Animal dequeueAny(){
        if (cats.front().serial < dogs.front().serial){
            return dequeueCat();
        }
        else {
            return dequeueDog();
        }
    }
    Animal dequeueCat(){
        Animal rv = cats.front();
        cats.pop();
        return rv;
    }
    Animal dequeueDog(){
        Animal rv = dogs.front();
        dogs.pop();
        return rv;
    }

};

int main(){
    Animal cat1(CAT, 1);
    Animal cat2(CAT, 2);
    Animal dog1(DOG, 3);
    Animal dog2(DOG, 4);

    AnimalQueue shelter;

    shelter.enqueue(cat2);
    shelter.enqueue(dog1);
    shelter.enqueue(dog2);
    shelter.enqueue(cat1);

    assert(shelter.dequeueAny().id == 2);
    assert(shelter.dequeueCat().id == 1);
    assert(shelter.dequeueDog().id == 3);

    cout << "Tests passed" << endl;

    return 0;
}
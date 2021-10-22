// ClassAnimal_classwork15.10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>

using namespace std;


class Animal 
{
public:
    Animal() { name = "Tom"; age = 10;}
    Animal(string name,int age)
    {
        this->name = name;
        this->age = age;
    }
    int age;
    string name;
    void voice()
    {
        cout << name << " " << "Says nothing" << endl;
    }
    void info()
    {cout << name <<" " << age << endl; }
};

class Home_animal : public Animal
{
public:
    string kind;
    Home_animal() 
    { 
    name = "Jack";
    age = 10; 
    kind = "Lion";
    }
    Home_animal(string name,string breed)
    {
        this->name = name;
        this->kind = kind;
    }
    void exhibition() 
    { cout << name << " " << "is" << " " << kind << endl;}
};

class Cat : public Home_animal
{
public:
    int IQ;
    Cat(string name,int IQ)
    { 
        this->name = name;
        this->IQ = IQ;
    }
    void stupid_owner() 
    { 
        cout<<"This cat`s name is "<< name << ". " << "Its` IQ is" << IQ <<" "<< "it is bigger then his owners`" << endl;
    }
};
class Dog : public Home_animal
{
public:
    int love;
    Dog(string name, int love) 
    {
        this->name = name;
        this->love = love;
    }
    void favourite_owner() 
    { 
        cout << "This dog" << " " << name << " " << "loves its` owner this much  " << love << endl; 
    }

};

class Toy:
{
public:
    string typee;
    string colour;
    int amount;
    Toy(string typee, string colour, int amount)
    {
        this->typee = typee;
        this->colour = colour;
        this->amount = amount;
    }
    void sound()
    {
        cout<<"Пищииит"
    }

};



int main()
{
    Animal Rat("Jerry", 2);
    Rat.info();
    Rat.voice();
    Cat Tomas("Tom", 260);
    Tomas.stupid_owner();
    Tomas.voice();
    Dog Louis ("Lim",500);
    Louis.favourite_owner();
    Louis.info();
};
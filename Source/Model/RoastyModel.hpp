#ifndef ROASTYMODEL_H
#define ROASTYMODEL_H
#include <list>
#include <string>

class Bean {
    std::string name;

    public:
    Bean(); // Other constructors?
    std::string getName();
    std::string const getName() const; // overload on const-ness

    Bean& operator=(Bean other) {
        this->name.assign(other.name);
        return *this;
    }
};

class Ingredient {
    Bean ingredientBean;
    int amount = 0;

    public:
    Bean getBean();
    Bean const getBean() const; // overload on const-ness
    Ingredient(Bean bean, int newAmount);
    Ingredient(){};
};

class Event {
    long roastId;
    long eventTimestamp;

    public:
    long getTimestamp();
}; 

class Roast {
    long id;
    long timestamp;
    std::list<Ingredient> ingredients; // need to have multiple ingredients
    std::list<Event> events;

    public:
    long getTimestamp();
    // === Ingredients ===
    Ingredient getIngredient(int index);
    int getIngredientsCount();
    void addIngredient(Ingredient ingredient); // Do I need to overload for Roasty.cpp line 126?
    void removeIngredientByBeanName(std::string beanName);
    // === Events ===
    Event getEvent(int index);
    // Event const& getEvent(int index) const;
    int getEventCount();
    void addEvent(Event event);
    void removeEventFromRoast();
    void removeEventByTimestamp(long eventTimestamp);
};

class StorageImplementation {
    std::list<Bean> beans;

    public:
    std::list<Bean> getBeans();
    Bean getBeanByBeanName(std::string beanName);
    Bean getBeanByStorageIndex(int i);

};

// ======= Overloading operators =========
bool operator==(std::string const& name, Ingredient const& ing) {return ing.getBean().getName() == name;}; // define comparing operator 
bool operator==(std::string const& name, Bean const& bean) {return bean.getName() == name;};


#endif
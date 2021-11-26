#ifndef ROASTYMODEL_H
#define ROASTYMODEL_H
#include <string>

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ======================= BEAN =========================
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Bean {
    std::string name;

public:
    // ------- Construction -------
    Bean(std::string const& name); // constructor
    Bean(Bean const& copyBean); // copy constructor
    Bean& operator=(Bean const& copyBean); // assignment
    ~Bean(){}; // default constructor explicitly defined to abide by rule of 3

    // ------- Getter functions -------
    std::string const& getName () const;
};

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ==================== INGREDIENT ======================
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Ingredient {
    Bean ingredientBean;
    int beanAmount;

public:
    Ingredient* nextIngredient = nullptr;

    // ------- Construction -------
    Ingredient(Bean const& bean, int amount); // constructor
    Ingredient(Ingredient const& copyIngredient); // copy constructor
    Ingredient& operator=(Ingredient const& copyIngredient); // assignment
    ~Ingredient(){}; // default constructor explicitly defined to abide by rule of 3
    
    // ------- Getters and setters -------
    Bean const& getBean() const;
    int getAmount() const;
    void setAmount(int amount);
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ==================== EVENT VALUE ======================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
class EventValue {
    long value;

public:
    // ------- Construction -------
    EventValue(long setValue); // constructor
    EventValue(EventValue const& copyValue); // copy constructor
    EventValue& operator=(EventValue const& copyValue); // assignment
    ~EventValue(){}; // default constructor explicitly defined to abide by rule of 3
    
    // ------- Getters and setters -------
    long getValue() const;
    void setValue(long setValue);
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ======================= EVENT =========================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Event{
    std::string eventType;
    long eventTimestamp;
    EventValue* eventValue = nullptr; //optional

public:
    Event* nextEvent = nullptr;

    // ------- Construction -------
    Event(std::string const& type, long timestamp); // constructor without eventValue
    Event(std::string const& type, long timestamp, EventValue* copyValue); // with eventValue
    Event(Event const& copyEvent); // copy constructor
    Event& operator=(Event& copyEvent); // assignment
    ~Event(); // deconstructor must delete extra objects

    // ------- Getters and setters -------
    std::string const& getType() const;
    long getTimestamp() const;
    EventValue* getValue() const;
    bool hasValue() const; // for the hasValue test in RoastyTests.cpp
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ======================= ROAST =========================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Roast {
    long roastTimestamp;
    int numberOfIngredients = 0;
    int numberOfEvents = 0;
    // numbers of ingredients are initialized to 0, they are incremented by 1 when add function called, and decremented by 1 when removed
    // this way we do not need to iterate through the linked list every time we call getXXXcount

public:
    Ingredient* ingredientHead = nullptr;
    Event* eventHead = nullptr;

    // ------- Construction -------
    Roast(long timestamp); // constructor
    Roast(Roast const& copyRoast); // copy constructor
    Roast& operator=(Roast const& copyRoast); // assignment
    ~Roast(); // deconstructor

    // ------- Adders -------
    void addIngredient(Ingredient const& ingredient);
    void addEvent(Event const& event);

    // ------- Removers -------
    void removeIngredientByBeanName(std::string const& beanName);
    void removeEventByTimestamp(long timestamp);

    // ------- Getter functions -------
    long getTimestamp() const;
    int getEventCount() const;
    int getIngredientsCount() const;
    Event const& getEventByTimestamp(long timestamp) const;
    Ingredient& getIngredient(int index) const;
    Event& getEvent(int index) const;
};

#endif
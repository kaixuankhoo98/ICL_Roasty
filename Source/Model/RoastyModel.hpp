#ifndef ROASTYMODEL_H
#define ROASTYMODEL_H
#include <string>

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ======================= BEAN =========================
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Bean {
    std::string name;

public:
    // Construction
    Bean(std::string const& beanName);
    Bean(Bean const& copyBean);
    Bean& operator=(Bean const& copyBean);
    Bean(){};

    // Getter functions
    std::string const& getName() const;

    // Bean& operator=(Bean other) {
    //     this->name.assign(other.name);
    //     return *this;
    // }
};

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ==================== INGREDIENT ======================
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Ingredient {
    Bean ingredientBean;
    int beanAmount;

public:
    // Construction
    Ingredient(Bean const& bean, int newAmount);
    Ingredient(Ingredient const& copyIngredient);
    Ingredient& operator=(Ingredient const& copyIngredient);
    ~Ingredient(){};

    // Getter functions
    Bean const& getBean() const;
    int getAmount() const;
    
    // Setter functions
    void setAmount(int const newAmount);

    Ingredient* next = nullptr; // For linked list
    
    // Bean getBean();
    // Bean const getBean() const; // overload on const-ness
    // Ingredient(Bean bean, int newAmount);
    // Ingredient(){};
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ==================== EVENT VALUE ======================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
class EventValue {
    long value;

public:
    // Construction
    EventValue(long startValue);
    EventValue(EventValue const& copyEventValue);
    EventValue& operator=(EventValue const& copyEventValue);
    //~Event(); ?? Why isn't this working

    // Getter functions
    long getValue() const;

    // Setter functions
    void setValue(long valueToSet);
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ======================= EVENT =========================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Event {
    // long roastId;
    long eventTimestamp;
    std::string eventType;
    EventValue* eventValue = nullptr;

public:
    // Construction 
    Event(std::string const& type, long timestamp);
    Event(std::string const& type, long timestamp, EventValue* eventValuePtr); // with event value
    Event(Event const& copyEvent);
    Event& operator=(Event const& copyEvent);
    ~Event(){delete eventValue;};

    // Getter functions
    long getTimestamp() const;
    std::string const& getType() const;
    EventValue* getValue() const;

    bool hasValue() const; // Does eventValue point to something??

    Event* next = nullptr; // Linked list
}; 

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ======================= ROAST =========================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Roast {
    // long id;
    long roastTimestamp; // Identifier

    // Lists of ingredients and events
    // std::list<Ingredient> ingredients; // need to have multiple ingredients
    // std::list<Event> events;
    Ingredient* ingredientHead = nullptr;
    int numberOfIngredients = 0; // initialized to zero? add ingredient will increase by 1
    Event* eventHead = nullptr;
    int numberOfEvents = 0;

public:
    // Construction
    Roast(long timestamp);
    ~Roast(){delete ingredientHead; delete eventHead;};
    Roast(Roast const& copyRoast);
    Roast& operator=(Roast const& copyRoast);

    // Adder funcitons
    void addIngredient(Ingredient const& newIngredient);
    void addEvent(Event const& newEvent);

    // Getter functions
    long getTimestamp() const;
    int getIngredientsCount() const;
    int getEventCount() const;
    // Non-constant references to const functions
    Ingredient& getIngredient(int index) const;
    Event& getEvent(int index) const;
    Ingredient& getIngredientByBeanName(std::string const& beanName) const;
    Event& getEventByTimestamp(long eventTimestamp) const;

    // Removers:
    void removeIngredientByBeanName(std::string const& beanName);
    void removeEventByTimestamp(long eventTimestamp);

    // long getTimestamp() const;
    // // === Ingredients ===
    // // Ingredient getIngredient(int index);
    // Ingredient const& getIngredient(int index) const;
    // int getIngredientsCount();
    // void addIngredient(Ingredient ingredient); // Do I need to overload for Roasty.cpp line 126?
    // void removeIngredientByBeanName(std::string beanName);
    // // === Events ===
    // // Event getEvent(int index);
    // Event const& getEvent(int index) const;
    // int getEventCount();
    // void addEvent(Event event);
    // void removeEventFromRoast();
    // void removeEventByTimestamp(long eventTimestamp);
    
};

// // ======= Overloading operators =========
// bool operator==(std::string const& name, Ingredient const& ing) {return ing.getBean().getName() == name;}; // define comparing operator 
// bool operator==(std::string const& name, Bean const& bean) {return bean.getName() == name;};


#endif
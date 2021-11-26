#include "RoastyModel.hpp"
#define NO_SUCH_MEMBER_IN_LIST 69

// =============== Bean ===================
// constructor
Bean::Bean(std::string const& beanName)
    : name(beanName){}
// copy constructor
Bean::Bean(Bean const& copyBean)
    : name(copyBean.name) {}
// assignment operator
Bean& Bean::operator=(Bean const& copyBean) {
    name = copyBean.name;
    return *this;
}
// getter
std::string const& Bean::getName() const {
    return name;
}

// =========== Ingredient ================
// constructor
Ingredient::Ingredient(Bean const& bean, int amount)
    : bean(bean), amount(amount) {}
// copy constructor
Ingredient::Ingredient(Ingredient const& copyIngredient)
    : bean(copyIngredient.bean), amount(copyIngredient.amount),
    next(copyIngredient.next) {}
// assignment operator
Ingredient& Ingredient::operator=(Ingredient const& copyIngredient) {
    bean = copyIngredient.bean;
    amount = copyIngredient.amount;
    next = copyIngredient.next;
    return *this;
}
// getter and setter
Bean const& Ingredient::getBean() const {
    return bean;
}
int Ingredient::getAmount() const {
    return amount;
}
void Ingredient::setAmount(int newAmount) {
    this->amount = newAmount;
}

// ============= Event Value ===============
// constructor
EventValue::EventValue(long value)
    : value(value) {}
// copy constructor 
EventValue::EventValue(EventValue const& copyEventValue)
    : value(copyEventValue.value) {}
// assignment operator
EventValue& EventValue::operator=(EventValue const& copyEventValue) {
    value = copyEventValue.value;
    return *this;
}
// getter and setter
long EventValue::getValue() const {
    return value;
}
void EventValue::setValue(long valueToSet) {
    value = valueToSet;
}

// =========== Events ===========
// constructor without eventValue
Event::Event(std::string const& type, long timestamp)
    : type(type), timestamp(timestamp) {}
// constructor with eventValue
Event::Event(std::string const& type, long timestamp, EventValue* eventValuePtr)
    : type(type), timestamp(timestamp) {
        eventValue = new EventValue(eventValuePtr->getValue());
    }
// copy constructor
Event::Event(Event const& copyEvent)
    : type(copyEvent.type), timestamp(copyEvent.timestamp), next(copyEvent.next) {
        if (copyEvent.eventValue != nullptr) {
            this-> eventValue = new EventValue(*copyEvent.eventValue);
        }
    }
// assingment operator
Event& Event::operator=(Event const& copyEvent) {
    type = copyEvent.type;
    timestamp = copyEvent.timestamp;
    eventValue = copyEvent.eventValue;
    next = copyEvent.next;
    return *this;
}



// -------------- GETTER & SETTER FUNCTIONS --------------
long Event::getTimestamp() const {
    return timestamp;
}
std::string const& Event::getType() const {
    return type;
}
EventValue* Event::getValue() const{
    return eventValue;
}

bool Event::hasValue() const {
    if (eventValue == nullptr)
        return false;
    return true;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ======================= ROAST =========================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// -------------------- CONSTRUCTION ---------------------
Roast::Roast(long timestamp) 
    : roastTimestamp(timestamp) {}
// copy constructor 
Roast::Roast(Roast const& copyRoast) 
    : roastTimestamp(copyRoast.roastTimestamp),
    numberOfIngredients(copyRoast.numberOfIngredients),
    numberOfEvents(copyRoast.numberOfEvents) {
    // let's do the hard part and copy everything from the copyRoast!
    if (copyRoast.ingredientHead != nullptr) {
        ingredientHead = new Ingredient(*copyRoast.ingredientHead);
        Ingredient* toIng = ingredientHead; // copies ingredient list to this Roast
        Ingredient* copyIng = copyRoast.ingredientHead->next; // from this copyRoast (what it's pointing to)!
        while (copyIng != nullptr) {
            toIng->next = new Ingredient(*copyIng);
            toIng = toIng->next;
            copyIng = copyIng->next;
        }
    }
    if (copyRoast.eventHead != nullptr) {
        eventHead = new Event(*copyRoast.eventHead);
        Event* toEve = eventHead; // copies ingredient list to this Roast
        Event* copyEve = copyRoast.eventHead->next; // from this copyRoast (what it's pointing to)!
        while (copyEve != nullptr) {
            toEve->next = new Event(*copyEve);
            toEve = toEve->next;
            copyEve = copyEve->next;
        }
    }

    // Ingredient* fromIng = copyRoast.ingredientHead;
    // Ingredient* toIng = this->ingredientHead;
    // while (fromIng != nullptr) {
    //     toIng = fromIng;
    //     toIng = toIng->next;
    //     fromIng = fromIng->next;
    // }

    // Event* fromEve = copyRoast.eventHead;
    // Event* toEve = this->eventHead;
    // while (fromEve != nullptr) {
    //     toEve = fromEve;
    //     toEve = toEve->next;
    //     fromEve = fromEve->next;
    // }
} 
// destructor???
// ------------------ ADDER FUNCTIONS --------------------
void Roast::addIngredient(Ingredient const& newIngredient) {
    // IF STATEMENT TO CHECK IF INGREDIENT IS ALREADY IN LIST ?? 
    // Ingredient ing = Ingredient(newIngredient);
    // Ingredient* ingPtr = &ing;
    // Assign new head if empty list
    if (ingredientHead == nullptr) {
        ingredientHead = new Ingredient(newIngredient);
    } else { // iterate to end of list
        Ingredient* previousPtr = ingredientHead;
        while (previousPtr->next != nullptr) {
            previousPtr = previousPtr->next;
        }
        previousPtr->next = new Ingredient(newIngredient);
    }
    numberOfIngredients++;
    // // Go to end of list
    // Ingredient* temp = ingredientHead;
    // while (temp->next != nullptr) {
    //     temp = temp->next;
    // }
    // temp->next = ingPtr;
    // numberOfIngredients++;
}
void Roast::addEvent(Event const& newEvent) {
    // Assign new head if empty list
    if (eventHead == nullptr) {
        eventHead = new Event(newEvent);
    } else {
        Event* previousPtr = eventHead;
        while (previousPtr->next != nullptr) {
            previousPtr = previousPtr->next;
        }
        previousPtr->next = new Event(newEvent);
    }
    numberOfEvents++;
}
// void Roast::addEvent(Event const& newEvent) {
//     Event* next = eventHead;
//     eventHead = new Event(newEvent);
//     eventHead->next = next;
// }
// -------------- GETTER & SETTER FUNCTIONS --------------
long Roast::getTimestamp() const {
    return roastTimestamp;
}
int Roast::getIngredientsCount() const {
    return numberOfIngredients;
}
// int Roast::getEventCount() const {
//     return numberOfEvents;
// }
int Roast::getEventCount() const {
    int result = 0;
    for(Event* iterator = eventHead; iterator != nullptr; iterator = iterator->next) {
        result++;
    }
    return result;
}
Ingredient& Roast::getIngredient(int index) const {
    Ingredient* ingredientPtr = ingredientHead;
    for (int i = 0; i < index; i++) {
        ingredientPtr = ingredientPtr->next;
    }
    return *ingredientPtr;
}
Event& Roast::getEvent(int index) const {
    Event* eventPtr = eventHead;
    for (int i = 0; i < index; i++) {
        eventPtr = eventPtr->next;
    }
    return *eventPtr;
}
Ingredient& Roast::getIngredientByBeanName(std::string const& beanName) const {
    Ingredient* ingredientPtr = ingredientHead;
    while (ingredientPtr->getBean().getName() != beanName) {
        ingredientPtr = ingredientPtr->next;
    }
    if (ingredientPtr == nullptr) {
        exit(NO_SUCH_MEMBER_IN_LIST);
    }
    return *ingredientPtr;
}
Event& Roast::getEventByTimestamp(long eventTimestamp) const {
    Event* eventPtr = eventHead;
    while (eventPtr->getTimestamp() != eventTimestamp) {
        eventPtr = eventPtr->next;
    }
    if (eventPtr == nullptr) {
        exit(NO_SUCH_MEMBER_IN_LIST);
    }
    return *eventPtr;
}

// ----------------- REMOVER FUNCTIONS -------------------
void Roast::removeIngredientByBeanName(std::string const& beanName) {
    Ingredient* previousPtr = ingredientHead;
    Ingredient* currentPtr = ingredientHead;
    while (currentPtr != nullptr) {
        if (currentPtr->getBean().getName() == beanName) {
            break;
        }
        else {
            previousPtr = currentPtr;
            currentPtr = currentPtr->next;
        }
    }
    if (currentPtr == nullptr) {
        exit(NO_SUCH_MEMBER_IN_LIST);
    }
    else {
        previousPtr->next = currentPtr->next;
        delete currentPtr;
    }
}
void Roast::removeEventByTimestamp(long eventTimestamp) {
    Event* previousPtr = eventHead;
    Event* currentPtr = eventHead;
    if (eventHead != nullptr) {
        currentPtr = currentPtr->next;
    } // ??? In case nothing in the list
    while (currentPtr != nullptr) {
        if (currentPtr->getTimestamp() == eventTimestamp) {
            break;
        }
        else {
            previousPtr = currentPtr;
            currentPtr = currentPtr->next;
        }
    }
    if (currentPtr == nullptr) {
        exit(NO_SUCH_MEMBER_IN_LIST);
    } 
    else {
        previousPtr->next = currentPtr->next;
        delete currentPtr;
    }
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ================ OPERATOR OVERLOADING =================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++

Roast& Roast::operator=(Roast const& copyRoast) {
    roastTimestamp = copyRoast.roastTimestamp;
    numberOfIngredients = copyRoast.numberOfIngredients;
    numberOfEvents = copyRoast.numberOfEvents;
    
    this->ingredientHead = nullptr;
    this->eventHead = nullptr;

    //delete
    Event* currentEventPtr = eventHead;
    while (currentEventPtr != nullptr) {
        Event* nextEventPtr = currentEventPtr->next;
        delete currentEventPtr;
        currentEventPtr = nextEventPtr;
    }

    //copy 
    if (copyRoast.ingredientHead != nullptr) {
        this->ingredientHead = new Ingredient(*copyRoast.ingredientHead);
        Ingredient* toIng = ingredientHead;
        Ingredient* copyIng = copyRoast.ingredientHead->next;
        while (copyIng != nullptr) {
            toIng->next = new Ingredient(*copyIng);
            toIng = toIng->next;
            copyIng = copyIng->next;
        }
    }
    if (copyRoast.eventHead != nullptr) {
        this->eventHead = new Event(*copyRoast.eventHead);
        Event* toEve = eventHead;
        Event* copyEve = copyRoast.eventHead->next;
        while (copyEve != nullptr) {
            toEve->next = new Event(*copyEve);
            toEve = toEve->next;
            copyEve = copyEve->next;
        }
    }
    // Ingredient* fromIng = copyRoast.ingredientHead;
    // Ingredient* toIng = this->ingredientHead;
    // while (fromIng != nullptr) {
    //     toIng = fromIng;
    //     toIng = toIng->next;
    //     fromIng = fromIng->next;
    // }

    // Event* fromEve = copyRoast.eventHead;
    // Event* toEve = this->eventHead;
    // while (fromEve != nullptr) {
    //     toEve = fromEve;
    //     toEve = toEve->next;
    //     fromEve = fromEve->next;
    // }

    return *this;
}
#include "RoastyModel.hpp"
#define NO_SUCH_MEMBER_IN_LIST 69 // hehe

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ======================== BEAN =========================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// -------------------- CONSTRUCTION ---------------------
// constructor
Bean::Bean(std::string const& name)
    : name(name) {}
// copy constructor
Bean::Bean(Bean const& copyBean)
    : name(copyBean.name) {}
// assignment overload
Bean& Bean::operator=(Bean const& copyBean) {
    name = copyBean.name;
    return *this;
}
// ------------------ GETTER FUNCTIONS -------------------
std::string const& Bean::getName () const {
    return name;
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ===================== INGREDIENT ======================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// -------------------- CONSTRUCTION ---------------------
// constructor
Ingredient::Ingredient(Bean const& bean, int amount)
    : ingredientBean(bean), beanAmount(amount) {}
// copy constructor
Ingredient::Ingredient(Ingredient const& copyIngredient) 
    : ingredientBean(copyIngredient.ingredientBean), beanAmount(copyIngredient.beanAmount),
    nextIngredient(copyIngredient.nextIngredient) {}
// assignment operator
Ingredient& Ingredient::operator=(Ingredient const& copyIngredient) {
    ingredientBean = copyIngredient.ingredientBean;
    beanAmount = copyIngredient.beanAmount;
    nextIngredient = copyIngredient.nextIngredient;
    return *this; 
}
// -------------- GETTER & SETTER FUNCTIONS --------------
Bean const& Ingredient::getBean() const {
    return ingredientBean;
}
int Ingredient::getAmount() const {
    return beanAmount;
}
void Ingredient::setAmount(int amount) {
    beanAmount = amount;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ==================== EVENT VALUE ======================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// -------------------- CONSTRUCTION ---------------------
// constructor
EventValue::EventValue(long setValue)
    : value(setValue) {}
// copy constructor
EventValue::EventValue(EventValue const& copyValue)
    : value(copyValue.value) {}
// assignment operator overload
EventValue& EventValue::operator=(EventValue const& copyValue) {
    value = copyValue.value;
    return *this;
}
// -------------- GETTER & SETTER FUNCTIONS --------------
long EventValue::getValue() const {
    return value;
}
void EventValue::setValue(long setValue) {
    value = setValue;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ======================= EVENT =========================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// -------------------- CONSTRUCTION ---------------------
// constructor without eventValue
Event::Event(std::string const& type, long timestamp)
    : eventType(type), eventTimestamp(timestamp) {}
// constructor with eventValue
Event::Event(std::string const& type, long timestamp, EventValue* copyValue)
    : eventType(type), eventTimestamp(timestamp) {
        eventValue = new EventValue(copyValue->getValue());
        delete copyValue;
    }
// copy constructor
Event::Event(Event const& copyEvent)
    : eventType(copyEvent.eventType), eventTimestamp(copyEvent.eventTimestamp), nextEvent(copyEvent.nextEvent) {
        if (copyEvent.eventValue != nullptr) {
            eventValue = new EventValue(*copyEvent.eventValue);
        }
    }
// assignment overload
Event& Event::operator=(Event& copyEvent) {
    eventType = copyEvent.eventType;
    eventTimestamp = copyEvent.eventTimestamp;
    eventValue = copyEvent.eventValue;
    nextEvent = copyEvent.nextEvent;
    return *this;
}
// -------------- GETTER & SETTER FUNCTIONS --------------
Event::~Event() {
    delete eventValue;
}
std::string const& Event::getType() const {
    return eventType;
}
long Event::getTimestamp() const {
    return eventTimestamp;
}
EventValue* Event::getValue() const {
    return eventValue;
}
bool Event::hasValue() const {
    return (eventValue != nullptr);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ======================= ROAST =========================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// -------------------- CONSTRUCTION ---------------------
// constructor
Roast::Roast(long timestamp)
    : roastTimestamp(timestamp) {}
// copy constructor WHY IS IT SO LONG!!
Roast::Roast(Roast const& copyRoast)
    : roastTimestamp(copyRoast.roastTimestamp), numberOfIngredients(copyRoast.numberOfIngredients),
    numberOfEvents(copyRoast.numberOfEvents) {
        // copies ingredients
        if (copyRoast.ingredientHead != nullptr) {
            ingredientHead = new Ingredient(*copyRoast.ingredientHead);
            Ingredient* toPtr = ingredientHead; // copy to this roast
            Ingredient* fromPtr = copyRoast.ingredientHead->nextIngredient; // from this roast (which points to next)
            // copy from fromPtr to toPtr
            while (fromPtr != nullptr) {
                toPtr->nextIngredient = new Ingredient(*fromPtr);
                toPtr = toPtr->nextIngredient;
                fromPtr = fromPtr->nextIngredient;
            } 
        }
        // copies events
        if (copyRoast.eventHead != nullptr) {
            eventHead = new Event(*copyRoast.eventHead);
            Event* toPtr = eventHead;
            Event* fromPtr = copyRoast.eventHead->nextEvent;
            while (fromPtr != nullptr) {
                toPtr->nextEvent = new Event(*fromPtr);
                toPtr = toPtr->nextEvent;
                fromPtr = fromPtr->nextEvent;
            }
        }
        // all new events here die at the end of their scopes, so no need to delete!
    }
// assignment
Roast& Roast::operator=(Roast const& copyRoast) {
    roastTimestamp = copyRoast.roastTimestamp;
    numberOfIngredients = copyRoast.numberOfIngredients;
    numberOfEvents = copyRoast.numberOfEvents;

    // copies ingredients
    if (copyRoast.ingredientHead != nullptr) {
        ingredientHead = new Ingredient(*copyRoast.ingredientHead);
        Ingredient* toPtr = ingredientHead; // copy to this roast
        Ingredient* fromPtr = copyRoast.ingredientHead->nextIngredient; // from this roast (which points to next)
        // copy from fromPtr to toPtr
        while (fromPtr != nullptr) {
            toPtr->nextIngredient = new Ingredient(*fromPtr);
            toPtr = toPtr->nextIngredient;
            fromPtr = fromPtr->nextIngredient;
        }
    }
    // copies events
    if (copyRoast.eventHead != nullptr) {
        eventHead = new Event(*copyRoast.eventHead);
        Event* toPtr = eventHead;
        Event* fromPtr = copyRoast.eventHead->nextEvent;
        while (fromPtr != nullptr) {
            toPtr->nextEvent = new Event(*fromPtr);
            toPtr = toPtr->nextEvent;
            fromPtr = fromPtr->nextEvent;
        }
    }
    return *this;
}
// desctructor
Roast::~Roast() {
    Event* currentEventPtr = eventHead;
    while (currentEventPtr != nullptr) {
        Event* nextEventPtr = currentEventPtr->nextEvent;
        delete currentEventPtr;
        currentEventPtr = nextEventPtr; // nextEventPtr dies at the end of scope
    }
    Ingredient* currentIngredientPtr = ingredientHead;
    while (currentIngredientPtr != nullptr) {
        Ingredient* nextIngredientPtr = currentIngredientPtr->nextIngredient;
        delete currentIngredientPtr;
        currentIngredientPtr = nextIngredientPtr; // nextIngredientPtr dies at the end of scope
    }
}
// ------------------ ADDER FUNCTIONS --------------------
void Roast::addIngredient(Ingredient const& ingredient) {
    if (ingredientHead == nullptr) { // if empty ingredient list
        ingredientHead = new Ingredient(ingredient);
    } else {
        Ingredient* ingredientPtr = ingredientHead;
        while (ingredientPtr->nextIngredient != nullptr) {
            ingredientPtr = ingredientPtr->nextIngredient;
        } // iterate to the end of the linked list
        ingredientPtr->nextIngredient = new Ingredient(ingredient);
    }
    numberOfIngredients++;
}
void Roast::addEvent(Event const& event) {
    if (eventHead == nullptr) { // if empty event list
        eventHead = new Event(event);
    } else {
        Event* eventPtr = eventHead;
        while (eventPtr->nextEvent != nullptr) {
            eventPtr = eventPtr->nextEvent;
        } // iterate to the end of the linked list
        eventPtr->nextEvent = new Event(event);
    }
    numberOfEvents++;
}
// ----------------- REMOVER FUNCTIONS -------------------
void Roast::removeIngredientByBeanName(std::string const& beanName) {
    if (ingredientHead == nullptr) {
        exit(NO_SUCH_MEMBER_IN_LIST);
    }
    Ingredient* currentPtr = ingredientHead;
    Ingredient* previousPtr = nullptr;
    while (currentPtr != nullptr) {
        if(currentPtr->getBean().getName() == beanName) {
            if (previousPtr == nullptr) {
                ingredientHead = currentPtr->nextIngredient;
            } else {
                previousPtr->nextIngredient = currentPtr->nextIngredient;
            }
            delete currentPtr;
            numberOfIngredients--;
            break;
        }
        previousPtr = currentPtr;
        currentPtr = currentPtr->nextIngredient;
    }
}
void Roast::removeEventByTimestamp(long timestamp) {
    if (eventHead == nullptr) {
        exit(NO_SUCH_MEMBER_IN_LIST);
    }
    Event* currentPtr = eventHead;
    Event* previousPtr = nullptr;
    while (currentPtr != nullptr) {
        if (currentPtr->getTimestamp() == timestamp) {
            if (previousPtr != nullptr) {
                previousPtr->nextEvent = currentPtr->nextEvent;
            } else {
                eventHead = currentPtr->nextEvent;
            }
            delete currentPtr;
            numberOfEvents--;
            break;
        }
        previousPtr = currentPtr;
        currentPtr = currentPtr->nextEvent;
    }
}
// -------------- GETTER & SETTER FUNCTIONS --------------
long Roast::getTimestamp() const {
    return roastTimestamp;
}
int Roast::getEventCount() const {
    return numberOfEvents;
}
int Roast::getIngredientsCount() const {
    return numberOfIngredients;
}
Event const& Roast::getEventByTimestamp(long timestamp) const {
    Event* eventPtr = eventHead;
    while (eventPtr->getTimestamp() != timestamp) {
        eventPtr = eventPtr->nextEvent;
    }
    if (eventPtr == nullptr) {
        exit(NO_SUCH_MEMBER_IN_LIST);
    }
    return *eventPtr;
}
Ingredient& Roast::getIngredient(int index) const {
    Ingredient* ingredientPtr = ingredientHead;
    for (int i = 0; i < index; i++) {
        ingredientPtr = ingredientPtr->nextIngredient;
    }
    return *ingredientPtr;
}
Event& Roast::getEvent(int index) const {
    Event* eventPtr = eventHead;
    for (int i = 0; i < index; i++) {
        eventPtr = eventPtr->nextEvent;
    }
    return *eventPtr;
}

// It is 6:21am on the day of submission. I pulled an all nighter for this.
// The words Bean, Event, Ingredient, and Roast have been forever ruined for me.
// * mic drop *

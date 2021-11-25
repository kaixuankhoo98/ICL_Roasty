#include "../Roasty.hpp"
#include <string>

#define NO_SUCH_MEMBER_IN_LIST  69

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ======================== BEAN =========================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// -------------------- CONSTRUCTION ---------------------
Bean::Bean(std::string const& beanName) {
    name.assign(beanName);
}
Bean::Bean(Bean const& copyBean) {
    this->name.assign(copyBean.name);
}
// ------------------ GETTER FUNCTIONS -------------------
std::string const& Bean::getName() const {
    return name;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ===================== INGREDIENT ======================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// -------------------- CONSTRUCTION ---------------------
Ingredient::Ingredient(Bean const& bean, int setAmount) {
    ingredientBean = Bean(bean);
    beanAmount = setAmount;
}
Ingredient::Ingredient(Ingredient const& copyIngredient) {
    this->ingredientBean = Bean(copyIngredient.ingredientBean);
    this->beanAmount = copyIngredient.beanAmount;
}
// -------------- GETTER & SETTER FUNCTIONS --------------
Bean const& Ingredient::getBean() const {
    return ingredientBean;
}
int Ingredient::getAmount() const {
    return beanAmount;
}
void Ingredient::setAmount(int const newAmount) {
    beanAmount = newAmount;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ==================== EVENT VALUE ======================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// -------------------- CONSTRUCTION ---------------------
EventValue::EventValue(long startValue) {
    value = startValue;
}
EventValue::EventValue(EventValue const& copyEventValue) {
    value = copyEventValue.value;
}
// -------------- GETTER & SETTER FUNCTIONS --------------
long EventValue::getValue() const {
    return value;
}
void EventValue::setValue(long valueToSet) {
    value = valueToSet;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ======================= EVENT =========================
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++
// -------------------- CONSTRUCTION ---------------------
Event::Event(std::string const& type, long timestamp) {
    eventType.assign(type);
    eventTimestamp = timestamp;
}
Event::Event(std::string const& type, long timestamp, EventValue* eventValuePtr) {
    eventType.assign(type);
    eventTimestamp = timestamp;
    eventValue = eventValuePtr;
}
Event::Event(Event const& copyEvent) {
    this->eventTimestamp = copyEvent.eventTimestamp;
    this->eventType.assign(copyEvent.eventType);
    this->eventValue = copyEvent.eventValue;
}
// -------------- GETTER & SETTER FUNCTIONS --------------
long Event::getTimestamp() const {
    return eventTimestamp;
}
std::string const& Event::getType() const {
    return eventType;
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
Roast::Roast(long timestamp) {
    roastTimestamp = timestamp;
}
Roast::Roast(Roast const& copyRoast) {
    this->roastTimestamp = copyRoast.roastTimestamp;
    this->numberOfIngredients = copyRoast.numberOfIngredients;
    this->numberOfEvents = copyRoast.numberOfEvents;
}
// ------------------ ADDER FUNCTIONS --------------------
void Roast::addIngredient(Ingredient const& newIngredient) {
    // IF STATEMENT TO CHECK IF INGREDIENT IS ALREADY IN LIST ?? 
    Ingredient ing = Ingredient(newIngredient);
    Ingredient* ingPtr = &ing;
    // Assign new head if empty list
    if (ingredientHead == nullptr) {
        ingredientHead = ingPtr;
        numberOfIngredients++;
        return;
    }
    // Go to end of list
    Ingredient* temp = ingredientHead;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = ingPtr;
    numberOfIngredients++;
}
void Roast::addEvent(Event const& newEvent) {
    Event eve = Event(newEvent);
    Event* evePtr = &eve;
    // Assign new head if empty list
    if (eventHead == nullptr) {
        eventHead = evePtr;
        numberOfEvents++;
        return;
    }
    // Go to end of list
    Event* temp = eventHead;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = evePtr;
    numberOfEvents++;
}
// -------------- GETTER & SETTER FUNCTIONS --------------
long Roast::getTimestamp() const {
    return roastTimestamp;
}
int Roast::getIngredientsCount() const {
    return numberOfIngredients;
}
int Roast::getEventCount() const {
    return numberOfEvents;
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
    Event* currentPtr = eventHead->next;
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
Bean& Bean::operator=(Bean const& copyBean) {
    this->name.assign(copyBean.name);
    return *this;
}
Ingredient& Ingredient::operator=(Ingredient const& copyIngredient) {
    this->ingredientBean = copyIngredient.ingredientBean;
    this->beanAmount = copyIngredient.beanAmount;
    return *this;
}
EventValue& EventValue::operator=(EventValue const& copyEventValue) {
    this->value = copyEventValue.value;
    return *this;
}
Event& Event::operator=(Event const& copyEvent) {
    this->eventTimestamp = copyEvent.eventTimestamp;
    this->eventType.assign(copyEvent.eventType);
    this->eventValue = copyEvent.eventValue;
    return *this;
}

// // ============== Ingredient ===============
// Bean Ingredient::getBean() {
//     // defensive programming?
//     return ingredientBean;
// }
// Bean const Ingredient::getBean() const {
//     // defensive programming?
//     return ingredientBean;
// } // Overload on const-ness
// Ingredient::Ingredient(Bean bean, int newAmount) {
//     ingredientBean = bean; // From overloaded bean assignment operator
//     amount = newAmount;
// }


// // ============== Event ===============
// // long& Event::getTimestamp() const {
// //     // defensive programming?
// //     return eventTimestamp;
// // }
// long const& Event::getTimestamp() const {
//     return eventTimestamp;
// }
// long& getTimestamp() {
//     return const_cast<long&>(const_cast<const Event*>(this)->getTimestamp());
// }

// // ============== Roast ===============
// long Roast::getTimestamp() const{
//     // defensive programming?
//     return timestamp;
// }
// // Ingredient Roast::getIngredient(int index) {
// //     // defensive programming?
// //     std::list<Ingredient>::iterator it = ingredients.begin();
// //     std::advance(it, index);
// //     return *it;
// // }
// Ingredient const& Roast::getIngredient(int index) const {
//     // defensive programming?
//     std::list<Ingredient>::const_iterator it = ingredients.begin();
//     std::advance(it, index);
//     return *it;
// }

// int Roast::getIngredientsCount() {
//     return ingredients.size();
// }
// void Roast::addIngredient(Ingredient ingredient) {
//     ingredients.push_back(ingredient);
// }
// void Roast::removeIngredientByBeanName(std::string beanName) {
//     for (auto i = 0; i < ingredients.size(); i++) {
//         if (beanName == getIngredient(i)) { // getIngredient(i).getBean().getName()
//             ingredients.remove(getIngredient(i));
//         }
//     }
// }
// // Event Roast::getEvent(int index) {
// //     std::list<Event>::iterator it = events.begin();
// //     std::advance(it, index);
// //     return *it;
// // }
// Event const& Roast::getEvent(int index) const {
//     std::list<Event>::const_iterator it = events.begin();
//     std::advance(it, index);
//     return *it;
// }
// int Roast::getEventCount() {
//     return events.size();
// }
// void Roast::addEvent(Event event) {
//     events.push_back(event);
// }

// // ============== Storage Implememtnation ===============
// std::list<Bean> StorageImplementation::getBeans() {
//     // defensive programming?
//     std::list<Bean> beanlist;
//     for (auto i = 0; i < beans.size(); i++) {
//         std::list<Bean>::iterator it = beans.begin();
//         std::advance(it, i);
//         beanlist.push_back(*it);
//     }
//     return beanlist;
// }
// Bean StorageImplementation::getBeanByStorageIndex(int i) {
//     std::list<Bean>::iterator it = beans.begin();
//     std::advance(it, i);
//     return *it;
// }
// Bean StorageImplementation::getBeanByBeanName(std::string beanName) {
//     for (int i = 0; i < beans.size(); i++) {
//         if (beanName == getBeanByStorageIndex(i))
//             return getBeanByStorageIndex(i);
//     }
//     exit(1);
// }

// /* Questions to ask:
//     warning: returning reference to temporary [-Wreturn-local-addr]
//    82 |       [&](auto i) -> Ingredient const& { return roast.getIngredient(i); },

//     error: passing ‘const Event’ as ‘this’ argument discards qualifiers [-fpermissive]
//   136 |     return event.getTimestamp() == eventTimestamp;
//     note:   in call to ‘long int Event::getTimestamp()’
//    35 |     long getTimestamp();

//     Should I be overloading operators inside the class or at the end?

//     General guidance on next steps because I feel lost? :(
// */
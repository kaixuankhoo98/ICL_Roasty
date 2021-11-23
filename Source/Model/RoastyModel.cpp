#include "../Roasty.hpp"


// ============== Bean ===============
std::string Bean::getName() {
    // defensive programming?
    return name;
}
std::string const Bean::getName() const {
    // defensive programming?
    return name;
} // Overload function on const-ness!


// ============== Ingredient ===============
Bean Ingredient::getBean() {
    // defensive programming?
    return ingredientBean;
}
Bean const Ingredient::getBean() const {
    // defensive programming?
    return ingredientBean;
} // Overload on const-ness
Ingredient::Ingredient(Bean bean, int newAmount) {
    ingredientBean = bean; // From overloaded bean assignment operator
    amount = newAmount;
}


// ============== Event ===============
long Event::getTimestamp() {
    // defensive programming?
    return eventTimestamp;
}

// ============== Roast ===============
long Roast::getTimestamp() {
    // defensive programming?
    return timestamp;
}
Ingredient Roast::getIngredient(int index) {
    // defensive programming?
    std::list<Ingredient>::iterator it = ingredients.begin();
    std::advance(it, index);
    return *it;
}

int Roast::getIngredientsCount() {
    return ingredients.size();
}
void Roast::addIngredient(Ingredient ingredient) {
    ingredients.push_back(ingredient);
}
void Roast::removeIngredientByBeanName(std::string beanName) {
    for (auto i = 0; i < ingredients.size(); i++) {
        if (beanName == getIngredient(i)) {
            ingredients.remove(getIngredient(i));
        }
    }
}
Event Roast::getEvent(int index) {
    std::list<Event>::iterator it = events.begin();
    std::advance(it, index);
    return *it;
}
// Event const& Roast::getEvent(int index) const {
//     std::list<Event>::const_iterator it = events.begin();
//     std::advance(it, index);
//     return *it;
// }
int Roast::getEventCount() {
    return events.size();
}
void Roast::addEvent(Event event) {
    events.push_back(event);
}

// ============== Storage Implememtnation ===============
std::list<Bean> StorageImplementation::getBeans() {
    // defensive programming?
    std::list<Bean> beanlist;
    for (auto i = 0; i < beans.size(); i++) {
        std::list<Bean>::iterator it = beans.begin();
        std::advance(it, i);
        beanlist.push_back(*it);
    }
    return beanlist;
}
Bean StorageImplementation::getBeanByStorageIndex(int i) {
    std::list<Bean>::iterator it = beans.begin();
    std::advance(it, i);
    return *it;
}
Bean StorageImplementation::getBeanByBeanName(std::string beanName) {
    for (int i = 0; i < beans.size(); i++) {
        if (beanName == getBeanByStorageIndex(i))
            return getBeanByStorageIndex(i);
    }
    exit(1);
}

/* Questions to ask:
    warning: returning reference to temporary [-Wreturn-local-addr]
   82 |       [&](auto i) -> Ingredient const& { return roast.getIngredient(i); },

    error: passing ‘const Event’ as ‘this’ argument discards qualifiers [-fpermissive]
  136 |     return event.getTimestamp() == eventTimestamp;
    note:   in call to ‘long int Event::getTimestamp()’
   35 |     long getTimestamp();

    Should I be overloading operators inside the class or at the end?

    General guidance on next steps because I feel lost? :(
*/
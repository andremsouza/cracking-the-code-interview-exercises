// An animal shelter, which holds only dogs and cats, operates on a stricly
// "first in, first out" basis. People must adopt either the "oldest" (based on
// arrival time) of all animals at the shelter, or they can select wheter they
// would prefer a dog or a cat (and they will receive the oldest animal of that
// type). They cannot select which specific animal they would like. Create the
// data structures to maintain this system and implement operations such as
// enqueue, dequeueAny, dequeueDog, and dequeueCat. You may use the built-in
// LinkedList data structure.

// * Solution: Maintain two queues (one for dogs and one for cats). For each
// * element, maintain an id to identify to order of insertion.

#include <list>
#include <string>

class Animal {
 private:
  uint m_id;
  std::string m_name;

 public:
  Animal(uint t_id, std::string t_name) : m_id(t_id), m_name(t_name) {}
  Animal(std::string t_name) : m_name(t_name) {}

  uint id() { return m_id; }
  std::string name() { return m_name; }
  void set_id(uint t_id) { m_id = t_id; }
  void set_name(std::string t_name) { m_name = t_name; }
};

class Cat : public Animal {
 public:
  Cat(uint t_id, std::string t_name) : Animal(t_id, t_name) {}
  Cat(std::string t_name) : Animal(t_name) {}
};

class Dog : public Animal {
 public:
  Dog(uint t_id, std::string t_name) : Animal(t_id, t_name) {}
  Dog(std::string t_name) : Animal(t_name) {}
};

class AnimalQueue {
 private:
  std::list<Cat> m_cat_queue;
  std::list<Dog> m_dog_queue;
  uint m_id_next = 0;

 public:
  void enqueue(Cat t_animal);
  void enqueue(Dog t_animal);
  Animal dequeueAny();
  Cat dequeueCat();
  Dog dequeueDog();
};

void AnimalQueue::enqueue(Cat t_animal) {
  t_animal.set_id(m_id_next++);
  m_cat_queue.push_back(t_animal);
}

void AnimalQueue::enqueue(Dog t_animal) {
  t_animal.set_id(m_id_next++);
  m_dog_queue.push_back(t_animal);
}

Animal AnimalQueue::dequeueAny() {
  if (m_cat_queue.empty()) {
    return dequeueDog();
  } else if (m_dog_queue.empty()) {
    return dequeueCat();
  }
  Cat cat = m_cat_queue.front();
  Dog dog = m_dog_queue.front();

  if (cat.id() > dog.id()) {
    return dog;
  } else {
    return cat;
  }
  // return cat.id() > dog.id() ? (Animal)dog : (Animal)cat;
}

Cat AnimalQueue::dequeueCat() {
  Cat cat = m_cat_queue.front();
  m_cat_queue.pop_front();
  return cat;
}

Dog AnimalQueue::dequeueDog() {
  Dog dog = m_dog_queue.front();
  m_dog_queue.pop_front();
  return dog;
}

int main() {
  // int main(int argc, char const *argv[]) { // not using argc/argv
  AnimalQueue a;
  /* code */
  return 0;
}

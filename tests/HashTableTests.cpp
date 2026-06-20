#include "structures/HashTable.hpp"

#include <iostream>
#include <string>

namespace {
constexpr const char *green = "\033[32m";
constexpr const char *red = "\033[31m";
constexpr const char *reset = "\033[0m";
}

bool expect(bool condition, const char *message) {
  if (!condition) {
    std::cout << red << "FAIL" << reset << ": " << message << "\n";
    return false;
  }

  std::cout << green << "PASS" << reset << ": " << message << "\n";
  return true;
}

int main() {
  bool passed = true;

  HashTable<int> table;

  passed = expect(table.isEmpty(), "new table starts empty") && passed;
  passed = expect(table.size() == 0, "new table starts with size 0") && passed;
  passed = expect(!table.contains("cannon"),
                  "empty table does not contain key") &&
           passed;
  passed = expect(table.find("cannon") == nullptr,
                  "find missing key returns nullptr") &&
           passed;

  table.insert("cannon", 50);
  table.insert("sniper", 120);
  table.insert("rapid", 40);

  passed = expect(!table.isEmpty(), "insert makes table non-empty") && passed;
  passed = expect(table.size() == 3, "insert increases size for new keys") &&
           passed;
  passed = expect(table.contains("cannon"), "contains finds first key") &&
           passed;
  passed = expect(table.contains("sniper"), "contains finds second key") &&
           passed;
  passed = expect(table.contains("rapid"), "contains finds third key") &&
           passed;
  passed = expect(!table.contains("missing"), "contains rejects missing key") &&
           passed;

  int *cannonCost = table.find("cannon");
  int *sniperCost = table.find("sniper");
  int *rapidCost = table.find("rapid");

  passed = expect(cannonCost != nullptr && *cannonCost == 50,
                  "find returns value for cannon") &&
           passed;
  passed = expect(sniperCost != nullptr && *sniperCost == 120,
                  "find returns value for sniper") &&
           passed;
  passed = expect(rapidCost != nullptr && *rapidCost == 40,
                  "find returns value for rapid") &&
           passed;

  table.insert("cannon", 75);
  passed = expect(table.size() == 3,
                  "duplicate key updates without increasing size") &&
           passed;
  passed = expect(table.find("cannon") != nullptr && *table.find("cannon") == 75,
                  "duplicate key updates existing value") &&
           passed;

  table.insert("a", 1);
  table.insert("i", 9);
  passed = expect(table.size() == 5, "collision-prone keys both insert") &&
           passed;
  passed = expect(table.find("a") != nullptr && *table.find("a") == 1,
                  "find works for first collision-prone key") &&
           passed;
  passed = expect(table.find("i") != nullptr && *table.find("i") == 9,
                  "find works for second collision-prone key") &&
           passed;

  HashTable<int> copy = table;
  copy.insert("cannon", 200);
  copy.insert("slow", 60);

  passed = expect(table.size() == 5,
                  "copy constructor keeps original size independent") &&
           passed;
  passed = expect(copy.size() == 6, "copy can insert its own key") && passed;
  passed = expect(table.find("cannon") != nullptr && *table.find("cannon") == 75,
                  "copy update does not modify original value") &&
           passed;
  passed = expect(copy.find("cannon") != nullptr && *copy.find("cannon") == 200,
                  "copy stores its own updated value") &&
           passed;

  HashTable<int> assigned;
  assigned.insert("temporary", 999);
  assigned = table;
  assigned.insert("sniper", 300);
  assigned.insert("laser", 180);

  passed = expect(table.size() == 5,
                  "copy assignment keeps original size independent") &&
           passed;
  passed = expect(assigned.size() == 6, "assigned table can insert own key") &&
           passed;
  passed = expect(table.find("sniper") != nullptr && *table.find("sniper") == 120,
                  "assigned update does not modify original value") &&
           passed;
  passed = expect(assigned.find("sniper") != nullptr &&
                      *assigned.find("sniper") == 300,
                  "assigned table stores its own updated value") &&
           passed;

  const HashTable<int> constTable = table;
  const int *constValue = constTable.find("rapid");
  passed = expect(constValue != nullptr && *constValue == 40,
                  "const find returns const value pointer") &&
           passed;

  assigned.clear();
  passed = expect(assigned.isEmpty(), "clear makes table empty") && passed;
  passed = expect(assigned.size() == 0, "clear resets size") && passed;
  passed = expect(assigned.find("sniper") == nullptr,
                  "find after clear returns nullptr") &&
           passed;

  if (!passed) {
    return 1;
  }

  std::cout << "All HashTable tests passed\n";
  return 0;
}

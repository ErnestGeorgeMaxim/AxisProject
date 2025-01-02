#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <tuple>


volatile uint8_t currentFloor = 0;
volatile uint8_t floorCalls = 0b00000010;
volatile uint8_t activeCall = 0;

#define FLOOR 4

int main() {
}
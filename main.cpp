#include "VolunteerSystem.h"
#include <iostream>
int main() {
    try { VolunteerSystem system; system.run(); }
    catch (const std::exception& e) { std::cerr << "Fatal error: " << e.what() << '\n'; return 1; }
    return 0;
}
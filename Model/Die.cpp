#include "Die.h"
#include <stdlib.h>

Die::Die(unsigned f) : faces(f) {}

unsigned Die::roll() const { return rand() % faces + 1; }

unsigned Die::getFaces() const { return faces; }

bool Die::operator==(const Die& d) const { return faces == d.faces; }
bool Die::operator!=(const Die& d) const { return faces != d.faces; }
bool Die::operator<(const Die& d) const { return faces < d.faces; }
bool Die::operator>(const Die& d) const { return faces > d.faces; }
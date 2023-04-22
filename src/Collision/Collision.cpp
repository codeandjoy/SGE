#include "Collision.h"

bool operator< (const Collision a, const Collision b){ return a.recipient < b.recipient; }
bool operator> (const Collision a, const Collision b){ return a.recipient > b.recipient; }
bool operator== (const Collision a, const Collision b){ return a.recipient == b.recipient; }
bool operator!= (const Collision a, const Collision b){ return a.recipient != b.recipient; }
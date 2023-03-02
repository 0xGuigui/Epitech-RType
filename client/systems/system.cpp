#include "client/systems/system.h"

bool System::isEnabled() const {
    return _enabled;
}

void System::setEnabled(bool enabled) {
    _enabled = enabled;
}

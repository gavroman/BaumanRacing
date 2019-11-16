#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include "event.hpp"
#include "base_manager.hpp"
#include "input_abst.hpp"
#include "event_throwable.hpp"

class input_manager : public base_manager, event_throwable {
 public:
    input_manager(input_abst *abst);
    int on_event(const event & e);
    event throw_event();
    input_abst *module;
};

#endif // INPUT_MANAGER_H_
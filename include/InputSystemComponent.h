#pragma once

#include <map>
#include <vector>
#include <functional>

#include "Component.h"
#include "InputComponent.h"
#include "InputAction.h"

class InputSystemComponent : public InputComponent {
public:
    InputSystemComponent() = default;
    ~InputSystemComponent() = default;

    void init() override;
    void update() override;

    void bindAction(const std::string& actionName, Key key, std::function<void()> callback);
    void unbindAction(const std::string& actionName, Key key);

private:
    InputComponent* m_inputComponent;
    std::map<Key, std::vector<InputAction>> m_keyToActionsMap;
    std::map<std::string, InputAction> m_actions;

    void handleActions();
};

#pragma once

#include <map>
#include <vector>
#include <functional>

#include "Component.h"
#include "InputComponent.h"
#include "InputAction.h"

class InputSystemComponent : public InputComponent
{
public:
    InputSystemComponent() = default;
    ~InputSystemComponent() = default;

    void init() override;
    void update() override;

    void bindAction(const std::string& actionName, Key key, std::function<void()> callback);
    void bindAction(const std::string& actionName, std::vector<Key> keys, std::function<void()> callback);

    // template<typename... Keys>
    // void bindAction(const std::string& actionName, std::function<void()> callback, Keys... keys)
    // {
    //     static_assert((std::is_same<Keys, Key>::value && ...), "A passed argument for 'Keys' is not of type 'Key'");

    //     if (m_actions.find(actionName) == m_actions.end())
    //     {
    //         m_actions[actionName] = InputAction(actionName, callback);
    //     }

    //     (m_actions[actionName].keys.push_back(keys), ...);
    //     (m_keyToActionsMap[keys].push_back(m_actions[actionName]), ...);
    // }

    // void unbindAction(const std::string& actionName, Key key);

    template<typename... Keys>
    void unbindAction(const std::string& actionName, Keys... keys)
    {
        static_assert((std::is_same<Keys, Key>::value && ...), "A passed argument for 'Keys' is not of type 'Key'");

        auto actionIt = m_actions.find(actionName);
        if (actionIt != m_actions.end())
        {
            auto& action = actionIt->second;
            (action.keys.erase(std::remove(action.keys.begin(), action.keys.end(), keys), action.keys.end()), ...);
            (m_keyToActionsMap[keys].erase(std::remove_if(m_keyToActionsMap[keys].begin(), m_keyToActionsMap[keys].end(),
                [&](const InputAction& a) { return a.actionName == actionName; }), m_keyToActionsMap[keys].end()), ...);
        }
    }

private:
    InputComponent* m_inputComponent;
    std::map<Key, std::vector<InputAction>> m_keyToActionsMap;
    std::map<std::string, InputAction> m_actions;

    void handleActions();
};

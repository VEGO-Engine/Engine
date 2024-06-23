#include "InputSystemComponent.h"

void InputSystemComponent::init()
{
    InputComponent::init();
}

void InputSystemComponent::update()
{
    InputComponent::update();
    handleActions();
}

// alternative to template function
void InputSystemComponent::bindAction(const std::string& actionName, Key key, std::function<void()> callback)
{
    if (m_actions.find(actionName) == m_actions.end())
    {
        m_actions[actionName] = InputAction(actionName, callback);
    }

    m_actions[actionName].keys.push_back(key);
    m_keyToActionsMap[key].push_back(m_actions[actionName]);

}

// alternative to template function
void InputSystemComponent::bindAction(const std::string& actionName, std::vector<Key> keys, std::function<void()> callback)
{
    if (m_actions.find(actionName) == m_actions.end())
    {
        m_actions[actionName] = InputAction(actionName, callback);
    }

    for (Key key : keys)
    {
        m_actions[actionName].keys.push_back(key);
        m_keyToActionsMap[key].push_back(m_actions[actionName]);
    }
}

void InputSystemComponent::unbindAction(const std::string& actionName, Key key)
{
    auto actionIt = m_actions.find(actionName);
    if (actionIt != m_actions.end())
    {
        auto& action = actionIt->second;
        action.keys.erase(std::remove(action.keys.begin(), action.keys.end(), key), action.keys.end());
        m_keyToActionsMap[key].erase(std::remove_if(m_keyToActionsMap[key].begin(), m_keyToActionsMap[key].end(),
            [&](const InputAction& a) { return a.name == actionName; }), m_keyToActionsMap[key].end());
    }
}

void InputSystemComponent::handleActions()
{
    for (auto& keyActionsPair : m_keyToActionsMap)
    {
        Key key = keyActionsPair.first;
        if (isKeyDown(key))
        {
            for (auto& action : keyActionsPair.second)
            {
                if (action.callback)
                {
                    action.callback();
                }
            }
        }
    }
}
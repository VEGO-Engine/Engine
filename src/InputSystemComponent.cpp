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

// alternative to bindAction template
void InputSystemComponent::bindAction(const std::string& actionName, Key key, std::function<void()> callback, InputActionType type)
{
    if (m_actions.find(actionName) == m_actions.end())
    {
        m_actions[actionName] = InputAction(actionName, callback, type);
    }

    m_actions[actionName].keys.push_back(key);
    m_keyToActionsMap[key].push_back(m_actions[actionName]);

}

// alternative to bindAction template
void InputSystemComponent::bindAction(const std::string& actionName, std::vector<Key> keys, std::function<void()> callback, InputActionType type)
{
    if (m_actions.find(actionName) == m_actions.end())
    {
        m_actions[actionName] = InputAction(actionName, callback, type);
    }

    for (Key key : keys)
    {
        m_actions[actionName].keys.push_back(key);
        m_keyToActionsMap[key].push_back(m_actions[actionName]);
    }
}

// alternative to unbindAction template
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

// alternative to unbindAction template
void InputSystemComponent::unbindAction(const std::string& actionName, const std::vector<Key>& keysToRemove)
{
    for (Key key : keysToRemove)
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
}

void InputSystemComponent::handleActions()
{
    for (auto& keyActionsPair : m_keyToActionsMap)
    {
        Key key = keyActionsPair.first;
        bool keyDown = isKeyDown(key);

        for (auto& action : keyActionsPair.second)
        {
            switch (action.get().type)
            {
                case InputActionType::Boolean:
                    std::get<bool>(action.get().value) = keyDown;
                    break;

                case InputActionType::Float:
                    float& floatValue = std::get<float>(action.get().value);
                    if (keyDown && floatValue < 1.0f)
                    {
                        floatValue += m_floatChangeRate;
                    }

                    else
                    {
                        if (floatValue > 0.1f)
                        {
                            floatValue -= m_floatChangeRate;
                        }
                    }
                    break;
            }

            if (keyDown && action.get().callback)
            {
                action.get().callback();
            }
        }
    }
}

InputValue InputSystemComponent::getValue(const std::string& actionName)
{
    if (m_actions.find(actionName) != m_actions.end())
    {
        return m_actions[actionName].value;
    }
    return InputValue();
}

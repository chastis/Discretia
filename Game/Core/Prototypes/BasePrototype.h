#pragma once

#include <Core/Consts/Consts.h>
#include <Core/Utility/Noncopyable.h>
#include <Core/Utility/Json.h>
#include <string>
#include <vector>
#include <fstream>

class BasePrototype
{
public:
    [[nodiscard]] long long GetID() const
    {
        return id;
    }
    [[nodiscard]] const std::string& GetSID() const
    {
        return sid;
    }
    bool operator==(const BasePrototype& prototype) const
    {
        return id == prototype.id;
    }
    virtual bool Init(const nlohmann::json& node)
    {
        if (!node.contains("id")
            || !node.contains("sid"))
        {
            __debugbreak();
            return false;
        }
        id = node.at("id").get<size_t>();
        sid = node["sid"].get<std::string>();
        return true;
    }
protected:
    size_t id = 0;
    std::string sid;
};

template <class T>
class BasePrototypes : public Noncopyable
{
public:
    void Init(std::string filePath);
    static const std::vector<T>& GetPrototypes();
    static const T& GetDefault();
    static size_t Size();

protected:
    inline static std::vector<T> prototypes{};
};

template <class T>
void BasePrototypes<T>::Init(std::string filePath)
{
    const std::string fullPath = Const::EngineConfigPath + filePath + Const::ConfigExt;
    std::ifstream file(fullPath);
    
    nlohmann::json j = nlohmann::json::parse(file);
    prototypes.reserve(j.size());
    for (const auto& node : j)
    {
        T newPrototype;
        if (newPrototype.Init(node))
        {
            prototypes.emplace_back(newPrototype);
        }
    }
}

template <class T>
const std::vector<T>& BasePrototypes<T>::GetPrototypes()
{
    return prototypes;
}

template <class T>
const T& BasePrototypes<T>::GetDefault()
{
    if (prototypes.size() == 0)
    {
        prototypes.push_back(T());
    }
    return prototypes[0];
}

template <class T>
size_t BasePrototypes<T>::Size()
{
    return prototypes.size();
}



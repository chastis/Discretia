#pragma once

#include <Core/Consts/Consts.h>
#include <Core/Utility/Noncopyable.h>
#include <Core/Utility/Json.h>
#include <string>
#include <vector>
#include <fstream>
#include <memory>

class BasePrototype
{
public:
    [[nodiscard]] size_t GetID() const
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
    virtual bool Init(nlohmann::json::iterator nodeIt)
    {
        nlohmann::json node = nodeIt.value();
        if (!node.contains("id"))
        {
            __debugbreak();
            return false;
        }
        id = node.at("id").get<size_t>();
        sid = nodeIt.key();
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
    static void Init(const std::string& filePath);
    static const T& GetDefault();
    static const T& Get(size_t inID);
    static const T& Get(const std::string& inSID);
    static size_t Size();

protected:
    static std::vector<std::unique_ptr<T>> prototypes;
};

template <class T>
std::vector<std::unique_ptr<T>> BasePrototypes<T>::prototypes;

template <class T>
void BasePrototypes<T>::Init(const std::string& filePath)
{
    const std::string fullPath = CoreConst::EngineConfigPath + filePath + CoreConst::ConfigExt;
    std::ifstream file(fullPath);
    
    nlohmann::json j = nlohmann::json::parse(file);
    prototypes.reserve(j.size());
    for (auto node = j.begin(); node != j.end(); ++node)
    {
        auto a = j.begin().key();
        std::unique_ptr<T> newPrototype = std::make_unique<T>();
        if (newPrototype && newPrototype->Init(node))
        {
            prototypes.emplace_back(std::move(newPrototype));
        }
    }

    file.close();
}

template <class T>
const T& BasePrototypes<T>::GetDefault()
{
    if (prototypes.size() == 0)
    {
        std::unique_ptr<T> defaultPrototype = std::make_unique<T>();
        prototypes.push_back(std::move(defaultPrototype));
    }
    return *prototypes[0];
}

template <class T>
const T& BasePrototypes<T>::Get(size_t inID)
{
    if (inID >=0 && inID < prototypes.size())
    {
        //auto basePrototype = static_cast<BasePrototype*>((prototypes[inID]);
        if (prototypes[inID] && prototypes[inID]->GetID()==inID)
        {
            return *prototypes[inID];
        }
    }
    __debugbreak();
    return GetDefault();
}

template <class T>
const T& BasePrototypes<T>::Get(const std::string& inSID)
{
    for (const auto& el : prototypes)
    {
        if (el && el->GetSID() == inSID)
        {
            return *el;
        }
    }
    __debugbreak();
    return GetDefault();
}

template <class T>
size_t BasePrototypes<T>::Size()
{
    return prototypes.size();
}


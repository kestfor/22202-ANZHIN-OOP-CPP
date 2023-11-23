#ifndef SOUNDPROCESSOR_CONVERTERFACTORY_H
#define SOUNDPROCESSOR_CONVERTERFACTORY_H
#include "Converter.h"
#include <map>


class abstractConverterCreator {
public:
    abstractConverterCreator() = default;
    virtual ~abstractConverterCreator() = default;
    virtual Converter *create(vector<int> &args) const = 0;
    virtual Converter *create(vector<string> &args) const = 0;
};

template<class C>
class ConverterCreator : public abstractConverterCreator {
public:

    Converter *create(std::vector<int> &args) const override {
        return new C(args);
    }

    Converter *create(std::vector<string> &args) const override {
        return new C(args);
    }


};

class ConverterFactory {
protected:
    typedef std::map<std::string, abstractConverterCreator*> FactoryMap;
    FactoryMap _factory;
    std::map<string, string> descriptions;

public:

    virtual ~ConverterFactory() {
        for (const auto& item: _factory) {
            delete item.second;
        }
    }

    vector<string> converterNames() const {
        vector<string> res = {};
        for (const auto &item : _factory) {
            res.push_back(item.first);
        }
        return res;
    }

    template<class C>
    void add(const std::string &name) {
        if (!_factory.contains(name)) {
            _factory[name] = new ConverterCreator<C>();
            descriptions[name] = C::description();
        }
    }

    const std::map<string, string> &getDescriptions() {
        return descriptions;
    }

    Converter *create(const std::string &name, std::vector<int> &params) {
        auto it = _factory.find(name);
        if (it != _factory.end()) {
            return it->second->create(params);
        }
        return nullptr;
    }

    Converter *create(const std::string &name, std::vector<string> &params) {
        auto it = _factory.find(name);
        if (it != _factory.end()) {
            return it->second->create(params);
        }
        return nullptr;
    }

    bool contains(const std::string &name) const {
        return _factory.contains(name);
    }

};

#endif //SOUNDPROCESSOR_CONVERTERFACTORY_H

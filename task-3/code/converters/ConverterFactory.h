#ifndef SOUNDPROCESSOR_CONVERTERFACTORY_H
#define SOUNDPROCESSOR_CONVERTERFACTORY_H
#include "Converter.h"
#include <map>


class abstractConverterCreator {
public:
    abstractConverterCreator() = default;
    virtual ~abstractConverterCreator() = default;
    virtual Converter *create(vector<int> &args) const = 0;
};

template<class C>
class ConverterCreator : public abstractConverterCreator {
public:

    virtual Converter *create(std::vector<int> &args) const {
        return new C(args);
    }


};

class ConverterFactory {
protected:
    typedef std::map<std::string, abstractConverterCreator*> FactoryMap;
    FactoryMap _factory;

public:

    virtual ~ConverterFactory() {
        for (const auto& item: _factory) {
            delete item.second;
        }
    }

    vector<string> converterNames() {
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
        }
    }

    Converter *create(const std::string &name, std::vector<int> &params) {
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

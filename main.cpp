#include <iostream>
#include <string>
#include <cassert>

#include <sstream>

#include "collector.h"

const size_t MAX_STRING_LENGTH = 50;

enum MetalType
{
    RARE,
    HEAVY,
    LIGHT
};

class Exhibit : public ICollectable
{
private:
    std::string _special_name;

    MetalType _metal_type;

    std::string _currency_name;

    int _count_of_currency, _count_of_coins;

protected:
    bool invariant() const
    {
        return _special_name.size() <= MAX_STRING_LENGTH && _metal_type >= RARE && _metal_type <= LIGHT &&
               _currency_name.size() <= MAX_STRING_LENGTH && _count_of_currency >= 0 && _count_of_coins >= 0;
    }

public:
    Exhibit() = delete;

    Exhibit(const Exhibit &p) = delete;

    Exhibit &operator=(const Exhibit &p) = delete;

    Exhibit(const std::string &special_name, MetalType metal_type, const std::string &currency_name,
            int count_of_currency, int count_of_coins)
        : _special_name(special_name), _metal_type(metal_type), _currency_name(currency_name),
          _count_of_currency(count_of_currency), _count_of_coins(count_of_coins)
    {
        assert(invariant());
    }

    const std::string &getSpecialName() const
    {
        return _special_name;
    }

    MetalType getMetalType() const
    {
        return _metal_type;
    }

    const std::string &getCurrencyName() const
    {
        return _currency_name;
    }

    int getCountOfCurrency() const
    {
        return _count_of_currency;
    }

    int getCountOfCoins() const
    {
        return _count_of_coins;
    }

    virtual bool write(std::ostream &os) override
    {
        writeString(os, _special_name);
        writeString(os, _metal_type);
        writeString(os, _currency_name);
        writeString(os, _count_of_currency);
        writeString(os, _count_of_coins);

        return os.good();
    }
};

class ItemCollector : public ACollector
{
public:
    virtual std::shared_ptr<ICollectable> read(std::istream &is) override
    {
        std::string special_name = readString(is, MAX_STRING_LENGTH);
        MetalType metal_type = readNumber<MetalType>(is);
        std::string currency_name = readString(is, MAX_STRING_LENGTH);
        int count_of_currency = readNumber<int>(is);
        int count_of_coins = readNumber<int>(is);

        return std::make_shared<Exhibit>(special_name, metal_type, currency_name, count_of_currency, count_of_coins);
    }
};

bool performCommand(const std::vector<std::string> &args, ItemCollector &col)
{
    if (args.empty())
    {
        return false;
    }

    if (args[0] == "l" || args[0] == "load")
    {
        std::string filename = (args.size() == 1) ? "hw.data" : args[1];

        if (!col.loadCollection(filename))
        {
            std::cerr << "Ошибка при загрузке файла '" << filename << "'" << std::endl;
            return false;
        }

        return true;
    }

    if (args[0] == "s" || args[0] == "save")
    {
        std::string filename = (args.size() == 1) ? "hw.data" : args[1];

        if (!col.saveCollection(filename))
        {
            std::cerr << "Ошибка при сохранении файла '" << filename << "'" << std::endl;
            return false;
        }

        return true;
    }

    if (args[0] == "c" || args[0] == "clean")
    {
        if (args.size() != 1)
        {
            std::cerr << "Некорректное количество аргументов команды clean" << std::endl;
            return false;
        }

        col.clean();

        return true;
    }

    if (args[0] == "a" || args[0] == "add")
    {
        if (args.size() != 6)
        {
            std::cerr << "Некорректное количество аргументов команды add" << std::endl;
            return false;
        }

        col.addItem(std::make_shared<Exhibit>(args[1].c_str(), MetalType(stoul(args[2])), args[3].c_str(),
                                              stoul(args[4]), stoul(args[5])));
        return true;
    }

    if (args[0] == "r" || args[0] == "remove")
    {
        if (args.size() != 2)
        {
            std::cerr << "Некорректное количество аргументов команды remove" << std::endl;
            return false;
        }

        col.removeItem(stoul(args[1]));
        return true;
    }

    if (args[0] == "u" || args[0] == "update")
    {
        if (args.size() != 7)
        {
            std::cerr << "Некорректное количество аргументов команды update" << std::endl;
            return false;
        }

        col.updateItem(stoul(args[1]), std::make_shared<Exhibit>(args[2].c_str(), MetalType(stoul(args[3])),
                                                                 args[4].c_str(), stoul(args[5]), stoul(args[6])));
        return true;
    }

    if (args[0] == "v" || args[0] == "view")
    {
        if (args.size() != 1)
        {
            std::cerr << "Некорректное количество аргументов команды view" << std::endl;
            return false;
        }

        size_t count = 0;
        for (size_t i = 0; i < col.getSize(); ++i)
        {
            const Exhibit &item = static_cast<Exhibit &>(*col.getItem(i));

            if (!col.isRemoved(i))
            {
                std::cout << "[" << i << "] "
                          << item.getSpecialName() << " "
                          << item.getMetalType() << " "
                          << item.getCurrencyName() << " "
                          << item.getCountOfCurrency() << " "
                          << item.getCountOfCoins() << std::endl;
                ++count;
            }
        }

        std::cout << "Количество элементов в коллекции: " << count << std::endl;

        return true;
    }

    std::cerr << "Недопустимая команда '" << args[0] << "'" << std::endl;
    return false;
}

int main(int, char **)
{
    ItemCollector col;

    for (std::string line; std::getline(std::cin, line);)
    {
        if (line.empty())
        {
            break;
        }

        std::istringstream iss(line);
        std::vector<std::string> args;

        for (std::string str; iss.good();)
        {
            iss >> str;
            args.emplace_back(str);
        }

        if (!performCommand(args, col))
        {
            return 1;
        }
    }

    std::cout << "Выполнение завершено успешно" << std::endl;
    return 0;
}

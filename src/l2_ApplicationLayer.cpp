#include "hw/l2_ApplicationLayer.h"

bool Application::performCommand(const std::vector<std::string> &args)
{
  if (args.empty())
  {
    return false;
  }

  if (args[0] == "l" || args[0] == "load")
  {
    std::string filename = (args.size() == 1) ? "hw.data" : args[1];

    if (!_col.loadCollection(filename))
    {
      _out.Output("Ошибка при загрузке файла '" + filename + "'");
      return false;
    }

    return true;
  }

  if (args[0] == "s" || args[0] == "save")
  {
    std::string filename = (args.size() == 1) ? "hw.data" : args[1];

    if (!_col.saveCollection(filename))
    {
      _out.Output("Ошибка при сохранении файла '" + filename + "'");
      return false;
    }

    return true;
  }

  if (args[0] == "c" || args[0] == "clean")
  {
    if (args.size() != 1)
    {
      _out.Output("Некорректное количество аргументов команды clean");
      return false;
    }

    _col.clean();

    return true;
  }

  if (args[0] == "a" || args[0] == "add")
  {
    if (args.size() != 6)
    {
      _out.Output("Некорректное количество аргументов команды add");
      return false;
    }

    _col.addItem(std::make_shared<Exhibit>(args[1].c_str(), MetalType(stoul(args[2])), args[3].c_str(),
                                           stoul(args[4]), stoul(args[5])));
    return true;
  }

  if (args[0] == "r" || args[0] == "remove")
  {
    if (args.size() != 2)
    {
      _out.Output("Некорректное количество аргументов команды remove");
      return false;
    }

    _col.removeItem(stoul(args[1]));
    return true;
  }

  if (args[0] == "u" || args[0] == "update")
  {
    if (args.size() != 7)
    {
      _out.Output("Некорректное количество аргументов команды update");
      return false;
    }

    _col.updateItem(stoul(args[1]), std::make_shared<Exhibit>(args[2].c_str(), MetalType(stoul(args[3])),
                                                              args[4].c_str(), stoul(args[5]), stoul(args[6])));
    return true;
  }

  if (args[0] == "v" || args[0] == "view")
  {
    if (args.size() != 1)
    {
      _out.Output("Некорректное количество аргументов команды view");
      return false;
    }

    size_t count = 0;
    for (size_t i = 0; i < _col.getSize(); ++i)
    {
      const Exhibit &item = static_cast<Exhibit &>(*_col.getItem(i));

      if (!_col.isRemoved(i))
      {
        _out.Output("[" + std::to_string(i) + "] " + item.getSpecialName() + " " +
                    std::to_string(item.getMetalType()) + " " + item.getCurrencyName() + " " +
                    std::to_string(item.getCountOfCurrency()) + " " + std::to_string(item.getCountOfCoins()));
        ++count;
      }
    }

    _out.Output("Количество элементов в коллекции: " + std::to_string(count));
    return true;
  }

  _out.Output("Недопустимая команда '" + args[0] + "'");
  return false;
}

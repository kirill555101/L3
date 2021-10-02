#include "hw/l3_DomainLayer.h"

bool Exhibit::invariant() const
{
  return _special_name.size() <= MAX_STRING_LENGTH && _metal_type >= RARE && _metal_type <= LIGHT &&
         _currency_name.size() <= MAX_STRING_LENGTH && _count_of_currency >= 0 && _count_of_coins >= 0;
}

Exhibit::Exhibit(const std::string &special_name, MetalType metal_type, const std::string &currency_name,
                 int count_of_currency, int count_of_coins)
    : _special_name(special_name), _metal_type(metal_type), _currency_name(currency_name),
      _count_of_currency(count_of_currency), _count_of_coins(count_of_coins)
{
  assert(invariant());
}

const std::string &Exhibit::getSpecialName() const
{
  return _special_name;
}

MetalType Exhibit::getMetalType() const
{
  return _metal_type;
}

const std::string &Exhibit::getCurrencyName() const
{
  return _currency_name;
}

int Exhibit::getCountOfCurrency() const
{
  return _count_of_currency;
}

int Exhibit::getCountOfCoins() const
{
  return _count_of_coins;
}

bool Exhibit::write(std::ostream &os)
{
  writeString(os, _special_name);
  writeNumber(os, _metal_type);
  writeString(os, _currency_name);
  writeNumber(os, _count_of_currency);
  writeNumber(os, _count_of_coins);

  return os.good();
}

std::shared_ptr<ICollectable> ItemCollector::read(std::istream &is)
{
  std::string special_name = readString(is, MAX_STRING_LENGTH);
  MetalType metal_type = readNumber<MetalType>(is);
  std::string currency_name = readString(is, MAX_STRING_LENGTH);
  int count_of_currency = readNumber<int>(is);
  int count_of_coins = readNumber<int>(is);

  return std::make_shared<Exhibit>(special_name, metal_type, currency_name, count_of_currency, count_of_coins);
}

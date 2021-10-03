#ifndef HW_L3_DOMAIN_LAYER_H
#define HW_L3_DOMAIN_LAYER_H

#include "hw/l4_InfrastructureLayer.h"

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
  bool invariant() const;

public:
  Exhibit() = delete;

  Exhibit(const Exhibit &p) = delete;

  Exhibit &operator=(const Exhibit &p) = delete;

  Exhibit(const std::string &special_name, MetalType metal_type, const std::string &currency_name,
          int count_of_currency, int count_of_coins);

  const std::string &getSpecialName() const;

  const std::string &getLastName() const;

  MetalType getMetalType() const;

  const std::string &getCurrencyName() const;

  int getCountOfCurrency() const;

  int getCountOfCoins() const;

  virtual bool write(std::ostream &os) override;
};

class ItemCollector : public ACollector
{
public:
  virtual std::shared_ptr<ICollectable> read(std::istream &is) override;
};

#endif // HW_L3_DOMAIN_LAYER_H

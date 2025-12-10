#ifndef POSTAL_H
#define POSTAL_H

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace GeoNLP
{

typedef std::map<std::string, std::vector<std::string> > ParseResult;
typedef std::vector<std::vector<std::string> >           Hierarchy;

class Postal
{
public:
  Postal();
  ~Postal();

  static std::string normalize_postalcode(const std::string &postal_code);
  static void        result2hierarchy(const std::vector<ParseResult> &p, std::vector<Hierarchy> &h,
                                      std::string &postal_code);

  /// \brief Parse and normalize input string
  ///
  bool parse(const std::string &input, std::vector<ParseResult> &parsed,
             ParseResult &nonormalization);

  /// \brief Normalize input string and return its expansions
  ///
  void expand_string(const std::string &input, std::vector<std::string> &expansions);

  bool get_initialize_every_call() const { return m_initialize_for_every_call; }
  void set_initialize_every_call(bool v) { m_initialize_for_every_call = v; }

  bool get_use_postal() const { return m_use_postal; }
  void set_use_postal(bool v)
  {
    m_use_postal = v;
    if (!v)
      drop();
  }

  bool get_use_primitive() const { return m_use_primitive; }
  void set_use_primitive(bool v) { m_use_primitive = v; }

  void set_postal_datadir(const std::string &global, const std::string &country);
  void set_postal_datadir_country(const std::string &country);

  void clear_languages()
  {
    m_postal_languages.clear();
    drop();
  }
  void add_language(const std::string &lang);

protected:
  bool init();
  void drop();

  void expand(const ParseResult &input, std::vector<ParseResult> &result);

protected:
  bool m_initialized               = false;
  bool m_initialize_for_every_call = false;
  bool m_use_postal                = true;
  bool m_use_primitive             = true;

  std::vector<char>               m_postal_datadir_global;
  std::vector<char>               m_postal_datadir_country;
  std::vector<std::vector<char> > m_postal_languages;
};

std::unique_ptr<Postal> new_postal();

std::unique_ptr<ParseResult> new_parse_result();

struct NiceParseResult
{
    std::vector<std::string> country;
    std::vector<std::string> country_region;
    std::vector<std::string> state;
    std::vector<std::string> state_district;
    std::vector<std::string> island;
    std::vector<std::string> city;
    std::vector<std::string> city_district;
    std::vector<std::string> suburb;
    std::vector<std::string> road;
    std::vector<std::string> house_number;
    std::vector<std::string> category;
    std::vector<std::string> house;

    const std::vector<std::string> &get_country() const { return country; }
    const std::vector<std::string> &get_country_region() const { return country_region; }
    const std::vector<std::string> &get_state() const { return state; }
    const std::vector<std::string> &get_state_district() const { return state_district; }
    const std::vector<std::string> &get_island() const { return island; }
    const std::vector<std::string> &get_city() const { return city; }
    const std::vector<std::string> &get_city_district() const { return city_district; }
    const std::vector<std::string> &get_suburb() const { return suburb; }
    const std::vector<std::string> &get_road() const { return road; }
    const std::vector<std::string> &get_house_number() const { return house_number; }
    const std::vector<std::string> &get_category() const { return category; }
    const std::vector<std::string> &get_house() const { return house; }
};
std::unique_ptr<NiceParseResult> new_nice_parse_result(const ParseResult &result);

}

#endif // POSTAL_H

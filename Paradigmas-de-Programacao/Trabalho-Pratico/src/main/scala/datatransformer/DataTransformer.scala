package datatransformer

import ujson.Value

trait DataTransformer:

  /** Extracts languages spoken in each country.
    * @param data
    *   The input data.
    * @return
    *   A map where keys are country names and values are lists of languages
    *   spoken.
    */
  def getLanguages(data: Value): Map[String, List[String]]

  /** Extracts population of each country.
    * @param data
    *   The input data.
    * @return
    *   A map where keys are country names and values are population counts.
    */
  def getPopulation(data: Value): Map[String, Int]

  /** Extracts the side of the road cars drive on in each country.
    * @param data
    *   The input data.
    * @return
    *   A map where keys are country names and values are "left" or "right".
    */
  def getCarSides(data: Value): Map[String, String]

  /** Extracts the independence status of each country.
    * @param data
    *   The input data.
    * @return
    *   A map where keys are country names and values are booleans indicating
    *   independence.
    */
  def getIndependenceStatus(data: Value): Map[String, Boolean]

  /** Extracts the population density of each country.
    * @param data
    *   The input data.
    * @return
    *   A map where keys are country names and values are population densities.
    */
  def getPopulationDensity(data: Value): Map[String, Double]

  /** Extracts countries with multiple official languages.
    * @param data
    *   The input data.
    * @return
    *   A list of country names with multiple official languages.
    */
  def getCountriesWithMultipleLanguages(data: Value): List[String]

  /** Finds the country with the maximum population.
    * @param data
    *   The input data.
    * @return
    *   A tuple containing the country name and its population.
    */
  def getCountryWithMaxPopulation(data: Value): (String, Int)

  /** Finds the country with the minimum population.
    * @param data
    *   The input data.
    * @return
    *   A tuple containing the country name and its population.
    */
  def getCountryWithMinPopulation(data: Value): (String, Int)

  /** Finds the country with the maximum area.
    * @param data
    *   The input data.
    * @return
    *   A tuple containing the country name and its area.
    */
  def getCountryWithMaxArea(data: Value): (String, Double)

  /** Finds the country with the minimum area.
    * @param data
    *   The input data.
    * @return
    *   A tuple containing the country name and its area.
    */
  def getCountryWithMinArea(data: Value): (String, Double)

  /** Counts the total number of countries.
    * @param data
    *   The input data.
    * @return
    *   The total number of countries.
    */
  def getTotalCountriesCount(data: Value): Int

  /** Finds the country with the maximum population density.
    * @param data
    *   The input data.
    * @return
    *   A tuple containing the country name and its population density.
    */
  def getCountryWithMaxDensity(data: Value): (String, Double)

  /** Finds the country with the minimum population density.
    * @param data
    *   The input data.
    * @return
    *   A tuple containing the country name and its population density.
    */
  def getCountryWithMinDensity(data: Value): (String, Double)

  /** Extracts countries with multiple currencies.
    * @param data
    *   The input data.
    * @return
    *   A list of country names with multiple currencies.
    */
  def getCountriesWithMultipleCurrencies(data: Value): List[String]

  /** Extracts countries with multiple capitals.
    * @param data
    *   The input data.
    * @return
    *   A list of country names with multiple capitals.
    */
  def getCountriesWithMultipleCapitals(data: Value): List[String]

  /** Finds the country with the maximum number of borders.
    * @param data
    *   The input data.
    * @return
    *   A tuple containing the country name and its number of borders.
    */
  def getCountryWithMaxBorders(data: Value): (String, Int)

  /** Finds the country with the minimum number of borders.
    * @param data
    *   The input data.
    * @return
    *   A tuple containing the country name and its number of borders.
    */
  def getCountryWithMinBorders(data: Value): (String, Int)

  /** Extracts countries with multiple timezones.
    * @param data
    *   The input data.
    * @return
    *   A list of country names with multiple timezones.
    */
  def getCountriesWithMultipleTimezones(data: Value): List[String]

  /** Finds the country with the maximum Gini coefficient.
    * @param data
    *   The input data.
    * @return
    *   A tuple containing the country name and its Gini coefficient.
    */
  def getCountryWithMaxGini(data: Value): (String, Map[String, Double])

  /** Finds the country with the minimum Gini coefficient.
    * @param data
    *   The input data.
    * @return
    *   A tuple containing the country name and its Gini coefficient.
    */
  def getCountryWithMinGini(data: Value): (String, Map[String, Double])

  /** Extracts countries with multiple continents.
    * @param data
    *   The input data.
    * @return
    *   A list of country names with multiple continents.
    */
  def getCountriesWithMultipleContinents(data: Value): List[String]

  /** Extracts countries with multiple calling codes.
    * @param data
    *   The input data.
    * @return
    *   A list of country names with multiple calling codes.
    */
  def getCountriesWithMultipleCallingCodes(data: Value): List[String]

  /** Extracts countries with multiple regional blocs.
    * @param data
    *   The input data.
    * @return
    *   A list of country names with multiple regional blocs.
    */
  def getCountriesWithMultipleRegionalBlocs(data: Value): List[String]

  /** Extracts countries with the most translations.
    * @param data
    *   The input data.
    * @return
    *   A list of country names with the most translations.
    */
  def getCountriesWithMostTranslations(data: Value): List[String]

  /** Finds the country with the maximum latitude.
    * @param data
    *   The input data.
    * @return
    *   A tuple containing the country name and its latitude.
    */
  def getCountryWithMaxLatitude(data: Value): (String, Double)

  /** Finds the country with the minimum latitude.
    * @param data
    *   The input data.
    * @return
    *   A tuple containing the country name and its latitude.
    */
  def getCountryWithMinLatitude(data: Value): (String, Double)

  /** Finds the country with the maximum longitude.
    * @param data
    *   The input data.
    * @return
    *   A tuple containing the country name and its longitude.
    */
  def getCountryWithMaxLongitude(data: Value): (String, Double)

  /** Finds the country with the minimum longitude.
    * @param data
    *   The input data.
    * @return
    *   A tuple containing the country name and its longitude.
    */
  def getCountryWithMinLongitude(data: Value): (String, Double)

  /** Extracts countries with multiple top-level domains.
    * @param data
    *   The input data.
    * @return
    *   A list of country names with multiple top-level domains.
    */
  def getCountriesWithMultipleTopLevelDomains(data: Value): List[String]

  /** Transforms the input data into a list of maps containing various country
    * attributes.
    * @param data
    *   The input data.
    * @return
    *   A list of maps where each map represents a country with its attributes.
    */
  def transformData(data: Value): List[Map[String, Any]]

object DataTransformerImpl extends DataTransformer:
  /** Extracts a mapping of country names to their respective languages from the
    * given data.
    *
    * @param data
    *   The input data containing country information.
    * @return
    *   A map where each key is a country name and the corresponding value is a
    *   list of languages spoken in that country.
    */
  def getLanguages(data: Value): Map[String, List[String]] =
    data.arr.map { country =>
      val name = country("name")("common").str
      val languages = country("languages").obj.values.map(_.str).toList
      name -> languages
    }.toMap

  def getPopulation(data: Value): Map[String, Int] =
    data.arr.map { country =>
      val name = country("name")("common").str
      val population = country("population").num.toInt
      name -> population
    }.toMap

  def getCarSides(data: Value): Map[String, String] =
    data.arr.map { country =>
      val name = country("name")("common").str
      val carSide = country("car")("side").str
      name -> carSide
    }.toMap

  def getIndependenceStatus(data: Value): Map[String, Boolean] =
    data.arr.map { country =>
      val name = country("name")("common").str
      val independent = country.obj.get("independent").exists(_.bool)
      name -> independent
    }.toMap

  def getPopulationDensity(data: Value): Map[String, Double] =
    data.arr.map { country =>
      val name = country("name")("common").str
      val population = country("population").num
      val area = country("area").num
      val density = if (area != 0) population / area else 0
      name -> density
    }.toMap

  def getCountriesWithMultipleLanguages(data: Value): List[String] =
    data.arr.collect {
      case country if country("languages").obj.size > 1 =>
        country("name")("common").str
    }.toList

  def getCountryWithMaxPopulation(data: Value): (String, Int) =
    val maxCountry = data.arr.maxBy(_("population").num)
    (maxCountry("name")("common").str, maxCountry("population").num.toInt)

  def getCountryWithMinPopulation(data: Value): (String, Int) =
    val minCountry = data.arr.minBy(_("population").num)
    (minCountry("name")("common").str, minCountry("population").num.toInt)

  def getCountryWithMaxArea(data: Value): (String, Double) =
    val maxCountry = data.arr.maxBy(_("area").num)
    (maxCountry("name")("common").str, maxCountry("area").num)

  def getCountryWithMinArea(data: Value): (String, Double) =
    val minCountry = data.arr.minBy(_("area").num)
    (minCountry("name")("common").str, minCountry("area").num)

  def getTotalCountriesCount(data: Value): Int =
    data.arr.size

  def getCountryWithMaxDensity(data: Value): (String, Double) =
    val densities = getPopulationDensity(data)
    densities.maxBy(_._2)

  def getCountryWithMinDensity(data: Value): (String, Double) =
    val densities = getPopulationDensity(data)
    densities.minBy(_._2)

  def getCountriesWithMultipleCurrencies(data: Value): List[String] =
    data.arr.collect {
      case country
          if country.obj
            .contains("currencies") && country("currencies").obj.size > 1 =>
        country("name")("common").str
    }.toList

  def getCountriesWithMultipleCapitals(data: Value): List[String] =
    data.arr.collect {
      case country
          if country.obj
            .contains("capital") && country("capital").arr.size > 1 =>
        country("name")("common").str
    }.toList

  def getCountryWithMaxBorders(data: Value): (String, Int) =
    val maxCountry =
      data.arr.filter(_.obj.contains("borders")).maxBy(_("borders").arr.size)
    (maxCountry("name")("common").str, maxCountry("borders").arr.size)

  def getCountryWithMinBorders(data: Value): (String, Int) =
    val minCountry =
      data.arr.filter(_.obj.contains("borders")).minBy(_("borders").arr.size)
    (minCountry("name")("common").str, minCountry("borders").arr.size)

  def getCountriesWithMultipleTimezones(data: Value): List[String] =
    data.arr.collect {
      case country if country("timezones").arr.size > 1 =>
        country("name")("common").str
    }.toList

  def getCountryWithMaxGini(data: Value): (String, Map[String, Double]) =
    val giniValues = data.arr.collect {
      case country if country.obj.contains("gini") =>
        country("name")("common").str -> country("gini").obj.map {
          case (year, value) => year -> value.num
        }.toMap
    }
    giniValues.maxBy(_._2.values.max)

  def getCountryWithMinGini(data: Value): (String, Map[String, Double]) =
    val giniValues = data.arr.collect {
      case country if country.obj.contains("gini") =>
        country("name")("common").str -> country("gini").obj.map {
          case (year, value) => year -> value.num
        }.toMap
    }
    giniValues.minBy(_._2.values.min)

  def getCountriesWithMultipleContinents(data: Value): List[String] =
    data.arr.collect {
      case country if country("continents").arr.size > 1 =>
        country("name")("common").str
    }.toList

  def getCountriesWithMultipleCallingCodes(data: Value): List[String] =
    data.arr.collect {
      case country
          if country("idd").obj
            .contains("suffixes") && country("idd")("suffixes").arr.size > 1 =>
        country("name")("common").str
    }.toList

  def getCountriesWithMultipleRegionalBlocs(data: Value): List[String] =
    data.arr.collect {
      case country
          if country.obj.contains("regionalBlocs") && country(
            "regionalBlocs"
          ).arr.size > 1 =>
        country("name")("common").str
    }.toList

  def getCountriesWithMostTranslations(data: Value): List[String] =
    data.arr.collect {
      case country if country("translations").obj.size > 1 =>
        country("name")("common").str
    }.toList

  def getCountryWithMaxLatitude(data: Value): (String, Double) =
    val maxCountry = data.arr.maxBy(_("latlng")(0).num)
    (maxCountry("name")("common").str, maxCountry("latlng")(0).num)

  def getCountryWithMinLatitude(data: Value): (String, Double) =
    val minCountry = data.arr.minBy(_("latlng")(0).num)
    (minCountry("name")("common").str, minCountry("latlng")(0).num)

  def getCountryWithMaxLongitude(data: Value): (String, Double) =
    val maxCountry = data.arr.maxBy(_("latlng")(1).num)
    (maxCountry("name")("common").str, maxCountry("latlng")(1).num)

  def getCountryWithMinLongitude(data: Value): (String, Double) =
    val minCountry = data.arr.minBy(_("latlng")(1).num)
    (minCountry("name")("common").str, minCountry("latlng")(1).num)

  def getCountriesWithMultipleTopLevelDomains(data: Value): List[String] =
    data.arr.collect {
      case country
          if country.obj.contains("tld") && country("tld").arr.size > 1 =>
        country("name")("common").str
    }.toList

  def transformData(data: Value): List[Map[String, Any]] =
    data.arr.map { country =>
      Map(
        "name" -> country("name")("common").str,
        "languages" -> country.obj
          .get("languages")
          .map(_.obj.values.map(_.str).toList)
          .getOrElse(List.empty),
        "population" -> country("population").num.toInt,
        "carSide" -> country.obj
          .get("car")
          .map(_("side").str)
          .getOrElse("unknown"),
        "independent" -> country.obj.get("independent").exists(_.bool),
        "density" -> (if (country.obj.get("area").exists(_.num != 0))
                        country("population").num / country("area").num
                      else 0),
        "currencies" -> country.obj
          .get("currencies")
          .map(
            _.obj.values
              .map {
                case obj: ujson.Obj => obj("name").str
                case other          => other.str
              }
              .toList
          )
          .getOrElse(List.empty),
        "capitals" -> country.obj
          .get("capital")
          .map(_.arr.map(_.str).toList)
          .getOrElse(List.empty),
        "borders" -> country.obj
          .get("borders")
          .map(_.arr.map(_.str).toList)
          .getOrElse(List.empty),
        "timezones" -> country.obj
          .get("timezones")
          .map(_.arr.map(_.str).toList)
          .getOrElse(List.empty),
        "gini" -> country.obj
          .get("gini")
          .map { giniObj =>
            giniObj.obj.values.map(_.num).max
          }
          .getOrElse(0.0),
        "continents" -> country.obj
          .get("continents")
          .map(_.arr.map(_.str).toList)
          .getOrElse(List.empty),
        "callingCodes" -> country.obj
          .get("idd")
          .flatMap(_.obj.get("suffixes"))
          .map(_.arr.map(_.str).toList)
          .getOrElse(List.empty),
        "regionalBlocs" -> country.obj
          .get("regionalBlocs")
          .map(_.arr.map(_.str).toList)
          .getOrElse(List.empty),
        "translations" -> country.obj
          .get("translations")
          .map(
            _.obj.values
              .map {
                case obj: ujson.Obj => obj("common").str
                case other          => other.str
              }
              .toList
          )
          .getOrElse(List.empty),
        "latitude" -> country.obj
          .get("latlng")
          .map(_.arr(0).num)
          .getOrElse(0.0),
        "longitude" -> country.obj
          .get("latlng")
          .map(_.arr(1).num)
          .getOrElse(0.0),
        "topLevelDomains" -> country.obj
          .get("tld")
          .map(_.arr.map(_.str).toList)
          .getOrElse(List.empty)
      )
    }.toList

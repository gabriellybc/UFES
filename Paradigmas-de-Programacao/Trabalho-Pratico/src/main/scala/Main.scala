import scala.concurrent.{Future, ExecutionContext}
import scala.concurrent.ExecutionContext.Implicits.global
import scala.util.{Success, Failure}
import datatransformer.DataTransformerImpl
import datafetcher.DataFetcher
import dataexporter.DataExporter
import visuals.Graph
import ujson.Value

@main def app(): Unit = {
  // Obter os dados de todos os países de forma paralela
  val allCountriesDataFuture: Future[Value] =
    Future(DataFetcher.fetchFromEndpoint("https://restcountries.com/v3.1/all"))

  val countriesLanguagesDataFuture: Future[Value] = Future(
    DataFetcher.fetchFromEndpoint(
      "https://restcountries.com/v3.1/all?fields=name,languages"
    )
  )

  val countriesPopulationDataFuture: Future[Value] = Future(
    DataFetcher.fetchFromEndpoint(
      "https://restcountries.com/v3.1/all?fields=name,population"
    )
  )

  val countriesCarSideDataFuture: Future[Value] = Future(
    DataFetcher.fetchFromEndpoint(
      "https://restcountries.com/v3.1/all?fields=name,car"
    )
  )

  val independentCountriesDataFuture: Future[Value] = Future(
    DataFetcher.fetchFromEndpoint(
      "https://restcountries.com/v3.1/all?fields=name,independent"
    )
  )

  // Combinar os futuros e processar os dados quando todos estiverem completos
  val combinedFuture = for {
    allCountriesData <- allCountriesDataFuture
    countriesLanguagesData <- countriesLanguagesDataFuture
    countriesPopulationData <- countriesPopulationDataFuture
    countriesCarSideData <- countriesCarSideDataFuture
    independentCountriesData <- independentCountriesDataFuture
  } yield {
    // Exportar os dados brutos para um arquivo CSV e JSON
    val rawExportCsv: Future[Unit] = Future {
      DataExporter.toCsv(allCountriesData, "raw_output.csv")
    }

    val rawExportJson: Future[Unit] = Future {
      DataExporter.toJson(allCountriesData, "raw_output.json")
    }

    // Transformações e exportações em paralelo
    val transformations: List[Future[Unit]] = List(
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Languages",
              "Data" -> DataTransformerImpl
                .getLanguages(countriesLanguagesData)
                .toString
            )
          ),
          "languages_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Population",
              "Data" -> DataTransformerImpl
                .getPopulation(countriesPopulationData)
                .toString
            )
          ),
          "population_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Car Side",
              "Data" -> DataTransformerImpl
                .getCarSides(countriesCarSideData)
                .toString
            )
          ),
          "car_side_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Independence",
              "Data" -> DataTransformerImpl
                .getIndependenceStatus(independentCountriesData)
                .toString
            )
          ),
          "independence_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Population Density",
              "Data" -> DataTransformerImpl
                .getPopulationDensity(allCountriesData)
                .toString
            )
          ),
          "population_density_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Countries with Multiple Languages",
              "Data" -> DataTransformerImpl
                .getCountriesWithMultipleLanguages(countriesLanguagesData)
                .toString
            )
          ),
          "multiple_languages_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Country with Max Population",
              "Data" -> DataTransformerImpl
                .getCountryWithMaxPopulation(countriesPopulationData)
                .toString
            )
          ),
          "max_population_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Country with Min Population",
              "Data" -> DataTransformerImpl
                .getCountryWithMinPopulation(countriesPopulationData)
                .toString
            )
          ),
          "min_population_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Country with Max Area",
              "Data" -> DataTransformerImpl
                .getCountryWithMaxArea(allCountriesData)
                .toString
            )
          ),
          "max_area_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Country with Min Area",
              "Data" -> DataTransformerImpl
                .getCountryWithMinArea(allCountriesData)
                .toString
            )
          ),
          "min_area_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Total Countries Count",
              "Data" -> DataTransformerImpl
                .getTotalCountriesCount(allCountriesData)
                .toString
            )
          ),
          "total_countries_count_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Country with Max Density",
              "Data" -> DataTransformerImpl
                .getCountryWithMaxDensity(allCountriesData)
                .toString
            )
          ),
          "max_density_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Country with Min Density",
              "Data" -> DataTransformerImpl
                .getCountryWithMinDensity(allCountriesData)
                .toString
            )
          ),
          "min_density_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Countries with Multiple Currencies",
              "Data" -> DataTransformerImpl
                .getCountriesWithMultipleCurrencies(allCountriesData)
                .toString
            )
          ),
          "multiple_currencies_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Countries with Multiple Capitals",
              "Data" -> DataTransformerImpl
                .getCountriesWithMultipleCapitals(allCountriesData)
                .toString
            )
          ),
          "multiple_capitals_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Country with Max Borders",
              "Data" -> DataTransformerImpl
                .getCountryWithMaxBorders(allCountriesData)
                .toString
            )
          ),
          "max_borders_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Country with Min Borders",
              "Data" -> DataTransformerImpl
                .getCountryWithMinBorders(allCountriesData)
                .toString
            )
          ),
          "min_borders_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Countries with Multiple Timezones",
              "Data" -> DataTransformerImpl
                .getCountriesWithMultipleTimezones(allCountriesData)
                .toString
            )
          ),
          "multiple_timezones_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Country with Max Gini",
              "Data" -> DataTransformerImpl
                .getCountryWithMaxGini(allCountriesData)
                .toString
            )
          ),
          "max_gini_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Country with Min Gini",
              "Data" -> DataTransformerImpl
                .getCountryWithMinGini(allCountriesData)
                .toString
            )
          ),
          "min_gini_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Countries with Multiple Continents",
              "Data" -> DataTransformerImpl
                .getCountriesWithMultipleContinents(allCountriesData)
                .toString
            )
          ),
          "multiple_continents_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Countries with Multiple Calling Codes",
              "Data" -> DataTransformerImpl
                .getCountriesWithMultipleCallingCodes(allCountriesData)
                .toString
            )
          ),
          "multiple_calling_codes_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Countries with Multiple Regional Blocs",
              "Data" -> DataTransformerImpl
                .getCountriesWithMultipleRegionalBlocs(allCountriesData)
                .toString
            )
          ),
          "multiple_regional_blocs_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Countries with Most Translations",
              "Data" -> DataTransformerImpl
                .getCountriesWithMostTranslations(allCountriesData)
                .toString
            )
          ),
          "most_translations_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Country with Max Latitude",
              "Data" -> DataTransformerImpl
                .getCountryWithMaxLatitude(allCountriesData)
                .toString
            )
          ),
          "max_latitude_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Country with Min Latitude",
              "Data" -> DataTransformerImpl
                .getCountryWithMinLatitude(allCountriesData)
                .toString
            )
          ),
          "min_latitude_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Country with Max Longitude",
              "Data" -> DataTransformerImpl
                .getCountryWithMaxLongitude(allCountriesData)
                .toString
            )
          ),
          "max_longitude_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Country with Min Longitude",
              "Data" -> DataTransformerImpl
                .getCountryWithMinLongitude(allCountriesData)
                .toString
            )
          ),
          "min_longitude_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Countries with Multiple Top Level Domains",
              "Data" -> DataTransformerImpl
                .getCountriesWithMultipleTopLevelDomains(allCountriesData)
                .toString
            )
          ),
          "multiple_top_level_domains_output.csv"
        )
      },
      Future {
        DataExporter.toCsv(
          List(
            Map(
              "Transformation" -> "Transform Data",
              "Data" -> DataTransformerImpl
                .transformData(allCountriesData)
                .toString
            )
          ),
          "transform_data_output.csv"
        )
      }
    )

    // Aguardar a conclusão de todas as transformações e exportações
    val allExports =
      Future.sequence(rawExportCsv :: rawExportJson :: transformations)

    allExports.onComplete {
      case Success(_) =>
        println("Todas as exportações foram concluídas com sucesso.")
      case Failure(e) => println(s"Falha na exportação: ${e.getMessage}")
    }

    // Geração de gráficos em paralelo
    val graphFutures: List[Future[Unit]] = List(
      Future {
        Graph.langRank(countriesLanguagesData, "grafico-linguas.html")
      },
      Future {
        Graph.populationRank(countriesPopulationData, "grafico-populacoes.html")
      },
      Future {
        Graph.carsideRank(countriesCarSideData, "grafico-volante.html")
      },
      Future {
        Graph.freedomRank(
          independentCountriesData,
          "grafico-paises-independentes.html"
        )
      },
      Future {
        Graph.populationDensityRank(
          DataTransformerImpl.getPopulationDensity(allCountriesData),
          "grafico-densidade-populacional.html"
        )
      }
    )

    // Aguardar a conclusão de todos os gráficos
    val allGraphs = Future.sequence(graphFutures)

    allGraphs.onComplete {
      case Success(_) =>
        println("\n\nTodos os gráficos foram gerados com sucesso!\n\n")
      case Failure(e) =>
        println(s"\n\nFalha na geração dos gráficos: ${e.getMessage}\n\n")
    }
  }

  // Esperar a conclusão de todas as operações
  combinedFuture.onComplete {
    case Success(_) => println("\n\nProcessamento concluído com sucesso!!\n\n")
    case Failure(exception) =>
      println(s"\n\nErro durante o processamento: ${exception.getMessage}\n\n")
  }
}

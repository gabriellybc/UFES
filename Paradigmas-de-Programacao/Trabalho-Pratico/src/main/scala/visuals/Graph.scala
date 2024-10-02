package visuals:
  import plotly._, element._, layout._, Plotly._
  import scala.collection.mutable.ArrayBuffer

  object Graph:
    /** Saves a plot to a specified file.
      *
      * @param plot
      *   A sequence of Scatter or Bar objects representing the plot data.
      * @param lay
      *   The layout configuration for the plot.
      * @param filename
      *   The name of the file to save the plot to.
      *
      * This method saves the provided plot to a file in the "graficos"
      * directory within the current working directory. If the directory does
      * not exist, it will be created. If a file with the specified name already
      * exists, it will be overwritten.
      */
    def savePlot(
        plot: Seq[Scatter | Bar],
        lay: Layout,
        filename: String
    ): Unit =
      val cwd = os.pwd
      val outputpath = cwd / "graficos"
      if os.exists(outputpath) == false then os.makeDir(outputpath)
      val filepath = outputpath / filename
      if os.exists(filepath) == true then os.remove(filepath)
      plot.plot(filepath.toString(), lay)

    /** Generates a bar chart showing the number of independent and
      * non-independent countries.
      *
      * @param listaPaisesCarside
      *   A JSON value containing a list of countries with their independence
      *   status.
      * @param filename
      *   The name of the file where the plot will be saved.
      *
      * The function processes the input JSON to extract the name and
      * independence status of each country. It counts the number of independent
      * and non-independent countries, then generates a bar chart with this
      * information. The chart is saved to the specified file.
      */
    def freedomRank(listaPaisesCarside: ujson.Value, filename: String): Unit =
      val pais_freedom: ArrayBuffer[Tuple2[String, Boolean]] =
        listaPaisesCarside.arr.map((obj: ujson.Value) =>
          Tuple2(
            obj("name")("common").str,
            if (obj("name")("common").str == "Kosovo") false
            else obj("independent").bool
          )
        )
      val independent = pais_freedom.count(_._2 == true)
      val dependent = pais_freedom.count(_._2 == false)
      val labels = Seq("Independente", "Nao independente")
      val values = Seq(independent, dependent)
      val plot = Seq(Bar(labels, values))
      val lay = Layout().withTitle("Paises independentes e nao independentes")
      this.savePlot(plot, lay, filename)

    /** Generates a bar chart showing the distribution of car steering positions
      * (left or right) for a given list of countries and saves the plot to a
      * specified file.
      *
      * @param listaPaisesCarside
      *   A ujson.Value containing an array of country objects, each with a
      *   "name" and "car" field.
      * @param filename
      *   The name of the file where the plot will be saved.
      */
    def carsideRank(listaPaisesCarside: ujson.Value, filename: String): Unit =
      val pais_carsize: ArrayBuffer[Tuple2[String, String]] =
        listaPaisesCarside.arr.map((obj: ujson.Value) =>
          Tuple2(obj("name")("common").str, obj("car")("side").str)
        )
      val left = pais_carsize.count(_._2 == "left")
      val right = pais_carsize.count(_._2 == "right")
      val labels = Seq("Right", "Left")
      val values = Seq(left, right)
      val plot = Seq(Bar(labels, values))
      val lay =
        Layout().withTitle("Posição do volante nos carros ao redor do mundo")
      this.savePlot(plot, lay, filename)

    /** Generates a population ranking graph for the top 10 most populous
      * countries.
      *
      * @param lista_paises_populacao
      *   A ujson.Value containing a list of countries with their population
      *   data.
      * @param filename
      *   The name of the file where the graph will be saved.
      */
    def populationRank(
        lista_paises_populacao: ujson.Value,
        filename: String
    ): Unit =
      val countriesPopulationData: ArrayBuffer[Tuple2[String, Double]] =
        lista_paises_populacao.arr.map((obj: ujson.Value) =>
          Tuple2(obj("name")("common").str, obj("population").num)
        )
      val countriesPopulationData_ordered: ArrayBuffer[Tuple2[String, Double]] =
        countriesPopulationData
          .sortWith((item1, item2) => item1._2 > item2._2)
          .slice(0, 10)
      val x = countriesPopulationData_ordered.map((elem) => elem._1)
      val y = countriesPopulationData_ordered.map((elem) => elem._2)
      val plot = Seq(Scatter(x, y))
      val lay = Layout().withTitle("Países mais populosos do mundo")
      this.savePlot(plot, lay, filename)

    /** This function generates a ranked plot of the most spoken languages in
      * the world based on the provided data.
      *
      * @param lista_paises_linguas
      *   A JSON value containing a list of countries and their respective
      *   languages.
      * @param filename
      *   The name of the file where the plot will be saved.
      *
      * The function performs the following steps:
      *   1. Extracts a list of all languages found in the provided list. 2.
      *      Flattens the list of languages to obtain a list of strings and
      *      optionally sorts it. 3. Removes duplicate languages to get a list
      *      of unique languages. 4. Counts how many countries speak each
      *      language. 5. Sorts the languages by the number of countries that
      *      speak them in descending order and takes the top 10. 6. Defines the
      *      x-axis of the plot as the names of the most spoken languages. 7.
      *      Defines the y-axis of the plot as the total number of countries
      *      that speak each language. 8. Prepares and plots the graph. 9. Saves
      *      the plot to the specified filename.
      */
    // Essa foi a primeira função que fiz, por isso está toda comentadinha :)
    def langRank(lista_paises_linguas: ujson.Value, filename: String): Unit =
      // Obtendo uma lista cujos elementos são todas as línguas encontradas na lista fornecida.
      val countriesLanguagesData0: ArrayBuffer[Iterable[ujson.Value]] =
        lista_paises_linguas.arr.map((obj: ujson.Value) =>
          obj("languages").obj.values
        )

      // Os elementos da lista anterior são iteráveis de strings.
      // Agora, utilizamos o método 'flatten' para obter as strings desses iteráveis, de forma a obter de fato uma lista de strings.
      // Em seguida, ordenamos a lista de strings (Opcional)
      val countriesLanguagesData1: ArrayBuffer[ujson.Value] =
        countriesLanguagesData0.flatten.sortWith((item1, item2) =>
          item1.str.take(3).compareTo(item2.str.take(3)) < 0
        )

      // Obtendo uma lista sem duplicatas de todas as línguas existentes
      val linguasUnicas = countriesLanguagesData1.distinct

      // Contando quantos países falam tal língua
      val contagemLinguasPais = linguasUnicas.map((elem) =>
        Map((elem.str, countriesLanguagesData1.count(_ == elem)))
      )
      // Ordenando o Map obtido anteriormente de acordo com os seus valores
      val contagemLinguasPaisOrdered = contagemLinguasPais
        .sortBy((v) => v.values.toSeq(0))
        .reverse
        .slice(0, 10)

      // Definindo o eixo x do plot como sendo o nome das línguas faladas no mundo
      val x = contagemLinguasPaisOrdered.map((elem) => elem.keys).flatten

      // Definindo o eixo y do plot como sendo o total de países que falam determinada língua
      val y = contagemLinguasPaisOrdered.map((elem) => elem.values).flatten

      // Preparando e plotando gráfico
      val plot = Seq(
        // Scatter(x, y).withName("Linguas mais faladas no mundo"),
        Scatter(x, y)
      )
      val lay = Layout().withTitle("Linguas mais faladas no mundo")

      // Salvando plot
      this.savePlot(plot, lay, filename)

    /** Generates a bar plot representing the population density rank for given
      * data and saves it to a file.
      *
      * @param data
      *   A map where keys are country names and values are their respective
      *   population densities.
      * @param filename
      *   The name of the file where the plot will be saved.
      */
    def populationDensityRank(
        data: Map[String, Double],
        filename: String
    ): Unit = {
      val labels = data.keys.toSeq
      val values = data.values.toSeq
      val plot = Seq(Bar(labels, values))
      val lay = Layout().withTitle("Densidade Populacional por País")
      savePlot(plot, lay, filename)
    }

//Referências
//https://www.baeldung.com/scala/maps-guide
//https://stackoverflow.com/questions/11448685/scala-how-can-i-count-the-number-of-occurrences-in-a-list
//https://www.baeldung.com/scala/sorting
//https://stackoverflow.com/questions/19386964/i-want-to-get-the-type-of-a-variable-at-runtime#19388888 (getClass)
//https://docs.scala-lang.org/toolkit/json-deserialize.html
//https://docs.scala-lang.org/toolkit/json-parse.html
//https://index.scala-lang.org/alexarchambault/plotly-scala

//Problemas e como eu os resolvi
//1: Não conseguia visualizar os arquivos html que são gerados pela biblioteca do plotly-js dentro do wsl
//Solução: Rodar `wslview <arquivo html plot>` permite visualizar o arquivo html gerado dentro do WSL no browser do Windows

//2: Por algum motivo o `xdg-open` estava tentando usar o vim para abrir os arquivos html gerados para os graficos (o que obviamente não funcionava)
//Solução: mudar a aplicação padrão para abrir o mime type do html usando o seguinte comando: `xdg-mime default wslview.desktop text/html`
//https://superuser.com/questions/1262977/open-browser-in-host-system-from-windows-subsystem-for-linux
//https://unix.stackexchange.com/questions/36380/how-to-properly-and-easily-configure-xdg-open-without-any-environment
//https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/MIME_types/Common_types

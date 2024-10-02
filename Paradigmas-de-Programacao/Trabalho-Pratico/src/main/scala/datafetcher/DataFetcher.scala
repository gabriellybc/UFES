package datafetcher:
  import sttp.client4.quick.*
  import sttp.client4.Response
  trait FetchFromURL:
    /**
     * Fetches data from the specified endpoint.
     *
     * @param endpoint The URL of the endpoint to fetch data from.
     * @return The fetched data as a ujson.Value.
     */
    def fetchFromEndpoint(endpoint: String): ujson.Value

  trait FetchFromFile:
    /**
     * Fetches data from a specified file.
     *
     * @param filename The name of the file from which to fetch data.
     * @return The data fetched from the file as a ujson.Value.
     */
    def fetchFromFile(filename: String): ujson.Value

  // Classe de instância única criada para o objeto responsável por obter os dados a serem usados na análise.
  // Não há porque ter mais de um desse carinha, por isso foi optado por esse design.
  // O design foi pensado para ser flexível, por isso são implementados serviços de data fetching por meio de traits.
  object DataFetcher extends FetchFromURL, FetchFromFile:
    def fetchFromEndpoint(endpoint: String): ujson.Value =
      val response: Response[String] = quickRequest
        .get(uri"$endpoint")
        .send()
      // println(response.code) //200
      // println(response.body) //Content
      val json: ujson.Value = ujson.read(response.body)
      json


    def fetchFromFile(filename: String): ujson.Value =
      val cwd = os.pwd
      val datapath = cwd / "data"
      val filepath = datapath / filename
      val content = os.read(filepath)
      val json = ujson.read(content)
      json

  /* Algumas referencias
   * https://docs.scala-lang.org/scala3/book/packaging-imports.html
   * https://docs.scala-lang.org/scala3/book/taste-objects.html
   * https://docs.scala-lang.org/scala3/book/taste-modeling.html
   * https://docs.scala-lang.org/scala3/book/taste-methods.html
   */

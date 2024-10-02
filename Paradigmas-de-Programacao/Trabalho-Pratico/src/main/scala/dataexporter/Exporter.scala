package dataexporter:
  import sttp.client4.quick.*
  import com.github.tototoshi.csv._
  import java.io.File
  import ujson.Value

  trait Export2Csv:
    /** Converts the given JSON data to a CSV format and writes it to the
      * specified output file.
      *
      * @param data
      *   The JSON data to be converted to CSV.
      * @param output
      *   The file path where the CSV data will be written.
      */
    def toCsv(data: ujson.Value, output: String): Unit

    /** Converts the given transformed data to a CSV format and writes it to the
      * specified output file.
      *
      * @param data
      *   The transformed data to be converted to CSV.
      * @param output
      *   The file path where the CSV data will be written.
      */
    def toCsv(data: List[Map[String, Any]], output: String): Unit

  trait Export2Json:
    /** Converts the given ujson.Value data to a JSON string and writes it to
      * the specified output.
      *
      * @param data
      *   The ujson.Value data to be converted to JSON.
      * @param output
      *   The file path or output destination where the JSON string will be
      *   written.
      */
    def toJson(data: ujson.Value, output: String): Unit

  object DataExporter extends Export2Csv, Export2Json:
    def ensureFileCreation(output: String) =
      val cwd = os.pwd
      val outputPath = cwd / "output"
      if !os.exists(outputPath) then os.makeDir(outputPath)
      val filePath = outputPath / output
      if os.exists(filePath) then os.remove(filePath)
      filePath

    def toCsv(data: ujson.Value, output: String): Unit =
      val filePath = this.ensureFileCreation(output).toString()
      val file = new File(filePath)
      val writer = CSVWriter.open(file)
      val header: List[String] = flattenMap(data.arr(0).obj.toMap).keys.toList
      writer.writeRow(header)
      val defaultValue = ""
      for value <- data.arr do
        val dirtyRow = flattenMap(value.obj.toMap)
        val row = header
          .map { key => key -> dirtyRow.getOrElse(key, defaultValue) }
          .map((elem) => elem._2)
        writer.writeRow(row)

    def toCsv(data: List[Map[String, Any]], output: String): Unit =
      val filePath = this.ensureFileCreation(output).toString()
      val file = new File(filePath)
      val writer = CSVWriter.open(file)
      if data.nonEmpty then
        val header: List[String] = data.head.keys.toList
        writer.writeRow(header)
        for row <- data do
          writer.writeRow(header.map(key => row.getOrElse(key, "").toString))
      writer.close()

    def toJson(data: ujson.Value, output: String): Unit =
      val filePath = this.ensureFileCreation(output).toString()
      os.write.over(os.Path(filePath), data.render())

    def flattenMap(
        map: Map[String, ujson.Value],
        parentKey: String = ""
    ): Map[String, ujson.Value] =
      map.flatMap {
        case (key, value: Map[_, _]) =>
          flattenMap(
            value.asInstanceOf[Map[String, ujson.Value]],
            parentKey + key + "."
          )
        case (key, value) => Map(parentKey + key -> value)
      }

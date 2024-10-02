val scala3Version = "3.5.0"

lazy val root = project
  .in(file("."))
  .settings(
    name := "Scala 3 Project Template",
    version := "0.1.0-SNAPSHOT",

    scalaVersion := scala3Version,

    libraryDependencies += "org.scalameta" %% "munit" % "1.0.0" % Test,
    libraryDependencies += "org.scala-lang" %% "toolkit" % "0.1.7",
    libraryDependencies += "com.github.tototoshi" %% "scala-csv" % "2.0.0",
    
    //https://index.scala-lang.org/alexarchambault/plotly-scala (Instruções do que colocar aqui no build.sbt não funcionaram)
    //https://github.com/alexarchambault/plotly-scala
    //> https://search.maven.org/artifact/org.plotly-scala/plotly-render_2.13/0.8.5/jar?eh= (Instruções funcionaram)
    libraryDependencies += "org.plotly-scala" % "plotly-render_2.13" % "0.8.5"
  )

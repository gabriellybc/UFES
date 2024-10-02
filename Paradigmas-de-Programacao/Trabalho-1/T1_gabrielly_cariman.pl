/*
 * Fonte de dados para informações das cidades do DBpedia usando SPARQL.
 */
:- data_source(
    dbpedia_cities,
    sparql("PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>
            PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
            PREFIX dbo: <http://dbpedia.org/ontology/>
            PREFIX geo: <http://www.w3.org/2003/01/geo/wgs84_pos#>

            select distinct ?city ?name ?country ?population ?area ?latitude ?longitude
            where {
                ?city a dbo:City;
                    rdfs:label ?name;
                    dbo:country ?country;
                    dbo:populationTotal ?population;
                    dbo:areaTotal ?area;
                    geo:lat ?latitude;
                    geo:long ?longitude.
                FILTER (lang(?name) = 'en')
            }",
            [ endpoint('https://dbpedia.org/sparql')])  ).

/*
 * Verifica se uma substring está presente em uma string.
 */
substring(String, Substring) :-
    sub_string(String, _, _, _, Substring).

/*
 * Associa as colunas de dados das cidades com variáveis Prolog.
 */
city_data(Name, Country, Population, Area, Latitude, Longitude) :-
    dbpedia_cities{name:Name, country:Country, population:Population, area:Area, latitude:Latitude, longitude:Longitude}.

/*
 * Encontra a cidade com a maior população e retorna o nome e a população.
 */
city_with_max_population(Population, Name) :-
    city_data(Name, _, Population, _, _, _),
    not((city_data(_, _, OtherPopulation, _, _, _), OtherPopulation > Population)).

/*
 * Encontra a cidade com a menor população e retorna o nome e a população.
 */
city_with_min_population(Population, Name) :-
    city_data(Name, _, Population, _, _, _),
    not((city_data(_, _, OtherPopulation, _, _, _), OtherPopulation < Population)).

/*
 * Encontra a cidade com a maior área e retorna o nome e a área.
 */
city_with_max_area(Area, Name) :-
    city_data(Name, _, _, Area, _, _),
    not((city_data(_, _, _, OtherArea, _, _), OtherArea > Area)).

/*
 * Encontra a cidade com a menor área e retorna o nome e a área.
 */
city_with_min_area(Area, Name) :-
    city_data(Name, _, _, Area, _, _),
    not((city_data(_, _, _, OtherArea, _, _), OtherArea < Area)).

/*
 * Obtém as coordenadas geográficas de uma cidade.
 */
city_coordinates(Name, Latitude, Longitude) :-
    city_data(Name, _, _, _, Latitude, Longitude).

/*
 * Conta o número de cidades com população acima de um milhão.
 */
cities_population_above_one_million(Count) :-
    aggregate_all(count, (city_data(_, _, Population, _, _, _), Population > 1000000), Count).

/*
 * Calcula a densidade populacional de uma cidade e retorna o resultado.
 */
city_density(Density, Name) :-
    city_data(Name, _, Population, Area, _, _),
    Population > 0, % Evita divisão por zero
    Area > 0,
    Density is Population / Area.

/*
 * Obtém a lista de países que possuem cidades na base de dados.
 */
countries_with_cities(Countries) :-
    findall(Country, city_data(_, Country, _, _, _, _), Countries).

/*
 * Encontra cidades cujo nome contém uma substring específica.
 */
cities_with_substring(Substr, Name) :-
    city_data(Name, _, _, _, _, _),
    substring(Name, Substr).

/*
 * Lista as cidades ordenadas por população em ordem decrescente.
 */
cities_ordered_by_population_descending(Names) :-
    findall([Name, Population], city_data(Name, _, Population, _, _, _), Data),
    sort(2, @>=, Data, Sorted),
    maplist([X,Y]>>(nth0(0,X,Y)), Sorted, Names).

/*
 * Conta o número total de cidades na base de dados.
 */
total_cities_count(Total) :-
    aggregate_all(count, city_data(_, _, _, _, _, _), Total).

/*
 * Verifica se uma cidade específica está na base de dados.
 */
city_exists(Name) :-
    city_data(Name, _, _, _, _, _).

/*
 * Visualização de dados em gráfico de população das cidades.
 */
:- use_rendering(c3).
city_population_chart(Chart) :-
    findall([Name, Population], city_data(Name, _, Population, _, _, _), Data),
    Chart = c3{data:_{x: 'name', rows: [['name', 'population']|Data]}}.


/** <examples>
?- city_data(Name, Country, Population, Area, Latitude, Longitude).
?- city_data("Caacupé", 'http://dbpedia.org/resource/Paraguay', 56864, 145000000.0, -25.38611030578613, -57.14083480834961).
?- city_with_max_population(Population, Name).
?- city_with_max_population(32054159, "Chongqing").
?- city_with_min_population(0, "Snihurivka").
?- city_with_max_area(Area, Name).
?- city_with_max_area(635100000000.0, "Cornélio Procópio").
?- city_with_min_area(Area, Name).
?- city_with_min_area(25899.88110336, "Clayton, Idaho").
?- city_coordinates(Name, Latitude, Longitude).
?- city_coordinates("Caacupé", -25.38611030578613, -57.14083480834961).
?- cities_population_above_one_million(Count).
?- cities_population_above_one_million(459).
?- city_density(Density, Name).
?- city_density(0.0003921655172413793, "Caacupé").
?- countries_with_cities(Countries).
?- countries_with_cities(['http://dbpedia.org/resource/Paraguay'])..
?- cities_with_substring(Substr, Name).
?- cities_with_substring("Floria", "Florianópolis").
?- cities_ordered_by_population_descending(Names).
?- cities_ordered_by_population_descending(["Florianópolis"]).
?- total_cities_count(Total).
?- total_cities_count(10000).
?- city_exists(Name).
?- city_exists("Caacupé").
*/

/**
 * Esse programa recebe o nome do arquivo em .csv contendo a lista de partidos, a lista de candidatos e
 * recebe uma data de referência.
 * A lista de partido deve ter o seguinte cabeçalho: numero_partido,votos_legenda,nome_partido,sigla_partido
 * A lista de candidatos deve ter o seguinte cabeçalho: numero,votos_nominais,situacao,nome,nome_urna,sexo,data_nasc,destino_voto,numero_partido
 * A data deve ter o formato dd/MM/yyyy e deve ser uma data válida
 * 
 * Com esses dados, imprime 11 relatórios ordenados com listas de teor importante, estes são:
 * 1. Número de vagas (= número de eleitos);
 * 2. Candidatos eleitos (nome completo e na urna), indicado partido e número de votos nominais;
 * 3. Candidatos mais votados dentro do número de vagas;
 * 4. Candidatos não eleitos e que seriam eleitos se a votação fosse majoritária;
 * 5. Candidatos eleitos no sistema proporcional vigente, e que não seriam eleitos se a votação fosse
 * majoritária, isto é, pelo número de votos apenas que um candidato recebe diretamente;
 * 6. Votos totalizados por partido e número de candidatos eleitos;
 * 7. Votos de legenda (com a porcentagem destes votos frente ao total de votos no partido);
 * 8. Primeiro e último colocados de cada partido (com nome da urna, número do candidato e total de votos
 * nominais). Partidos que não possuírem candidatos com um número positivo de votos válidos devem
 * ser ignorados;
 * 9. Distribuição de eleitos por faixa etária, considerando a idade do candidato no dia da eleição;
 * 10. Distribuição de eleitos por sexo;
 * 11. Total de votos, total de votos nominais e total de votos de legenda
 * 
 * @author Dayane Silva Erlacher Castro
 * @author Gabrielly Barcelos Cariman
 */

public class Main {
    public static void main(String[] args) {
        Leitura.run(args);
    }
}
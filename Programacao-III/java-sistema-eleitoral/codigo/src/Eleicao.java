import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Locale;
import java.util.Objects;
import java.util.zip.DataFormatException;

public class Eleicao {
  private static List<Partido> partidos;
  private static List<Candidato> todosCandidatos;
  private static List<Candidato> candidatosEleitos;
  private static int eleitosSexoFeminino;
  private static LocalDate dataAtual;

  static {
    eleitosSexoFeminino = 0;
    partidos = new ArrayList<Partido>();
    todosCandidatos = new ArrayList<Candidato>();
    candidatosEleitos = new ArrayList<Candidato>();
  }

  /**
	 * Adiciona 1 no quantitativo de eleitos do sexo feminino
	 */
  public static void setNovaCandidata() {
    eleitosSexoFeminino++;
  }

  /**
	 * Retorna o quantitativo de eleitos do sexo feminino  
	 * @return int 
	 */
  public static int getEleitosSexoFeminino() {
    return eleitosSexoFeminino;
  }

  /**
	 * Retorna quantitativo de eleitos do sexo masculino
	 * @return int quantitativo de eleitos do sexo masculino 
	 */
  public static int getEleitosSexoMasculino() {
    return (candidatosEleitos.size() - eleitosSexoFeminino);
  }

  /**
	 * Converte a data para formato LocalDate e guarda na referência
	 * @param String data de referência
   * @throws FormatoIncorretoDataArgumentoException
   * @throws DataFormatException
	 */
  public static void setDataAtual(String data) throws FormatoIncorretoDataArgumentoException, DataFormatException {
    // dd/MM/yyyy = 10
    if (data.length() != 10) {
        throw new FormatoIncorretoDataArgumentoException("O terceiro parâmetro esperado é uma data no formato dd/MM/yyyy.");
    }
    String[] dataDesmebrada = data.split("/");
    if (Integer. parseInt(dataDesmebrada[0]) > 31 || Integer. parseInt(dataDesmebrada[1]) > 13){
        throw new DataFormatException("Data inválida. Campo dia maior que 31 ou campo mês maior que 12.");
    }
    DateTimeFormatter formatter = DateTimeFormatter.ofPattern("d/MM/yyyy");
    dataAtual = LocalDate.parse(data, formatter);
  }

  /**
   * Retorna a data de referência
   * @return LocalDate data de referência
   */
  public static LocalDate getDataAtual() {
    return dataAtual;
  }

  /**
	 * Salva o número de candidatos eleitos por Partido
   */
  public static void setNumeroCandidatosEleitos() {
    for (Candidato candidato : candidatosEleitos) {
      candidato.getPartido().setNumeroCandidatosEleitos();
    }
  }

  /**
   * Define como deve ser impresso o nome "voto"
   * @param voto número de referência
   * @return "voto" para singular e "votos" para plural
   */
  public static String getPalavraCorretaVoto(int voto) {
    if (voto <= 1)
      return "voto";
    return "votos";
  }

  /**
   * Define como deve ser impresso o nome "candidato eleito"
   * @param candidato número de referência
   * @return "candidato eleito" para singular e "candidatos eleitos" para plural
   */
  public static String getPalavraCorretaCandidatoEleito(int candidato) {
    if (candidato <= 1)
      return "candidato eleito";
    return "candidatos eleitos";
  }

  /**
   * Define como deve ser impresso o nome "nominal"
   * @param votos número de referência
   * @return "nominal" para singular e "nominais" para plural
   */
  public static String getPalavraCorretaNominal(int votos) {
    if (votos <= 1)
      return "nominal";
    return "nominais";
  }

  /**
   * Busca pelo número do partido o objeto Partido
   * @param numeroPartido número do partido
   * @return Partido Object
   */
  public static Partido getPartidoPorNumero(int numeroPartido) {
    for (Partido partido : partidos)
      if (partido.getNumeroPartido() == numeroPartido)
        return partido;
    return null;
  }

  /**
   * Adiciona partido a lista de partidos
   * @param partido Partido
   */
  public static void addPartido(Partido partido) {
    partidos.add(partido);
  }

  /**
   * Adiciona candidato a lista de candidatos
   * @param candidato Candidato
   */
  public static void addNovoCandidato(Candidato candidato) {
    todosCandidatos.add(candidato);
  }

  /**
   * Adiciona candidato a lista de candidatos eleitos
   * @param candidatoEleito Candidato
   */
  public static void addNovoCandidatoEleito(Candidato candidatoEleito) {
    candidatosEleitos.add(candidatoEleito);
  }

  /**
   * Método orquestra na ordem correta a execução dos métodos que geram os relatórios
   */
  public static void gerarRelatorio() {
    // Arrumando listas para agilizar na geração do relatório
    Collections.sort(candidatosEleitos, new ComparadorCandidatoPorVotosNominais());
    Collections.sort(todosCandidatos, new ComparadorCandidatoPorVotosNominais());
    Locale localeBR = new Locale("pt","BR");
    gerarRelatorio01();
    gerarRelatorio02();
    gerarRelatorio03();
    gerarRelatorio04();
    gerarRelatorio05();
    gerarRelatorio06();
    gerarRelatorio07(localeBR);
    gerarRelatorio08();
    gerarRelatorio09(localeBR);
    gerarRelatorio10(localeBR);
    gerarRelatorio11(localeBR);
  }

  /**
   * Gerar Relatório 1
   * Número de vagas (= número de eleitos)
   */
  public static void gerarRelatorio01() {
    System.out.printf("Número de vagas: %d\n", candidatosEleitos.size());
    System.out.println();
  }

  /**
   * Gerar Relatório 2
   * Candidatos eleitos (nome completo e na urna), indicado partido e número de votos nominais;
   */
  public static void gerarRelatorio02() {
    int i = 1;
    System.out.printf("Vereadores eleitos:\n");
    for (Candidato candidato : candidatosEleitos) {
      System.out.printf("%d - %s / %s (%s, %d %s)\n", i, candidato.getNome(), candidato.getNomeUrna(),
          candidato.getPartido().getSiglaPartido(), candidato.getVotosNominais(),
          getPalavraCorretaVoto(candidato.getVotosNominais()));
      i++;
    }
    System.out.println();
  }

  /**
   * Gerar Relatório 3
   * Candidatos mais votados dentro do número de vagas
   */
  public static void gerarRelatorio03() {
    System.out.println("Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):");
    int i = 1;
    for (Candidato candidato : todosCandidatos) {
      System.out.printf("%d - %s / %s (%s, %d %s)\n", i, candidato.getNome(), candidato.getNomeUrna(),
          candidato.getPartido().getSiglaPartido(), candidato.getVotosNominais(),
          getPalavraCorretaVoto(candidato.getVotosNominais()));
      if (i == candidatosEleitos.size())
        break;
      i++;
    }
    System.out.println();
  }

  /**
   * Gerar Relatório 4
   * Candidatos não eleitos e que seriam eleitos se a votação fosse majoritária
   */
  public static void gerarRelatorio04() {
    System.out.println("Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:");
    System.out.println("(com sua posição no ranking de mais votados)");
    int i = 1;
    for (Candidato candidato : todosCandidatos) {
      if (!candidato.getSituacao().equals("Eleito")) {
        System.out.printf("%d - %s / %s (%s, %d %s)\n", i, candidato.getNome(), candidato.getNomeUrna(),
            candidato.getPartido().getSiglaPartido(), candidato.getVotosNominais(),
            getPalavraCorretaVoto(candidato.getVotosNominais()));
      }
      if (i == candidatosEleitos.size())
        break;
      i++;
    }
    System.out.println();
  }

  /**
   * Gerar Relatório 5
   * Candidatos eleitos no sistema proporcional vigente, e que não seriam eleitos se a votação fosse
   * majoritária, isto é, pelo número de votos apenas que um candidato recebe diretamente;
   */
  public static void gerarRelatorio05() {
    System.out.println("Eleitos, que se beneficiaram do sistema proporcional:");
    System.out.println("(com sua posição no ranking de mais votados)");
    int i = 1;
    int qntEleitos = 0;
    for (Candidato candidato : todosCandidatos) {
      if(candidato.getSituacao().equals("Eleito")) {
        qntEleitos++;
        if (i > candidatosEleitos.size()){
          System.out.printf("%d - %s / %s (%s, %d %s)\n", i, candidato.getNome(), candidato.getNomeUrna(), candidato.getPartido().getSiglaPartido(), candidato.getVotosNominais(),
            getPalavraCorretaVoto(candidato.getVotosNominais()));
            if(qntEleitos == candidatosEleitos.size())
              break;
        }
      }
      i++;
    }
    System.out.println();
  }

  /**
   * Gerar Relatório 6
   * Votos totalizados por partido e número de candidatos eleitos
   */
  public static void gerarRelatorio06() {
    setNumeroCandidatosEleitos();
    Collections.sort(partidos, new ComparadorPartidoPorTotalVotos());
    int i = 1, soma=0;
    System.out.println("Votação dos partidos e número de candidatos eleitos:");
    for (Partido partido : partidos) {
      soma = partido.getVotosLegenda() + partido.getVotosNominais();
      System.out.printf("%d - %s - %d, %d %s (%d %s e %d de legenda), %d %s\n",
          i, partido.getSiglaPartido(), partido.getNumeroPartido(),
          soma, getPalavraCorretaVoto(soma), partido.getVotosNominais(), getPalavraCorretaNominal(partido.getVotosNominais()),
          partido.getVotosLegenda(), partido.getNumeroCandidatosEleitos(), getPalavraCorretaCandidatoEleito(partido.getNumeroCandidatosEleitos()));
      i++;
    }
    System.out.println();
  }

  /**
   * Gerar Relatório 7
   * Votos de legenda (com a porcentagem destes votos frente ao total de votos no
   * partido)
   * @param localeBR converter número para formato brasileiro (,)
   */
  public static void gerarRelatorio07(Locale localeBR) {
    Collections.sort(partidos, new ComparadorPartidoPorVotosLegenda());
    System.out.println("Votação dos partidos (apenas votos de legenda):");
    int i = 1, total;
    for (Partido partido : partidos) {
      total = (partido.getVotosLegenda() + partido.getVotosNominais());
      if (total > 0) {
        System.out.printf(localeBR, "%d - %s - %d, %d %s de legenda (%.2f%% do total do partido)\n", i,
            partido.getSiglaPartido(), partido.getNumeroPartido(), partido.getVotosLegenda(), getPalavraCorretaVoto(partido.getVotosLegenda()),
            (double) partido.getVotosLegenda() * 100 / total);
      } else {
        System.out.printf("%d - %s - %d, %d voto de legenda (proporção não calculada, 0 voto no partido)\n", i,
            partido.getSiglaPartido(), partido.getNumeroPartido(), partido.getVotosLegenda());
      }
      i++;
    }
    System.out.println();
  }

  /**
   * Gerar Relatório 8
   * Primeiro e último colocados de cada partido (com nome da urna, número do
   * candidato e total de votos
   * nominais). Partidos que não possuírem candidatos com um número positivo de
   * votos válidos devem
   * ser ignorados
   */
  public static void gerarRelatorio08() {
    Collections.sort(partidos, new ComparadorPartidoPorTotalVotosNominaisCandidatoMaisVotado());
    System.out.println("Primeiro e último colocados de cada partido:");
    int i = 1;
    for (Partido partido : partidos) {
      if (!Objects.isNull(partido.getPrimeiroColocado())) {
        Candidato primeiro = partido.getPrimeiroColocado();
        Candidato ultimo = partido.getUltimoColocado();

        System.out.printf("%d - %s - %d, %s (%d, %d %s) / %s (%d, %d %s)\n", i, partido.getSiglaPartido(),
            partido.getNumeroPartido(), primeiro.getNomeUrna(), primeiro.getNumeroUrna(), primeiro.getVotosNominais(), getPalavraCorretaVoto(primeiro.getVotosNominais()),
            ultimo.getNomeUrna(), ultimo.getNumeroUrna(), ultimo.getVotosNominais(), getPalavraCorretaVoto(ultimo.getVotosNominais()));
      }
      i++;
    }
    System.out.println();
  }

  /**
   * Gerar Relatório 9
   * Distribuição de eleitos por faixa etária, considerando a idade do candidato
   * no dia da eleição
   * @param localeBR converter número para formato brasileiro (,)
   */
  public static void gerarRelatorio09(Locale localeBR) {
    /*
     * [0] Idade < 30
     * [1] 30 <= Idade < 40
     * [2] 40 <= Idade < 50
     * [3] 50 <= Idade < 60
     * [4] 60 <= Idade
     */
    int[] faixaEtaria = new int[5];
    for (Candidato candidato : candidatosEleitos) {
      int idade = candidato.calculaIdade();
      if (idade < 30)
        faixaEtaria[0]++;
      else if (30 <= idade && idade < 40)
        faixaEtaria[1]++;
      else if (40 <= idade && idade < 50)
        faixaEtaria[2]++;
      else if (50 <= idade && idade < 60)
        faixaEtaria[3]++;
      else
        faixaEtaria[4]++;
    }
    System.out.println("Eleitos, por faixa etária (na datada eleição):");
    int total = faixaEtaria[0] + faixaEtaria[1] + faixaEtaria[2] + faixaEtaria[3] + faixaEtaria[4];
    if (total == 0) {
      System.out.printf(localeBR, "      Idade < 30: %d (0.00%%)\n", faixaEtaria[0]);
      System.out.printf(localeBR, "30 <= Idade < 40: %d (0.00%%)\n", faixaEtaria[1]);
      System.out.printf(localeBR, "40 <= Idade < 50: %d (0.00%%)\n", faixaEtaria[2]);
      System.out.printf(localeBR, "50 <= Idade < 60: %d (0.00%%)\n", faixaEtaria[3]);
      System.out.printf(localeBR, "60 <= Idade     : %d (0.00%%)\n", faixaEtaria[4]);
    } else {
      System.out.printf(localeBR, "      Idade < 30: %d (%.2f%%)\n", faixaEtaria[0], (double) faixaEtaria[0] * 100 / total);
      System.out.printf(localeBR, "30 <= Idade < 40: %d (%.2f%%)\n", faixaEtaria[1], (double) faixaEtaria[1] * 100 / total);
      System.out.printf(localeBR, "40 <= Idade < 50: %d (%.2f%%)\n", faixaEtaria[2], (double) faixaEtaria[2] * 100 / total);
      System.out.printf(localeBR, "50 <= Idade < 60: %d (%.2f%%)\n", faixaEtaria[3], (double) faixaEtaria[3] * 100 / total);
      System.out.printf(localeBR, "60 <= Idade     : %d (%.2f%%)\n", faixaEtaria[4], (double) faixaEtaria[4] * 100 / total);
    }
    System.out.println();
  }

  /**
   * Gerar Relatório 10
   * Distribuição de eleitos por sexo
   * @param localeBR converter número para formato brasileiro (,)
   */
  public static void gerarRelatorio10(Locale localeBR) {
    System.out.println("Eleitos, por sexo:");
    int total = (getEleitosSexoFeminino() + getEleitosSexoMasculino());
    if (total == 0) {
      System.out.printf(localeBR,"Feminino: %d (0.00%%)\n", getEleitosSexoFeminino());
      System.out.printf(localeBR,"Masculino: %d (0.00%%)\n", getEleitosSexoMasculino());
    } else {
      System.out.printf(localeBR,"Feminino: %d (%.2f%%)\n", getEleitosSexoFeminino(),
        (double) getEleitosSexoFeminino() * 100 / total);
    System.out.printf(localeBR,"Masculino: %d (%.2f%%)\n", getEleitosSexoMasculino(),
        (double) getEleitosSexoMasculino() * 100 / total);
    }
    System.out.println();
  }

  /**
   * Gerar Relatório 11
   * Total de votos, total de votos nominais e total de votos de legenda
   * @param localeBR converter número para formato brasileiro (,)
   */
  public static void gerarRelatorio11(Locale localeBR) {
    int totalvotosLegenda = 0, totalvotosNominais = 0;
    for (Partido partido : partidos) {
      totalvotosLegenda = totalvotosLegenda + partido.getVotosLegenda();
      totalvotosNominais = totalvotosNominais + partido.getVotosNominais();
    }
    System.out.printf("Total de votos válidos:    %d \n", totalvotosLegenda + totalvotosNominais);
    int total = (totalvotosLegenda + totalvotosNominais);
    if (total == 0) {
      System.out.printf(localeBR, "Total de votos nominais:   %d (0.00%%)\n", totalvotosNominais);
      System.out.printf(localeBR, "Total de votos de legenda: %d (0.00%%)\n", totalvotosLegenda);
    } else {
      System.out.printf(localeBR, "Total de votos nominais:   %d (%.2f%%)\n", totalvotosNominais,
        (double) totalvotosNominais * 100 / total);
    System.out.printf(localeBR, "Total de votos de legenda: %d (%.2f%%)\n", totalvotosLegenda,
        (double) totalvotosLegenda * 100 / total);
    }
  }
}
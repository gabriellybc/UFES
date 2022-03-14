import java.util.Comparator;
import java.util.Objects;

public class Partido {
  private int numeroPartido;
  private int votosLegenda;
  private String nomePartido;
  private String siglaPartido;
  private int votosNominais;
  private Candidato primeiroColocado;
  private Candidato ultimoColocado;
  private int numeroCandidatosEleitos;

  public Partido(int numeroPartido, int votosLegenda, String nomePartido, String siglaPartido) {
    this.numeroPartido = numeroPartido;
    this.votosLegenda = votosLegenda;
    this.nomePartido = nomePartido;
    this.siglaPartido = siglaPartido;
    this.votosNominais = 0;
    this.numeroCandidatosEleitos = 0;
  }

  /**
	 * Retorna o número do partido na urna 
	 * @return int número do partido na urna 
	 */
  public int getNumeroPartido() {
    return numeroPartido;
  }

  /**
	 * Altera o número do partido na urna 
	 * @param numeroPartido int número do partido na urna 
	 */
  public void setNumeroPartido(int numeroPartido) {
    this.numeroPartido = numeroPartido;
  }

  /**
	 * Retorna a quantidade de votos de legenda
	 * @return int quantidade de votos de legenda
	 */
  public int getVotosLegenda() {
    return votosLegenda;
  }

  /**
	 * Altera a quantidade de votos de legenda
	 * @param votosLegenda int quantidade de votos de legenda
	 */
  public void setVotosLegenda(int votosLegenda) {
    this.votosLegenda = votosLegenda;
  }

  /**
	 * Retorna o nome do partido 
	 * @return String nome do partido 
	 */
  public String getNomePartido() {
    return nomePartido;
  }

  /**
	 * Altera o nome do partido 
	 * @param nomePartido String nome do partido 
	 */
  public void setNomePartido(String nomePartido) {
    this.nomePartido = nomePartido;
  }

  /**
	 * Retorna a sigla do partido 
	 * @return String sigla do partido 
	 */
  public String getSiglaPartido() {
    return siglaPartido;
  }

  /**
	 * Altera a sigla do partido 
	 * @param siglaPartido String sigla do partido 
	 */
  public void setSiglaPartido(String siglaPartido) {
    this.siglaPartido = siglaPartido;
  }
  
  /**
	 * Retorna a quantidade de votos nominais 
	 * @return int quantidade de votos nominais 
	 */
  public int getVotosNominais() {
    return votosNominais;
  }
  
  /**
	 * Adiciona valor ao quantitativo de votos nominais 
	 * @param votosNominais int quantidade de votos nominais 
	 */
  public void somaVotosNominais(int votosNominais) {
    this.votosNominais = this.votosNominais + votosNominais;
  }
  
  /**
	 * Retorna o Candidato com maior número de votos dentro do partido 
	 * @return Candidato com maior número de votos dentro do partido 
	 */
  public Candidato getPrimeiroColocado() {
    return primeiroColocado;
  }
  
  /**
	 * Altera o Candidato com maior número de votos dentro do partido 
	 * @param primeiroColocado Candidato Candidato com maior número de votos dentro do partido 
	 */
  public void setPrimeiroColocado(Candidato primeiroColocado) {
    this.primeiroColocado = primeiroColocado;
  }
  
  /**
	 * Retorna o Candidato com menor número de votos dentro do partido  
	 * @return Candidato com menor número de votos dentro do partido  
	 */
  public Candidato getUltimoColocado() {
    return ultimoColocado;
  }

  /**
	 * Altera o Candidato com menor número de votos dentro do partido  
	 * @param ultimoColocado Candidato Candidato com menor número de votos dentro do partido  
	 */
  public void setUltimoColocado(Candidato ultimoColocado) {
    this.ultimoColocado = ultimoColocado;
  }
  
  /**
	 * Retorna o número de candidatos do partido eleitos 
	 * @return int número de candidatos do partido eleitos 
	 */
  public int getNumeroCandidatosEleitos() {
    return numeroCandidatosEleitos;
  }

  /**
	 * Adiciona +1 ao número de candidatos do partido eleitos 
	 */
  public void setNumeroCandidatosEleitos() {
    this.numeroCandidatosEleitos = this.numeroCandidatosEleitos + 1;
  }
}

/**
 * Classe que compara partido utilizando como parâmetro o número total de votos
 * que cada possui. O número do partido é considerado critério de desempate.
 */
class ComparadorPartidoPorTotalVotos implements Comparator<Partido> {
  @Override
  public int compare(Partido o1, Partido o2) {
    int totalVotos1 = o1.getVotosLegenda() + o1.getVotosNominais();
    int totalVotos2 = o2.getVotosLegenda() + o2.getVotosNominais();
    int numeroPartido1 = o1.getNumeroPartido();
    int numeroPartido2 = o2.getNumeroPartido();
    if (totalVotos1 < totalVotos2) return 1;
    else if (totalVotos1 > totalVotos2) return -1;
    else {
      if (numeroPartido1 < numeroPartido2) return -1;
      else if (numeroPartido1 > numeroPartido2) return 1;
      else return 0;
    }
  }
}

/**
 * Classe que compara partido utilizando como parâmetro o número de votos de legenda
 * que cada possui. O número de votos nominais é considerando em caso de empate. 
 * O número do partido é considerado critério de desempate final.
 */
class ComparadorPartidoPorVotosLegenda implements Comparator<Partido> {
  @Override
  public int compare(Partido o1, Partido o2) {
    int votosLegenda1 = o1.getVotosLegenda();
    int votosLegenda2 = o2.getVotosLegenda();
    int votosNominais1 = o1.getVotosNominais();
    int votosNominais2 = o2.getVotosNominais();
    int numeroPartido1 = o1.getNumeroPartido();
    int numeroPartido2 = o2.getNumeroPartido();
    if (votosLegenda1 < votosLegenda2) return 1;
    else if (votosLegenda1 > votosLegenda2) return -1;
     else {
      if (votosNominais1 < votosNominais2) return 1;
      else if (votosNominais1 > votosNominais2) return -1;
      else {
        if (numeroPartido1 < numeroPartido2) return -1;
        else if (numeroPartido1 > numeroPartido2) return 1;
        else return 0;
      }
    }
  }
}

/**
 * Classe que compara partido utilizando como parâmetro o número de votos de nominais
 * que cada possui. O número do partido é considerado critério de desempate.
 */
class ComparadorPartidoPorTotalVotosNominaisCandidatoMaisVotado implements Comparator<Partido> {
  @Override
  public int compare(Partido o1, Partido o2) {
    // Tratamento caso partido não tenha colocado válido
    if(Objects.isNull(o1.getPrimeiroColocado())) {
      return 1;
    } else if (Objects.isNull(o2.getPrimeiroColocado())) {
      return -1;
    }
    int totalVotos1 = o1.getPrimeiroColocado().getVotosNominais();
    int totalVotos2 = o2.getPrimeiroColocado().getVotosNominais();
    int numeroPartido1 = o1.getNumeroPartido();
    int numeroPartido2 = o2.getNumeroPartido();
    if (totalVotos1 < totalVotos2) return 1;
    else if (totalVotos1 > totalVotos2) return -1;
    else {
      if (numeroPartido1 < numeroPartido2) return -1;
      else if (numeroPartido1 > numeroPartido2) return 1;
      else return 0;
    }
  }
}
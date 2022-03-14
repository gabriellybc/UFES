import java.time.LocalDate;
import java.util.Comparator;

public class Candidato extends Pessoa {
	private int numeroUrna;
	private int votosNominais;
	private String situacao;
	private String nomeUrna;
	private Partido partido;

	public Candidato(String nome, char sexo, LocalDate dataNascimento, int numeroUrna, int votosNominais,
			String situacao, String nomeUrna, Partido partido) {
		super(nome, sexo, dataNascimento);
		this.numeroUrna = numeroUrna;
		this.votosNominais = votosNominais;
		this.situacao = situacao;
		this.nomeUrna = nomeUrna;
		this.partido = partido;
	}

	public Candidato(String nome, char sexo, String dataNascimento, int numeroUrna, int votosNominais,
			String situacao, String nomeUrna, Partido partido) {
		super(nome, sexo, dataNascimento);
		this.numeroUrna = numeroUrna;
		this.votosNominais = votosNominais;
		this.situacao = situacao;
		this.nomeUrna = nomeUrna;
		this.partido = partido;
	}

	/**
	 * Retorna o número do candidato na urna 
	 * @return int número do candidato na urna 
	 */
	public int getNumeroUrna() {
		return numeroUrna;
	}

	/**
	 * Altera o número do candidato na urna 
	 * @param numeroUrna int número do candidato na urna 
	 */
	public void setNumeroUrna(int numeroUrna) {
		this.numeroUrna = numeroUrna;
	}

	/**
	 * Retorna a quatidade de votos nominais que o candidato possui 
	 * @return int quatidade de votos nominais que o candidato possui 
	 */
	public int getVotosNominais() {
		return votosNominais;
	}

	/**
	 * Altera a quatidade de votos nominais que o candidato possui 
	 * @param votosNominais int quatidade de votos nominais que o candidato possui 
	 */
	public void setVotosNominais(int votosNominais) {
		this.votosNominais = votosNominais;
	}

	/**
	 * Retorna a situação do candidato em relação a Eleição 
	 * @return String situação do candidato em relação a Eleição: Eleito, 
	 * Não Eleito ou Suplente 
	 */
	public String getSituacao() {
		return situacao;
	}

	/**
	 * Altera a situação do candidato em relação a Eleição 
	 * @param situacao String situação do candidato em relação a Eleição: Eleito, 
	 * Não Eleito ou Suplente 
	 */
	public void setSituacao(String situacao) {
		this.situacao = situacao;
	}

	/**
	 * Retorna o nome do candidato na urna 
	 * @return String nome do candidato na urna 
	 */
	public String getNomeUrna() {
		return nomeUrna;
	}

	/**
	 * Altera o nome do candidato na urna 
	 * @param nomeUrna String nome do candidato na urna 
	 */
	public void setNomeUrna(String nomeUrna) {
		this.nomeUrna = nomeUrna;
	}

	/**
	 * Retorna o objeto partido do candidato 
	 * @return Object Partido  
	 */
	public Partido getPartido() {
		return partido;
	}

	/**
	 * Altera o objeto partido do candidato 
	 * @param partido Partido
	 */
	public void setPartido(Partido partido) {
		this.partido = partido;
	}
}


/**
 * Classe que compara candidato utilizando como parâmetro o número de votos nominais
 * que cada possui. A idade é considerada critério de desempate.
 */
class ComparadorCandidatoPorVotosNominais implements Comparator<Candidato> {
	@Override
	public int compare(Candidato o1, Candidato o2) {
		int votosNominais1 = o1.getVotosNominais();
		int votosNominais2 = o2.getVotosNominais();
		if (votosNominais1 < votosNominais2) return 1;
		 else if (votosNominais1 > votosNominais2) return -1;
		 else return o2.comparaIdade(o1);
	}
}
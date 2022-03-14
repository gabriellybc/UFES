import java.time.LocalDate;
import java.time.Period;
import java.time.format.DateTimeFormatter;

public class Pessoa {
  private String nome;
  private char sexo;
  private LocalDate dataNascimento;
  
	public Pessoa(String nome, char sexo, LocalDate dataNascimento) {
		this.nome = nome;
		this.sexo = sexo;
		this.dataNascimento = dataNascimento;
	}

	public Pessoa(String nome, char sexo, String dataNascimento) {
		this.nome = nome;
		this.sexo = sexo;
		DateTimeFormatter formatter = DateTimeFormatter.ofPattern("d/MM/yyyy");
		this.dataNascimento = LocalDate.parse(dataNascimento, formatter);
	}
	
	
	/**
	 * Retorna o nome 
	 * @return String nome 
	 */
	public String getNome() {
		return nome;
	}
	
	/**
	 * Altera o nome 
	 * @param nome String nome 
	 */
	public void setNome(String nome) {
		this.nome = nome;
	}
	
	/**
	 * Retorna o sexo
	 * @return char sexo: F ou M 
	 */
	public char getSexo() {
		return sexo;
	}
	
	/**
	 * Altera o sexo
	 * @param sexo char sexo: F ou M 
	 */
	public void setSexo(char sexo) {
		this.sexo = sexo;
	}
	
	/**
	 * Retorna a data de nascimento 
	 * @return LocalDate data de nascimento 
	 */
	public LocalDate getDataNascimento() {
		return dataNascimento;
	}
	
	/**
	 * Altera a data de nascimento 
	 * @param dataNascimento LocalDate data de nascimento 
	 */
	public void setDataNascimento(LocalDate dataNascimento) {
		this.dataNascimento = dataNascimento;
	}
	
	/**
	 * Altera a data de nascimento 
	 * @param dataNascimento String data de nascimento
	 */
	public void setDataNascimento(String dataNascimento) {
		DateTimeFormatter formatter = DateTimeFormatter.ofPattern("d/MM/yyyy");
		this.dataNascimento = LocalDate.parse(dataNascimento, formatter);
	}
	
	/**
	 * Cálcula a idade da pessoa 
	 * @return int idade da pessoa 
	 * ou 0 caso data de nascimento ou a data de referência sejam nulos
	 */
	public int calculaIdade() {
        if ((dataNascimento != null) && (Eleicao.getDataAtual() != null)) {
            return Period.between(dataNascimento, Eleicao.getDataAtual()).getYears();
        } else {
            return 0;
        }
    }
	/**
	 * Compara idade entre duas pessoas
	 * @param o2 Pessoa para comparar
	 * @return int 
	 * se o2 é mais velho valor é negativo
	 * se o2 é mais novo valor é positivo
	 */
	public int comparaIdade(Pessoa o2) {
		return (this.calculaIdade() - o2.calculaIdade());
	}
}
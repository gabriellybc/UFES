/**
 * Classe para tratar casos em que o formato da data no argumento de entrada
 * esteja fora do especificado
 */
public class FormatoIncorretoDataArgumentoException extends Exception {
    /**
     * Método Exception FormatoIncorretoDataArgumentoException
     * @param message mensagem a ser mostrada no terminal
     */
    public FormatoIncorretoDataArgumentoException(String message) {
        super(message);
    }

}
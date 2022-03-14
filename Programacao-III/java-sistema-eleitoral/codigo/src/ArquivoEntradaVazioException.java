/**
 * Classe para tratar os casos em que o arquivo csv está vazio
 */
public class ArquivoEntradaVazioException extends Exception {
    /**
     * Método Exception ArquivoEntradaVazioException
     * @param message mensagem a ser mostrada no terminal
     */
    public ArquivoEntradaVazioException(String message) {
        super(message);
    }
}

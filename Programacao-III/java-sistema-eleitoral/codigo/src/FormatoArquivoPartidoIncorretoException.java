/**
 * Classe para tratar o formato do cabeçalho do arquivo de entrada com
 * os dados do Partido
 */
public class FormatoArquivoPartidoIncorretoException extends Exception{
    /**
     * Método Exception FormatoArquivoPartidoIncorretoException
     * @param message mensagem a ser mostrada no terminal
     */
    public FormatoArquivoPartidoIncorretoException(String message) {
        super(message);
    }
}

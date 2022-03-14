import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Objects;
import java.util.zip.DataFormatException;

public class Leitura extends Exception {

    /**
     * Esse método recebe os dados da Eleição, armazena nas listas e chama método para gerar relatórios
     * 
     * @param args Array com três posições: primeira contendo o nome do arquivo contendo a lista de partidos, 
     * a lista de candidatos e uma data de referência
     */
    public static void run(String args[]) {
        try {
            lerEntradas(args);
            Eleicao.gerarRelatorio();
        } catch (FormatoIncorretoDataArgumentoException e) {
            e.printStackTrace();
        } catch (DataFormatException e) {
            e.printStackTrace();
        } catch (FormatoArquivoPartidoIncorretoException e) {
            e.printStackTrace();
        } catch (FormatoArquivoCandidatoIncorretoException e) {
            e.printStackTrace();
        } catch (ArquivoEntradaVazioException e) {
            e.printStackTrace();
        } catch(FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    /**
     * Esse método recebe os dados da Eleição e armazena nas listas para posteriormente gerar o relatório
     * 
     * @param args Array com três posições: primeira contendo o nome do arquivo contendo a lista de partidos, 
     * a lista de candidatos e uma data de referência
     * @throws FormatoIncorretoDataArgumentoException
     * @throws DataFormatException
     * @throws FormatoArquivoPartidoIncorretoException
     * @throws FormatoArquivoCandidatoIncorretoException
     * @throws FileNotFoundException
     * @throws IOException
     * @throws ArquivoEntradaVazioException
     */
    public static void lerEntradas(String[] args) throws FormatoIncorretoDataArgumentoException, DataFormatException, FormatoArquivoPartidoIncorretoException, FormatoArquivoCandidatoIncorretoException, IOException, ArquivoEntradaVazioException{
        // Tratamento para entrada de dados com tamanho ou formato diferente do esperado
        if (args.length < 3) {
            throw new IllegalArgumentException("3 parâmetros são esperados.");
        }

        Eleicao.setDataAtual(args[2].trim());
        lerArquivoPartidos(args[1]);
    	lerArquivoCandidatos(args[0]);
    }
    /** 
    * Recebe os dados dos partidos e armazena na lista de partidos da Eleição
    *
    * @param filePath nome do arquivo contendo os dados dos partidos 
    * @throws FormatoArquivoPartidoIncorretoException
    * @throws FileNotFoundException
    * @throws IOException
    */
    private static void lerArquivoPartidos(String filePath) throws FormatoArquivoPartidoIncorretoException, FileNotFoundException, IOException, ArquivoEntradaVazioException {
        String line = "";
        final String delimiter = ",";
        String[] token;
        Partido partido;
        FileReader fileReader = new FileReader(filePath);
        BufferedReader reader = new BufferedReader(fileReader);
        line = reader.readLine(); // titulos
        if (line != null) {
            // Tratamento caso Cabeçalho não seja o esperado
            if(!line.trim().equals("numero_partido,votos_legenda,nome_partido,sigla_partido")) {
                reader.close();
                throw new FormatoArquivoPartidoIncorretoException("Cabeçalho do csv de Partidos não está no formato esperado.");
            }
            while ((line = reader.readLine()) != null) {
                token = line.split(delimiter);
                // São 4 entradas de dados esperadas por linha conforme cabeçalho
                if (token.length == 4) {
                    partido = new Partido(Integer.parseInt(token[0]), Integer.parseInt(token[1]), token[2].trim(), token[3].trim());
                    Eleicao.addPartido(partido);
                }
            }
        } else {
            reader.close();
            throw new ArquivoEntradaVazioException("Arquivo de partidos está vazio.");
        }
        reader.close();
    }

    /** 
    * Recebe os dados dos candidatos e armazena diversos dados importante separadamente
    * para posteriormente, na geração dos relatórios, serem utilizados
    *
    * @param filePath nome do arquivo contendo os dados dos candidatos 
    * @throws FormatoArquivoCandidatoIncorretoException
    * @throws FileNotFoundException
    * @throws IOException
    */
    private static void lerArquivoCandidatos(String filePath) throws FormatoArquivoCandidatoIncorretoException, FileNotFoundException, IOException, ArquivoEntradaVazioException  {
        String line = "";
        final String delimiter = ",";
        String[] token;
        Partido partido;
        Candidato candidato;
        FileReader fileReader = new FileReader(filePath);
        BufferedReader reader = new BufferedReader(fileReader);
        line = reader.readLine(); // titulos
        if(line != null) {
            if(!line.trim().equals("numero,votos_nominais,situacao,nome,nome_urna,sexo,data_nasc,destino_voto,numero_partido")) {
                reader.close();
                throw new FormatoArquivoCandidatoIncorretoException("Cabeçalho do csv de Candidato não está no formato esperado.");
            }
            while ((line = reader.readLine()) != null) {
                token = line.split(delimiter);
                // São 9 entradas de dados esperadas por linha conforme cabeçalho
                if(token.length == 9) {
                    // Busca o partido do candidato na lista de partidos utilizando o número do partido
                    partido = Eleicao.getPartidoPorNumero(Integer.parseInt(token[8]));
                    // Adiciona se partido e candidato são válidos
                if (partido != null && token[7].equals("Válido")) {
                    
                    /*Verificação se a data está formatada corretamente, caso não o candidato é descartado
                    Data dd/MM/yyyy = 10*/
                    token[6] = token[6].trim();
                    String[] dataDesmebrada = token[6].split("/");
                    if (token[6].length() == 10 && 
                    Integer. parseInt(dataDesmebrada[0]) > 0 && Integer. parseInt(dataDesmebrada[0]) < 32 && //dia
                    Integer. parseInt(dataDesmebrada[1]) > 0 && Integer. parseInt(dataDesmebrada[1]) < 13){ //mes

                        partido.somaVotosNominais(Integer.parseInt(token[1]));
                        candidato = new Candidato(token[3].trim(), token[5].charAt(0), token[6],
                                Integer.parseInt(token[0]), Integer.parseInt(token[1]),
                                token[2].trim(), token[4].trim(), partido);
                        // Adiciona candidato a lista de todos os candidatos
                        Eleicao.addNovoCandidato(candidato);
        
                        // DEFININDO CANDIDATO MAIS VOTATO E MENOS VOTADO
                        if (Objects.isNull(partido.getPrimeiroColocado())) {
                            partido.setPrimeiroColocado(candidato);
                            partido.setUltimoColocado(candidato);
                            // Caso exista um candidato com mais votos OU
                            // se os dois tiverem a mesma quantidade de votos e o outro candidato é mais velho
                        } else if (partido.getPrimeiroColocado().getVotosNominais() < candidato
                                .getVotosNominais() ||
                                partido.getPrimeiroColocado().getVotosNominais() == candidato.getVotosNominais()
                                        && partido.getPrimeiroColocado().comparaIdade(candidato) < 0) {
                            partido.setPrimeiroColocado(candidato);
                            // Caso exista um candidato com menos votos OU
                            // se os dois tiverem a mesma quantidade de votos e o outro candidato é mais velho
                        } else if (partido.getUltimoColocado().getVotosNominais() > candidato.getVotosNominais()
                                ||
                                partido.getUltimoColocado().getVotosNominais() == candidato.getVotosNominais()
                                        && partido.getUltimoColocado().comparaIdade(candidato) > 0) {
                            partido.setUltimoColocado(candidato);
                        }
                        // Adiciona candidato a lista de candidatos eleitos
                        if (candidato.getSituacao().equals("Eleito")) {
                            Eleicao.addNovoCandidatoEleito(candidato);
                            // Contando total de eleitos do sexo feminino
                            if (candidato.getSexo() == 'F') {
                                Eleicao.setNovaCandidata();
                            }
                        }
                    }
                }
            }
        }
        reader.close();
        } else {
            reader.close();
            throw new ArquivoEntradaVazioException("Arquivo de candidatos está vazio.");
        }
    }
}
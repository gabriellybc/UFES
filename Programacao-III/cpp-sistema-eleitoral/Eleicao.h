#ifndef ELEICAO_H_
#define ELEICAO_H_

#include "Partido.h"
class Eleicao
{
    vector<Partido *> partidos;
    vector<Candidato *> todosCandidatos;
    vector<Candidato *> candidatosEleitos;
    time_t dataAtual;

public:
    //Construtor padrão
    Eleicao();

    /**
     * @brief Retorna a data de referência
     * 
     * @return time_t data de referência
     */
    const time_t &getDataAtual() const;

    /**
     * @brief Retorna Partido object
     * 
     * @param idx 
     * @return Partido* 
     */
    Partido *getPartido(int idx) const;

    /**
     * @brief Retorna Candidato object
     * 
     * @param idx 
     * @return Candidato* 
     */
    Candidato *getCandidato(int idx) const;

    /**
     * @brief Retorna Candidato Eleito object
     * 
     * @param idx 
     * @return Candidato* 
     */
    Candidato *getCandidatoEleito(int idx) const;

    /**
	 * @brief Converte a data para formato time_t e guarda na referência
     * 
	 * @param string data de referência
     */
    void setDataAtual(const string &data);

    /**
     * @brief Adiciona partido a lista de partidos
     * 
     * @param partido Partido
    */
    void addPartido(Partido *partido);

    /**
     * @brief Adiciona candidato a lista de candidatos
     * 
     * @param candidato Candidato
     */
    void addCandidato(Candidato *candidato);

    /**
     * @brief Adiciona candidato a lista de candidatos eleitos
     * 
     * @param candidatoEleito Candidato
     */
    void addCandidatoEleito(Candidato *candidato);

    /**
	 * @brief Retorna o quantitativo de eleitos do sexo de acordo com a entrada 
     * 
     * @param string sexo
	 * @return int 
	 */
    int getEleitosPorSexo(const string &str) const;

    /**
     * @brief Retorna o Partido object referente ao número do partido
     * 
     * @param numeroPartido 
     * @return Partido* 
     */
    Partido *getPartidoPorNumero(int numeroPartido) const;

    /**
     * @brief Define como deve ser impresso o nome "voto" 
     * 
     * @param voto número de referência
     * @return "voto" para singular e "votos" para plural
     */
    string getNomenclaturaVoto(int voto) const;

    /**
     * @brief Define como deve ser impresso o nome "candidato eleito"
     * 
     * @param candidato número de referência
     * @return "candidato eleito" para singular e "candidatos eleitos" para plural
     */
    string getNomenclaturaCandidatoEleito(int candidato) const;

    /**
     * @brief Define como deve ser impresso o nome "nominal"
     * 
     * @param voto número de referência
     * @return "nominal" para singular e "nominais" para plural
     */
    string getNomenclaturaNominal(const int voto) const;

    /**
     * @brief Método orquestra na ordem correta a execução dos métodos que geram os relatórios
     * 
     */
    void gerarRelatorios();

    /**
     * @brief Gerar Relatório 1
     * Número de vagas (= número de eleitos)
     * 
     */
    void gerarRelatorio01() const;
    
    /**
     * @brief Gerar Relatório 2
     * Candidatos eleitos (nome completo e na urna), indicado partido e número de votos nominais;
     * 
     */
    void gerarRelatorio02();

    /**
     * @brief Gerar Relatório 3
     * Candidatos mais votados dentro do número de vagas
     * 
     */
    void gerarRelatorio03();

    /**
     * @brief Gerar Relatório 4
     * Candidatos não eleitos e que seriam eleitos se a votação fosse majoritária
     * 
     */
    void gerarRelatorio04();

    /**
     * @brief Gerar Relatório 5
     * Candidatos eleitos no sistema proporcional vigente, e que não seriam eleitos se a votação fosse
     * majoritária, isto é, pelo número de votos apenas que um candidato recebe diretamente;
     * 
     */
    void gerarRelatorio05();

    /**
     * @brief Gerar Relatório 6
     * Votos totalizados por partido e número de candidatos eleitos
     * 
     */
    void gerarRelatorio06();

    /**
     * @brief Gerar Relatório 7
     * Votos de legenda (com a porcentagem destes votos frente ao total de votos no
     * partido)
     * 
     */
    void gerarRelatorio07();

    /**
     * @brief Gerar Relatório 8
     * Primeiro e último colocados de cada partido (com nome da urna, número do
     * candidato e total de votos
     * nominais). Partidos que não possuírem candidatos com um número positivo de
     * votos válidos devem
     * ser ignorados
     * 
     */
    void gerarRelatorio08();

    /**
     * @brief Gerar Relatório 9
     * Distribuição de eleitos por faixa etária, considerando a idade do candidato
     * no dia da eleição
     * 
     */
    void gerarRelatorio09() const;

    /**
     * @brief Gerar Relatório 10
     * Distribuição de eleitos por sexo
     * 
     */
    void gerarRelatorio10() const;

    /**
     * @brief Gerar Relatório 11
     * Total de votos, total de votos nominais e total de votos de legenda
     * 
     */
    void gerarRelatorio11() const;

    /**
     * @brief Libera memória da lista de todos os partidos 
     * 
     */
    void liberaPartidos();

    /**
     * @brief Libera memória da lista de todos os candidatos
     * 
     */
    void liberaCandidatos();

    /**
     * @brief Destrutor da classe
     * 
     */
    ~Eleicao();

};

#endif
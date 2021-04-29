/**
 * Representa uma casa no tabuleiro do jogo.
 * 
 * @author Alan Moraes / alan@ci.ufpb.br
 * @author Victor Koehler / koehlervictor@cc.ci.ufpb.br
 * @author Kelvin Brenand / kelvinsilva@cc.ci.ufpb.br
 */
public class Casa {

    // Semelhante as Listas Encadeadas, armazena ou não a casa seguinte, anterior e ou segura.
    private Casa casaSeguinte;
    private Casa casaSegura;
    private Casa casaAnterior;
    
    // Guarita da casa, caso pertença a alguma.
    private Guarita guarita; 
    
    // Peça presentes neste casa
    private Peca peca; 
    
    // Quantidade de peças presente na casa (Para casas finais).
    private int qtdePecas; 
    
    // Consulte a classe Cores; -1 para neutro/nulo.
    private final String cor; 
    
    /**
     * Construtor padrão para casas comuns indexadas.
     */
    public Casa() {
        this("BRANCO", null, null);
    }
    
    public Casa(String cor) {
        this(cor, null, null);
    }
    
    /**
     * Construtor padrão para casas da guarita.
     * @param guarita
     */
    public Casa(Guarita guarita) {
        this(guarita.obterCor(), null, guarita);
    }

    /**
     * Construtor padrão para todas as casas.
     *
     * @param cor Cor do jogador
     * @param anterior Casa anterior.
     */
    public Casa(String cor, Casa anterior) {
        this(cor, anterior, null);
    }
    
    private Casa(String cor, Casa anterior, Guarita guarita) {
        this.cor = cor;
        this.casaAnterior = anterior;
        this.guarita = guarita;
        this.casaSeguinte = null;
        this.casaSegura = null;
        this.peca = null;
        this.qtdePecas = 0;
    }

    /**
     * Se a casa possui peça.
     *
     * @return true se a casa possui peça; false caso contrário.
     */
    public boolean possuiPeca() {
        return getPeca() != null;
    }

    /**
     * Obtém a peça presente nesta casa, se houver.
     *
     * @return A peça se presente nesta casa ou null caso contrário.
     */
    public Peca getPeca() {
        return peca;
    }

    /**
     * Coloca a peça especificada nesta Casa.
     *
     * @param peca Peça que será inserida.
     * @return A peça que estava anteriormente nesta casa, ou null caso não
     * houvesse alguma.
     */
    public Peca setPeca(Peca peca) {
        Peca r = getPeca();
        this.peca = peca;
        if (peca == null) {
            this.qtdePecas = 0;
        } else {
            this.qtdePecas = 1;
        }
        return r;
    }

    /**
     * Obtém a quantidade de peças presente nesta casa.
     * Este método é designado para casas finais, consulte o método casaFinal()
     * para mais detalhes.
     * @return Quantidade de peças na casa.
     */
    public int getQuantidadePecas() {
        return qtdePecas;
    }

    /**
     * Define a quantidade de peças presente nesta casa.
     * Este método é designado para casas finais, consulte o método casaFinal()
     * para mais detalhes.
     * @param quantidade Quantidade de peças na casa.
     */
    public void setQuantidadePecas(int quantidade) {
        this.qtdePecas = quantidade;
    }
    
    /**
     * Define a casa seguinte a esta.
     * @param seguinte A casa seguinte a esta.
     */
    public void setCasaSeguinte(Casa seguinte) {
        this.casaSeguinte = seguinte;
    }

    /**
     * Define a casa anterior a esta.
     * @param anterior A casa anterior a esta.
     */
    public void setCasaAnterior(Casa anterior) {
        this.casaAnterior = anterior;
    }

    /**
     * A casa segura seguinte a esta. Isto é, caso este campo seja diferente de
     * null, então esta casa é o ponto final por onde os peões de um jogador de
     * determinada cor passarão antes de entrar na zona segura, e portanto,
     * esta é a casa que tal peão deve seguir ao invés de setCasaSeguinte().
     * @param casa A casa segura seguinte a esta.
     */
    public void setCasaSegura(Casa casa) {
        casaSegura = casa;
    }
    
    /**
     * Obtém a casa seguinte a esta, se houver.
     *
     * @return A casa seguinte. Null caso não exista.
     */
    public Casa getCasaSeguinte() {
        return casaSeguinte;
    }
    
    /**
     * Obtém a casa anterior a esta, se houver.
     *
     * @return A casa anterior. Null caso não exista.
     */
    public Casa getCasaAnterior() {
        return casaAnterior;
    }
    
    /**
     * Se esta casa for entrada da zona segura, então retorna a primeira casa da
     * zona de segurança.
     *
     * @return A casa segura. Null caso não exista.
     */
    public Casa getCasaSegura() {
        return casaSegura;
    }
        
    /**
     * Verifica se existe alguma casa especial de zona segura em frente a esta.
     * Consulte obterCasaSegura() para mais detalhes.
     * @return Se possui casa de zona segura em frente a esta.
     */
    public boolean ehEntradaZonaSegura() {
        return casaSegura != null;
    }
    
    /**
     * Se a é a última casa do jogador (isto é, se é a casa que o jogador almeja
     * colocar todas as suas peças).
     * Esta casa deve ter algumas propriedades particulares, como empilhar mais
     * de uma peça (isto é, pode conter mais de uma peça).
     * Explicação: Se a casa não tem sucessor mas tem antecessor, então é uma
     * casa terminal.
     * @return true se é a casa final.
     */
    public boolean ehCasaFinal() {
        return getCasaSeguinte() == null && getCasaAnterior() != null;
    }
    
    /**
     * Se a casa pertence a alguma guarita de algum jogador.
     * Consulte o método obterGuarita().
     * @return True caso pertença, false caso contrário.
     */
    public boolean pertenceGuarita() {
        return guarita != null;
    }
    
    /**
     * Obtém a guarita a qual esta casa pertence, se existir.
     * @return Instância de Guarita caso pertença, null caso contrário.
     */
    public Guarita getGuarita() {
        return guarita;
    }
    
    /**
     * Obtém a cor desta casa ou "Branco" caso seja neutra.
     * Consulte a classe Cores para mais detalhes.
     * 
     * @return Cor da casa.
     */
    public String getCor() {
        return cor;
    }
}

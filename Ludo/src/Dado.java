import java.util.Random;

/**
 * Representa um dado com números de 1 a 6.
 * 
 * @author Alan Moraes / alan@ci.ufpb.br
 * @author Victor Koehler / koehlervictor@cc.ci.ufpb.br
 * @author Kelvin Brenand / kelvinsilva@cc.ci.ufpb.br
 */
public class Dado {
    private Random random; // Gerador de números aleatórios
    private int valor; // Último valor obtido ao jogar os dados
    
    /**
     * Construtor padrão para dados.
     */
    public Dado() {
        this(System.currentTimeMillis());
    }
    
    /**
     * Construtor de dados batizados.
     * @param seed Semente do gerador
     */
    public Dado(long seed) {
        this.random = new Random(seed);
        this.valor = -1;
    }
    
    /**
     * Lança os dados e salva o seu valor.
     */
    public void rolar() {
        valor = random.nextInt(6) + 1;
    }
    
    /**
     * Obtém o último valor obtido ao lançar os dados.
     * Retorna -1 caso jogarDados ainda não tenha sido invocado.
     * @return Último valor obtido ao lançar os dados.
     */
    public int getValor() {
        return valor;
    }
}

import java.util.Arrays;

/**
 *
 * Implementa a guarita, um espaço reservado as peças fora do jogo.
 * 
 * @author Alan Moraes / alan@ci.ufpb.br
 * @author Victor Koehler / koehlervictor@cc.ci.ufpb.br
 * @author Kelvin Brenand / kelvinsilva@cc.ci.ufpb.br
 */
public class Guarita {
    private final Casa[] casas;
    private final String cor;

    /**
     * Inicializa a guarita vazia.
     * @param cor Cor
     */
    public Guarita(String cor) {
        this.cor = cor;
        this.casas = new Casa[] { new Casa(this), new Casa(this), new Casa(this), new Casa(this) };
    }
    
    /**
     * Obtém a casa associada a esta guarita de acordo com o índice especificado.
     * @param indice Índice da casa, entre 0 (inclusivo) e 4 (exclusivo).
     * @return Casa
     */
    public Casa getCasa(int indice) {
        return casas[indice];
    }
    
    /**
     * Obtém o número de peças presentes nas casas da guarita.
     * @return Número de peças
     */
    public int obterNumeroDePecas() {
        int s = 0;
        for (Casa casa : casas) {
            if (casa.possuiPeca()) {
                s++;
            }
        }
        return s;
    }
    
    /**
     * Obtém uma cópia da lista de casas desta guarita.
     * Útil para iterar sobre as casas usando o for(each).
     * @return Array contendo as casas.
     */
    public Casa[] obterTodasAsCasas() {
        return Arrays.copyOf(casas, casas.length);
    }

    /**
     * @return A cor da guarita
     */
    public String obterCor() {
        return cor;
    }
}

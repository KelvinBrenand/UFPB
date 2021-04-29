/**
 * Representa uma peça do jogo.
 * 
 * @author Alan Moraes / alan@ci.ufpb.br
 * @author Victor Koehler / koehlervictor@cc.ci.ufpb.br
 */
public class Peca {
    
    // Cor da peça
    private final String cor;
    
    // Casa na qual a peça se encontra
    private Casa casa;
    
    /**
     * Construtor padrão para peças.
     * @param cor Cor da peça
     */
    public Peca(String cor) {
        this.cor = cor;
        this.casa = null;
    }
    
    
    /**
     * Cor da peça.
     * @return Cor da peça.
     */
    public String obterCor() {
        return cor;
    }
    
    /**
     * Casa na qual a peça se encontra.
     * @return Casa na qual a peça se encontra.
     */
    public Casa obterCasa() {
        return casa;
    }
    
    /**
     * Retira a peça da casa atual e coloca-a na casa de destino.
     * @param casaDestino 
     */
    public void mover(Casa casaDestino) {
        if (casa != null) {
            casa.setPeca(null);
        }
        casaDestino.setPeca(this);
        casa = casaDestino;
    }
}

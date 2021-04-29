/**
 * Representa o tabuleiro do jogo.
 * 
 * @author Alan Moraes / alan@ci.ufpb.br
 * @author Victor Koehler / koehlervictor@cc.ci.ufpb.br
 * @author Kelvin Brenand / kelvinsilva@cc.ci.ufpb.br
 */
public class Tabuleiro {

    // Armazena as casas de início das diferentes cores.
    private Casa casaInicioAmarelo;
    private Casa casaInicioAzul;
    private Casa casaInicioVerde;
    private Casa casaInicioVermelho;
    
    
    // Armazena as guaritas do tabuleiro.
    private Guarita guaritaAmarelo;
    private Guarita guaritaAzul;
    private Guarita guaritaVerde;
    private Guarita guaritaVermelho;
    
    
    /**
     * Construtor padrão de um tabuleiro.
     */
    public Tabuleiro() {
        guaritaAmarelo = new Guarita("AMARELO");
        guaritaAzul = new Guarita("AZUL");
        guaritaVerde = new Guarita("VERDE");
        guaritaVermelho = new Guarita("VERMELHO");
        
        // Inicializamos um tabuleiro de Ludo
        
        // Casas de Inicio
        casaInicioAmarelo = new Casa("AMARELO");
        casaInicioAzul = new Casa("AZUL");
        casaInicioVerde = new Casa("VERDE");
        casaInicioVermelho = new Casa("VERMELHO");
        
        
        // Casas comuns
        // Usaremos uma espécie de lista encadeada informal para guardar as casas.
        popularCasas(casaInicioAmarelo, casaInicioVerde);
        popularCasas(casaInicioVerde, casaInicioVermelho);
        popularCasas(casaInicioVermelho, casaInicioAzul);
        popularCasas(casaInicioAzul, casaInicioAmarelo);
    }
    
    /**
     * Método usado na construção do tabuleiro para popular as casas com for.
     * @param ultimaCasa
     */
    private void popularCasas(Casa primeiraCasa, Casa ultimaCasa) {
        Casa casa = primeiraCasa; 
        for (int i = 0; i < 12; i++) {
            Casa casaSeguinte = new Casa();
            casa.setCasaSeguinte(casaSeguinte);
            casa = casaSeguinte;
            
            if (i == 10) {
                criarCasasZonaSegura(casa, ultimaCasa.getCor());
            }
        }
        casa.setCasaSeguinte(ultimaCasa);
    }
    
    /**
     * Método usado na construção do tabuleiro para popular as casas seguras com for.
     * @param casaEntradaZonaSegura
     * @param cor 
     */
    private void criarCasasZonaSegura(Casa casaEntradaZonaSegura, String cor) {
        Casa casaZonaSegura = new Casa(cor);
        casaEntradaZonaSegura.setCasaSegura(casaZonaSegura);
        for (int i = 0; i < 5; i++) {
            Casa casaNova = new Casa(cor, casaZonaSegura);
            casaZonaSegura.setCasaSeguinte(casaNova);
            casaZonaSegura = casaNova;
        }
    }
    
    
    /**
     * Obtém a guarita do jogador especificado.
     * Consulte a classe Guarita para mais detalhes.
     * @param cor Cor do jogador. Consulte a classe Cores.
     * @return Guarita do jogador
     */
    public Guarita getGuarita(String cor) {
        switch (cor) {
            case "AMARELO":
                return guaritaAmarelo;
            case "AZUL":
                return guaritaAzul;
            case "VERDE":
                return guaritaVerde;
            case "VERMELHO":
                return guaritaVermelho;
            default:
                return null;
        }
    }
    
    
    /**
     * Obtém a casa de início da cor especificada.
     * @param cor Cor do jogador. Consulte a classe Cores.
     * @return Casa de início.
     */
    public Casa getCasaInicio(String cor) {
        switch (cor) {
            case "AMARELO":
                return casaInicioAmarelo;
            case "AZUL":
                return casaInicioAzul;
            case "VERDE":
                return casaInicioVerde;
            case "VERMELHO":
                return casaInicioVermelho;
            default:
                return null;
        }
    }
    
}

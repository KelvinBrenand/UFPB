/**
 * Implementa as mecânicas e regras do jogo Ludo.
 *
 * @author Alan Moraes / alan@ci.ufpb.br
 * @author Victor Koehler / koehlervictor@cc.ci.ufpb.br
 * @author Kelvin Brenand / kelvinsilva@cc.ci.ufpb.br
 * 
 */
public class Jogo {
    // Tabuleiro do jogo
    private final Tabuleiro tabuleiro;
    
    // Dados do jogo.
    private final Dado[] dados;
    
    private boolean verificadorDado = true;
    private int controleValor = 0 , valorDado1 , valorDado2 , x = 0;
   
    /**
     * Construtor padrão do Jogo Ludo.
     * Isto é, um jogo de Ludo convencional com dois dados.
     */
    public Jogo() {
        this(2);
    }
    
    /**
     * Construtor do Jogo Ludo para inserção de um número arbitrário de dados.
     * @param numeroDados Número de dados do jogo.
     */
    public Jogo(int numeroDados) {
        this.tabuleiro = new Tabuleiro();
        this.dados = new Dado[numeroDados];
        
        for (int i = 0; i < this.dados.length; i++) {
            // remover parâmetro do construtor para dado não batizado
            this.dados[i] = new Dado();
        }

        inicializaJogo();
    }
    
    /**
     * Construtor do Jogo Ludo para inserção de dados arbitrários.
     * Útil para inserir dados "batizados" e fazer testes.
     * @param dados Dados
     */
    public Jogo(Dado[] dados) {
        this.tabuleiro = new Tabuleiro();
        this.dados = dados;
        //assert dados.length > 0; // TO BE REMOVED

        inicializaJogo();
    }
    
    private void inicializaJogo() {
        Guarita guarita;
        
        guarita = tabuleiro.getGuarita("VERDE");
        for (Casa casaGuarita : guarita.obterTodasAsCasas()) {
            Peca novaPeca = new Peca("VERDE");
            novaPeca.mover(casaGuarita);
        }
        
        guarita = tabuleiro.getGuarita("VERMELHO");
        for (Casa casaGuarita : guarita.obterTodasAsCasas()) {
            Peca novaPeca = new Peca("VERMELHO");
            novaPeca.mover(casaGuarita);
        }
        
        guarita = tabuleiro.getGuarita("AZUL");
        for (Casa casaGuarita : guarita.obterTodasAsCasas()) {
            Peca novaPeca = new Peca("AZUL");
            novaPeca.mover(casaGuarita);
        }
        
        guarita = tabuleiro.getGuarita("AMARELO");
        for (Casa casaGuarita : guarita.obterTodasAsCasas()) {
            Peca novaPeca = new Peca("AMARELO");
            novaPeca.mover(casaGuarita);
        }
    }
    
    /**
     * Método invocado pelo usuário através da interface gráfica ou da linha de comando para jogar os dados.
     * Aqui deve-se jogar os dados e fazer todas as verificações necessárias.
     */
    public void rolarDados() {
        if(verificadorDado == true)
        {
            for (Dado dado : dados) {
                dado.rolar();
                if(controleValor == 0)
                {
                    valorDado1 = dado.getValor();
                }
                if(controleValor == 1)
                {
                    valorDado2 = dado.getValor();
                    controleValor = 0;
                }
            }
            verificadorDado = false;
            controleValor = 1;
        }
    }
    
    /**
     * Método invocado pelo usuário através da interface gráfica ou da linha de comando quando escolhida uma peça.
     * Aqui deve-se mover a peça e fazer todas as verificações necessárias.
     * @param casa Casa escolhida pelo usuário/jogador.
     */
    public void escolherCasa(Casa casa) {
        Guarita guarita;
        int numeroGuarita;
        guarita = tabuleiro.getGuarita(getJogadorDaVez());
        numeroGuarita = guarita.obterNumeroDePecas();
        
        //Verifica se os dados forem diferentes e a garita tiver cheia, ele passa o turno quando o player tenta mover uma peça.  
        if((valorDado1 != valorDado2) && (numeroGuarita == 4))
        {
            Peca peca = casa.getPeca();
            if(peca.obterCor() != getJogadorDaVez())
            {
                return;
            }
            else
            {
                incrementadorX();
                verificadorDado = true;
                return;
            }
        }
        
        if (!casa.possuiPeca()) {
            return;
        }
        
        // Perguntamos à casa qual é a peça.
        Peca peca = casa.getPeca();
        if(peca.obterCor() != getJogadorDaVez())
        {
            while(peca.obterCor() != getJogadorDaVez())
            {
                peca = casa.getPeca();
            }
        }
        
        //Tira peça da guarita.
        if((valorDado1 == valorDado2) && (casa.pertenceGuarita() == true))
        {
            Casa casaInicio;
            casaInicio = tabuleiro.getCasaInicio(getJogadorDaVez());
            if(casaInicio.possuiPeca() == true)
            {
                if(casaInicio.getCor() == getJogadorDaVez())
                {
                    return;
                }
            }
            else
            {
                peca.mover(casaInicio);
                verificadorDado = true;
                valorDado1 = -2;
                return;
            }
        }
        // Percorremos cada dado, somando o valor nele à variável somaDados.
        int somaDados = 0;
        for (Dado dado : dados) {
            somaDados += dado.getValor();
        }
        
        // Percorreremos N casas.
        Casa proximaCasa = casa;
        for (int i = 0; i < somaDados && proximaCasa != null; i++) {
            
            //Faz a movimentação das peças
            if(proximaCasa.ehEntradaZonaSegura() == true)
            {
                if(proximaCasa.getCasaSegura().getCor() == getJogadorDaVez())
                {
                    proximaCasa = proximaCasa.getCasaSegura();
                }
                else
                {
                    proximaCasa = proximaCasa.getCasaSeguinte();
                }
            }
            else if(proximaCasa.getCasaSeguinte() == null)
            {
                while((i < somaDados) && (proximaCasa.getCasaAnterior() != null))
                {
                    proximaCasa = proximaCasa.getCasaAnterior();
                    i++;
                }
            }
            else
            {
                proximaCasa = proximaCasa.getCasaSeguinte();
            }
            
            //Verifica se chegamos ao fim do jogo e um player venceu.
            if((proximaCasa.getCor() == "VERDE") && (proximaCasa.getCasaSeguinte() == null) && (i == (somaDados - 1)))
            {
                int pecasNaCasaFinal;
                pecasNaCasaFinal = casa.getQuantidadePecas();
                if(pecasNaCasaFinal == 4)
                {
                    System.out.println("O VERDE VENCEU!!!");
                    verificadorDado = false;
                }
            }
            if((proximaCasa.getCor() == "VERMELHO") && (proximaCasa.getCasaSeguinte() == null) && (i == (somaDados - 1)))
            {
                int pecasNaCasaFinal;
                pecasNaCasaFinal = casa.getQuantidadePecas();
                if(pecasNaCasaFinal == 4)
                {
                    System.out.println("O VERMELHO VENCEU!!!");
                    verificadorDado = false;
                }
            }
            if((proximaCasa.getCor() == "AZUL") && (proximaCasa.getCasaSeguinte() == null) && (i == (somaDados - 1)))
            {
                int pecasNaCasaFinal;
                pecasNaCasaFinal = casa.getQuantidadePecas();
                if(pecasNaCasaFinal == 4)
                {
                    System.out.println("O AZUL VENCEU!!!");
                    verificadorDado = false;
                }
            }
            if((proximaCasa.getCor() == "AMARELO") && (proximaCasa.getCasaSeguinte() == null) && (i == (somaDados - 1)))
            {
                int pecasNaCasaFinal;
                pecasNaCasaFinal = casa.getQuantidadePecas();
                if(pecasNaCasaFinal == 4)
                {
                    System.out.println("O AMARELO VENCEU!!!");
                    verificadorDado = false;
                }
            }
        }
        
        //Faz a "começão" de pecas.
        if((proximaCasa.possuiPeca() == true) && (verificadorDado == false))
        {
            Peca peca1;
            peca1 = proximaCasa.getPeca();
            if(peca1.obterCor() == getJogadorDaVez())
            {
                return;
            }
            else
            {
                String corPecaK = "PRETO";
                corPecaK = peca1.obterCor();
                Guarita novaNovaGuarita = tabuleiro.getGuarita(corPecaK);
                Casa[] casaVaziaGuarita = novaNovaGuarita.obterTodasAsCasas();
                for(Casa casaK : casaVaziaGuarita)
                {
                    if(casaK.possuiPeca() == false)
                    {
                        Peca novaNovaPeca = new Peca(peca1.obterCor());
                        novaNovaPeca.mover(casaK);
                        break;
                    }
                }
                peca.mover(proximaCasa);
                verificadorDado = true;
            }
        }
        else
        {
            if ((proximaCasa != null) && (verificadorDado == false)) 
            {
                // Finalmente, a variável casaN contém a casa que a peça deve ser inserida.
                peca.mover(proximaCasa);
                verificadorDado = true;
            }
        }
        
        //Chamada do método de passar o turno.
        if((valorDado1 != -2) && (valorDado1 != valorDado2))
        {
            incrementadorX();
        }
    }
    
    /**
     * Retorna o jogador que deve jogar os dados ou escolher uma peça.
     * @return Cor do jogador.
     */
    public String getJogadorDaVez() {
       if(x == 0)
       {
            return "VERDE";
       }
       if(x == 1)
       {
            return "VERMELHO";
       }
       if(x == 2)
       {
            return "AZUL";
       }
       if(x == 3)
       {
            return "AMARELO";
       }
       return null;
    }
    
    /**
     * Método que incrementa a variável responsável pelos turnos.
     * 
     */
    public void incrementadorX()
    {
        x++;
        if(x > 3)
        {
            x = 0;
        }
    }
    
    /**
     * O tabuleiro deste jogo.
     * @return O tabuleiro deste jogo.
     */
    public Tabuleiro getTabuleiro() {
        return tabuleiro;
    }

    /**
     * Retorna o i-ésimo dado deste jogo entre 0 (inclusivo) e N (exclusivo).
     * Consulte obterQuantidadeDeDados() para verificar o valor de N
     * (isto é, a quantidade de dados presentes).
     * @param i Indice do dado.
     * @return O i-ésimo dado deste jogo.
     */
    public Dado getDado(int i) {
        return dados[i];
    }
    
    /**
     * Obtém a quantidade de dados sendo usados neste jogo.
     * @return Quantidade de dados.
     */
    public int getQuantidadeDados() {
        return dados.length;
    }
}

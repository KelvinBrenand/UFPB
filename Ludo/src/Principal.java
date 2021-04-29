import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.util.HashMap;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JFrame;

/**
 * Classe principal do pacote. Encapsula o jogo e a interface gráfica.
 *
 * @author Alan Moraes / alan@ci.ufpb.br
 * @author Victor Koehler / koehlervictor@cc.ci.ufpb.br
 * @author Kelvin Brenand / kelvinsilva@cc.ci.ufpb.br
 */
public class Principal extends JFrame {

    private Jogo jogo; // Jogo em andamento

    private final HashMap<String, Color> cores;
    private final HashMap<String, Icon> icones;

    /**
     * Construtor da classe.
     */
    public Principal() {
        initComponents();
        cores = new HashMap<>();
        icones = new HashMap<>();
        carregarIconesECores();

        // configura action listener para o menu novo
        menuNovo.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                reiniciarJogo();
            }
        });

        // configura action listener para o menu sair
        menuSair.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
            }
        });

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowOpened(WindowEvent we) {
                setSize(getPreferredSize());
            }
        });

        super.setLocationRelativeTo(null);
        super.setVisible(true);

        reiniciarJogo();
    }

    /**
     * Cria um novo jogo e atualiza o tabuleiro gráfico.
     */
    public void reiniciarJogo() {

        // Faz com que a peça verde caia em cima da vermelha na primeira volta.
        //jogo = new Jogo(new Dado(14));
        jogo = new Jogo();

        jPanel_Dados.removeAll();
        for (int i = 0; i < jogo.getQuantidadeDados(); i++) {
            DadoGUI d = new DadoGUI(this);
            jPanel_Dados.add(d);
        }

        tabuleiroGUI.reiniciarLayout();
        atualizar();
    }

    /**
     * Evento invocado quando o usuário clica no dado desenhado na GUI.
     *
     * @param dadoClicado Dado clicado pelo usuário
     */
    public void reagirDadoClicado(DadoGUI dadoClicado) {
        // rola os dados
        jogo.rolarDados();

        // redefine os estados das interfaces gráficas dos dados
        // de acordo com os valores dos dados
        for (int i = 0; i < jogo.getQuantidadeDados(); i++) {
            DadoGUI dadoGUI = (DadoGUI) jPanel_Dados.getComponent(i);
            Dado dado = jogo.getDado(i);
            dadoGUI.setValor(dado.getValor());
        }
        atualizar();
    }

    /**
     * Evento invocado quando o usuário clica em uma casa desenhada na GUI.
     *
     * @param casaClicada Casa clicada pelo usuário
     */
    public void reagirCasaClicada(CasaGUI casaClicada) {
        Casa casa = casaClicada.getCasa();
        jogo.escolherCasa(casa);
        atualizar();
    }
    /**
     * Atualiza a interface gráfica
     */
    private void atualizar() {
        tabuleiroGUI.repaint();
        tabuleiroGUI.revalidate();
    }
    
    /**
     * @return O jogo em andamento
     */
    public Jogo getJogo() {
        return jogo;
    }

    /**
     * Cor AWT associada a String 'cor'.
     * @param cor Cor
     * @return Color AWT
     */
    public Color obterCorPadrão(String cor) {
        return obterCorPadrão(cor, Color.WHITE);
    }

    /**
     * Cor AWT associada a String 'cor'.
     * @param cor Cor
     * @param defaultColor Retorno padrão caso 'cor' não seja encontrada.
     * @return Color AWT
     */
    public Color obterCorPadrão(String cor, Color defaultColor) {
        return cores.getOrDefault(cor, defaultColor);
    }

    /**
     * Obtém um ícone gráfico do dicionário de ícones.
     * Para uma entrada correspondente a uma cor, é retornado o peão colorido.
     * 
     * @param icone Icone representado por uma String.
     * @return Icon AWT
     */
    public Icon obterIconePadrão(String icone) {
        return icones.get(icone);
    }

    private void carregarIconesECores() {
        cores.put("AMARELO", Color.YELLOW);
        icones.put("AMARELO", carregarIcone("imagens/amarelo.png"));
        
        cores.put("AZUL", Color.BLUE);
        icones.put("AZUL", carregarIcone("imagens/azul.png"));
        
        cores.put("VERDE", Color.GREEN);
        icones.put("VERDE", carregarIcone("imagens/verde.png"));
        
        cores.put("VERMELHO", Color.RED);
        icones.put("VERMELHO", carregarIcone("imagens/vermelho.png"));
        
        icones.put("ESTRELA", carregarIcone("imagens/star.png"));
        for (int i = 0; i < 7; i++) {
            icones.put("DADO_" + i, carregarIcone("imagens/dado_" + i + ".png"));
        }
    }

    private Icon carregarIcone(String endereco) {
        String enderecoCompleto = Principal.class.getResource(endereco).getFile();
        File arquivo = new File(enderecoCompleto);
        if (arquivo.exists()) {
            return new ImageIcon(arquivo.getPath());    
        }
        else {
            System.out.println("Não foi possível carregar os arquivos de imagens.");
            return null;
        }
        
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        tabuleiroGUI = new TabuleiroGUI(this);
        jPanel_Dados = new javax.swing.JPanel();
        jMenuBar1 = new javax.swing.JMenuBar();
        menuArquivo = new javax.swing.JMenu();
        menuNovo = new javax.swing.JMenuItem();
        jSeparator1 = new javax.swing.JPopupMenu.Separator();
        menuSair = new javax.swing.JMenuItem();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        jPanel_Dados.setBorder(javax.swing.BorderFactory.createEmptyBorder(1, 1, 1, 1));
        jPanel_Dados.setLayout(new java.awt.GridLayout(0, 1));

        menuArquivo.setText("Jogo");

        menuNovo.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_N, java.awt.event.InputEvent.CTRL_MASK));
        menuNovo.setText("Novo");
        menuArquivo.add(menuNovo);
        menuArquivo.add(jSeparator1);

        menuSair.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_S, java.awt.event.InputEvent.CTRL_MASK));
        menuSair.setText("Sair");
        menuArquivo.add(menuSair);

        jMenuBar1.add(menuArquivo);

        setJMenuBar(jMenuBar1);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jPanel_Dados, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(tabuleiroGUI, javax.swing.GroupLayout.DEFAULT_SIZE, 688, Short.MAX_VALUE)
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(10, 10, 10)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(tabuleiroGUI, javax.swing.GroupLayout.DEFAULT_SIZE, 456, Short.MAX_VALUE)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jPanel_Dados, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(0, 0, Short.MAX_VALUE)))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                new Principal().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JPanel jPanel_Dados;
    private javax.swing.JPopupMenu.Separator jSeparator1;
    private javax.swing.JMenu menuArquivo;
    private javax.swing.JMenuItem menuNovo;
    private javax.swing.JMenuItem menuSair;
    private TabuleiroGUI tabuleiroGUI;
    // End of variables declaration//GEN-END:variables

}

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import javax.swing.JPanel;
import javax.swing.BorderFactory;

/**
 * Implementa as rotinas da interface gráfica do jogo relacionadas ao Tabuleiro.
 * 
 * @author Alan Moraes / alan@ci.ufpb.br
 * @author Victor Koehler / koehlervictor@cc.ci.ufpb.br
 */
public class TabuleiroGUI extends JPanel {

    private final JPanel[][] microGrid, macroGrid;
    private final Principal principal;
    private final int DIVISAO, MACRODIVISAO;

    /**
     * Creates new form Tabuleiro
     */
    public TabuleiroGUI() {
        this.MACRODIVISAO = 5;
        this.DIVISAO = 15;
        this.principal = null;
        this.microGrid = null;
        this.macroGrid = null;
    }

    public TabuleiroGUI(Principal principal) {
        this.MACRODIVISAO = 5;
        this.DIVISAO = 15;
        this.principal = principal;
        this.microGrid = new JPanel[DIVISAO][DIVISAO];
        this.macroGrid = new JPanel[MACRODIVISAO][MACRODIVISAO];
        initComponents();
        inicializarLayout();
    }
    
    
    
    private Tabuleiro getTabuleiro() {
        return principal.getJogo().getTabuleiro();
    }

    
    
    private void pintarCentro(Graphics gp) {
        java.awt.Graphics2D g = (java.awt.Graphics2D) gp.create();
        JPanel centro = macroGrid[2][2];
        int f = centro.getWidth(), h = f/2;
        
        if (principal == null) {
            return;
        }
        
        g.setColor(principal.obterCorPadrão("VERDE"));
        g.fillPolygon(new int[] {0, 0, h}, new int[] {0, f, h}, 3);
        
        g.setColor(principal.obterCorPadrão("VERMELHO"));
        g.fillPolygon(new int[] {0, f, h}, new int[] {0, 0, h}, 3);
        
        g.setColor(principal.obterCorPadrão("AMARELO"));
        g.fillPolygon(new int[] {0, f, h}, new int[] {f, f, h}, 3);
        
        g.setColor(principal.obterCorPadrão("AZUL"));
        g.fillPolygon(new int[] {f, f, h}, new int[] {0, f, h}, 3);

        g.setColor(Color.GRAY);
        g.setStroke(new BasicStroke(2));
        g.drawLine(0, 0, f, f);
        g.drawLine(0, f, f, 0);
    }
    
    private void inicializarLayout() {        
        addComponentListener(new ComponentAdapter() {
            @Override
            public void componentResized(ComponentEvent e) {
                int w = getWidth(), h = getHeight();
                int s = Math.min(getWidth(), getHeight());
                if (s != 0) {
                    s = (s/DIVISAO)*DIVISAO; // MAGIC!
                    jPanel1.setPreferredSize(new Dimension(s, s));
                    revalidate();
                    repaint();
                }
            }
        });
        
        final int piece = DIVISAO / MACRODIVISAO;
        
        for (int m = 0; m < MACRODIVISAO; m++) {
            for (int n = 0; n < MACRODIVISAO; n++) {
                if (m == 2 && n == 2) {
                    macroGrid[m][n] = new JPanel() {
                        @Override
                        protected void paintComponent(Graphics g) {
                            pintarCentro(g);
                            super.paintComponent(g);
                        }
                    };
                    macroGrid[m][n].setOpaque(false);
                }
                else {
                    macroGrid[m][n] = new JPanel();
                }
                macroGrid[m][n].setLayout(new java.awt.GridLayout(piece, piece));
                macroGrid[m][n].setBorder(BorderFactory.createEmptyBorder());
                jPanel1.add(macroGrid[m][n]);
            }
        }
        
        
        for (int m = 0; m < DIVISAO; m++) {
            for (int n = 0; n < DIVISAO; n++) {
                microGrid[m][n] = new JPanel();
                microGrid[m][n].setLayout(new java.awt.GridLayout(1, 1));
                microGrid[m][n].setBorder(BorderFactory.createEmptyBorder());
                microGrid[m][n].setOpaque(false);
                macroGrid[m / piece][n / piece].add(microGrid[m][n]);
            }
        }
        
        guaritaInit("AMARELO", 0, 14, 1, -1);
        guaritaInit("AZUL", 14, 14, -1, -1);
        guaritaInit("VERDE", 0, 0, 1, 1);
        guaritaInit("VERMELHO", 14, 0, -1, 1);
    }
    
    
    private JPanel getPanelFromGrid(int x, int y) {
        return microGrid[y][x];
    }
    
    
    private void guaritaInit(String cor, int xi, int yi, int xm, int ym) {
        int func = 0;
        for (int x = 0; x < 6; x++) {
            for (int y = 0; y < 6; y++) {
                if ((x == 4 || x == 1) && (y == 4 || y == 1)) {
                    getPanelFromGrid(x*xm + xi, y*ym + yi).add(new GuaritaGUI(cor, func++, principal));
                }
                else {
                    getPanelFromGrid(x*xm + xi, y*ym + yi).add(new GuaritaGUI(cor, principal));
                }
            }
        }
    }
    
    
    
    
    
    private final int[][] pontos = {
        {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6},
        {6, 5}, {6, 4}, {6, 3}, {6, 2}, {6, 1}, {6, 0}, {7, 0}, {8, 0},
        {8, 1}, {8, 2}, {8, 3}, {8, 4}, {8, 5},
        {9, 6}, {10, 6}, {11, 6}, {12, 6}, {13, 6}, {14, 6}, {14, 7}, {14, 8},
        {13, 8}, {12, 8}, {11, 8}, {10, 8}, {9, 8},
        {8, 9}, {8, 10}, {8, 11}, {8, 12}, {8, 13}, {8, 14}, {7, 14}, {6, 14},
        {6, 13}, {6, 12}, {6, 11}, {6, 10}, {6, 9},
        {5, 8}, {4, 8}, {3, 8}, {2, 8}, {1, 8}, {0, 8}, {0, 7}, {0, 6}
    };
    
    private final int[][][] pontosCentrais = {
        { {7, 1}, {7, 2}, {7, 3}, {7, 4}, {7, 5}, {7, 6} },
        { {13, 7}, {12, 7}, {11, 7}, {10, 7}, {9, 7}, {8, 7} },
        { {7, 13}, {7, 12}, {7, 11}, {7, 10}, {7, 9}, {7, 8} },
        { {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7} }
    };
    
    public void reiniciarLayout() {
        for (int x = 6; x < 9; x++) {
            for (int y = 0; y < DIVISAO; y++) {
                getPanelFromGrid(x, y).removeAll();
                getPanelFromGrid(y, x).removeAll();
            }
        }
                
        
        int subPontoAtual = 0;
        Casa atual = getTabuleiro().getCasaInicio("VERDE");
        for (int[] ponto : pontos) {
            int x = ponto[0];
            int y = ponto[1];
            getPanelFromGrid(x, y).add(new CasaGUI(atual, principal));
            
            if (atual.ehEntradaZonaSegura()) {
                Casa sub = atual.getCasaSegura();
                
                for (int[] pontoCentrais : pontosCentrais[subPontoAtual]) {
                    int xj = pontoCentrais[0];
                    int yj = pontoCentrais[1];
                    getPanelFromGrid(xj, yj).add(new CasaGUI(sub, principal));
                    sub = sub.getCasaSeguinte();
                }
                subPontoAtual++;
            }
            
            atual = atual.getCasaSeguinte();
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

        jPanel1 = new javax.swing.JPanel();

        setBackground(new java.awt.Color(250, 250, 250));

        jPanel1.setLayout(new java.awt.GridLayout(5, 5));
        add(jPanel1);
    }// </editor-fold>//GEN-END:initComponents

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JPanel jPanel1;
    // End of variables declaration//GEN-END:variables
}

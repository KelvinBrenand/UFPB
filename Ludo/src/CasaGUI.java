import java.awt.Color;
import java.awt.Graphics;
import javax.swing.BorderFactory;
import javax.swing.Icon;
import javax.swing.JButton;
import javax.swing.SwingConstants;

/**
 * Implementa as rotinas da interface gráfica do jogo relacionadas a Casa.
 * 
 * @author Alan Moraes / alan@ci.ufpb.br
 * @author Victor Koehler / koehlervictor@cc.ci.ufpb.br
 */
public class CasaGUI extends JButton {
    
    // Classe principal, para dados do jogo.
    private final Principal janelaPrincipal;
    
    private Casa casa; // Casa correspondente
        
    /**
     * Construtor padrão da interface gráfica de uma casa do tabuleiro.
     * @param casa Casa relacionada.
     * @param janelaPrincipal Janela principal
     */
    public CasaGUI(Casa casa, Principal janelaPrincipal) {
        this.casa = casa;
        this.janelaPrincipal = janelaPrincipal;
        
        // Layout e cor
        setOpaque(false);
        setContentAreaFilled(false);
        setIcon(null);
        setVerticalTextPosition(SwingConstants.CENTER);
        setHorizontalTextPosition(SwingConstants.CENTER);
        
        java.awt.Font f = getFont();
        setFont(f.deriveFont(f.getSize2D() + 5.0f));
        
        
        addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                janelaPrincipal.reagirCasaClicada((CasaGUI) evt.getSource());
            }
        });
    }
    
    public Casa getCasa() {
        return casa;
    }
    
    public void setCasa(Casa casa) {
        this.casa = casa;
    }
    
    
        
    private Color obterCor() {
        if (casa == null || janelaPrincipal == null || casa.pertenceGuarita()) {
            return Color.WHITE;
        }
        return janelaPrincipal.obterCorPadrão(casa.getCor());
    }
    
    
    
    private boolean possuiBorda() {
        return casa != null && !casa.ehCasaFinal();
    }

    
    @Override
    protected void paintComponent(Graphics g) {
        setBackground(obterCor());
        
        if (possuiBorda()) {
            setBorder(BorderFactory.createLineBorder(Color.GRAY, 1));
        }
        else {
            setBorder(BorderFactory.createEmptyBorder());
        }
        
        setIcon(null);
        if (casa != null && janelaPrincipal != null) {
            int q = casa.getQuantidadePecas();
            setText(q >= 2 ? q + "" : "");
            
            if (casa.possuiPeca()) {
                Icon icon = janelaPrincipal.obterIconePadrão(casa.getPeca().obterCor());
                setIcon(icon);
            }
            else if (casa.ehEntradaZonaSegura()) {
                Icon icon = janelaPrincipal.obterIconePadrão("ESTRELA");
                setIcon(icon);
            }
        }
        
        g.setColor(getBackground());
        g.fillRect(0, 0, getWidth(), getHeight());
        super.paintComponent(g);
    }
        
    
}

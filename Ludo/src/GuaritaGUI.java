import java.awt.Color;
import java.awt.Graphics;
import java.awt.GridLayout;
import javax.swing.BorderFactory;
import javax.swing.JButton;

/**
 * Implementa as funcionalidades gráficas das bordas do jogo, nomeadamente as guaritas.
 * 
 * @author Alan Moraes / alan@ci.ufpb.br
 * @author Victor Koehler / koehlervictor@cc.ci.ufpb.br
 */
public class GuaritaGUI extends JButton {
    
    // Classe principal, para dados do jogo.
    private final Principal principal;
    private final CasaGUI casagui;
    
    // Cor da guarita.
    private final String cor;
    
    // Função que representa a guarita.
    private final int func;

    
    /**
     * Um bloco da guarita colorido sem borda simples.
     * @param cor Cor da guarita
     * @param principal Classe principal
     */
    public GuaritaGUI(String cor, Principal principal) {
        this(cor, -1, principal);
    }

    /**
     * Um bloco da guarita branco, que de acordo com a cor e 'func', representa
     * a quantidade de peças restantes do jogador.
     * 
     * @param cor Cor da guarita
     * @param func Função da guarita
     * @param principal Classe principal
     */
    public GuaritaGUI(String cor, int func, Principal principal) {
        this.principal = principal;
        this.cor = cor;
        this.func = func;
        this.casagui = func == -1 ? null : new CasaGUI(obterCasa(), principal);
        setLayout(new GridLayout());
        setBorder(BorderFactory.createEmptyBorder());
        setContentAreaFilled(false);
        setIcon(null);
        if (eCasa()) {
            add(this.casagui);
        }
    }
    
    private boolean eCasa() {
        return this.casagui != null;
    }
    
    private Casa obterCasa() {
        if (principal.getJogo() == null) {
            return null;
        }
        return principal.getJogo().getTabuleiro().getGuarita(cor).getCasa(func);
    }
    
    private Color obterCor() {
        if (func == -1 && principal != null) {
            Color padrao = principal.obterCorPadrão(cor, null);
            if (padrao == null) {
                return Color.WHITE;
            }
            else if (principal.getJogo() != null) {
                String j = principal.getJogo().getJogadorDaVez();
                if (cor.equals(j)) {
                    return padrao.darker();
                }
            }
            
            return padrao;
        }
        else return Color.WHITE;
    }
    
    @Override
    protected void paintComponent(Graphics g) {
        if (eCasa()) {
            casagui.setCasa(obterCasa());
        }
        else {
            setBackground(obterCor());
            g.setColor(getBackground());
            g.fillRect(0, 0, getWidth(), getHeight());
        }
        super.paintComponent(g);
    }
}

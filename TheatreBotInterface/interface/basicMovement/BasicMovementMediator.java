package basicMovement;

import java.awt.CardLayout;

import javax.swing.JPanel;

public class BasicMovementMediator {

	private CardLayout layout;
	private JPanel jpanelPrincipal;
	
	public void layoutRegistration(CardLayout layout){
		this.layout = layout;
	}
	
	public void jpanelRegistretion(JPanel  jpanel){
		jpanelPrincipal = jpanel;
	}
	
	public void showOptionsMenu(){
		layout.show(jpanelPrincipal, "a");
	}
	
	public void showGenerationFirstMenu(){
		layout.show(jpanelPrincipal, "b");
	}
	
	public void showExecution(){
		layout.show(jpanelPrincipal, "c");
	}
}

package general;


import javax.swing.JFrame;

import basicMovement.BasicMovementJPanel;

import java.awt.CardLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ButtonGroup;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import net.miginfocom.swing.MigLayout;
import javax.swing.JRadioButtonMenuItem;

public class PrincipalWindow implements ActionListener{

	JFrame frmTheatrebot;
	private BasicMovementJPanel basicMovement;
	private float distance = 2000;

	/**
	 * Create the application.
	 */
	public PrincipalWindow(String[] acceleration, String [] emotions) {
		initialize();
		frmTheatrebot.getContentPane().setLayout(new CardLayout());
		
		//MenuBar
		JMenuBar menuBar = new JMenuBar();
		frmTheatrebot.setJMenuBar(menuBar);
		
		JMenu mnMenu = new JMenu("Menu");
		menuBar.add(mnMenu);
		
		JRadioButtonMenuItem rdbtnmntmBasicMovements = new JRadioButtonMenuItem("Basic Movements");
		mnMenu.add(rdbtnmntmBasicMovements);
		
		JRadioButtonMenuItem rdbtnmntmPatternMovement = new JRadioButtonMenuItem("Pattern Movement");
		mnMenu.add(rdbtnmntmPatternMovement);
		
		JRadioButtonMenuItem rdbtnmntmBasicTrajectory = new JRadioButtonMenuItem("Basic Trajectory");
		mnMenu.add(rdbtnmntmBasicTrajectory);
		//Add Action Listeners
		rdbtnmntmBasicMovements.addActionListener(this);
		rdbtnmntmPatternMovement.addActionListener(this);
		rdbtnmntmBasicTrajectory.addActionListener(this);
		
		//Group the option
		ButtonGroup group = new ButtonGroup();
		group.add(rdbtnmntmBasicMovements);
		group.add(rdbtnmntmPatternMovement);
		group.add(rdbtnmntmBasicTrajectory);
		//Panels
		basicMovement = new BasicMovementJPanel(acceleration,emotions,distance);
		frmTheatrebot.getContentPane().add(basicMovement);
		basicMovement.setVisible(false);
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frmTheatrebot = new JFrame();
		frmTheatrebot.setTitle("TheatreBot");
		frmTheatrebot.setBounds(100, 100, 710, 610);
		frmTheatrebot.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getActionCommand().compareTo("Basic Movements")==0){
			basicMovement.setVisible(true);
		}else if(e.getActionCommand().compareTo("Pattern Movement")==0){
			basicMovement.setVisible(false);
		}else if(e.getActionCommand().compareTo("Basic Trajectory")==0){
			basicMovement.setVisible(false);
		}
	}

}

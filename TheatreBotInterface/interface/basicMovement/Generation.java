package basicMovement;

import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;

import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.JLabel;
import net.miginfocom.swing.MigLayout;
import javax.swing.JComboBox;
import javax.swing.JTextField;

import basicMovementController.GenerationController;

public class Generation extends JPanel{
	
	/**
	 * Attributes 
	 */
	private JTextField textFieldName;
	private BasicMovementMediator mediator;
	private JComboBox comboBoxEmotions;
	private JButton btnCreate;
	private JComboBox comboBoxPoints;
	private JButton btnCancel;
	
	JLabel lblPoints;
	/**
	 * Create the panel.
	 */
	public Generation(BasicMovementMediator mediator, String [] emotions) {
		//setLayout(new MigLayout("", "[grow][grow][grow]", "[grow][grow][grow]"));
		setLayout(new GridBagLayout());
		GridBagConstraints gbc = new GridBagConstraints( 0, 0, 1, 1, 0, 1, GridBagConstraints.CENTER, GridBagConstraints.NONE, new Insets( 3, 3, 3, 3 ), 0, 0 );
			
		
		this.mediator = mediator;
		
		comboBoxEmotions = new JComboBox(emotions);
		comboBoxEmotions.setPreferredSize( new Dimension( 100, 30 ) );
		
		textFieldName = new JTextField();
		textFieldName.setColumns(10);
		textFieldName.setPreferredSize( new Dimension( 100, 30 ) );
		
		lblPoints = new JLabel("Points");
		//Possible points that could be used for the user
		String[] points = new String [100];
		for(int i=0;i<100;i++){
			points[i] = Integer.toString(i+1);
		}
		comboBoxPoints = new JComboBox(points);
		comboBoxPoints.setPreferredSize( new Dimension( 100, 30 ) );
		
		btnCreate = new JButton("Create");
		btnCreate.setPreferredSize( new Dimension( 100, 30 ) );
		
		JLabel lblName = new JLabel("Name");
		lblName.setPreferredSize( new Dimension( 100, 30 ) );
		
		btnCancel = new JButton("Cancel");
		btnCancel.setPreferredSize( new Dimension( 100, 30 ) );

		add(lblName, gbc);
		gbc.gridx = 1;
		add(comboBoxEmotions, gbc);
		gbc.gridx = 2;
		add(textFieldName, gbc);
		gbc.gridy = 1;
		gbc.gridx = 0;
		add(lblPoints,gbc);
		gbc.gridx = 1;
		add(comboBoxPoints,gbc);
		gbc.gridy = 2;
		gbc.gridx = 0;
		add(btnCreate, gbc);
		gbc.gridx = 2;
		add(btnCancel, gbc);
		
		/*add(lblName, "cell 0 0");
		add(comboBoxEmotions, "cell 1 0");
		add(textFieldName, "cell 2 0");
		add(lblPoints,"cell 0 1");
		add(comboBoxPoints," cell 1 1");
		add(btnCreate, "cell 0 2");
		add(btnCancel, "cell 2 2");*/

	}

	/**
	 * This method reset the whole panel, which make it to look as the tool is the first time to be used
	 */
	public void resetPanel(){
		comboBoxEmotions.setSelectedIndex(0);
		comboBoxPoints.setSelectedIndex(0);
		textFieldName.setText("");
	}
	
	public void addController(GenerationController controller){
		btnCreate.addActionListener(controller);
		btnCancel.addActionListener(controller);
		
	}

	public JTextField getTextFieldName() {
		return textFieldName;
	}

	public void setTextFieldName(JTextField textFieldName) {
		this.textFieldName = textFieldName;
	}

	public BasicMovementMediator getMediator() {
		return mediator;
	}

	public void setMediator(BasicMovementMediator mediator) {
		this.mediator = mediator;
	}

	public JComboBox getComboBoxEmotions() {
		return comboBoxEmotions;
	}

	public void setComboBoxEmotions(JComboBox comboBoxEmotions) {
		this.comboBoxEmotions = comboBoxEmotions;
	}

	public JComboBox getComboBoxPoints() {
		return comboBoxPoints;
	}

	public void setComboBoxPoints(JComboBox comboBoxPoints) {
		this.comboBoxPoints = comboBoxPoints;
	}

	public JLabel getLblPoints() {
		return lblPoints;
	}

	public void setLblPoints(JLabel lblPoints) {
		this.lblPoints = lblPoints;
	}
	
	

}

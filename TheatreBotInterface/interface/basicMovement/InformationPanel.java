package basicMovement;

import java.awt.Color;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;

import javax.swing.JPanel;
import net.miginfocom.swing.MigLayout;

import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JComboBox;
import javax.swing.border.TitledBorder;

import basicMovementController.ExecutionController;

public class InformationPanel extends JPanel {
	
	/*
	 * Attributes
	 */
	private JTextField textField;
	private JTextField textDistance;
	private String pointNumber;
	private JComboBox comboBox;
	//This variable says the maximum angle for the upper part
	private JLabel upperMaximumAngelLabel;
	private JTextField upperMaximumAngelText;
	//This variable says the speed for the upper part
	private JLabel upperSpeedAngelLabel;
	private JTextField upperSpeedAngelText;
	//This variable says if there is a maximum angle for the platform
	private JLabel maxAngularLabelRestriction;
	private JComboBox comboxAngleRestriction;
	private JLabel maxAngularLabelAngle;
	private JTextField maxAngularTextAngle;
	private JLabel angularLabelVelocity;
	private JTextField angularTextVelocity;

	/**
	 * Create the panel.
	 */
	public InformationPanel(String pointNumber,String[] acceleration) {
		TitledBorder title;
		title = BorderFactory.createTitledBorder(
				BorderFactory.createLineBorder(Color.black), "Point Number: "+pointNumber);
		setBorder(title);
		setLayout(new GridBagLayout());
		GridBagConstraints gbc = new GridBagConstraints( 0, 0, 1, 1, 0, 1, GridBagConstraints.CENTER, 
				GridBagConstraints.NONE, new Insets( 3, 3, 3, 3 ), 0, 0 );
		this.pointNumber = pointNumber;
		//--------------
		gbc.gridy = 1;
		gbc.gridx = 0;
		JLabel lblVelocity = new JLabel("Velocity");
		add(lblVelocity, gbc);
		gbc.gridx = 1;
		textField = new JTextField();
		add(textField, gbc);
		textField.setColumns(12);
		//-------------
		gbc.gridy = 2;
		gbc.gridx = 0;			
		JLabel lblDistance = new JLabel("Distance");
		add(lblDistance, gbc);
		gbc.gridx = 1;			
		textDistance = new JTextField();
		add(textDistance, gbc);
		textDistance.setColumns(12);		
		//--------------
		gbc.gridy = 3;
		gbc.gridx = 0;
		maxAngularLabelRestriction = new JLabel("Angle Restriction");
		add(maxAngularLabelRestriction, gbc);
		gbc.gridx = 1;
		String t [] = {"Not Apply","Apply"};
		comboxAngleRestriction = new JComboBox(t);
		add(comboxAngleRestriction, gbc);
		//-------------
		gbc.gridy = 4;
		gbc.gridx = 0;
		maxAngularLabelAngle = new JLabel("Max Angle");
		add(maxAngularLabelAngle,gbc);
		gbc.gridx = 1;
		maxAngularTextAngle = new JTextField("0");
		maxAngularTextAngle.setColumns(12);
		add(maxAngularTextAngle, gbc);
		//-------------
		gbc.gridy = 5;
		gbc.gridx = 0;
		angularLabelVelocity = new JLabel("Angular Velocity");
		add(angularLabelVelocity,gbc);
		gbc.gridx = 1;
		angularTextVelocity = new JTextField("0");
		angularTextVelocity.setColumns(12);
		add(angularTextVelocity,gbc);
		//-------------
		gbc.gridy = 6;
		gbc.gridx = 0;		
		JLabel lblReach = new JLabel("Reach");
		add(lblReach, gbc);
		gbc.gridx = 1;		
		comboBox = new JComboBox(acceleration);
		add(comboBox, gbc);
		//-------------
		gbc.gridy = 7;
		gbc.gridx = 0;
		upperSpeedAngelLabel = new JLabel("Upper Position");
		add(upperSpeedAngelLabel,gbc);
		gbc.gridx = 1;
		upperSpeedAngelText = new JTextField("0");
		upperSpeedAngelText.setColumns(12);
		add(upperSpeedAngelText,gbc);

		//-------------
		gbc.gridy = 8;
		gbc.gridx = 0;
		upperMaximumAngelLabel = new JLabel("Upper Max Angel");
		add(upperMaximumAngelLabel,gbc);
		gbc.gridx = 1;
		upperMaximumAngelText = new JTextField("0");
		upperMaximumAngelText.setColumns(12);
		add(upperMaximumAngelText,gbc);

	}
	
	/**
	 * This method is to make online validations
	 * @param controller
	 */
	public void addController(ExecutionController controller){
		textDistance.getDocument().addDocumentListener(controller);
		textDistance.getDocument().putProperty("name", "distance-"+pointNumber);
		textField.getDocument().addDocumentListener(controller);
		textField.getDocument().putProperty("name", "velocity-"+pointNumber);
	}

	public void setAngularVelocity(String velocity){
		this.angularTextVelocity.setText(velocity);
	}
	
	public String getAngularVelocity(){
		return angularTextVelocity.getText();
	}
		
	public void setMaxAngularAngle(String angle){
		maxAngularTextAngle.setText(angle);
	}
	
	public String getMaxAngularAngle(){
		return maxAngularTextAngle.getText();
	}
	
	public String getMaxUpperAngel(){
		return upperMaximumAngelText.getText();
	}
	
	public void setMaxUpperAngel(String angle){
		upperMaximumAngelText.setText(angle);
	}
	
	public void setUpperSpeed(String angle){
		upperSpeedAngelText.setText(angle);
	}
	
	public String getUpperSpeed(){
		return upperSpeedAngelText.getText();
	}
	
	/**
	 * this says if is any restriction in the maximum angle that could be reach by the platform
	 */
	public void setIsMaxAngelRestriction(String text){
		comboxAngleRestriction.setSelectedIndex(findPositionOfSelectedItemRestriction(text));
	}
	
	/**
	 * this says if is any restriction in the maximum angle that could be reach by the platform
	 * @return
	 */
	public String getIsMaxAngelRestriction(){
		return comboxAngleRestriction.getSelectedItem().toString();
	}
	
	private int findPositionOfSelectedItemRestriction(String text){
		for(int i =0 ; i < comboxAngleRestriction.getItemCount(); i++){
			if(comboxAngleRestriction.getItemAt(i).equals(text)){
				return i;
			}
		}
		return 0;
	}
	
	public void setAcelleration(String text){
		comboBox.setSelectedIndex(findPositionOfSelectedItem(text));
	}
	
	private int findPositionOfSelectedItem(String text){
		for(int i =0 ; i < comboBox.getItemCount(); i++){
			if(comboBox.getItemAt(i).equals(text)){
				return i;
			}
		}
		return 0;
	}
	
	public void setTextDistance(String text){
		this.textDistance.setText(text);
	}
	
	public void setTextVelocity(String text){
		this.textField.setText(text);
	}
	
	public String getTextDistance(){
		return this.textDistance.getText();
	}
	
	public String getTextVelocity(){
		return this.textField.getText();
	}
	
	public String getPointNumber(){
		return this.pointNumber;
	}
	
	public String getAcceleration(){
		return this.comboBox.getSelectedItem().toString();
	}

}

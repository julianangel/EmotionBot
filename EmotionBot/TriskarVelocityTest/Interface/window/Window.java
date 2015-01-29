package window;

import gnu.io.SerialPort;

import java.awt.EventQueue;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public class Window implements ActionListener, KeyListener{
	
	
	public JFrame frmTriskar;
	private JPanel panelTriskar;
	private JComboBox comboxPort;
	private JButton stopRobot;
	private JButton openPort;
	private JButton closePort;
	private JButton sendMessage;
	private JLabel strLabelVelocity;
	private JTextField strTextVelocity;
	private JLabel straightLabelVelocity;
	private JTextField straightTextVelocity;
	private JLabel angularLabelVelocity;
	private JTextField angularTextVelocity;
	private JLabel maxAngularLabelVelocity;
	private JTextField maxAngularTextVelocity;
	//This variable says the maximum angle for the upper part
	private JLabel upperMaximumAngelLabel;
	private JTextField upperMaximumAngelText;
	//This variable says the speed for the upper part
	private JLabel upperSpeedAngelLabel;
	private JTextField upperSpeedAngelText;
	//This variable says if there is a maximum angle for the platform
	private JLabel maxAngularLabelRestriction;
	private JComboBox comboxAngleRestriction;
	private JLabel accelerationLabel;
	private JComboBox comboxAccelerationLabel;
	
	private SerialCommunication serialCommunication;
	
	public Window(){
		initialize();
		serialCommunication = new SerialCommunication(true);
		panelTriskar = new JPanel();
		panelTriskar.setFocusable(true);
		panelTriskar.addKeyListener(this);
		frmTriskar.addKeyListener(this);
		frmTriskar.setFocusable(true);
		frmTriskar.getContentPane().add(panelTriskar);
		panelTriskar.setLayout(new GridBagLayout());
		GridBagConstraints gbc = new GridBagConstraints( 0, 0, 1, 1, 0, 1, GridBagConstraints.CENTER, GridBagConstraints.NONE, new Insets( 3, 3, 3, 3 ), 0, 0 );
		//-------------
		strLabelVelocity = new JLabel("Strafe Velocity");
		panelTriskar.add(strLabelVelocity, gbc);
		strTextVelocity = new JTextField("0");
		gbc.gridx = 1;
		panelTriskar.add(strTextVelocity, gbc);
		strTextVelocity.setColumns(12);
		//-------------
		gbc.gridy = 1;
		gbc.gridx = 0;
		straightLabelVelocity = new JLabel("Linear Velocity");
		panelTriskar.add(straightLabelVelocity, gbc);
		gbc.gridx =  1;
		straightTextVelocity = new JTextField("500");
		straightTextVelocity.setColumns(12);
		panelTriskar.add(straightTextVelocity, gbc);
		//-------------
		gbc.gridy = 2;
		gbc.gridx = 0;
		angularLabelVelocity = new JLabel("Angular Velocity");
		panelTriskar.add(angularLabelVelocity, gbc);
		gbc.gridx = 1;
		angularTextVelocity = new JTextField("0");
		angularTextVelocity.setColumns(12);
		panelTriskar.add(angularTextVelocity, gbc);
		//--------------
		gbc.gridy = 3;
		gbc.gridx = 0;
		maxAngularLabelRestriction = new JLabel("Angle Restriction");
		panelTriskar.add(maxAngularLabelRestriction, gbc);
		gbc.gridx = 1;
		String t [] = {"Not Apply","Apply"};
		comboxAngleRestriction = new JComboBox(t);
		panelTriskar.add(comboxAngleRestriction, gbc);
		//-------------
		gbc.gridy = 4;
		gbc.gridx = 0;
		maxAngularLabelVelocity = new JLabel("Max Angle");
		panelTriskar.add(maxAngularLabelVelocity,gbc);
		gbc.gridx = 1;
		maxAngularTextVelocity = new JTextField("0");
		maxAngularTextVelocity.setColumns(12);
		panelTriskar.add(maxAngularTextVelocity, gbc);
		//-------------
		gbc.gridy = 5;
		gbc.gridx = 0;
		accelerationLabel = new JLabel("Reach Velocity");
		panelTriskar.add(accelerationLabel,gbc);
		gbc.gridx = 1;
		String temp[] = {"As soon as Possible","At the End"};
		comboxAccelerationLabel = new JComboBox(temp);
		panelTriskar.add(comboxAccelerationLabel, gbc);
		//-------------
		gbc.gridy = 6;
		gbc.gridx = 0;
		upperSpeedAngelLabel = new JLabel("Upper Speed");
		panelTriskar.add(upperSpeedAngelLabel,gbc);
		gbc.gridx = 1;
		upperSpeedAngelText = new JTextField("0");
		upperSpeedAngelText.setColumns(12);
		panelTriskar.add(upperSpeedAngelText,gbc);

		//-------------
		gbc.gridy = 7;
		gbc.gridx = 0;
		upperMaximumAngelLabel = new JLabel("Upper Max Angel");
		panelTriskar.add(upperMaximumAngelLabel,gbc);
		gbc.gridx = 1;
		upperMaximumAngelText = new JTextField("0");
		upperMaximumAngelText.setColumns(12);
		panelTriskar.add(upperMaximumAngelText,gbc);
		//-------------
		gbc.gridy = 8;
		gbc.gridx = 0;
		sendMessage = new JButton("Send Message");
		sendMessage.addActionListener(this);
		sendMessage.setEnabled(false);
		panelTriskar.add(sendMessage, gbc);
		gbc.gridx = 1;
		stopRobot = new JButton("Stop");
		stopRobot.addActionListener(this);
		stopRobot.setEnabled(false);
		panelTriskar.add(stopRobot, gbc);
		//-------------
		gbc.gridy = 9;
		gbc.gridx = 0;
		comboxPort = new JComboBox(SerialCommunication.listPorts());
		panelTriskar.add(comboxPort,gbc);
		gbc.gridx = 1;
		openPort = new JButton("Connect");
		openPort.addActionListener(this);
		openPort.addKeyListener(this);
		panelTriskar.add(openPort, gbc);
		gbc.gridx = 2;
		closePort = new JButton("Disconnect");
		closePort.addActionListener(this);
		closePort.addKeyListener(this);
		closePort.setEnabled(false);
		panelTriskar.add(closePort, gbc);
		
	}
	
	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frmTriskar = new JFrame();
		frmTriskar.setTitle("Triskar");
		frmTriskar.setBounds(100, 100, 627, 532);
		frmTriskar.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		//Window
				EventQueue.invokeLater(new Runnable() {
					public void run() {
						try {
							Window window = new Window();
							window.frmTriskar.setVisible(true);
						} catch (Exception e) {
							e.printStackTrace();
						}
					}
				});
	}

	private void changeStateButtons(boolean state){
		stopRobot.setEnabled(state);
		sendMessage.setEnabled(state);
		closePort.setEnabled(state);
		openPort.setEnabled(!state);
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getActionCommand().compareTo("Send Message")==0){
			String message;
			// r strVelocity straightV AngularVelocity acceleration AngleRestriction MaxAngelRestriction
			message = "r "+Float.parseFloat(strTextVelocity.getText())/1000+
					" "+Float.parseFloat(straightTextVelocity.getText())/1000+
					" "+Float.parseFloat(angularTextVelocity.getText())/1000;
			if(comboxAccelerationLabel.getSelectedItem().toString().compareTo("As soon as Possible")==0){
				message +=" "+0.0;
			}else if(comboxAccelerationLabel.getSelectedItem().toString().compareTo("At the End")==0){
				message +=" "+1.0;				
			}
			message +=" \n";
			serialCommunication.sendMessage(message);
			/*message = "r ";
			if(comboxAngleRestriction.getSelectedItem().toString().compareTo("Not Apply")==0){
				message += " "+-1.0;
			} else {
				message += " "+1.0;
			}
			message += " "+maxAngularTextVelocity.getText();
			message += " "+upperMaximumAngelText.getText();
			message += " "+0.0;
			message += " "+Float.parseFloat(angularTextVelocity.getText())/1000;
			message += " "+upperSpeedAngelText.getText();
			message += "\n";
			serialCommunication.sendMessage(message);*/
		}else if(e.getActionCommand().compareTo("Stop")==0){
			serialCommunication.sendMessage("s \n");
		}else if(e.getActionCommand().compareTo("Connect")==0){
			if(comboxPort.getSize().height>0){
				serialCommunication.setPortName(comboxPort.getSelectedItem().toString().split("-")[0]);
				serialCommunication.connect();
				changeStateButtons(true);
				
			}			
		}else if(e.getActionCommand().compareTo("Disconnect")==0){
			if(serialCommunication.isConnected()){
				serialCommunication.disconnect();
				changeStateButtons(false);
			}
		}
		
	}

	@Override
	public void keyPressed(KeyEvent key) {
		System.out.println(key.getKeyCode());
		if(serialCommunication.isConnected()){
			String message;
			switch (key.getKeyCode()) {
			//left
			case 37:
				message = "r -0.5 0.0 0.0 \n";
				break;
			//fordward	
			case 38:
				message = "r 0.0 0.5 0.0 \n";
				break;
			//right
			case 39:
				message = "r 0.5 0.0 0.0 \n";
				break;
			//back
			case 40:
				message = "r 0.0 -0.5 0.0 \n";
				break;
			//angular left
			case 83:
				message = "r 0.0 0.0 -0.5 \n";
				break;
			//angular right
			case 65:
				message = "r 0.0 0.0 0.5 \n";
				break;
			default:
				message = "s \n";
				break;
			}
			serialCommunication.sendMessage(message);
		}
	}

	@Override
	public void keyReleased(KeyEvent key) {
		if(serialCommunication.isConnected()){
			serialCommunication.sendMessage("s \n");
		}
	}

	@Override
	public void keyTyped(KeyEvent key) {
		
	}
	
}

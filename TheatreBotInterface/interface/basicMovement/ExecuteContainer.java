package basicMovement;

import general.SerialCommunication;
import gnu.io.CommPortIdentifier;

import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.JScrollPane;

import basicMovementController.ExecutionController;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.LinearGradientPaint;
import java.awt.TextArea;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import net.miginfocom.swing.MigLayout;

public class ExecuteContainer extends JPanel{

	/*
	 * Attributes
	 */
	private JScrollPane scrollPane;
	private JPanel panelScrollPane;
	private LineVelocityDraw lineDraw;
	private JComboBox cbxPortSelection;
	private JButton btnExecute;
	private JButton btnAbort;
	private JButton btnSave;
	private JButton btnPrevious;
	private JButton btnCancel;
	private JButton btnAddNewPoint;
	private JButton btnDeleteLastPoint;
	private JButton btnOpenPort;
	private JButton btnClosePort;
	private TextArea observationText;
	private JLabel fileName;
	
	/*
	 * Create the panel.
	 */
	public ExecuteContainer() {
		//setLayout(new MigLayout("",
			//	"[grow][grow][grow][grow]",
			//	"[grow][grow][grow][][grow]"));
		
		setLayout(new BorderLayout());
		
		scrollPane = new JScrollPane();
		panelScrollPane = new JPanel();
		scrollPane.setViewportView(panelScrollPane);
		FlowLayout layoutScroll = new FlowLayout(FlowLayout.CENTER);
		panelScrollPane.setLayout(layoutScroll);
		add(scrollPane, BorderLayout.CENTER);
		
		lineDraw = new LineVelocityDraw();
		add(lineDraw, BorderLayout.NORTH);
		
		JPanel  buttonsPanel = new JPanel();
		buttonsPanel.setLayout(new GridBagLayout());
		GridBagConstraints gbc = new GridBagConstraints( 0, 0, 1, 1, 0, 1, GridBagConstraints.CENTER, GridBagConstraints.NONE, new Insets( 3, 3, 3, 3 ), 0, 0 );
			
		add(buttonsPanel, BorderLayout.SOUTH);
		
			
		cbxPortSelection = new JComboBox(SerialCommunication.listPorts());
		cbxPortSelection.setPreferredSize( new Dimension( 100, 35 ) );
		buttonsPanel.add(cbxPortSelection, gbc);
		

		btnOpenPort = new JButton("Open Port");
		btnOpenPort.setPreferredSize( new Dimension( 100, 35 ) );
		gbc.gridx = 1;
		buttonsPanel.add(btnOpenPort, gbc);
		
		btnClosePort = new JButton("Close Port");
		btnClosePort.setEnabled(false);
		btnClosePort.setPreferredSize( new Dimension( 100, 35 ) );
		gbc.gridx = 2;
		buttonsPanel.add(btnClosePort, gbc);
		
		fileName = new JLabel();
		fileName.setPreferredSize( new Dimension( 150, 35 ) );
		gbc.gridx = 3;
		buttonsPanel.add(fileName,gbc);
		
		btnExecute = new JButton("Execute");
		btnExecute.setPreferredSize( new Dimension( 100, 35 ) );
		btnExecute.setEnabled(false);
		gbc.gridx = 0;
		gbc.gridy = 1;
		buttonsPanel.add(btnExecute,gbc);
		//btnExecute.addActionListener(this);
		
		btnAbort = new JButton("Abort");
		btnAbort.setPreferredSize(new Dimension(100,35));
		btnAbort.setEnabled(false);
		gbc.gridx = 1;
		buttonsPanel.add(btnAbort,gbc);
		
		btnSave = new JButton("Save");
		btnSave.setPreferredSize( new Dimension( 100, 35 ) );
		gbc.gridx = 2;
		buttonsPanel.add(btnSave,gbc);
		
		observationText = new TextArea(6, 30);
		gbc.gridx = 3;
		gbc.gridheight = 3;
		buttonsPanel.add(observationText,gbc);

		gbc.gridheight = 1;
		btnPrevious = new JButton("Previous");
		btnPrevious.setPreferredSize( new Dimension( 100, 35 ) );
		gbc.gridx = 0;
		gbc.gridy = 2;
		buttonsPanel.add(btnPrevious, gbc);
		//btnPrevious.addActionListener(this);
		
		btnAddNewPoint = new JButton("New Point");
		btnAddNewPoint.setPreferredSize( new Dimension( 100, 35 ) );
		gbc.gridx = 1;
		buttonsPanel.add(btnAddNewPoint,gbc);
		
		btnDeleteLastPoint = new JButton("Delete Last Point");
		btnDeleteLastPoint.setPreferredSize( new Dimension( 100, 35 ) );
		gbc.gridx = 2;
		buttonsPanel.add(btnDeleteLastPoint,gbc);
		
		btnCancel = new JButton("Cancel");
		btnCancel.setPreferredSize( new Dimension( 100, 35 ) );
		gbc.gridy = 3;
		gbc.gridx = 1;
		buttonsPanel.add(btnCancel,gbc);
		//btnCancel.addActionListener(this);
	}
	
	
	/*
	 * Methods
	 */
	public void addController(ExecutionController executionController){
		btnExecute.addActionListener(executionController);
		btnSave.addActionListener(executionController);
		btnPrevious.addActionListener(executionController);
		btnCancel.addActionListener(executionController);
		btnAbort.addActionListener(executionController);
		btnAddNewPoint.addActionListener(executionController);
		btnDeleteLastPoint.addActionListener(executionController);
		lineDraw.addController(executionController);
		btnOpenPort.addActionListener(executionController);
		btnClosePort.addActionListener(executionController);
	}
	
	public void generateReferencePoints(int numberOfPoints){
		lineDraw.setNumberOfPoints(numberOfPoints);
	}
	
	public void setPreviousBottonPushable(boolean enable){
		btnPrevious.setEnabled(enable);
	}
	
	
	/**
	 * Return the panel to the basic form
	 */
	public void resetPanel(){
		lineDraw.resetDraw();
		panelScrollPane.removeAll();
	}
	
	public void addInformationPanel(InformationPanel informationPanel){
		panelScrollPane.add(informationPanel);
	}
	
	/*
	 * Gets
	 */
	public TextArea getObservation(){
		return observationText;
	}
	
	public void setObservation(String observation){
		observationText.setText(observation);
	}
	
	public JLabel getFileName(){
		return fileName;
	}
	
	public JButton getBtnAbort(){
		return btnAbort;
	}
	
	public JScrollPane getScrollPane() {
		return scrollPane;
	}
	public LineVelocityDraw getLineDraw() {
		return lineDraw;
	}
	public JButton getBtnExecute() {
		return btnExecute;
	}
	public JButton getBtnSave() {
		return btnSave;
	}
	public JButton getBtnPrevious() {
		return btnPrevious;
	}
	public JButton getBtnCancel() {
		return btnCancel;
	}
	
	public String getPort(){
		return cbxPortSelection.getSelectedItem().toString();
	}
	
	public JButton getBtnDelete(){
		return btnDeleteLastPoint;
	}

	public JButton getBtnOpenPort(){
		return btnOpenPort;
	}
	
	public JButton getBtnClosePort(){
		return btnClosePort;
	}
	
}

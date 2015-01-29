package basicMovementController;

import general.ExecuteBasicMovement;
import general.SendBasicCommands;
import general.SerialCommunication;
import general.WriterXMLBasicMovement;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.security.acl.LastOwnerException;
import java.util.ArrayList;

import javax.swing.JOptionPane;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

import miscellaneous.Rectangle;

import basicMovement.BasicMovementMediator;
import basicMovement.ExecuteContainer;
import basicMovement.InformationPanel;

import trajectory.BasicMovementRepresentation;
import trajectory.PointInformation;

public class ExecutionController implements ActionListener,MouseListener,DocumentListener,
											MouseMotionListener{
	
	/*
	 * Constants
	 */

	/*
	 * Attributes 
	 */
	//Remember that the reference is 1 meter, thus is 1000 mm
	private float basicDistance = 1000;
	//Minimum distance among references point
	private float deltaX=10;
	//these are for allow the save of different profiles, allowing the user to do un do
	private BasicMovementRepresentation currentRepresentation;
	private BasicMovementRepresentation pastRepresentation;
	private boolean hasPastRepresentation = false;
	//This is the graphical interface
	private ExecuteContainer executionContainer;
	//This class mediates among all the jpanel to be shown to the user
	private BasicMovementMediator mediator;
	//These three changes respect to the user selection
	private int numberOfPoints;
	private ArrayList<InformationPanel> informationPanels;
	private ArrayList<PointInformation> pointsInformation;
	private ArrayList<Rectangle> rectangles;
	//This is given by the class that instance this class
	private String[] acceleration;
	//These change when is selected a rectangle
	private boolean isSelectedRectangle;
	private int indexRectangleSelected;
	private String pathToSave;
	private String fileName;
	private WriterXMLBasicMovement writer;
	private SerialCommunication serialCommunication;
	private ExecuteBasicMovement executeBasicMovement;
	private SendBasicCommands sendBasicCommand;
	
	/**
	 * Constructor
	 * @param acceleration, is the array of the current acceleration that the system
	 * can support
	 */
	public ExecutionController(String[] acceleration){
		informationPanels = new ArrayList<InformationPanel>();
		pointsInformation = new ArrayList<PointInformation>();
		rectangles = new ArrayList<Rectangle>();
		this.acceleration = acceleration;
		isSelectedRectangle = false;
		writer = new WriterXMLBasicMovement(pathToSave, pointsInformation,basicDistance);
		serialCommunication = new SerialCommunication(true);
	}
	
	
	
	/*
	 * Methods
	 */
	
	public void setDistance(float distance){
		this.basicDistance = distance;
	}
	
	public float getDistance(){
		return basicDistance;
	}
	
	public void setDeltaX(float deltaX){
		this.deltaX = deltaX;
	}
	
	public void setPathToSave(String pathToSave){
		this.pathToSave = pathToSave;
		writer.setPath(pathToSave);
	}
	
	public void setFileName(String fileName){
		this.fileName = fileName;
		writer.setFileName(fileName);
	}
	
	public void setMediator(BasicMovementMediator mediator){
		this.mediator = mediator;
	}
	
	public void setExecuteContainer(ExecuteContainer executionContainer){
		this.executionContainer = executionContainer;
	}
	
	private void saveInformation(){
		for(int i=0;i<pointsInformation.size();i++){
			updateModel(i);
		}
		//executionContainer.setPreviousBottonPushable(true);
		writer.execute(basicDistance,executionContainer.getObservation().getText());
	}
	
	
	public void generatePanels(){
		hasPastRepresentation = false;
		executionContainer.setPreviousBottonPushable(false);
		currentRepresentation = new BasicMovementRepresentation(this.numberOfPoints);
		currentRepresentation.setDistance(basicDistance);
		executionContainer.setObservation("");
		//Create the panels and send it to the panel
		this.generateReferencePanels();
		//Create the lines and send it to the draw
		this.generateReferencePoints();
		executionContainer.getFileName().setText("File Name: "+fileName);
		if(numberOfPoints<=1){
			executionContainer.getBtnDelete().setEnabled(false);
		} else if (numberOfPoints>1){
			executionContainer.getBtnDelete().setEnabled(true);
		}
		
	}
	
	public void setNumberOfPoints(int numberOfPoints){
		this.numberOfPoints = numberOfPoints;
	}
	
	
	public void doReferencePanels(float distance, int pointNumber, boolean addPanel){
		InformationPanel panel = new InformationPanel(Integer.toString(pointNumber),acceleration);
		panel.setTextDistance(Float.toString(distance));
		panel.setTextVelocity("0");
		if(addPanel){
			executionContainer.addInformationPanel(panel);
		}
		panel.addController(this);
		panel.addMouseListener(this);
		doReferencePointModel(distance, pointNumber, panel.getAcceleration());
		informationPanels.add(panel);
	}
	
	public void generateModel(){
		hasPastRepresentation = false;
		executionContainer.setPreviousBottonPushable(false);
		currentRepresentation = new BasicMovementRepresentation(this.numberOfPoints);
		currentRepresentation.setDistance(basicDistance);
		executionContainer.getFileName().setText("File Name: "+fileName);
		if(numberOfPoints<=1){
			executionContainer.getBtnDelete().setEnabled(false);
		} else if (numberOfPoints>1){
			executionContainer.getBtnDelete().setEnabled(true);
		}
	}
	
	public void setObservation(String Observation){
		executionContainer.getObservation().setText(Observation);
	}
	
	public void doReferencePanels(float distance, int pointNumber, boolean addPanel,
			String velocity, String currentAcceleration, String maxAngularAngle, 
			String isMaxAngularRestriction, String upperSpeed, String upperMaxAngle,
			String angularVelocity){
		InformationPanel panel = new InformationPanel(Integer.toString(pointNumber),this.acceleration);
		panel.setTextDistance(Float.toString(distance));
		panel.setAcelleration(currentAcceleration);
		panel.setTextVelocity(velocity);
		panel.setMaxAngularAngle(maxAngularAngle);
		panel.setIsMaxAngelRestriction(isMaxAngularRestriction);
		panel.setUpperSpeed(upperSpeed);
		panel.setMaxUpperAngel(upperMaxAngle);
		panel.setAngularVelocity(angularVelocity);
		if(addPanel){
			executionContainer.addInformationPanel(panel);
		}
		//public boolean updatePoint(int pointNumber, float distance, float velocity, String reach,
		//float maxAngularAngle, String maxAngularRestriction, float upperSpeed, float upperMaxAngel){
		currentRepresentation.updatePoint(pointNumber, distance, Float.parseFloat(velocity), currentAcceleration,
				Float.parseFloat(maxAngularAngle),isMaxAngularRestriction,Float.parseFloat(upperSpeed),Float.parseFloat(upperMaxAngle),
				Float.parseFloat(angularVelocity));
		panel.addController(this);
		panel.addMouseListener(this);
		doReferencePointModel(distance, pointNumber, panel.getAcceleration());
		informationPanels.add(panel);
	}
	
	private void doReferencePointModel(float distance, int pointNumber, String reach){
		PointInformation point = new PointInformation(pointNumber, distance);
		point.setVelocity(0);
		point.setReach(reach);
		point.setMaxAngularAngle(0);
		point.setIsMaxAngularRestriction("No Apply");
		point.setUpperSpeed(0);
		point.setUpperMaxAngle(0);
		point.setAngularVelocity(0);
		pointsInformation.add(point);
	}
	
	public void generateReferencePanels(){
		float separation = basicDistance/numberOfPoints;
		for(int i=0;i<numberOfPoints;i++){
			doReferencePanels(separation*(i+1),i,true);
		}
	}
	
	/**
	 * This method is used to show where are the current points
	 * @param distance is the distance selected by the user and it is given in millimeters 
	 */
	public void doDrawReferencePoint(float distance){
		Dimension size = executionContainer.getLineDraw().getSize();
		Rectangle rectangle = new Rectangle((float)(size.width*0.05+(size.width-size.width*0.1)*distance/basicDistance), 
				(float)(size.height*0.2), 
				(float)(size.width*0.003), (float)(size.height*0.65));
       rectangles.add(rectangle);
	}
	
	public void addRetangles(){
		executionContainer.getLineDraw().setRectangles(rectangles);
		executionContainer.getLineDraw().repaint();
	}
	
	private void updateReferencePoint(float distance, int index){
		Dimension size = executionContainer.getLineDraw().getSize();
		rectangles.get(index).setX((float)(size.width*0.05+(size.width-size.width*0.1)*distance/basicDistance));
		executionContainer.getLineDraw().repaint();		
	}
	/**
	 * This method generates all the reference points distributed equally in the window
	 * @param numberPoints, is the number of points that should be appear on the window
	 */
	public void generateReferencePoints(){
		float separation = basicDistance/numberOfPoints; 
		for(int i=0;i<numberOfPoints;i++){
			doDrawReferencePoint((i+1)*separation);
		}
		addRetangles();
	}
	
	@Override
	public void actionPerformed(ActionEvent event) {
		if(event.getActionCommand().compareTo("Execute")==0){
			saveInformation();
			hasPastRepresentation = false;
			executionContainer.getBtnAbort().setEnabled(true);
			executionContainer.getBtnExecute().setEnabled(false);
			sendBasicCommand
			= new SendBasicCommands(pointsInformation,serialCommunication);
			//TODO unable possible modifications while the robot is executing
			//executeBasicMovement 
			//= new ExecuteBasicMovement(pointsInformation,serialCommunication);
			//Thread thread = new Thread(executeBasicMovement);
			Thread thread = new Thread(sendBasicCommand);
			thread.start();
			//Execute class
		} else if(event.getActionCommand().compareTo("Abort")==0){
			//executeBasicMovement.abort(true);
			sendBasicCommand.stop();
			sendBasicCommand.abort(true);
			executionContainer.getBtnAbort().setEnabled(false);
			executionContainer.getBtnExecute().setEnabled(true);
		} else if(event.getActionCommand().compareTo("Previous")==0){
			currentRepresentation = pastRepresentation;
			hasPastRepresentation = false;
			//Update graphical interface
			/*
			 * This is the difficult part, because in order to generate all the points that were before
			 * it should be generated new panels and assigned to the previous view.
			 */
		} else if(event.getActionCommand().compareTo("Cancel")==0){
			executionContainer.resetPanel();
			rectangles.clear();
			informationPanels.clear();
			pointsInformation.clear();
			mediator.showOptionsMenu();
			if(serialCommunication.isConnected()){
				serialCommunication.close();
			}
			executionContainer.getBtnExecute().setEnabled(false);
			executionContainer.getBtnOpenPort().setEnabled(true);
			executionContainer.getBtnClosePort().setEnabled(false);
			executionContainer.getBtnAbort().setEnabled(false);
		} else if(event.getActionCommand().compareTo("Save")==0){
			saveInformation();
			hasPastRepresentation = true;
		} else if(event.getActionCommand().compareTo("New Point")==0){
			//Add a new point in the last position and repaint everything
			addNewPoint();
		} else if(event.getActionCommand().compareTo("Delete Last Point")==0){
			//Delete the last point and repaint everything
			if(numberOfPoints>1){
				deletePoint();
			}
		} else if(event.getActionCommand().compareTo("Open Port") == 0){
			serialCommunication.setPortName(executionContainer.getPort().split("-")[0]);
			serialCommunication.connect();
			if(serialCommunication.isConnected()){
				executionContainer.getBtnExecute().setEnabled(true);
				executionContainer.getBtnOpenPort().setEnabled(false);
				executionContainer.getBtnClosePort().setEnabled(true);
			}
			
		} else if(event.getActionCommand().compareTo("Close Port")==0){
			serialCommunication.close();
			executionContainer.getBtnExecute().setEnabled(false);
			executionContainer.getBtnAbort().setEnabled(false);
			executionContainer.getBtnOpenPort().setEnabled(true);
			executionContainer.getBtnClosePort().setEnabled(false);
		}
		
	}
	
	private void addNewPoint(){
		executionContainer.resetPanel();
		numberOfPoints++;
		doDrawReferencePoint(basicDistance);
		doReferencePanels(basicDistance,numberOfPoints-1,false);
		//TODO implement the previous system
		currentRepresentation.addPoint(numberOfPoints, basicDistance);
		for(int i = 0;i<informationPanels.size();i++){
			executionContainer.addInformationPanel(informationPanels.get(i));
		}
		if(numberOfPoints<=1){
			executionContainer.getBtnDelete().setEnabled(false);
		} else if (numberOfPoints>1){
			executionContainer.getBtnDelete().setEnabled(true);
		}
		executionContainer.getScrollPane().updateUI();		
	}
	
	private void deletePoint(){
		executionContainer.resetPanel();
		numberOfPoints--;
		rectangles.remove(numberOfPoints);
		informationPanels.remove(numberOfPoints);
		pointsInformation.remove(numberOfPoints);
		//TODO implement the previous system
		currentRepresentation.removeLastPoint();
		for(int i = 0;i<informationPanels.size();i++){
			executionContainer.addInformationPanel(informationPanels.get(i));
		}
		if(numberOfPoints<=1){
			executionContainer.getBtnDelete().setEnabled(false);
		} else if (numberOfPoints>1){
			executionContainer.getBtnDelete().setEnabled(true);
		}
		executionContainer.getScrollPane().updateUI();
	}
	
	private boolean isSelectedARectangle(int x, int y){
		for(int i=0;i<rectangles.size();i++){
			if(rectangles.get(i).isInside(x, y)){
				indexRectangleSelected = i;
				isSelectedRectangle = true;
				updateRectangle(i,true);
				changePanelColor();
				return true;				
			}
		}
		return false;
	}
	
	private void changePanelColor(){
		if(isSelectedRectangle){
			informationPanels.get(indexRectangleSelected).setBackground(Color.gray);
		}else{
			informationPanels.get(indexRectangleSelected).setBackground(new Color(238,238,238));
		}
	}

	@Override
	public void mouseClicked(MouseEvent event) {	
	}

	@Override
	public void mouseEntered(MouseEvent event) {
		if(event.getSource().getClass().getSimpleName().compareTo("InformationPanel")==0){
			InformationPanel infoTemp = (InformationPanel) event.getSource();
			updateRectangle(Integer.parseInt(infoTemp.getPointNumber()), true);
		}
	}

	@Override
	public void mouseExited(MouseEvent event) {
		//TODO resolver problems when the mouse is passing by a panel, the problem comes up when is passing above the text fields and combbox
		if(event.getSource().getClass().getSimpleName().compareTo("InformationPanel")==0){
			InformationPanel infoTemp = (InformationPanel) event.getSource();
			updateRectangle(Integer.parseInt(infoTemp.getPointNumber()), false);
		}
	}

	@Override
	public void mousePressed(MouseEvent event) {
		if(event.getComponent().getClass().getSimpleName().compareTo("LineVelocityDraw")==0){
			isSelectedARectangle(event.getX(), event.getY());
		}
	}

	@Override
	public void mouseReleased(MouseEvent event) {
		if(isSelectedRectangle){
			isSelectedRectangle = false;
			updateRectangle(indexRectangleSelected, false);
			changePanelColor();
		}
	}
	
	/**
	 * This method upgrade the rectangle selected state
	 * @param index, position of the array
	 * @param state, if is selected or not
	 */
	private void updateRectangle(int index, boolean state){
		rectangles.get(index).setIsSelected(state);
		executionContainer.getLineDraw().repaint();		
	}

	/*
	 * (non-Javadoc)
	 * This is the document event, which give information when a value of the distance is change 
	 */
	@Override
	public void changedUpdate(DocumentEvent e) {		
	}

	@Override
	public void insertUpdate(DocumentEvent e) {
		updateGraphicalInterface(e);
	}

	@Override
	public void removeUpdate(DocumentEvent e) {
		updateGraphicalInterface(e);
	}
	
	/**
	 * This method get the information from the distance text field and upgrade the graphical interface
	 * @param e
	 */
	private void updateGraphicalInterface(DocumentEvent e){
		String property = e.getDocument().getProperty("name").toString();
		int index = Integer.parseInt(property.split("-")[1]);	
		if(property.contains("distance")){
			String text = informationPanels.get(index).getTextDistance();
		if(text.isEmpty()||isSelectedRectangle){
			
		}else if(isInteger(text)&&!isSelectedRectangle){
				Float distance = Float.parseFloat(text);
				updateReferencePoint(distance,index);
				updateModel(index);
				//TODO return to the previous value when the people write an non correct value
			}else{
				//TODO delete the character
			    JOptionPane.showMessageDialog(null,
			    	          "Error: Please enter number", "Error Massage",
			    	          JOptionPane.ERROR_MESSAGE);
			}
		}	
	}
	
	private void updateModel(int index){
		InformationPanel panel = informationPanels.get(index);
		PointInformation point = pointsInformation.get(index);
		point.setDistance(Float.parseFloat(panel.getTextDistance()));
		point.setVelocity(Float.parseFloat(panel.getTextVelocity()));
		point.setReach(panel.getAcceleration());
		point.setMaxAngularAngle(Float.parseFloat(panel.getMaxAngularAngle()));
		point.setIsMaxAngularRestriction(panel.getIsMaxAngelRestriction());
		point.setUpperSpeed(Float.parseFloat(panel.getUpperSpeed()));
		point.setAngularVelocity(Float.parseFloat(panel.getAngularVelocity()));
		point.setUpperMaxAngle(Float.parseFloat(panel.getMaxUpperAngel()));
	}
	
	public static boolean isInteger(String s) {
	    try { 
	        Float.parseFloat(s); 
	    } catch(NumberFormatException e) { 
	        return false; 
	    }
	    // only got here if we didn't return false
	    return true;
	}

	@Override
	public void mouseDragged(MouseEvent event) {
		Dimension size = executionContainer.getLineDraw().getSize();
		//TODO implement a mechanism that not allow the person to move further a reference point with a lower index
		if(isSelectedRectangle&&size.width*0.05<=event.getX()
				&&(size.width-size.width*0.05)>=event.getX()/*&&verifyConditions(indexRectangleSelected)*/){
			rectangles.get(indexRectangleSelected).setX((float)event.getX());
			executionContainer.getLineDraw().repaint();		
			float distance = (float)((((float)event.getX())-((float)size.width*0.05))/(size.width*0.9)*basicDistance);
			informationPanels.get(indexRectangleSelected).setTextDistance(Float.toString(distance));
			updateModel(indexRectangleSelected);
		}
	}

	@Override
	public void mouseMoved(MouseEvent event) {
		// TODO Auto-generated method stub
		
	}
}

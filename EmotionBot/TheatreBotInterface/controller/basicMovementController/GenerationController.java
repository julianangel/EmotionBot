package basicMovementController;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Calendar;

import javax.swing.JOptionPane;

import basicMovement.BasicMovementMediator;
import basicMovement.Generation;

public class GenerationController implements ActionListener{


	private BasicMovementMediator mediator;
	private Generation generator;
	private int numberOfPoints = 0;
	private String emotion = null; 
	private String folderToSave = "SaveProfileFiles";
	private String folderPath = null;
	private String fileName = null;
	private ExecutionController executionController = null;
	
	@Override
	public void actionPerformed(ActionEvent event) {
		if(event.getActionCommand().compareTo("Create")==0){
			//Check that the name field is not empty
			if(generator.getTextFieldName().getText().isEmpty()||generator.getTextFieldName().getText().contains(" ")){
				JOptionPane.showMessageDialog(generator,
					    "It should hava a name nor containt spaces",
					    "Inane warning",
					    JOptionPane.WARNING_MESSAGE);
			} else{
				//get information and used it to generate the next window, and send the panels to the next window
				numberOfPoints = new Integer(generator.getComboBoxPoints().getSelectedItem().toString());
				emotion = generator.getComboBoxEmotions().getSelectedItem().toString();
				Calendar now = Calendar.getInstance();
				String folder = Integer.toString(now.get(Calendar.YEAR));
				folder += Integer.toString(now.get(Calendar.MONTH));
				folder += Integer.toString(now.get(Calendar.DAY_OF_MONTH));
				folderPath = folderToSave+"/"+folder+"/"+generator.getComboBoxEmotions().getSelectedItem().toString();
				/*
				*Modify the execution controller parameters
				*/
				//Set points 
				executionController.setNumberOfPoints(numberOfPoints);
				executionController.setPathToSave(folderPath);
				executionController.setFileName(generator.getTextFieldName().getText());
				executionController.generatePanels();
				
				//Generate model of the points
				//call mediator to show the other window
				this.mediator.showExecution();
				//Resets the panel for further calls
				generator.resetPanel();
			}
		}else if(event.getActionCommand().compareTo("Cancel")==0){
			generator.resetPanel();
			this.mediator.showOptionsMenu();
		}		
	}

	public void addExecutionController(ExecutionController executionController){
		this.executionController = executionController;
	}
	
	public void setBasicMovementMediator(BasicMovementMediator mediator){
		this.mediator = mediator;
	}
	
	public void setGeneration(Generation generator){
		this.generator = generator;
	}
}

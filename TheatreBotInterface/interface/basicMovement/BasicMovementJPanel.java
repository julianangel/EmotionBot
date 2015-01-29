package basicMovement;

import javax.swing.JPanel;
import java.awt.CardLayout;
import java.awt.Color;
import java.io.File;
import java.io.IOException;

import javax.swing.border.TitledBorder;
import javax.swing.UIManager;

import basicMovementController.ExecutionController;
import basicMovementController.GenerationController;

public class BasicMovementJPanel extends JPanel{

	BasicMovementOptions basicOptions;
	Generation generation;
	BasicMovementMediator mediator;
	ExecuteContainer executeContainer;
	CardLayout layout;
	/**
	 * Create the panel.
	 * This panel contains all the other panels that are used for generation, modification and elimination of 
	 * basic movements. The basic movements consist of a straight trajectory, which contain different velocities and acellerations.
	 */
	public BasicMovementJPanel(String[] acceleration,String[] emotions, float distance) {
		setBorder(new TitledBorder(UIManager.getBorder("TitledBorder.border"), "Basic Movements", TitledBorder.LEADING, TitledBorder.TOP, null, Color.BLACK));
		layout = new CardLayout();
		GenerationController generationController = new GenerationController();
		ExecutionController executionController = new ExecutionController(acceleration);
		executionController.setDistance(distance);
		//Mediator
		mediator = new BasicMovementMediator();
		mediator.layoutRegistration(layout);
		mediator.jpanelRegistretion(this);
		generationController.setBasicMovementMediator(mediator);
		executionController.setMediator(mediator);
		setLayout(layout);
		//Options Pane
		basicOptions = new BasicMovementOptions(mediator,executionController);
		this.add(basicOptions,"a");
		basicOptions.setVisible(false);
		//Generation Pane
		generation = new Generation(mediator, emotions);
		this.add(generation,"b");
		generation.setVisible(false);
		//It add a controller for this panel
		generationController.setGeneration(generation);
		generation.addController(generationController);
		//Execute Pane
		executeContainer = new ExecuteContainer();
		this.add(executeContainer,"c");
		executeContainer.setVisible(false);
		executionController.setExecuteContainer(executeContainer);
		executeContainer.addController(executionController);
		generationController.addExecutionController(executionController);
		//Show the first JPanel
		layout.show(this, "generation");
	}
}

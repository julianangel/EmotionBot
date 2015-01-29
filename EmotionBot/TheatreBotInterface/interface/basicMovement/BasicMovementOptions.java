package basicMovement;

import general.ReaderXMLBasicMovement;

import javax.swing.JFileChooser;
import javax.swing.JPanel;
import javax.swing.SpringLayout;

import java.awt.GridBagLayout;
import java.awt.FlowLayout;
import javax.swing.JButton;

import basicMovementController.ExecutionController;

import java.awt.CardLayout;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;


public class BasicMovementOptions extends JPanel implements ActionListener{

	
	private String infoPath = "./saveProfileFiles";
	private BasicMovementMediator mediator;
	private ExecutionController executionController;
	/**
	 * Create the panel.
	 * This panel contains all the possible options that could be done for basic movements.
	 * 
	 */
	public BasicMovementOptions(BasicMovementMediator mediator, ExecutionController executionController) {
		this.executionController = executionController;
		//setLayout(new GridLayout(3, 1, 60, 60));
		setLayout(new GridBagLayout());
		 GridBagConstraints gbc = new GridBagConstraints( 0, 0, 1, 1, 0, 1, GridBagConstraints.CENTER, GridBagConstraints.NONE, new Insets( 3, 3, 3, 3 ), 0, 0 );
		
		this.mediator = mediator;
		
		JButton btnGenerate = new JButton("Generate");
		btnGenerate.addActionListener(this);
		btnGenerate.setPreferredSize( new Dimension( 180, 60 ) );
		btnGenerate.setFont(new Font(Font.DIALOG, Font.PLAIN, 20));
		add(btnGenerate, gbc);
		gbc.gridy=1;
		JButton btnModify = new JButton("Modify");
		btnModify.addActionListener(this);
		btnModify.setPreferredSize( new Dimension( 180, 60 ) );
		btnModify.setFont(new Font(Font.DIALOG, Font.PLAIN, 20));
		add(btnModify,gbc);
		gbc.gridy=2;
		JButton btnDelete = new JButton("Delete");
		btnDelete.addActionListener(this);
		btnDelete.setPreferredSize( new Dimension( 180, 60 ) );
		btnDelete.setFont(new Font(Font.DIALOG, Font.PLAIN, 20));
		add(btnDelete,gbc);
		

	}

	@Override
	public void actionPerformed(ActionEvent event) {
		if(event.getActionCommand().compareTo("Generate")==0){
			mediator.showGenerationFirstMenu();
		}else if(event.getActionCommand().compareTo("Modify")==0){
            JFileChooser fc = new JFileChooser( infoPath );
            fc.setDialogTitle( "Open Profile" );
            fc.setFileSelectionMode( JFileChooser.FILES_ONLY );
            fc.setMultiSelectionEnabled( false ); int resultado = fc.showSaveDialog( this );

            if( resultado == JFileChooser.APPROVE_OPTION )
            {
                File seleccionado = fc.getSelectedFile();
                infoPath = seleccionado.getParentFile().getAbsolutePath();
                executionController.setPathToSave(seleccionado.getParentFile().getAbsolutePath());
                executionController.setFileName(seleccionado.getName().split(".xml")[0]);
                ReaderXMLBasicMovement reader = 
                new ReaderXMLBasicMovement(seleccionado.getAbsolutePath(), executionController);
                reader.readFile();
                mediator.showExecution();
            }			
		}else if(event.getActionCommand().compareTo("Delete")==0){
			System.out.println("Delete");
		}
	}

}

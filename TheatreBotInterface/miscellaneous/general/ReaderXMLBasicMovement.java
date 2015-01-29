package general;

import java.io.File;
import java.io.IOException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import basicMovementController.ExecutionController;

public class ReaderXMLBasicMovement {

	private String file;
	private ExecutionController executionController;
	
	public ReaderXMLBasicMovement(String file, ExecutionController executionController){
		this.executionController = executionController;
		this.file = file;
	}
	
	public void readFile(){
		try {
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder dBuilder;
			dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(new File(file));
			doc.getDocumentElement().normalize();
			//Get the distance in which this model was created
			float basicDistance = Float.parseFloat(doc.getDocumentElement().getAttribute("distance"));
			NodeList obsevation = doc.getElementsByTagName("observation");
			for(int i=0;i<obsevation.getLength();i++){
				Node node = obsevation.item(i);
				if(node.getNodeType()==Node.ELEMENT_NODE){
					executionController.setObservation(((Element) node).getTextContent());
				}
			}
			executionController.setDistance(basicDistance);
			//Get the nodes, which each node is a panel
			NodeList listOfEmotions = doc.getElementsByTagName("panel");
			executionController.setNumberOfPoints(listOfEmotions.getLength());
			executionController.generateModel();
			for(int i=0;i<listOfEmotions.getLength();i++){
				Node node = listOfEmotions.item(i);
				if(node.getNodeType()==Node.ELEMENT_NODE){
					//(float distance, int pointNumber, boolean addPanel,
					//String velocity, String currentAcceleration, 
					//String maxAngularAngle, String maxAngularRestriction, String upperSpeed, String upperMaxAngel)
					executionController.doReferencePanels(
							
							Float.parseFloat(((Element) node).getElementsByTagName("distance").item(0).getTextContent()), 
							Integer.parseInt(((Element) node).getAttribute("id").toString()), true, 
							((Element) node).getElementsByTagName("velocity").item(0).getTextContent(), 
							((Element) node).getElementsByTagName("acceleration").item(0).getTextContent(),
							(((Element) node).getElementsByTagName("maxAngularAngel").item(0)!=null?
									((Element) node).getElementsByTagName("maxAngularAngel").item(0).getTextContent():"0"),
							(((Element) node).getElementsByTagName("angularRestriction").item(0)!=null?
									((Element) node).getElementsByTagName("angularRestriction").item(0).getTextContent():"0"),
							(((Element) node).getElementsByTagName("upperSpeed").item(0)!=null?
									((Element) node).getElementsByTagName("upperSpeed").item(0).getTextContent():"0"),
							(((Element) node).getElementsByTagName("upperAngel").item(0)!=null?
									((Element) node).getElementsByTagName("upperAngel").item(0).getTextContent():"0"),
							(((Element) node).getElementsByTagName("angularVelocity").item(0)!=null?
									((Element) node).getElementsByTagName("angularVelocity").item(0).getTextContent():"0")
									);
					executionController.doDrawReferencePoint(
							Float.parseFloat(((Element) node).getElementsByTagName("distance").item(0).getTextContent()));
				}
			}
			executionController.addRetangles();
		} catch (ParserConfigurationException | SAXException | IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	
	public String getFilePath(){
		return file;
	}
	
	public void setFilePath(String filePath){
		this.file = filePath;
	}
	
}

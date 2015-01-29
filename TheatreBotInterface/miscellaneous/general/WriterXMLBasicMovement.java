package general;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import trajectory.PointInformation;

import basicMovement.InformationPanel;

public class WriterXMLBasicMovement {

	/*
	 * Attributes
	 */
	private String folderPath = null;
	private String fileName;
	private ArrayList<PointInformation> pointsInformation;
	private float basicDistance;
	
	public WriterXMLBasicMovement(String folderPath,ArrayList<PointInformation> pointsInformation,
			float basicDistance){
		this.folderPath = folderPath;
		this.pointsInformation = pointsInformation;
		this.basicDistance = basicDistance;
	}
	
	public void execute(float basicDistance, String textObservation){
		try {
			DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
			Document doc = docBuilder.newDocument();
			Element rootElement = doc.createElement("profile");
			doc.appendChild(rootElement);
			rootElement.setAttribute("distance", Float.toString(basicDistance));
			//Generate Info for each panel
			Iterator<PointInformation> iterator = pointsInformation.iterator();
			while(iterator.hasNext()){
				PointInformation currentPoint = iterator.next();
				Element panel =  doc.createElement("panel");
				rootElement.appendChild(panel);
				
				//Set attribute of the panel (number of the panel)
				panel.setAttribute("id",currentPoint.getPointNumber());
				
				//Add elements
				//distance
				Element distance = doc.createElement("distance");
				distance.appendChild(doc.createTextNode(currentPoint.getDistanceString()));
				panel.appendChild(distance);
				//velocity
				Element velocity = doc.createElement("velocity");
				velocity.appendChild(doc.createTextNode(currentPoint.getVelocityString()));
				panel.appendChild(velocity);
				//acceleration
				Element acceleration = doc.createElement("acceleration");
				acceleration.appendChild(doc.createTextNode(currentPoint.getReach()));
				panel.appendChild(acceleration);
				//maxAngularAngel
				Element maxAngularAngel = doc.createElement("maxAngularAngel");
				maxAngularAngel.appendChild(doc.createTextNode(currentPoint.getMaxAngularAngleString()));
				panel.appendChild(maxAngularAngel);
				//angularRestriction
				Element angularRestriction = doc.createElement("angularRestriction");
				angularRestriction.appendChild(doc.createTextNode(currentPoint.getIsMaxAngularRestriction()));
				panel.appendChild(angularRestriction);
				//angularVelocity
				Element angularVelocity = doc.createElement("angularVelocity");
				angularVelocity.appendChild(doc.createTextNode(currentPoint.getAngularVelocityString()));
				panel.appendChild(angularVelocity);
				//upperSpeed
				Element upperSpeed = doc.createElement("upperSpeed");
				upperSpeed.appendChild(doc.createTextNode(currentPoint.getUpperSpeedString()));
				panel.appendChild(upperSpeed);
				//upperAngel
				Element upperAngel = doc.createElement("upperAngel");
				upperAngel.appendChild(doc.createTextNode(currentPoint.getUpperMaxAngleString()));
				panel.appendChild(upperAngel);
			}
			//Observation
			Element observation = doc.createElement("observation");
			observation.appendChild(doc.createTextNode(textObservation));
			rootElement.appendChild(observation);
			//Write the content in XML file
			TransformerFactory transformerFactory = TransformerFactory.newInstance();
			Transformer transformer = transformerFactory.newTransformer();
			DOMSource source = new DOMSource(doc);
			System.out.println(folderPath+"/"+fileName+".xml");
			File file = new File(folderPath);
			if(!file.exists()){
				file.mkdirs();
			}
			StreamResult result = new StreamResult(new File(folderPath)+"/"+fileName+".xml");
			transformer.transform(source, result);
			System.out.println("File saved!");
		} catch (ParserConfigurationException | TransformerException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void setPath(String path){
		this.folderPath = path;
	}
	
	public void setFileName(String fileName){
		this.fileName = fileName;
	}
}

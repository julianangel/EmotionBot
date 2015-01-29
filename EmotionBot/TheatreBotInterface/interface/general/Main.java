package general;

import java.awt.EventQueue;
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

public class Main {

	/*
	 * Attributes
	 */
	 //route to the emotions file description
	private static String emotionFileRoute = "./configurationFiles/Emotions.xml";
	//route to the acceleration file description
	private static String accelerationFileDescription = "./configurationFiles/AccelerationDescription.xml";
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		//Load Information
		//Additional information that should be loaded from files
		final String[] emotions = getEmotions();
		final String[] acceleration = getAcceleration();
		//Models
		//Window
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					PrincipalWindow window = new PrincipalWindow(acceleration,emotions);
					window.frmTheatrebot.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
		
	}
	
	/*
	 * Methods
	 */
	
	private static String[] getAcceleration(){
		String[] acceleration;
		try {
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder dBuilder;
			dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(new File(accelerationFileDescription));
			NodeList listOfAcceleration = doc.getElementsByTagName("accelerationDescription");
			acceleration = new String[listOfAcceleration.getLength()];
			int j=0;
			for(int i=0;i<listOfAcceleration.getLength();i++){
				Node node = listOfAcceleration.item(i);
				if(node.getNodeType()==Node.ELEMENT_NODE){
					acceleration[j] = ((Element) node).getElementsByTagName("name").item(0).getTextContent();
							j++;
				}
			}
			return acceleration;
		} catch (ParserConfigurationException | SAXException | IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;
	}
	
	/**
	 * This method read the file with the emotions
	 * @return an array with all the emotions read it in the file
	 */
	private static String[] getEmotions(){ 
		String [] emotions;
		try {
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder dBuilder;
			dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(new File(emotionFileRoute));
			NodeList listOfEmotions = doc.getElementsByTagName("emotion");
			emotions = new String[listOfEmotions.getLength()];
			int j=0;
			for(int i=0;i<listOfEmotions.getLength();i++){
				Node node = listOfEmotions.item(i);
				if(node.getNodeType()==Node.ELEMENT_NODE){
					emotions[j] = ((Element) node).getElementsByTagName("name").item(0).getTextContent();
							j++;
				}
			}
			return emotions;
		} catch (ParserConfigurationException | SAXException | IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return null;
	}

}

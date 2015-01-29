package general;

import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Iterator;

import trajectory.PointInformation;
import acceleration.AsSoonAsPossible;
import acceleration.AtTheEnd;
import acceleration.DistanceBaseAcceleration;
import acceleration.InTheMiddle;

public class SendBasicCommands implements Runnable {	/*
	 * Attributes
	 */
	
	//these attributes are for one window specification
	private float initialDistance;
	private float initialVelocity;
	private float angularInitialVelocity;
	private ArrayList<PointInformation> pointsInformation;
	private SerialCommunication serialCommunication;
	private boolean abort = false;
	
	public SendBasicCommands(ArrayList<PointInformation> pointsInformation,
			SerialCommunication serialCommunication){
		this.pointsInformation = pointsInformation;
		this.serialCommunication = serialCommunication;
	}
	
	public void stop(){
		serialCommunication.sendMessage("s \n");
	}
	
	public void execute(){
		Iterator<PointInformation> pointInformationIterator = pointsInformation.iterator();
		initialDistance = 0;
		initialVelocity = 0;
		angularInitialVelocity = 0;
		String message = "rp "+ pointsInformation.size()+" \n";
		serialCommunication.sendMessage(message);
		//moves around the all array and convert it to the acceleration class
		while(pointInformationIterator.hasNext()&&!abort){
			PointInformation pointTemp = pointInformationIterator.next();
			//Generate classes for each acceleration
			/*
			 * Message format
			 * p initialDistance finalDistance initialVelocity finalVelocity 
			 * typeOfAcceleration isAngularRestriction maxAngularRestrictionw
			 * initialAngularVelicity finalAngularVelocity
			 *  maxUpperAngel upperPosition->(origanally it was upperSpeed what was not longer used,
			 *  this new one controls the position of the "head")
			 */
			message = "p "+(initialDistance/1000.0)+" "+
			 (pointTemp.getDistanceFloat()/1000.0)+
					" "+(initialVelocity/1000.0)+" "+
					(pointTemp.getVelocityFloat()/1000.0);
			System.out.println(pointTemp.getVelocityFloat()/1000.0);
			if(pointTemp.getReach().compareTo("As soon as Possible")==0){
				message +=" "+0.0+" \n";
			}else if(pointTemp.getReach().compareTo("At the End")==0){
				message +=" "+1.0+" \n";				
			}
			serialCommunication.sendMessage(message);
			message = "p ";
			if(pointTemp.getIsMaxAngularRestriction().compareTo("Not Apply")==0){
				message += " "+-1.0;
			}else{
				message += " "+1.0;
			}
			message += " "+pointTemp.getMaxAngularAngle();
			message += " "+pointTemp.getUpperMaxAngle();
			message += " "+(angularInitialVelocity/1000.0);
			message += " "+(pointTemp.getAngularVelocity()/1000.0);
			message += " "+pointTemp.getUpperSpeed();
			message += " \n";
			serialCommunication.sendMessage(message);
			initialDistance = pointTemp.getDistanceFloat();
			initialVelocity = pointTemp.getVelocityFloat();
			angularInitialVelocity = pointTemp.getAngularVelocity();
		}
	}	
	
	
	public void abort(boolean abort){
		this.abort = true;
	}

	@Override
	public void run() {
		this.execute();		
	}

}

package general;

import java.util.ArrayList;
import java.util.Iterator;

import acceleration.AsSoonAsPossible;
import acceleration.AtTheEnd;
import acceleration.DistanceBaseAcceleration;
import acceleration.InTheMiddle;

import trajectory.PointInformation;

public class ExecuteBasicMovement implements Runnable{

	/*
	 * Attributes
	 */
	
	//these attributes are for one window specification
	private float initialDistance;
	private float initialVelocity;
	private ArrayList<PointInformation> pointsInformation;
	private SerialCommunication serialCommunication;
	private boolean abort = false;
	
	public ExecuteBasicMovement(ArrayList<PointInformation> pointsInformation,
			SerialCommunication serialCommunication){
		this.pointsInformation = pointsInformation;
		this.serialCommunication = serialCommunication;
	}
	
	
	public void execute(){
		//Get the list of acceleration class
		ArrayList<DistanceBaseAcceleration> accelerations = generateAcceleration();
		//Get the iterator to move around the list of accelerations
		Iterator<DistanceBaseAcceleration> distanceAcceleration = accelerations.iterator();
		//distance that the robot has moved
		float currentDistance = 0;
		float baseDistance = 0;
		long baseTimet = (System.currentTimeMillis());
		//move until there is not more components
		while(distanceAcceleration.hasNext()&&!abort){
			//Get the current object
			DistanceBaseAcceleration acceleration = distanceAcceleration.next();
			//While the distance of the current part has not been traveled by the robot
			while(currentDistance<=acceleration.getFinalDistance()&&!abort){
				//get the desire velocity
				float desireVelocity = 
						acceleration.calculateSpeedFromDistance(currentDistance-acceleration.getInitialDistance());
				//get base time
				long baseTime = (System.currentTimeMillis());
				baseDistance = currentDistance;
				while(currentDistance<=(baseDistance+acceleration.getResolution())&&!abort){
					String message = "r 0.0 "+Float.toString(desireVelocity/1000)+" 0.0\n";
					serialCommunication.sendMessage(message);
					//get current time
					//get time difference and calculate current distance
					long currentTime = ( System.currentTimeMillis());
					currentDistance+=acceleration.calculateTravelDistance(baseTime, currentTime);
					baseTime = currentTime;
					//System.out.println(currentDistance+"--"+desireVelocity);
				}
				//System.out.println(currentDistance+"-->"+desireVelocity);
			}
		}
		serialCommunication.sendMessage("s");
		System.out.println(System.currentTimeMillis()-baseTimet);
	}
	
	private ArrayList<DistanceBaseAcceleration> generateAcceleration(){
		ArrayList<DistanceBaseAcceleration> accelerations = new ArrayList<DistanceBaseAcceleration>();
		//go through each point and generate its acceleration system
		Iterator<PointInformation> pointInformationIterator = pointsInformation.iterator();
		initialDistance = 0;
		initialVelocity = 0;
		//moves around the all array and convert it to the acceleration class
		while(pointInformationIterator.hasNext()){
			PointInformation pointTemp = pointInformationIterator.next();
			//Generate classes for each acceleration
			if(pointTemp.getReach().compareTo("As soon as Possible")==0){
				accelerations.add(new AsSoonAsPossible(initialDistance, pointTemp.getDistanceFloat(), 
						initialVelocity, pointTemp.getVelocityFloat()));
			}else if(pointTemp.getReach().compareTo("At the End")==0){
				accelerations.add(new AtTheEnd(initialDistance,  pointTemp.getDistanceFloat(), 
						initialVelocity, pointTemp.getVelocityFloat()));
			}else if(pointTemp.getReach().compareTo("In the Middle")==0){
				accelerations.add(new InTheMiddle(initialDistance,  pointTemp.getDistanceFloat(), 
						initialVelocity, pointTemp.getVelocityFloat()));
			}
			initialDistance = pointTemp.getDistanceFloat();
			initialVelocity = pointTemp.getVelocityFloat();
		}
		return accelerations;

	}

	public void abort(boolean abort){
		this.abort = true;
	}

	@Override
	public void run() {
		this.execute();		
	}
	
}

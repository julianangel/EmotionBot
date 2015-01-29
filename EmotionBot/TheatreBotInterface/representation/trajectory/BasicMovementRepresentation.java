package trajectory;

import java.util.ArrayList;

public class BasicMovementRepresentation implements Cloneable {

	/*
	 * Constants
	 */
	
	
	
	/*
	 * Attributes
	 */
	private float basicDistance = 1000;
	private int numberOfPoints = 0;
	private ArrayList<PointInformation> informationPoints;
	
	
	public BasicMovementRepresentation(int numberOfPoints){
		this.numberOfPoints = numberOfPoints;
		informationPoints = new ArrayList<PointInformation>();
		for(int i=0;i<this.numberOfPoints;i++){
			float separation = basicDistance/numberOfPoints;
			informationPoints.add(new PointInformation(i,i*separation));
		}
	}
	
	/*
	 * Methods
	 */
	public boolean updatePoint(int pointNumber, float distance, float velocity, String reach,
			float maxAngularAngle, String isMaxAngularRestriction, float upperSpeed, float upperMaxAngle
			,float angularVelocity){
		if(pointNumber<numberOfPoints){
			informationPoints.get(pointNumber).setDistance(distance);
			informationPoints.get(pointNumber).setVelocity(velocity);
			informationPoints.get(pointNumber).setReach(reach);
			informationPoints.get(pointNumber).setMaxAngularAngle(maxAngularAngle);
			informationPoints.get(pointNumber).setIsMaxAngularRestriction(isMaxAngularRestriction);
			informationPoints.get(pointNumber).setUpperSpeed(upperSpeed);
			informationPoints.get(pointNumber).setUpperMaxAngle(upperMaxAngle);
			informationPoints.get(pointNumber).setAngularVelocity(angularVelocity);
			return true;
		}
		return false;
	}
	
	public void setDistance(float distance){
		this.basicDistance = distance;
	}
	
	public float getDistance(){
		return basicDistance;
	}

	public int getNumberOfPoints() {
		return numberOfPoints;
	}

	public void setNumberOfPoints(int numberOfPoints) {
		this.numberOfPoints = numberOfPoints;
	}
	
	public void removeLastPoint(){
		informationPoints.remove(numberOfPoints-1);
		numberOfPoints--;
	}
	
	public void addPoint(int pointNumber, float distance){
		informationPoints.add(new PointInformation(pointNumber, distance));
		numberOfPoints++;
	}
	
	
	//TODO implements clonable
}

package trajectory;

/**
 * This class is the representation of one point
 * It saves:
 * 	-distance
 * 	-velocity
 * 	-acceleration, which is given in 3 options:
 * 		*as soon as possible
 * 		*in the middle
 * 		*as late as possible
 * @author user
 *
 */
public class PointInformation {
	/*
	 * Attributes
	 */
	/**
	 * This is the id of the point
	 */
	private int pointNumber;
	/**
	 * Current distance
	 */
	private float distance;
	private float velocity;
	private String reach;
	private float maxAngularAngle;
	//this variable says if it should be applied the angle restriction
	private String isMaxAngularRestriction;
	private float upperSpeed;
	private float upperMaxAngle;
	private float angularVelocity;
	
	
	public PointInformation(){
		pointNumber =  -1;
		distance = 0;
		velocity =  0;
		maxAngularAngle = 0;
		upperSpeed = 0;
		upperMaxAngle = 0;
		angularVelocity = 0;
		reach = null;
		isMaxAngularRestriction = null;
	}

	public PointInformation(int pointNumber){
		this.pointNumber =  pointNumber;
		distance = 0;
		velocity =  0;
		maxAngularAngle = 0;
		upperSpeed = 0;
		upperMaxAngle = 0;
		angularVelocity = 0;
		reach = null;
		isMaxAngularRestriction = null;
	}

	public PointInformation(int pointNumber, float distance){
		this.pointNumber =  pointNumber;
		this.distance = distance;
		velocity =  0;
		maxAngularAngle = 0;
		upperSpeed = 0;
		upperMaxAngle = 0;
		angularVelocity = 0;
		reach = null;
		isMaxAngularRestriction = null;
	}
	
	/*
	 * Methods
	 */
	
	public float getAngularVelocity(){
		return angularVelocity;
	}
	
	public String getAngularVelocityString(){
		return Float.toString(angularVelocity);
	}
	
	public void setAngularVelocity(float velocity){
		this.angularVelocity = velocity;
	}
	
	public float getMaxAngularAngle(){
		return maxAngularAngle;
	}
	
	public String getMaxAngularAngleString(){
		return Float.toString(maxAngularAngle);
	}
	
	public void setMaxAngularAngle(float maxAngle){
		maxAngularAngle = maxAngle;
	}
	
	public float getUpperSpeed(){
		return upperSpeed;
	}
	
	public String getUpperSpeedString(){
		return Float.toString(upperSpeed);
	}
	
	public void setUpperSpeed(float upperSpeed){
		this.upperSpeed = upperSpeed; 
	}
	
	public float getUpperMaxAngle(){
		return upperMaxAngle;
	}
	
	public String getUpperMaxAngleString(){
		return Float.toString(upperMaxAngle);
	}
	
	public void setUpperMaxAngle(float maxAngle){
		upperMaxAngle = maxAngle;
	}
	
	public String getIsMaxAngularRestriction(){
		return isMaxAngularRestriction;
	}
	
	
	
	public void setIsMaxAngularRestriction(String restriction){
		isMaxAngularRestriction = restriction;
	}
	
	public String getDistanceString() {
		return Float.toString(distance);
	}
	
	public float getDistanceFloat(){
		return distance;
	}

	public void setDistance(float distance) {
		this.distance = distance;
	}

	public String getVelocityString() {
		return Float.toString(velocity);
	}
	
	public float getVelocityFloat(){
		return velocity;
	}

	public void setVelocity(float velocity) {
		this.velocity = velocity;
	}

	public String getReach() {
		return reach;
	}

	public void setReach(String reach) {
		this.reach = reach;
	}

	public String getPointNumber() {
		return Integer.toString(pointNumber);
	}

	public void setPointNumber(int pointNumber) {
		this.pointNumber = pointNumber;
	}
	
	
}

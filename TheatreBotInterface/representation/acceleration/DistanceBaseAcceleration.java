package acceleration;

/**
 * This class represent an acceleration that is calculated using just distances.
 * The calculation of the acceleration changes from implementation to implementation
 * @author user
 *
 */
public abstract class DistanceBaseAcceleration extends BasicAcceleration{
	
	/*
	 * Attributes
	 */
	protected String name;
	protected float initialDistance;
	protected float finalDistance;
	protected float initialVelocity;
	protected float finalVelocity;
	protected float lastDistance;
	//resolution is the size of the steps, and it is given in mm
	protected float resolution = 10;
	
	/*
	 * Constructor
	 */
	public DistanceBaseAcceleration(float initialDistance, float finalDistance, float initialVelocity, float finalVelocity){
		this.initialDistance = initialDistance;
		this.finalDistance = finalDistance;
		this.initialVelocity = initialVelocity;
		this.finalVelocity = finalVelocity;
	}
	
	/*
	 * Methods
	 */
	/**
	 * This method calculates the current velocity given distance constrains. Also it uses the inherent
	 * acceleration description. This is usually use when the acceleration is given in terms of distance
	 */
	public abstract float calculateSpeedFromDistance(float currentDistance);
	
	public abstract float calculateTravelDistance(long initialTime, long currentTime);
	
	public float getFinalDistance(){
		return finalDistance;
	}
	
	public float getFinalVelocity(){
		return finalVelocity;
	}
	
	public float getInitialVelocity(){
		return initialVelocity;
	}
	
	public float getInitialDistance(){
		return initialDistance;
	}

	public String getName(){
		return name;
	}
	
	public float getResolution(){
		return resolution;
	}
}

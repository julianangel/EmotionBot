package acceleration;

/**
 * This class is a representation of a number acceleration, thus it is possible to calculate the velocity
 * in a easy way.
 * @author user
 *
 */
public class TimeBaseAcceleration extends BasicAcceleration{
	/*
	 * Attributes
	 */
	//mm/s^2
	private float acceleration;
	
	/*
	 * Constructor
	 */
	
	public TimeBaseAcceleration(float acceleration){
		this.acceleration = acceleration;
	}
	/*
	 * Methods
	 */
	/**
	 * This method calculates the current velocity given time information. Also it uses the inherent
	 * acceleration description. This is usually use when the acceleration is given in number
	 * @param initialTime, time when begins the change of velocity, which is not 
	 * 			necessarily 0
	 * @param currentTime, time that the velocity is desire
	 * @return the velocity in mm/s
	 */
	public float calculateSpeedFromTime(float initialTime, float currentTime){
		return acceleration*(currentTime-initialTime);
	}

}

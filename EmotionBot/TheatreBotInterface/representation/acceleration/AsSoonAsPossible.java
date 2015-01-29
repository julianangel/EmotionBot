package acceleration;

/**
 * The desire velocity should be reach as soon as possible, in other words in the less time possible
 * @author user
 *
 */
public class AsSoonAsPossible extends DistanceBaseAcceleration{



	public AsSoonAsPossible(float initialDistance,
			float finalDistance, float initialVelocity, float finalVelocity) {
		super(initialDistance, finalDistance, initialVelocity, finalVelocity);
		this.name = "As soon as Possible";
		lastDistance = initialDistance;
	}
	

	@Override
	public float calculateSpeedFromDistance(float currentDistance) {
		return finalVelocity;
	}


	@Override
	public float calculateTravelDistance(long initialTime, long currentTime) {
		float differenceTime = ((float)(currentTime-initialTime));
		return (float)(finalVelocity*(differenceTime)/1000.0);
	}



}

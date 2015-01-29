package acceleration;

public class AtTheEnd extends DistanceBaseAcceleration{

	protected float slope;
	protected float currentVelocity;
	
	public AtTheEnd(float initialDistance, float finalDistance,
			float initialVelocity, float finalVelocity) {
		super(initialDistance, finalDistance, initialVelocity, finalVelocity);
		slope = (finalVelocity-initialVelocity)/(finalDistance-initialDistance);
		this.name = "At the End";
		currentVelocity = initialVelocity;
	}

	/*@Override
	public float calculateSpeedFromDistance(float currentDistance) {
		currentVelocity = slope*(currentDistance-initialDistance)+initialVelocity;
		return currentVelocity;		
	}*/
	@Override
	public float calculateSpeedFromDistance(float currentDistance) {
		currentVelocity = slope*(currentDistance+resolution)+initialVelocity;
		if((slope>0&&currentVelocity>finalVelocity)||(slope<0&&currentVelocity<finalVelocity)){
			currentVelocity = finalVelocity;
		}
		return currentVelocity;
	}

	@Override
	public float calculateTravelDistance(long initialTime, long currentTime) {
		float differenceTime = ((float)(currentTime-initialTime));
		return currentVelocity*(differenceTime)/1000;
	}

}

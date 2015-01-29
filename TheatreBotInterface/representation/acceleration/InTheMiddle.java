package acceleration;

public class InTheMiddle extends DistanceBaseAcceleration{

	protected float slope;
	protected float currentVelocity;
	
	public InTheMiddle(float initialDistance, float finalDistance,
			float initialVelocity, float finalVelocity) {
		super(initialDistance, finalDistance, initialVelocity, finalVelocity);
		slope = (finalVelocity-initialVelocity)/((finalDistance-initialDistance)/2);
		this.name = "In the Middle";
		lastDistance = initialDistance;
		currentVelocity = initialVelocity;
	}

	@Override
	public float calculateSpeedFromDistance(float currentDistance) {
		if((currentDistance)>((finalDistance-initialDistance)/2)){
			currentVelocity = finalVelocity;
		}else{
			currentVelocity = slope*(currentDistance+resolution)+initialVelocity;
		}
		return currentVelocity;
	}

	@Override
	public float calculateTravelDistance(long initialTime, long currentTime) {
		float differenceTime = ((float)(currentTime-initialTime));
		return currentVelocity*(differenceTime)/1000;
	}

	

}

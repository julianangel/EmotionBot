* robot_initial_position.json
	it has the initial position of the robot respect the scene

* scene_description.json
	this file describes the size of each part of the scene
	To make the representation easy, i am going to consider that all the rectangles have the same size.
	The parameters are:
		maximum_lenght_x in millimeters
		maximum_lenght_y in millimeters
		number_rectangles_x
		number_rectangles_y
		
		<0,0>										<0, max y>
		*---------------*---------------*----------------
		|				|				|				|
		|		0		|		1		|		3		|
		|				|				|				|
		*---------------*---------------*---------------*
		|				|				|				|
		|		3		|		4		|		5		|
		|				|				|				|
		*---------------*---------------*---------------*
		|				|				|				|
		|		6		|		7		|		8		|
		|				|				|				|
		*---------------*---------------*---------------*
		<max x, 0>									<max x, max y>
							AUDIENCE
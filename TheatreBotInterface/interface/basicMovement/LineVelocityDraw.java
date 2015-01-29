package basicMovement;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.Rectangle2D;
import java.util.ArrayList;

import javax.swing.JPanel;
import javax.swing.border.LineBorder;

import basicMovementController.ExecutionController;

import miscellaneous.Rectangle;


/**
 * This class draws a line base on the information written in the description
 * @author user
 *
 */
public class LineVelocityDraw extends JPanel{
	
	
	/*
	 * Attributes
	 */
	private Rectangle2D rectangle;
	private Graphics g;
	private ArrayList<Rectangle> rectangles;
	private int numberOfPoints;
	
	public LineVelocityDraw() {
		setBorder(new LineBorder(new Color(0, 0, 0), 2));
		setPreferredSize(new Dimension(500, 75));
		rectangles = new ArrayList<Rectangle>();
	}
	
	private void doDrawing(Graphics g) {
		this.g=g;
		Dimension size = getSize();
        Graphics2D g2d = (Graphics2D) g;
        g2d.setColor(Color.blue);
        rectangle = new Rectangle2D.Float((float)(size.width*0.05), (float)(size.height*0.5), 
        		(float)(size.width-size.width*0.1), (float)(size.height*0.1));
        g2d.fill(rectangle);
        g2d.draw(rectangle);
        drawRectangles();
   } 
	
	/*public void doDrawReferencePoint(float distance){
		Dimension size = getSize();
		Rectangle rectangle = new Rectangle((float)(size.width*0.05+(size.width-size.width*0.1)*distance/1000), 
				(float)(size.height*0.2), 
				(float)(size.width*0.003), (float)(size.height*0.65));
       rectangle.draw((Graphics2D)g, false);
	}*/
	
	
	public void drawRectangles(){
		for(int i = 0 ; i<rectangles.size();i++){
			rectangles.get(i).draw((Graphics2D) g);
		}
	}
	public void setNumberOfPoints(int numberOfPoints){
		this.numberOfPoints = numberOfPoints;
	}
	
	public void setRectangles(ArrayList<Rectangle> rectangles){
		this.rectangles = rectangles;
	}
	
	public void setRectangleXPosition(int position, float x){
		rectangles.get(position).setX(x);
	}
	
	public void resetDraw(){
		this.removeAll();
		this.repaint();
	}
	
	@Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        doDrawing(g);
    }

	public void addController(ExecutionController controller){
		this.addMouseListener(controller);
		this.addMouseMotionListener(controller);
	}
}

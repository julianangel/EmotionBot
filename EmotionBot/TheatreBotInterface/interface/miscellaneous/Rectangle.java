package miscellaneous;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.geom.Rectangle2D;

/**
 * This class is going to be use to draw the lines in the interface
 * @author user
 *
 */
public class Rectangle {

	/*
	 * Attributes 
	 */
	/**
	 * Representation of the rectangle
	 */
	private Rectangle2D rectangle;
	private float x;
	private float y;
	private float width;
	private float height;
	private Color colorFill;
	private Color colorLine;
	private boolean isSelected;
	
	/*
	 * Construct
	 */
	/**
	 * If the color is not given, by default are black
	 * @param x, position of of origin
	 * @param y, position of origin
	 * @param width of the line
	 * @param height of the line
	 */
	public Rectangle(float x, float y, float width, float height){
		this.x = x;
		this.y = y;
		this.width = width;
		this.height = height;
		colorFill = Color.black;
		colorLine = Color.black;
		rectangle = new Rectangle2D.Float(x, y, width, height);
		isSelected = false;
	}
	
	public Rectangle(float x, float y, float width, float height, Color colorFill, Color colorLine){
		this.x = x;
		this.y = y;
		this.width = width;
		this.height = height;
		this.colorFill = colorFill;
		this.colorLine = colorLine;
		this.isSelected = false;
	}
	
	public void draw(Graphics2D g){
		drawRectangle(g);
		if(isSelected){
			g.setPaint(Color.red);
			g.fill(rectangle);
			g.draw(rectangle);
		}
	}
	
	public void setX(float x){
		this.x = x;
		rectangle.setFrame((double)this.x, (double)y, (double)width, (double)height);
	}
	
	public void setY(float y){
		this.y = y;
		rectangle.setFrame((double)this.x, (double)y, (double)width, (double)height);
	}
	
	private void drawRectangle(Graphics2D g){
		g.setPaint(colorFill);
		g.fill(rectangle);
		g.setPaint(colorLine);
		g.draw(rectangle);
	}
	
	public boolean isInside(int x, int y){
		return rectangle.contains(x, y);
	}
	
	public void setIsSelected(boolean state){
		isSelected = state;
	}
}

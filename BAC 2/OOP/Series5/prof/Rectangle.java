import java.lang.Math;
public class Rectangle {
    private Coordinates min;
    private Coordinates max;
    private MyColor color;

    public Rectangle(int xMin, int yMin, int xMax, int yMax, MyColor color){
        if(xMin >= xMax || yMin >= yMax){
            throw new Error("The area of the rectangle must be strictly postive");
        }
        this.min = new Coordinates(xMin, yMin);
        this.max = new Coordinates(xMax, yMax); 
        this.color = color;

    }

    public int getXmin(){return min.getX();}
    public int getYmin(){return min.getY();}
    public int getXmax(){return max.getX();}
    public int getYmax(){return max.getY();}
    public MyColor getColor(){return color;}

    public void rotate(int cx, int cy){
        Coordinates center = new Coordinates(cx, cy);
        min.rotate(center);
        max.rotate(center);

        Coordinates newMin = new Coordinates(Math.min(min.getX(), max.getX()), Math.min(min.getY(), max.getY()));
        Coordinates newMax = new Coordinates(Math.max(min.getX(), max.getX()), Math.max(min.getY(), max.getY()));
        min = newMin;
        max = newMax;

    }

    public boolean overlaps(Rectangle r){
        if(max.getX() <= r.min.getX())
            return false;
        
        if(min.getX() >= r.max.getX())
            return false;
        
        if(max.getY() <= r.min.getY())
            return false;
        
        if(min.getY() >= r.max.getY())
            return false;

        return true;
    }
}

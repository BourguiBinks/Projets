import java.lang.Math;
public class LineSegment {
    private Coordinates p1, p2;

    public LineSegment(int x1, int y1, int x2, int y2){
        this.p1 = new Coordinates(x1, y1);
        this.p2 = new Coordinates(x2, y2);
    }

    public void translate(int dx, int dy){
        p1.translate(dx, dy);
        p2.translate(dx, dy);
    }

    public double length(){
        return Math.hypot(p1.getX() - p2.getX(), p1.getY() - p2.getY());
    }

    public String toString(){
        return "[ " + p1.toString() + "," + p2.toString() + " ]";
    }
}

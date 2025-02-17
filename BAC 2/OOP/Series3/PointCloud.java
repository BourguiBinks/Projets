import java.util.Vector;
public class PointCloud{
   private Vector<Coordinates> cloud;

   public void addPoint(int x, int y){
    Coordinates tmp = new Coordinates(x,y);
    cloud.add(tmp);
       }

    public void translate(int dx, int dy){
        for(Coordinates p1 : cloud){
            p1.translate(dx, dy);
        }

    public void connect(PointCloud cloud){
        LineSegment
        for(Coordinates p1: cloud){
            p1.get
        }
    }
    }
}
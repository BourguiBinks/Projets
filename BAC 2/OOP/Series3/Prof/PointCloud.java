import java.util.Vector;

public class PointCloud {
    private Vector<Coordinates> cloud;

    public PointCloud(){
        this.cloud = new Vector<>();
    }

    public void addPoint(int x, int y){
        Coordinates tmp = new Coordinates(x, y);
        cloud.add(tmp);
    }

    public void translate(int dx, int dy){
        for(Coordinates c1 : cloud){
            c1.translate(dx, dy);
        }
    }

    public LineSegment[] connectedLine(){
        int size = cloud.size();
        LineSegment[] res = new LineSegment[size -1];

        for(int i = 0; i < size - 1; i++ ){
            Coordinates beginning = cloud.get(i);
            Coordinates end = cloud.get(i+1);
            res[i] = new LineSegment(beginning.getX(), beginning.getY(), end.getX(), end.getY());
        }
        return res;
    }
}

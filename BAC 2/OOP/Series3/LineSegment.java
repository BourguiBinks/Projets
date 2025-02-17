public class LineSegment{
    private Coordinates point1;
    private Coordinates point2;

    public LineSegment(){
        point1 = (0,0);
        point2 = (0,0);
    }
    public LineSegment(Coordinates point1, Coordinates point2){
        this.point1 = point1;
        this.point2 = point2;
    }
    public translate(int dx, int dy){
        this.point1 += dx
        this.point2 += dy
    }

    public toString(){
        System.out.println("[(" + point1.getX, point2.getY + ") , (" + point2.getX , point2.getY + ")]")
    }
}
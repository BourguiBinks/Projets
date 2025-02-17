public class LineSegmentTest {
    public static void main(String[] args)
    {
        LineSegment line1  = new LineSegment(-2, 0, 3, 2);
        System.out.println(line1.toString());
        
        line1.translate(3, 4);
        System.out.println(line1.length());
        System.out.println(line1.toString());
        System.out.println(line1.length());
    }
}

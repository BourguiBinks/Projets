public class TestGrid {
    public static void main(String[] args) throws Exception{
        Grid g = new Grid();
        g.addRectangle(-2, 2, -3, 4, MyColor.RED);

        GUI i = new GUI(g);
        i.start();
    }
}

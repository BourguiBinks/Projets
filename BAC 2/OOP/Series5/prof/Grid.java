import java.util.Vector;
public class Grid {
   private Vector<Rectangle> vectorRectangles;

   public Grid(){
    vectorRectangles = new Vector<>();
   }

   public void addRectangle(int xMin, int xMax, int yMin, int yMax, MyColor color){
        Rectangle newRectangle = new Rectangle(xMin, yMin, xMax, yMax, color);
        vectorRectangles.add(newRectangle);
   }

   public Rectangle[] getRectangles(){
        Rectangle[] returned = new Rectangle[vectorRectangles.size()];
        for(int i = 0; i < vectorRectangles.size(); i++){
            returned[i] = vectorRectangles.get(i);
        }
        return returned;
   }
   public void rotate(MyColor color){
        rotate(0,0, color);
   }
   public void rotate(int cx, int cy, MyColor color){
        for(Rectangle r: vectorRectangles){
            if(r.getColor() == color){
                r.rotate(cx, cy);
            }
        }
   }
   public boolean overlaps(){
        for(int i = 0; i < vectorRectangles.size(); i++){
            for(int j = i + 1; j < vectorRectangles.size(); j++){
                if(vectorRectangles.get(i).overlaps(vectorRectangles.get(j))){
                    return true;
                }
            }
        }
        return false;
   }

}

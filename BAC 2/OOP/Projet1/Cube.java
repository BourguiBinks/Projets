public class Cube{
    private int x,y,z; 
    private char geometry;

    public Cube(char geometry){
        this.x = 0;
        this.y = 0;
        this.z = 0;
        this.geometry = geometry;
    }

    public Cube(int x, int y, int z, char geometry){
        this.x = x;
        this.y = y;
        this.z = z;
        this.geometry = geometry;
    }

    public int getX(){ return x;}
    public int getY(){ return y;}
    public int getZ(){ return z;}
    public char getGeometry(){ return geometry;}

    public void setX(int x){
        this.x = x;
    }
    public void setY(int y){
        this.y = y;
    }
    public void setZ(int z){
        this.z = z;
    }
}
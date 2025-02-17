public class Stacktest{
    public static void main(String[] args){
        Stack s = new Stack();

        s.put(newContent: "Hello");
        s.put(newContent: "Bonjour");

        System.out.println(s.get());
        System.out.println(s.get());
    }
}
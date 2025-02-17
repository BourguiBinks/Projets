public class StackTest {
    public static void main(String[] args){
        Stack s = new Stack();

        s.put("Hello");
        s.put("Bonjour");

        System.out.println(s.get());
        System.out.println(s.get());
    }
}

public class Stack {
    private int size;
    private Node last;

    public Stack(){
        size = 0;
        last = null;
    }
    public void put(Object newContent){
        if(size <= 0){
            last = new Node(newContent);
        }else{
            last = new Node(newContent,last);
        }
        size++;
    }

    public Object get(){
        if(size <= 0){
            return null;
        }else{
            Object returnContent = last.getContent();
            last = last.getNextNode();
            size--;
            return returnContent;
        }
    }

    public Object first(){
        if(size <= 0){
            return null;
        }else{
            return last.getContent();
        }
    }
    public int size(){
        return size;
    }
}

public class Queue{
    private int size;
    private Node head;
    private Node tail;

    public Queue(){
        head = null;
        tail = null;
        size = 0;
    }
    public void put(Object newContent){
        New newNode = new Node(newContent);

        if(size <= 0){
            head = newNode;
            tail = newNode;
        }
        else{
            tail.setNext(newNode);
            tail = newNode; 
        }
        size++;
    }

    public Object get(){
        if(size <= 0){
            return null;
        }else{
            Object retrunContent = head.getContent();
            head = head.getNextNode();
            size--;
            return retrunContent;

        }
    }

    public int size(){
        return size;
    }
}
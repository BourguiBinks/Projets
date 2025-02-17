public class Queue {
    private int size;
    private Node head;
    private Node tail;

    public Queue(){
        head = null;
        tail = null;
        size = 0;
    }

    public void put(Object newContent){
        Node newNode = new Node(newContent);

        if(size <= 0){
            head = newNode;
            tail = newNode;
        }else{
            tail.setNextNode(newNode);
            tail = newNode;
        }
        size++;
    }

    public Object get(){
        if(size <= 0){
            return null;
        }else{
            Object returnContent = head.getContent();
            head = head.getNextNode();
            size--;
            return returnContent;
        }
    }

    public Object first(){
        if(size <= 0){
            return null;
        }else{
            Object returnContent = head.getContent();
            return returnContent;
        }
    }

    public int size(){
        return size;
    }
}

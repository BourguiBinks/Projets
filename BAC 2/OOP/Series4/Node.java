import java.util.Objects;

public class Node {

    private Object content;
    private Node next;
//Constructeur
    public Node(Object content, Node next){
        this.content = content;
        this.next = next;
    }
    public Node(){
        this.content = null;
        this.next = null;
    }

    public Node(Object content){
        this.content = content;
        this.next = null;
    }

    public Object get_content(){
        return value;
    }

    public Node getNextNode(){
        return next;
    }

    public Object getContent(){
        return content;
    }

    public void setNext(Node next){
        this.next = next;
    }
   
}
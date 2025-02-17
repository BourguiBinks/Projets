public class Node {
    private Object content;
    private Node nextNode;

    public Node(Object content, Node next){
        this.content = content;
        this.nextNode = next;
    }

    public Node(){
        this.content = null;
        this.nextNode = null;
    }

    public Node(Object content){
        this.content = content;
        this.nextNode = null;
    }

    public Node getNextNode(){
        return nextNode;
    }

    public Object getContent(){
        return content;
    }

    public void setNextNode(Node next){
        this.nextNode = next;
    }
}

public class Student {
    //déclaration de variables
    private int studentID;
    private String firstName;
    private String lastName;
    //déclaration du créateur
    public Student(int id, String firstN, String lastN){
        this.studentID = id;
        this.firstName = firstN;
        this.lastName = lastN;
    }
    // liste de getters
    public int getStudentID(){
        return studentID;
    }
    public String toString(){
        return firstName + "" + lastName;
    }

}
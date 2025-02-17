public class TestStudent {
    public static void main(String[] args){
        Student newStudent;
        newStudent = new Student(211381, "Julien", "Peffer");

        System.out.println(newStudent.getStudentID());
        System.out.println(newStudent.toString());
    }

}
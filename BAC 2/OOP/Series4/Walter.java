import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Objects;

public class Walter {

    public static void main(String args[]) throws IOException {
        Boolean running = true;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        while (running) {
            System.out.println("Say my name !");
            String answer = br.readLine();
            if (answer.equals ("Heisenberg")) running = false;
         }

        System.out.println("Je suis homosexuel :3!");
    }

}

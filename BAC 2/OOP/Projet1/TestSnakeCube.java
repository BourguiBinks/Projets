public class TestSnakeCube{
    public static void main(String[] args) {
        final String initialConfiguration;

	//if there is no argument given to the program, exit
        if (args.length < 1) {
            System.out.println("No initialConfiguration");
            return;
        }
	//store the given configuration
        initialConfiguration = args[0];

        System.out.println("initialConfiguration : " + initialConfiguration);

        if (initialConfiguration.charAt(0) != 'E' || initialConfiguration.charAt(initialConfiguration.length() - 1) != 'E') {
            System.out.println("Invalid configuration : the configuration must start and end with an 'E'");
            return;
        }
         // Vérifiez que la longueur de la configuration est un cube
        double cubeRoot = Math.cbrt(initialConfiguration.length());
        if(Math.floor(cubeRoot) != cubeRoot){
            System.out.println("Invalid configuration : the number of cubes must have a cubic root");
            return;
        }
        for (int i = 1; i < initialConfiguration.length() - 1; i++) {
            char c = initialConfiguration.charAt(i);
            if (c != 'A' && c != 'S') {
                System.out.println("Invalid configuration : the configuration can only contain 'A' and 'S' and can only have 'E' at the beginning and at the end");
                return;
            }
        }  
        Puzzle puzzle = new Puzzle(initialConfiguration);
        if(puzzle.getAllGroups(initialConfiguration) == 1)
            System.out.println("Pas de solution !");
        else{
            puzzle.fillCube(initialConfiguration);
        }

        return;
    }
}
// import java.lang.Object;
// import java.lang.String;
import java.util.Vector;

public class Puzzle{
    public final String initialConfiguration;
    private int n;
    private Vector<Integer> groups ;
    private int cubeInGroup = 2;
    private Cube[] cubes;
    //int[x][y][z] contiendra 1 si un cube s'y trouve et 0 sinon.
    private int[][][] puzzle;

    public Puzzle(String initialConfiguration){
        this.initialConfiguration = initialConfiguration;
        this.n = (int) Math.cbrt(initialConfiguration.length());
        System.out.println("n = " + n);
        this.cubes = new Cube[initialConfiguration.length()];
        this.puzzle = new int[n][n][n]; 
        this.groups = new Vector<>();
    }
    public int getAllGroups(String initialConfiguration){
        //place dans le tableau group le nombre de cubes dans chaque groupe. Retourne 0 si il y'a une solution ou 1 quand il y'en a pas et 2 quand la solution est à déterminer
        if(n == 1)
            return 0;
        for(int i = 1; i < n - 1; i++){
            // System.out.println("cubeInGroup = " + cubeInGroup );
            
            if(initialConfiguration.charAt(i) == 'A'){
                if(cubeInGroup > n)
                //cas où un groupe contient un nombre de cube plus grand que n (on sort du n x n x n)
                    return 1;
                groups.add(cubeInGroup);
                cubeInGroup = 2;
            }
            else
                cubeInGroup++;
                
            if(i == n - 2)
                if(cubeInGroup > n)
                //cas où un groupe contient un nombre de cube plus grand que n (on sort du n x n x n)
                    return 1;
                groups.add(cubeInGroup);
            // System.out.println("cubeInGroup :\n" + cubeInGroup);
        }

        // Affichage de tous les éléments du tableau groups
        for(int k = 0; k < groups.size(); k++)
            System.out.println("Group " + (k + 1) + ": " + groups.get(k));
        
        return 2;
    }

    public boolean isPossible(int x, int y, int z, int[][][] puzzle){
        //Détermine si un cube peut être placé aux coordonnées en paramètres

        //cas ou les coordonnees sont hors du domaine
        if(x < 0 || x > n - 1 || y < 0 || y > n - 1 ||z < 0 || z > n - 1 )
            return false;

        //cas où il y a deja un cube a cet emplacement dans le puzzle
        if(puzzle[x][y][z] != 0)
            return false;

        else
            return true;

    }
    public void fillCube(String initialConfiguration){
        // On initiantiate chaque groupe un par un
        // on incrémise le i 
        // on remplisse le vecteurre 
        // on rézoude le problemme
        // on electrise le megatron
        // on compte le nombre de ziganet
        // on trinite les compteurs métriques
        // on brise la chaine de zigotrons
        // on ougandise le continuum espace temps en ouvrant une faille obselète.
        
        
        //On crée tous les cubes qu'on met dans le tableau de cubes
        for(int i = 0; i < n; i++){
            this.cubes[i] = new Cube(initialConfiguration.charAt(i));
            System.out.println("Cube " + (i+1) + ": (" +  this.cubes[i].getX() + "," + this.cubes[i].getY() + "," + this.cubes[i].getZ() + "," + this.cubes[i].getGeometry() +")" );

        }
        //On place les groupes de cubes dans le puzzle tant que c'est possible et on retire le dernier groupe s'il n'y a plus de solution
    //     for(int i = 0; i < n; i++){
    //         for(int j = 0; j < )
    //     }
    }

} 
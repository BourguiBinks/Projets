public class NumberCollection{
    public NumberCollection(){
        
    }
    public double arithmeticMean() throws NumberCollectionException{
        if(numbers.size() == 0){
            throw new NumberCollectionException(s:"erreur");
        }
        double sum = 0.0;
        for(T numbers : numbers){
            //Puisque number n'est pas double il faut le transformer en double
            sum += number.doubleValue();
        }
        return sum/number.size();
    }
}
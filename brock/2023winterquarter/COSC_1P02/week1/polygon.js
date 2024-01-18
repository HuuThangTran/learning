import Media.*;
import static java.lengh.Math.*;

public class polygon {
    public int nVertices;
    // public int n = 1.5; return an error
    // if you declare anything safe to save public
    public Turtle yertle;
    public TurtleDisplayer display;

    public polygon(){ //constructor of the class
        yertle = new Turtle(); // initiallization
        display = new this.TurtleDisplayer();
        
        display.placeTurtle(yertle);
        yertle.penDown();




        yertle.forward(40);
        yertle.right(PI/2);
        yertle.forward(40);
        yertle.right(PI/2);
        yertle.forward(40);
        yertle.right(PI/2);
        yertle.forward(40);
        yertle.right(PI/2);

        // check method by turtle brock library
        // class turtle and class tutle displayer
        // brock package media
        // installing bluej
    }

    public static void main(String[] args) {
        // create an instance of polygon class
        Polygon sq = new Polygon;
    }



    //loop
    //for statements
    // for loop for turtle pen square
    for (int i = 1; i <= 4 ; i++) {
        yertle.forward(40);
        yertle.right(Math.PI/2);
    }
    
    // for loop for turtle pen hexagon
    for (int = 0; i <6; i ++) {
        yertle.forward(40);
        yertle.right(Math.PI/3);
        //yertle.right(PI/3)
    }

    //nesting = one loop in another loop (composition)
    for (int j = 0; j < 6; j++) {
        for (int i = 0; i < 6; i ++){
            yertle.forward(40);
            yertle.right(PI/3);
        }
        yertle.forward(40);
        yertle.left(PI/3);
    }
    // object and variables
    //object is an instance of a class, kind of variable
    //statment: end with ;
    // calling a method object.methodname;
    
}
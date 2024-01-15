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

    }
}
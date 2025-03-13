package model;

public class Turtle implements Animal{
    protected int age;
    protected String name = "None";
    protected String color = "None";
    protected int weight = 0;
    protected int size = 0;
    protected String type = "None"; //terrestrial or aquatic

    public Turtle(int age){
        this.age = age;
    }

    public Turtle(int age, String color, int weight, int size, String type){
        this.age = age;
        this.color = color;
        this.weight = weight;
        this.size = size;
        this.type = type;
    }

    public int getAge(){
        return this.age;
    }
    public void setAge(int a){
        this.age = a;
    }
    public String getColor(){
        return this.color;
    }
    public void setColor(String c){
        this.color = c;
    }
    public int getWeight(){
        return this.weight;
    }
    public void setWeight(int w){
        this.weight = w;
    }
    public int getSize(){
        return this.size;
    }
    public void setSize(int s){
        this.size = s;
    }
    public String getType(){
        return this.type;
    }
    public void setType(String t){
        this.type = t;
    }
    public String toString(){
        return "Turtle| Age: " + this.age + " days | Color: " + this.color + "| Weight: " + this.weight + "| Size: " + this.size + "| Type: " + this.type;
    }
}

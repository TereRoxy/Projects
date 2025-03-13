package model;

public class Fish implements Animal{
    protected int age;
    protected String name;
    protected String color = "None";
    protected int weight = 0;
    protected int size = 0;

    public Fish(int age){
        this.age = age;
    }

    public Fish(int age, String name, String color, int weight, int size){
        this.age = age;
        this.name = name;
        this.color = color;
        this.weight = weight;
        this.size = size;
    }

    public int getAge(){
        return this.age;
    };
    public void setAge(int a){
        this.age = a;
    };
    public String getName(){
        return this.name;
    };
    public void setName(String n){
        this.name = n;
    };
    public String getColor(){
        return this.color;
    };
    public void setColor(String c){
        this.color = c;
    };
    public int getWeight(){
        return this.weight;
    };
    public void setWeight(int w){
        this.weight = w;
    };
    public int getSize(){
        return this.size;
    };
    public void setSize(int s){
        this.size = s;
    };
    public String toString(){
        return "Fish| Name: " + this.name + "| Age: " + this.age + " days | Color: " + this.color + "| Weight:  " + this.weight + "| Size: " + this.size;
    };

}
